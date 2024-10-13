#include "DPCompressor.h"
#include <cmath>
#include <iostream>

int DPCompressor::calculateKey(int x, int y, int z) {
    return std::abs(x * 73856093 ^ y * 19349663 ^ z * 83492791) % 1000000007;
}

void DPCompressor::reset() {
    blockCache.clear();
    totalMerges = 0;
    failedMerges = 0;
}

bool DPCompressor::canMergeBlocks(const Block& block1, const Block& block2, const BlockModel& blockModel) {
    if (block1.label != block2.label) {
        return false;
    }

    int mergedXSize = std::max(block1.x, block2.x) - std::min(block1.x, block2.x) + 1;
    int mergedYSize = std::max(block1.y, block2.y) - std::min(block1.y, block2.y) + 1;
    int mergedZSize = std::max(block1.z, block2.z) - std::min(block1.z, block2.z) + 1;

    return mergedXSize <= blockModel.getParentX() &&
           mergedYSize <= blockModel.getParentY() &&
           mergedZSize <= blockModel.getParentZ();
}

// Perform a complex merge operation on two blocks
Block DPCompressor::complexMerge(const Block& block1, const Block& block2, const BlockModel& blockModel) {
    Block mergedBlock = block1;

    mergedBlock.x = std::min(block1.x, block2.x);
    mergedBlock.y = std::min(block1.y, block2.y);
    mergedBlock.z = std::min(block1.z, block2.z);

    int mergedXSize = std::max(block1.x, block2.x) - std::min(block1.x, block2.x) + 1;
    int mergedYSize = std::max(block1.y, block2.y) - std::min(block1.y, block2.y) + 1;
    int mergedZSize = std::max(block1.z, block2.z) - std::min(block1.z, block2.z) + 1;

    if (mergedXSize > blockModel.getParentX() || 
        mergedYSize > blockModel.getParentY() || 
        mergedZSize > blockModel.getParentZ()) {
        return block1;
    }

    return mergedBlock;
}

// Stage One: Group and merge blocks
void DPCompressor::stageOneCompression(const std::vector<Block>& blocks, std::unordered_map<int, Block>& mergedBlocks, const BlockModel& blockModel) {
    for (const auto& block : blocks) {
        int key = calculateKey(block.x, block.y, block.z);

        if (blockCache.find(key) != blockCache.end()) {
            mergedBlocks[key] = blockCache[key];
            continue;
        }

        if (mergedBlocks.find(key) == mergedBlocks.end()) {
            mergedBlocks[key] = block;
        } else {
            if (canMergeBlocks(mergedBlocks[key], block, blockModel)) {
                mergedBlocks[key] = complexMerge(mergedBlocks[key], block, blockModel);
                totalMerges++;
            } else {
                failedMerges++;
            }
        }

        blockCache[key] = mergedBlocks[key];
    }
}

// Stage Two: Further refine the merged blocks, ensuring constraints are met
void DPCompressor::stageTwoCompression(const std::unordered_map<int, Block>& mergedBlocks, std::vector<Block>& refinedBlocks, const BlockModel& blockModel) {
    for (const auto& entry : mergedBlocks) {
        const Block& block = entry.second;

        refinedBlocks.push_back(block);
    }
}

// Main compression function
std::vector<Block> DPCompressor::compress(const std::vector<Block>& blocks, const BlockModel& blockModel) {
    std::unordered_map<int, Block> mergedBlocks;
    std::vector<Block> refinedBlocks;

    stageOneCompression(blocks, mergedBlocks, blockModel);

    stageTwoCompression(mergedBlocks, refinedBlocks, blockModel);

    std::cout << "Compression completed. Total merges: " << totalMerges << ", Failed merges: " << failedMerges << std::endl;

    return refinedBlocks;
}
