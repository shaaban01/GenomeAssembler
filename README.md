# first create a folder named "files" and paste in in the reads.txt and reference.txt

# De Bruijn Genome Assembler

This is a De Bruijn genome assembler written in C++. It takes in a file of reads return the assembled genome into data/output.txt

## To Compile and Run

`cd build`

`cmake ..`

`make`

`./GenomeAssembler </path/to/reads>`

## For Testing

Make sure to have gtest installed on your machine `sudo apt install libgtest-dev` to install it on ubuntu

### To run the test

build the project using:

`cd build`

`cmake ..`

`make`

then run

`./GenomeAssemblerTests`
