#include "InputHandler.h"
#include <fstream>
#include <iostream>
#include <sstream>

void InputHandler::parseInput(const std::string& filename, BlockModel& blockModel) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return;
    }

    parseDimensions(inputFile, blockModel);

    std::map<int, std::string> tagTable;
    parseTagTable(inputFile, tagTable);

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int x, y, z, label;
        if (iss >> x >> y >> z >> label) {
            blockModel.addBlock(x, y, z, label);
        }
    }
    inputFile.close();
}

void InputHandler::parseDimensions(std::ifstream& inputFile, BlockModel& blockModel) {
    std::string line;
    if (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int xDim, yDim, zDim, parentX, parentY, parentZ;
        if (iss >> xDim >> yDim >> zDim >> parentX >> parentY >> parentZ) {
            blockModel.setDimensions(xDim, yDim, zDim, parentX, parentY, parentZ);
        }
    }
}

void InputHandler::parseTagTable(std::ifstream& inputFile, std::map<int, std::string>& tagTable) {
    std::string line;
    while (std::getline(inputFile, line) && !line.empty()) {
        size_t commaPos = line.find(", ");
        if (commaPos != std::string::npos) {
            int label = std::stoi(line.substr(commaPos + 2));
            std::string tag = line.substr(0, commaPos);
            tagTable[label] = tag;
        }
    }
}
