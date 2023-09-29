/********************************************************************************* 
 * Samantha Cortes
 * Order.cpp
 * Source file that alphabetizes the lines and prints
 * "key : value\n" pairs in alphabetical order using Dictionary ADT 
 *********************************************************************************/ 

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
  ifstream input;
  ofstream output;
  string key;
  
  if(argc < 3 || argc > 3) {
    cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
    return EXIT_FAILURE;
  }
  
  input.open(argv[1]);
  if(!input.is_open()) {
    cerr << "Unable to open file " << argv[1] << " for reading"<<endl;
    return EXIT_FAILURE;
  }

  output.open(argv[2]);
  if(!output.is_open()) {
    cerr << "Unable to open file " << argv[2] << " for writing" << endl;
    return EXIT_FAILURE;
  }

  Dictionary D;
  int value = 1;

  while(getline(input, key)) {
    D.setValue(key, value);
    value++;
  }

  output << D << endl << endl;
  output << D.pre_string() << endl;

  input.close();
  output.close();
   
  return EXIT_SUCCESS;
}


