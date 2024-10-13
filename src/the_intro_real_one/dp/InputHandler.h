#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "BlockModel.h"
#include <string>
#include <map>

class InputHandler {
public:
    void parseInput(const std::string& filename, BlockModel& blockModel);
private:
    void parseDimensions(std::ifstream& inputFile, BlockModel& blockModel);
    void parseTagTable(std::ifstream& inputFile, std::map<int, std::string>& tagTable);
};

#endif
