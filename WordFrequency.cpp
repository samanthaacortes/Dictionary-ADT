/********************************************************************************* 
 * Samantha Cortes, saalcort 
 * 2023 Winter CSE101 PA8 
 * WordFrequency.cpp
 * Source file that read in each line of a file, 
 * parse the individual words on each line, convert 
 * each word to all lower case characters, then place 
 * it (as key) in a Dictionary.
 *********************************************************************************/ 


#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <algorithm>

#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
  ifstream input;
  ofstream output;

  Dictionary D;

  if(argc < 3 || argc > 3) {
    cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
  }

  input.open(argv[1]);
  if(!input.is_open()) {
    cerr << "Unable to open file " << argv[1] << " for reading" << endl;
  }

  output.open(argv[2]);
  if(!output.is_open()) {
    cerr << "Unable to open file " << argv[1] << " for writng" << endl;
  }

  size_t begin;
  size_t end;
  size_t length;
  string line;
  string token;
  string delim = " ";

  delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789"; 

  while(getline(input, line)) {
    
    length = line.length();

    begin = min(line.find_first_not_of(delim, 0), length);
    end   = min(line.find_first_of(delim, begin), length);
    token = line.substr(begin, end - begin);
    
    transform(token.begin(), token.end(), token.begin(), ::tolower);

    while(token != "") {
      try {
        D.getValue(token) += 1;
      } catch(logic_error& e) {
        D.setValue(token, 1);
      }

      begin = min(line.find_first_not_of(delim, end + 1), length);
      end = min(line.find_first_of(delim, begin), length);
      token = line.substr(begin, end - begin);
      transform(token.begin(), token.end(), token.begin(), ::tolower);
    }
  }
  output << D << endl;

  input.close();
  output.close();

  return EXIT_SUCCESS;
}

