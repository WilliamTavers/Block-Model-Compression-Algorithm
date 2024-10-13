#include "InputHandler.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <cstring>

// Include OpenMP headers only if OpenMP is enabled
#ifdef _OPENMP
#include <omp.h>
#endif

// Constructor
InputHandler::InputHandler() : dimensions(6), tagTable(128){}

// Method to access the dimensions vector
const std::vector<int>& InputHandler::getDimensions() const { return dimensions; }

// Main method to parse the input data
void InputHandler::parseInput(DataModel& dataModel) {

    std::ios_base::sync_with_stdio(false); // Disable synchronization with C stdio
    std::cin.tie(nullptr); // Untie cin from cout for faster input

    std::string line;
    std::getline(std::cin, line);
    parseDimensions(line);
    parseTagTable();  
    parseBlockData(dataModel);
}

// Helper method to parse the dimensions from the first line of input
void InputHandler::parseDimensions(const std::string& line) {
    size_t start = 0;
    size_t end = 0;

    for (int i = 0; i < 6; ++i) {
        end = line.find(',', start);
        dimensions[i] = std::stoi(line.substr(start, end - start));
        start = end + 1;
    }
}

// Helper method to parse the tag table from the input
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
        
        // Replace vector with unordered_map
        // tagTable[tag] = label;
        tagTable[static_cast<unsigned char>(tag)] = label;
    }
}

void InputHandler::parseBlockData(DataModel& dataModel) {
    int cols = dimensions[0], rows = dimensions[1], slices = dimensions[2];
    
    std::string line;
    char tag;
    char formattedBlock[128];

    for (int z = 0; z < slices; ++z) {
        for (int y = 0; y < rows; ++y) {
            std::getline(std::cin, line);

            for (int x = 0; x < cols; ++x) {
                tag = line[x];

                const std::string& label = tagTable[static_cast<unsigned char>(tag)];
        
                // Check if the tag exists in the map
                if (!label.empty()) {
                    // Adding blocks with initial size (1,1,1)
                    dataModel.addBlockMap(x, y, z, Block(x, y, z, 1, 1, 1, label));   
                    dataModel.addBlock(x, y, z, 1, 1, 1, label);                 
                } else {
                    std::cerr << "Missing tag at: " << x << ", " << y << ", " << z << std::endl;
                }
            }
        }
        std::getline(std::cin, line); // Read the blank line separating slices
    }
}
