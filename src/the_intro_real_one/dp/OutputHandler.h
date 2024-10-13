#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H

#include "BlockModel.h"
#include <string>
#include <vector>

class OutputHandler {
public:
    void writeOutput(const std::string& filename, const std::vector<Block>& blocks);
    void writeSummary(const std::string& filename, const std::vector<Block>& blocks);
    void writeDetailedReport(const std::string& filename, const std::vector<Block>& blocks);
};

#endif
