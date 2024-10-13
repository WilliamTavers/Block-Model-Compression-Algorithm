#include "OutputGenerator.h"
#include <fstream>
#include <iostream>
#include <sstream>



// Constructor
OutputGenerator::OutputGenerator() {}

// Destructor
OutputGenerator::~OutputGenerator() {}


void OutputGenerator::writeOutput(const std::string& filename, const DataModel& dataModel) const {
    std::ostream* outStream;
    std::ofstream outFile;

    if (!filename.empty()) {
        outFile.open(filename);
        if (!outFile) {
            std::cerr << "Error: Could not open file " << filename << " for writing.\n";
            return;
        }
        outStream = &outFile;
    } else {
        outStream = &std::cout;
    }

    const auto& blocksMap = dataModel.getStoredBlocks();

    // Iterate over the blocks in the unordered_map
    for (const auto& entry : blocksMap) {
        const Block& block = entry;

        std::ostringstream formattedBlock;
        formattedBlock << block.getXPosition() << ","
                       << block.getYPosition() << ","
                       << block.getZPosition() << ","
                       << block.getSizeX() << ","
                       << block.getSizeY() << ","
                       << block.getSizeZ() << ","
                       << block.getLabel();

        *outStream << formattedBlock.str() << "\n";
    }
}
