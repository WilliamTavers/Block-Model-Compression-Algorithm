#include "pch.h"
#include "InputHandler.h"


InputHandler::InputHandler() : dimensions(6), tagTable(128){}

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
    char currentLabel;
    std::ostringstream resultStream;

    while (true) {
        for (int z = 0; z < slices; ++z) {
            for (int y = 0; y < rows; ++y) {
                for (int x = 0; x < cols; ++x) {
                    currentLabel = std::cin.get();

                    std::cout << x << ',' << y << ',' << z << ",1,1,1," 
                                 << tagTable[static_cast<unsigned char>(currentLabel)] << '\n';

                    // std::cout << resultStream.str();
                    // std::cout.flush();
                    // resultStream.str(""); 
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}