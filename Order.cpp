//-----------------------------------------------------------------------------
// Order.cpp
// Client file for the Dictionary ADT
// Bradley Haire
// bhaire
// pa8
//-----------------------------------------------------------------------------

#include "Dictionary.h"
#include <iostream>
#include <fstream>

using std::cerr;
using std::endl;

int main(int argc, char** argv) {
    if(argc != 3) {
        cerr << "Usage: " << argv[0] << " invalid number of arguments " << endl;
        return(EXIT_FAILURE);
    }
    std::string file_1 = argv[1];
    std::string file_2 = argv[2];
    std::ifstream input(file_1);
    std::ofstream output(file_2);
    int counter = 1;
    std::string word = "";
    Dictionary* dict = new Dictionary();
    while(std::getline(input, word, '\n')) {
        dict->setValue(word, counter);
        counter += 1;
    }
    output << dict->to_string();

    output << dict->pre_string();

    delete dict;
}
