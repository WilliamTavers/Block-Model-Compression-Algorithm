#ifndef DATAMODEL_H 
#define DATAMODEL_H


#include <vector>
#include <unordered_map>
#include <tuple>
#include "Block.h"

class DataModel {
    public:
    // Contsructor
    DataModel();

    // Function to get block from DataMode;
    const Block& getBlock(int index) const; // vec
    const Block& getBlockMap(int x, int y, int z) const; // map

    const std::unordered_map<std::tuple<int, int, int>, Block>& getStoredBlocksMap() const {
        return storedBlocksMap;
    }
    
    const std::vector<Block>& getStoredBlocks() const {
        return storedBlocks;
    }

    // Function to add blocks to DataModel -> keep for now for if we want to use vectors or 0 compression
    template <typename... Args>
    void addBlock(Args&&... args) {
        storedBlocks.emplace_back(std::forward<Args>(args)...); // vec
    }
    void addBlockMap(int x, int y, int z, const Block& block); // map

    // Function to return number of blocks stored
    int getBlocksMapCount() const;
    int getBlocksCount() const;



    // Destructor
    ~DataModel();


    private:
    // Vector of blocks (Could definitely be stored as a map if needed)
    std::vector<Block> storedBlocks;
    std::unordered_map<std::tuple<int, int, int>, Block> storedBlocksMap;
};

#endif // DATAMODEL_H