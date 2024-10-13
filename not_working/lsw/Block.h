#ifndef BLOCK_H
#define BLOCK_H

#include <string>

#include <unordered_map>
#include <tuple>
#include <vector>

namespace std {
    template <>
    struct hash<std::tuple<int, int, int>> {
        size_t operator()(const std::tuple<int, int, int>& key) const {
            return std::get<0>(key) ^ (std::get<1>(key) << 1) ^ (std::get<2>(key) << 2);
        }
    };
}

// this class represents a single data block within a block model
// holds blocks pos, size, and the label associated with it

class Block {
    
public:
    // Default constructor
    Block() : xPos(0), yPos(0), zPos(0), sizeX(1), sizeY(1), sizeZ(1), label("") {}
    // constructor
    Block(int x, int y, int z, int sizeX, int sizeY, int sizeZ, const std::string &label);

    // get functions for block object
    int getXPosition() const;
    int getYPosition() const;
    int getZPosition() const;

    int getSizeX() const;
    int getSizeY() const;
    int getSizeZ() const;

    const std::string& getLabel() const;
    
    void setLabel(const std::string &label);

    // Compression methods
 

    // destructor
    ~Block();

private:

    // coordinates of each block in block model
    int xPos, yPos, zPos;

    // block dimensions
    int sizeX, sizeY, sizeZ;

    // lebel describing content of the block
    std::string label;

    // compressed or not 
    bool compressed;

};

#endif 
