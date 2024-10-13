#include "OutputGenerator.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "LZWCompression.h"

OutputGenerator::OutputGenerator() {}
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

    LZWCompression lzw;

    for (const auto& entry : blocksMap) {
        const Block& block = entry;

        std::vector<int> uncompressedBlock;
        // std::ostringstream formattedBlock;

        // formattedBlock << block.getXPosition() << "," << block.getYPosition() << ","
        //                << block.getZPosition() << "," << block.getSizeX() << ","
        //                << block.getSizeY() << "," << block.getSizeZ() << ","
        //                << block.getLabel();


        // concatenate the coordinates and sizes
        uncompressedBlock.push_back(block.getXPosition());
        uncompressedBlock.push_back(block.getYPosition());
        uncompressedBlock.push_back(block.getZPosition());
        uncompressedBlock.push_back(block.getSizeX());
        uncompressedBlock.push_back(block.getSizeY());
        uncompressedBlock.push_back(block.getSizeZ());

        // compress the coordinates using LZW
        std::vector<int> compressedData = lzw.compress(uncompressedBlock);

        // debug output for compressed data
        *outStream << "Compressed Data: ";
        for (const auto& value : compressedData) {
            *outStream << value << " ";
        }
        *outStream << "\n";

        // write the compressed coordinates and the uncompressed label
        for (size_t i = 0; i < compressedData.size(); ++i) {
            *outStream << compressedData[i];
            if (i < compressedData.size() - 1) {
                *outStream << ",";
            }
        }
        *outStream << "," << block.getLabel() << "\n";
    }
}
