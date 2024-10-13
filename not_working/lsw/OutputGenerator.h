#ifndef OUTPUTGENERATOR_H
#define OUTPUTGENERATOR_H

#include <string>
#include "DataModel.h" 
#include "Block.h" 

class OutputGenerator {
public:
    // Constructor
    OutputGenerator();

    // Destructor
    ~OutputGenerator();

    // Method to write formatted output data to a file
    void writeOutput(const std::string& filename, const DataModel& dataModel) const;

};

#endif // OUTPUTGENERATOR_H
