#ifndef BLOCK_MODEL_H
#define BLOCK_MODEL_H

#include <vector>
#include <mutex>
#include <map>
#include <set>

struct Block {
    int x, y, z;
    int label;
};

class BlockModel {
private:
    std::vector<Block> blocks;
    std::map<int, std::set<int>> labelIndex;
    std::mutex mtx;
    int xDim, yDim, zDim;
    int parentX, parentY, parentZ;

public:
    void addBlock(int x, int y, int z, int label);
    void setDimensions(int x, int y, int z, int parentX, int parentY, int parentZ);
    std::vector<Block> getBlocks();
    std::vector<Block> getBlocksByRange(int start, int end);
    std::vector<Block> getBlocksByLabel(int label);
    size_t size();

    int getParentX() const { return parentX; }
    int getParentY() const { return parentY; }
    int getParentZ() const { return parentZ; }
};

#endif
