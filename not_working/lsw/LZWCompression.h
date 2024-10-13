#ifndef LZW_COMPRESSION_H
#define LZW_COMPRESSION_H

#include <vector>

class LZWCompression {
public:
    std::vector<int> compress(const std::vector<int>& input);

private:
    std::vector<std::vector<int>> dictionary;
    int findIndex(const std::vector<int>& entry) const;
};

#endif