#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H


#include <iostream>
#include <vector> 
#include <string>
#include "DataModel.h" 
#include "Block.h" 

// The InputHandler class is responsible for reading and parsing raw input data
// and providing it in a structured format that can be used by other parts of the system

class InputHandler {
    public: 
    // Constructor 
    InputHandler();

    // Main method to read and parse input data from standard input
    void parseInput(DataModel& dataModel);

    // Method to access the dimensions vector
    const std::vector<int>& getDimensions() const;

    private: 
    // Stores the dimensions of the block model (x_count, y_count, z_count, parent_x, parent_y, parent_z)
    std::vector<int> dimensions;

    // stores the mapping of tags (characters) to labels as provided in the tag table
    std::vector<std::string> tagTable;

    // Helper method to parse the dimensions from the first line of input 
    void parseDimensions(const std::string& line);

    // Helper method to parse the tag table from the input 
    void parseTagTable();

    // Helper method to parse the block data and populate the DataModel with Block instances
    void parseBlockData(DataModel& dataModel);

};

#endif // INPUTHANDLER_H