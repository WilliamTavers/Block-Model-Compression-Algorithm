#include "DataModel.h"
#include <sstream>

DataModel::DataModel() {
    // Initialize block vector
}

const Block& DataModel::getBlock(int index) const {
    return storedBlocks[index];
}

const Block& DataModel::getBlockMap(int x, int y, int z) const {
    auto it = storedBlocksMap.find(std::make_tuple(x, y, z));
    if (it != storedBlocksMap.end()) {
        return it->second;
    }
    throw std::runtime_error("Block not found at the given position");
}

void DataModel::addBlockMap(int x, int y, int z, const Block& block) {
    storedBlocksMap[std::make_tuple(x, y, z)] = block;
}

int DataModel::getBlocksMapCount() const {
    return storedBlocksMap.size();
}

int DataModel::getBlocksCount() const {
    return storedBlocks.size();
}


DataModel::~DataModel() {
    // Cleanup code, if necessary
}
