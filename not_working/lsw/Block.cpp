#include "Block.h"
#include <sstream>
#include <vector>
#include <cctype>
// constructor
Block::Block(int x, int y, int z, int sizeX, int sizeY, int sizeZ, const std::string& label)
    : xPos(x), yPos(y), zPos(z), sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ), label(label) {}

// get for X position
int Block::getXPosition() const {
    return xPos;
}

// get for Y position
int Block::getYPosition() const {
    return yPos;
}

// get for Z position
int Block::getZPosition() const {
    return zPos;
}

// get for size in the X dimension
int Block::getSizeX() const {
    return sizeX;
}

// get for size in the Y dimension
int Block::getSizeY() const {
    return sizeY;
}

// get for size in the Z dimension
int Block::getSizeZ() const {
    return sizeZ;
}

const std::string& Block::getLabel() const { return label; }

void Block::setLabel(const std::string &label) {
    this->label = label;
    this->compressed = false;
}

// destructor
Block::~Block() {}
