#include "pch.h"
#include "InputHandler.h"
#include <map>
#include <tuple>
#include <vector>
#include <algorithm>
#include <sstream>

struct BlockInfo {
    int x, y, z;
    int runLengthX, runLengthY, runLengthZ;
    std::string label;
    bool isMerged;
    int vectorIndex;
};

std::tuple<int, int, int> createKey(int x, int y, int z) {
    return std::make_tuple(x, y, z);
}

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

    std::vector<std::string> blockStrings;
    std::map<std::tuple<int, int, int>, BlockInfo> allBlocks;


    for (int z = 0; z < slices; ++z) {
        for (int y = 0; y < rows; ++y) {
            std::getline(std::cin, line);

            for (int x = 0; x < cols; ++x) {
                currentLabel = line[x];
                int xRunLength = 1;

          
                while (x + xRunLength < cols && line[x + xRunLength] == currentLabel && (x + xRunLength) % parentSizeX != 0) {
                    xRunLength++;
                }

                BlockInfo block = {x, y, z, xRunLength, 1, 1, tagTable[static_cast<unsigned char>(currentLabel)], false, static_cast<int>(blockStrings.size())};
                allBlocks[createKey(x, y, z)] = block;

                blockStrings.push_back(
                    std::to_string(x) + ',' + std::to_string(y) + ',' + std::to_string(z) + ',' +
                    std::to_string(xRunLength) + ",1,1," + tagTable[static_cast<unsigned char>(currentLabel)]
                );

                x += (xRunLength - 1);
            }
        }
        std::getline(std::cin, line);  
    }


    for (auto& [key, block] : allBlocks) {
        if (block.isMerged) continue;

        int x = block.x;
        int y = block.y;
        int z = block.z;

        int yRunLength = 1;
        std::vector<int> indices;
        indices.push_back(block.vectorIndex);

        while (y + yRunLength < rows && (y + yRunLength) % parentSizeY != 0 &&
               allBlocks.find(createKey(x, y + yRunLength, z)) != allBlocks.end()) {
            BlockInfo& nextBlock = allBlocks[createKey(x, y + yRunLength, z)];
            if (nextBlock.label == block.label && nextBlock.runLengthX == block.runLengthX && !nextBlock.isMerged) {
                yRunLength++;
                nextBlock.isMerged = true;
                indices.push_back(nextBlock.vectorIndex);
            } else {
                break;
            }
        }

        std::sort(indices.begin(), indices.end());
        int minIndex = indices[0];
        blockStrings[minIndex] = std::to_string(block.x) + ',' + std::to_string(block.y) + ',' + std::to_string(block.z) + ',' +
                                 std::to_string(block.runLengthX) + ',' + std::to_string(yRunLength) + ",1," + block.label;

        for (size_t i = 1; i < indices.size(); ++i) {
            blockStrings[indices[i]] = "";
        }
    }


    std::map<std::tuple<int, int, int>, BlockInfo> zBlocks;

    for (size_t i = 0; i < blockStrings.size(); ++i) {
        if (!blockStrings[i].empty()) {
            std::istringstream iss(blockStrings[i]);
            std::string xStr, yStr, zStr, runLengthXStr, runLengthYStr, runLengthZStr, label;
            std::getline(iss, xStr, ',');
            std::getline(iss, yStr, ',');
            std::getline(iss, zStr, ',');
            std::getline(iss, runLengthXStr, ',');
            std::getline(iss, runLengthYStr, ',');
            std::getline(iss, runLengthZStr, ',');
            std::getline(iss, label);

            int x = std::stoi(xStr);
            int y = std::stoi(yStr);
            int z = std::stoi(zStr);
            int runLengthX = std::stoi(runLengthXStr);
            int runLengthY = std::stoi(runLengthYStr);
            int runLengthZ = std::stoi(runLengthZStr);

            BlockInfo block = {x, y, z, runLengthX, runLengthY, runLengthZ, label, false, static_cast<int>(i)};
            zBlocks[createKey(x, y, z)] = block;
        }
    }

    for (auto& [key, block] : zBlocks) {
        if (block.isMerged) continue;

        int x = block.x;
        int y = block.y;
        int z = block.z;

        int zRunLength = 1;
        std::vector<int> indices;
        indices.push_back(block.vectorIndex);

        while (z + zRunLength < slices && (z + zRunLength) % parentSizeZ != 0 &&
               zBlocks.find(createKey(x, y, z + zRunLength)) != zBlocks.end()) {
            BlockInfo& nextBlock = zBlocks[createKey(x, y, z + zRunLength)];
            if (nextBlock.label == block.label && nextBlock.runLengthX == block.runLengthX && nextBlock.runLengthY == block.runLengthY && !nextBlock.isMerged) {
                zRunLength++;
                nextBlock.isMerged = true;
                indices.push_back(nextBlock.vectorIndex);
            } else {
                break;
            }
        }

        std::sort(indices.begin(), indices.end());
        int minIndex = indices[0];
        blockStrings[minIndex] = std::to_string(block.x) + ',' + std::to_string(block.y) + ',' + std::to_string(block.z) + ',' +
                                 std::to_string(block.runLengthX) + ',' + std::to_string(block.runLengthY) + ',' +
                                 std::to_string(zRunLength) + ',' + block.label;

        for (size_t i = 1; i < indices.size(); ++i) {
            blockStrings[indices[i]] = "";
        }
    }

    for (const std::string& blockString : blockStrings) {
        if (!blockString.empty()) {
            resultStream << blockString << '\n';
        }
    }

    std::cout << resultStream.str();
}
