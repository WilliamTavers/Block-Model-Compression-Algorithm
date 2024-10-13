#include "ThreadManager.h"
#include <future>
#include <iostream>

std::vector<Block> ThreadManager::compressSection(DPCompressor& compressor, const std::vector<Block>& section, BlockModel& blockModel) {
    return compressor.compress(section, blockModel);  
}

// Merge the results from multiple threads
void ThreadManager::mergeResults(std::vector<Block>& finalBlocks, const std::vector<Block>& partialBlocks) {
    finalBlocks.insert(finalBlocks.end(), partialBlocks.begin(), partialBlocks.end());
}

// Perform compression using multiple threads
std::vector<Block> ThreadManager::performCompression(DPCompressor& compressor, BlockModel& blockModel) {
    std::vector<Block> blocks = blockModel.getBlocks();  
    size_t numThreads = std::thread::hardware_concurrency(); 
    size_t sectionSize = blocks.size() / numThreads;

    
    std::vector<std::future<std::vector<Block>>> futures;

    for (size_t i = 0; i < numThreads; ++i) {
        size_t start = i * sectionSize;
        size_t end = (i == numThreads - 1) ? blocks.size() : (i + 1) * sectionSize;
        std::vector<Block> section = blockModel.getBlocksByRange(start, end);
        
        futures.push_back(std::async(std::launch::async, &ThreadManager::compressSection, this, std::ref(compressor), section, std::ref(blockModel)));
    }

    std::vector<Block> compressedBlocks;
    for (auto& future : futures) {
        std::vector<Block> partialCompressedBlocks = future.get();
        mergeResults(compressedBlocks, partialCompressedBlocks);
    }

    return compressedBlocks;
}
