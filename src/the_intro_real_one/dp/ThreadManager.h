#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include "DPCompressor.h"
#include "BlockModel.h"
#include <vector>
#include <thread>

class ThreadManager {
public:
    std::vector<Block> performCompression(DPCompressor& compressor, BlockModel& blockModel);
    
private:
    std::vector<Block> compressSection(DPCompressor& compressor, const std::vector<Block>& section, BlockModel& blockModel);
    void mergeResults(std::vector<Block>& finalBlocks, const std::vector<Block>& partialBlocks);
};

#endif
