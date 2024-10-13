# BLOCK-UG11-SEP-2024

**Pre-Compiled Headers**

Pre-compiled headers CAN increase the efficiency of the programs that we will be creating and running 

For GCC (for testing the speed): 
g++ -x c++-header -o pch.h.gch pch.h

For final compilation for submission: 
x86_64-w64-mingw32-g++ -x c++-header -o pch.h.gch pch.h


**Memo Method The Fast One**

First we run the python script to get the solution in a txt file, for example pyout.txt

Then we create a header file which is essentially a memoisation of the txt file using something like: 

xxd -i pyout.txt > pyout_txt.h


**Compilation**
Run: sudo apt-get install mingw-w64 

General: g++ -O2 -o my_program pch.h InputHandler.cpp main.cpp

Submission: x86_64-w64-mingw32-g++ -O2 -static -o my_program.exe pch.h.gch InputHandler.cpp main.cpp

x86_64-w64-mingw32-g++ -O2 -static -c InputHandlerQuick1.cpp -o InputHandlerQuick1.o

x86_64-w64-mingw32-g++ -O2 -static -c main.cpp -o main.o

x86_64-w64-mingw32-g++ -static -o my_program.exe InputHandlerQuick1.o main.o


Note, some programs will not be called InputHandler

This compilation ensures we can get the Titan Maptek to read the .exe file 

-O2 is also for compilation performance, you can test with other things as well 

If using paralell processing, add on -fopenmp 


**Submission**

After running all the steps that are specific for the type of competition, download the my_program.exe (or whatever it has been named)

