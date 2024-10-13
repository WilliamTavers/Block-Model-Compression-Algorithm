#include "BlockModel.h"

void BlockModel::addBlock(int x, int y, int z, int label) {
    std::lock_guard<std::mutex> lock(mtx);
    blocks.push_back({x, y, z, label});
    labelIndex[label].insert(blocks.size() - 1);
}

void BlockModel::setDimensions(int x, int y, int z, int parentX, int parentY, int parentZ) {
    std::lock_guard<std::mutex> lock(mtx);
    this->xDim = x;
    this->yDim = y;
    this->zDim = z;
    this->parentX = parentX;
    this->parentY = parentY;
    this->parentZ = parentZ;
}

std::vector<Block> BlockModel::getBlocks() {
    std::lock_guard<std::mutex> lock(mtx);
    return blocks;
}

std::vector<Block> BlockModel::getBlocksByRange(int start, int end) {
    std::lock_guard<std::mutex> lock(mtx);
    return std::vector<Block>(blocks.begin() + start, blocks.begin() + end);
}

std::vector<Block> BlockModel::getBlocksByLabel(int label) {
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<Block> result;
    for (int index : labelIndex[label]) {
        result.push_back(blocks[index]);
    }
    return result;
}

size_t BlockModel::size() {
    std::lock_guard<std::mutex> lock(mtx);
    return blocks.size();
}
