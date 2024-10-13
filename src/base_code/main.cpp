#include <iostream>
#include "InputHandler.h"
#include "DataModel.h"
#include "OutputGenerator.h"
#include <chrono>  

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false); 
    std::cin.tie(nullptr);

    // starting speed timer
    auto start = std::chrono::high_resolution_clock::now();
    
    InputHandler inputHandler;
    DataModel dataModel;
    OutputGenerator outputGenerator;

    // parsing input
    inputHandler.parseInput(dataModel);

    // out file name
    std::string outputFileName = "";

    // Check if the program was called with an output filename argument
    if (argc > 2) {
        outputFileName = argv[2]; 
    }

    // writing output to filename or standard output
    outputGenerator.writeOutput(outputFileName, dataModel);

    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed = end - start;

   // send output to cerr
    std::cerr << "Output written to " << (outputFileName.empty() ? "standard output" : outputFileName) << std::endl;
    std::cerr << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
