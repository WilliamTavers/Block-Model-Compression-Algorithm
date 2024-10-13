#ifndef DP_COMPRESSOR_H
#define DP_COMPRESSOR_H

#include "BlockModel.h"
#include <vector>
#include <unordered_map>
#include <mutex>
#include <set>

class DPCompressor {
public:
    std::vector<Block> compress(const std::vector<Block>& blocks, const BlockModel& blockModel);
    void reset();

private:
    int calculateKey(int x, int y, int z);
    void mergeBlocks(Block& existingBlock, const Block& newBlock, const BlockModel& blockModel);
    
    void stageOneCompression(const std::vector<Block>& blocks, std::unordered_map<int, Block>& mergedBlocks, const BlockModel& blockModel);
    void stageTwoCompression(const std::unordered_map<int, Block>& mergedBlocks, std::vector<Block>& refinedBlocks, const BlockModel& blockModel);
    
    bool canMergeBlocks(const Block& block1, const Block& block2, const BlockModel& blockModel);
    Block complexMerge(const Block& block1, const Block& block2, const BlockModel& blockModel);
    
    std::unordered_map<int, Block> blockCache;

    size_t totalMerges = 0;
    size_t failedMerges = 0;
};

#endif
