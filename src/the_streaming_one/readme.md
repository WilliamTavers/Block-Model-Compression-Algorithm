streamProcessor.cpp is standard I/O for the competition (no compression)

rleStream.cpp is our standard RLE code modified to work with the new competition, including print after 50 seconds

rleStringStream.cpp has tried to improve the 50 second print adjustment, and reducing standard cout by using string streams. 
The program prints from the stringstream every 50 seconds, and until that point it keeps adding to the stringstream
