#include "pch.h"
#include "InputHandler.h"

InputHandler::InputHandler() : dimensions(6), tagTable(128) {}

void InputHandler::parseInput() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

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

    tagTable.reserve(52);
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
    const int parentSizeX = dimensions[3], parentSizeY = dimensions[4], parentSizeZ = dimensions[5];

    std::ostringstream resultStream;
    std::string line;
    char currentLabel;

    for (int z = 0; z < slices; ++z) {
        for (int y = 0; y < rows; ++y) {
            std::getline(std::cin, line);

            for (int x = 0; x < cols; ++x) {
                currentLabel = line[x];

                int xRunLength = 1;

                while (x + xRunLength < cols && line[x + xRunLength] == currentLabel && (x + xRunLength) % parentSizeX != 0) {
                    xRunLength++;
                }

                resultStream << x << ',' << y << ',' << z << ',' << xRunLength << ',' << 1 << ',' << 1 << ',' << tagTable[static_cast<unsigned char>(currentLabel)] << '\n';

                x += (xRunLength - 1);
            }
        }
        std::getline(std::cin, line);
    }

    std::cout << resultStream.str();
}
