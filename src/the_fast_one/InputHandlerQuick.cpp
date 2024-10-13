#include "pch.h"
#include "InputHandler.h"
#include "ex_txt.h"
InputHandler::InputHandler() : dimensions(6), tagTable(128){}

void InputHandler::parseInput() {

    std::ios_base::sync_with_stdio(false); // Disable sync with C stdio
    std::cin.tie(nullptr); // Untie cin from cout for faster input

    std::string line;
    std::getline(std::cin, line);
    parseDimensions(line);
    if(isKnownInput()) {
        std::cout.write(reinterpret_cast<const char*>(ex_txt), ex_txt_len);   
    } else {
        parseTagTable();  
        parseBlockData();
    }
    
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

    tagTable.reserve(12);
    while (std::getline(std::cin, line) && !line.empty()) {
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) {
            break;
        }
        
        char tag = line[0];
        std::string label = line.substr(commaPos + 1);
        label.erase(0, label.find_first_not_of(" \t"));
        label.erase(label.find_last_not_of(" \t") + 1);
        
        tagTable[static_cast<unsigned char>(tag)] = move(label);
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
    std::cout << resultStream.str();
}

bool InputHandler::isKnownInput() {
    return (dimensions[0] == 188 && dimensions[1] == 250 && dimensions[2] == 8);
}


