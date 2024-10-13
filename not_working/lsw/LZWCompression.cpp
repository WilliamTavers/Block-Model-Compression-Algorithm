#include "LZWCompression.h"
#include <vector>
#include <algorithm>

int LZWCompression::findIndex(const std::vector<int>& entry) const {
    for (size_t i = 0; i < dictionary.size(); ++i) {
        if (dictionary[i] == entry) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

std::vector<int> LZWCompression::compress(const std::vector<int>& input) {
    std::vector<int> result;
    dictionary.clear();
    std::vector<int> w;
    int dictSize = 256;

    // initialize the dictionary with single char strings
    for (int i = 0; i < 256; ++i) {
        dictionary.push_back({i});
    }

    for (int k : input) {
        w.push_back(k);
        int index = findIndex(w);
        if (index == -1) {
            // output w without k
            w.pop_back();
            index = findIndex(w);
            result.push_back(index);
            // add w to dictionary
            dictionary.push_back(w);
            dictSize++;
            w.clear();
            w.push_back(k);
        }
    }

    // output w
    if (!w.empty()) {
        result.push_back(findIndex(w));
    }

    return result;
}
