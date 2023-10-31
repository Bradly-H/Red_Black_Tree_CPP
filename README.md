Bradley Haire
bhaire
pa8
CSE 101 Patrick Tantalo
------------------------------------

# Order.cpp
This is the main file for the order functionality. It will take a file in and a file out. The file in should contain a series of line separated words, and these words will be put into the dictionary 1 by one, inserted according to a lexicographical sort. Each word is a key, and its value will be how many words have been inserted before it + 1. This will then print out an in order representation of the Dictionary tree, with both key and value, and then print a pre-order representation, containing only keys. Both representations are written into the output file.  

# WordFrequency.cpp
This is the other main file for the dictionary. It will also take an input and an output file, and now, instead of the value for each word being the number of words inserted, it will instead be the count of how many times that particular word appears in the input file. After reading through the entire input file and constructing the tree, this will then print out an in-order representation of the tree to the output file

# Dictionary.cpp
The implementation of the Dictionary ADT. 

# Dictionary.h
This is the header file for the Dictionary ADT. It is required for compilation of the program. 

# DictionaryTest.cpp
This is a client file used for testing the Dictionary ADT and can be safely ignored. 

# Makefile
This is the file used to build all of the C++ code into an executable binary. It supports several different commands. 
### make
This command will call make all
### make all
This command compiles the Order, WordFrequency, and DictionaryTest binaries
### make Order
This command compiles only the Order binary
### make WordFrequency
This command compiles only the WordFrequency binary
### make DictionaryTest
This command compiles only the DictionaryTest binary
### make clean
This command removes all .o object files, as well as the DictionaryTest, WordFrequency and Order binaries, should they exist
