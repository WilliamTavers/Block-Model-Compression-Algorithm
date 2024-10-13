#include "pch.h"
#include "InputHandlerArith.h"

InputHandler::InputHandler() : dimensions(6), tagTable(128), high(0xFFFFFFFF), low(0), bits_in_buf(0), buffer(0), opposite_bits(0) {
    Compress();
}

void InputHandler::parseInput() {
    std::ios_base::sync_with_stdio(false); // Disable sync with C stdio
    std::cin.tie(nullptr); // Untie cin from cout for faster input

    std::string line;
    std::getline(std::cin, line);
    parseDimensions(line);
    parseTagTable();  
    parseBlockData();
}

void InputHandler::parseDimensions(const std::string& line) {
    size_t start = 0;
    size_t end = 0;

    for (int i = 0; i < 6; ++i) {
        end = line.find(',', start);
        dimensions[i] = std::stoi(line.substr(start, end - start));
        start = end + 1;
    }
}

void InputHandler::parseTagTable() {
    std::string line;
    tagTable.reserve(14);
    while (std::getline(std::cin, line) && !line.empty()) {
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) {
            break;
        }
        char tag = line[0];
        std::string label = line.substr(commaPos + 1);
        label.erase(0, label.find_first_not_of(" \t"));
        label.erase(label.find_last_not_of(" \t") + 1);
        
        tagTable[static_cast<unsigned char>(tag)] = label;
    }
}

void InputHandler::parseBlockData() {
    int cols = dimensions[0], rows = dimensions[1], slices = dimensions[2];
    
    std::ostringstream resultStream;
    std::string line;

    for (int z = 0; z < slices; ++z) {
        for (int y = 0; y < rows; ++y) {
            std::getline(std::cin, line);
            for (int x = 0; x < cols; ++x) {
                resultStream << x << ',' << y << ',' << z << ",1,1,1," << tagTable[static_cast<unsigned char>(line[x])] << '\n';
            }
        }
        std::getline(std::cin, line); 
    }

    encode(resultStream.str());
}

void InputHandler::encode(const std::string& resultStream) {
    std::istringstream in(resultStream);
    if (!in) {
        std::cerr << "Error: Can't open input stream" << std::endl;
        return;
    }

    while (true) {
        char ch = in.get();
        if (in.eof()) {
            std::cout << "Encoding is done" << std::endl;
            break;
        }
        int symbol = char_to_index[static_cast<unsigned char>(ch)];
        encode_symbol(symbol);
        update_tables(symbol);
    }
    encode_symbol(EOF_SYMBOL);
    end_encoding();
}

void InputHandler::encode_symbol(int symbol) {
    int range = high - low + 1; // Add 1 for inclusive range

    high = low + (range * cum_freq[symbol]) / cum_freq[0] - 1;
    low = low + (range * cum_freq[symbol - 1]) / cum_freq[0];

    while (true) {
        if (high < HALF) {
            output_bits(0);
        } else if (low >= HALF) {
            output_bits(1);
            low -= HALF;
            high -= HALF;
        } else if (low >= FIRST_QTR && high < THIRD_QTR) {
            opposite_bits++;
            low -= FIRST_QTR;
            high -= FIRST_QTR;
        } else {
            break;
        }
        low *= 2;
        high = high * 2 + 1;
    }
}

void InputHandler::end_encoding() {
    opposite_bits++;
    if (low < FIRST_QTR) {
        output_bits(0);
    } else {
        output_bits(1);
    }

    if (bits_in_buf > 0) {
        std::cout.put(buffer >> bits_in_buf); // Ensure output is correct
    }
}

void InputHandler::output_bits(int bit) {
    write_bit(bit);
    while (opposite_bits > 0) {
        write_bit(!bit);
        opposite_bits--;
    }
}

void InputHandler::write_bit(int bit) {
    buffer >>= 1;
    if (bit) buffer |= 0x80;
    bits_in_buf++;
    if (bits_in_buf == 8) {
        std::cout.put(buffer);
        bits_in_buf = 0;
        buffer = 0; // Reset buffer after output
    }
}

void InputHandler::Compress() {
    for (int i = 0; i < NO_OF_CHARS; i++) {
        char_to_index[i] = i + 1;
        index_to_char[i + 1] = i;
    }
    for (int i = 0; i <= NO_OF_SYMBOLS; i++) {
        freq[i] = 1;
        cum_freq[i] = NO_OF_SYMBOLS - i;
    }
    freq[0] = 0;
}

void InputHandler::update_tables(int sym_index) {
    int i;
    if (cum_freq[0] == MAX_FREQ) {
        int cum = 0;
        for (i = NO_OF_SYMBOLS; i >= 0; i--) {
            freq[i] = (freq[i] + 1) / 2;
            cum_freq[i] = cum;
            cum += freq[i];
        }
    }
    for (i = sym_index; freq[i] == freq[i - 1]; i--);
    if (i < sym_index) {
        int ch_i = index_to_char[i];
        int ch_symbol = index_to_char[sym_index];
        index_to_char[i] = ch_symbol;
        index_to_char[sym_index] = ch_i;
        char_to_index[ch_i] = sym_index;
        char_to_index[ch_symbol] = i;
    }
    freq[i]++;
    while (i > 0) {
        i--;
        cum_freq[i]++;
    }
}

