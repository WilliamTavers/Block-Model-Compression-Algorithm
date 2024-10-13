#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "pch.h"

class InputHandler {
public:
    InputHandler();

    void parseInput();

private:
    std::vector<int> dimensions;
    
    std::vector<std::string> tagTable;

    void parseDimensions(const std::string& line);

    void parseTagTable();

    void parseBlockData();

    bool isKnownInput();
};

#endif 
