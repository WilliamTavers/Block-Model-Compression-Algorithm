#include "OutputHandler.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <iomanip>

void OutputHandler::writeOutput(const std::string& filename, const std::vector<Block>& blocks) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return;
    }

    for (const auto& block : blocks) {
        outputFile << block.x << " " << block.y << " " << block.z << " " << block.label << "\n";
    }
    outputFile.close();
}

void OutputHandler::writeSummary(const std::string& filename, const std::vector<Block>& blocks) {
    std::ofstream summaryFile(filename);
    if (!summaryFile.is_open()) {
        std::cerr << "Failed to open summary file." << std::endl;
        return;
    }

    std::unordered_map<int, int> labelCounts;
    for (const auto& block : blocks) {
        labelCounts[block.label]++;
    }

    summaryFile << "Label Summary:\n";
    for (const auto& entry : labelCounts) {
        summaryFile << "Label: " << entry.first << " Count: " << entry.second << "\n";
    }
    summaryFile.close();
}

void OutputHandler::writeDetailedReport(const std::string& filename, const std::vector<Block>& blocks) {
    std::ofstream reportFile(filename);
    if (!reportFile.is_open()) {
        std::cerr << "Failed to open detailed report file." << std::endl;
        return;
    }

    reportFile << std::setw(10) << "X" << std::setw(10) << "Y" << std::setw(10) << "Z" << std::setw(10) << "Label" << "\n";
    reportFile << std::string(40, '-') << "\n";
    for (const auto& block : blocks) {
        reportFile << std::setw(10) << block.x << std::setw(10) << block.y << std::setw(10) << block.z << std::setw(10) << block.label << "\n";
    }
    reportFile.close();
}

