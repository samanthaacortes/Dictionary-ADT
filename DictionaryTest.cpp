/********************************************************************************* 
 * Samantha Cortes, saalcort 
 * 2023 Winter CSE101 PA8 
 * DictionaryTest.cpp 
 * Dictionary Test for Dictionary ADT 
 *********************************************************************************/ 

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main() {
  string key;
  int val;
  string S[] = {"cat", "woof", "hiiiiii", "water", "fun", "drive", "sleep"};

  Dictionary X;
  Dictionary Y;

  cout << endl;

  for(int i = 0; i < 7; i++) {
    X.setValue(S[i], i+1);
  }
   
  Y = X;

  cout << "X.size() = " << X.size() << endl  << X << endl;
  
  cout << "Y.size() = " << Y.size() << endl  << Y << endl;

  Y.setValue("cat", 8);

  cout << "Y.size() = " << Y.size() << endl  << Y << endl;
  
  Y.remove("cat");

  Dictionary Z = Y;

  cout << "Y.size() = " << Y.size() << endl  << Y << endl;
  
  cout << "Z.size() = " << Z.size() << endl  << Z << endl;

  cout << "X==Y is " << (X==Y?"true":"false") << endl;
  
  cout << "Z==X is " << (Z==X?"true":"false") << endl << endl;

  cout << "Y==Z is " << (Y==Z?"true":"false") << endl;

  cout << "X.contains('cat')" << X.contains("cat") << endl;
  
  cout << X.getValue("cat") << endl;
  
  X.getValue("cat") *= 9; 
  
  cout << X.getValue("cat") << endl << endl;
  
  X.remove("woof");
  
  X.remove("water");

  cout << "X.size() = " << X.size() << endl  << X << endl;
  
  cout << X.pre_string() << endl;

  for(Y.begin(); Y.hasCurrent(); Y.next()) {
    key = Y.currentKey();
    val = Y.currentVal();
    cout << "("+key+", " << val << ") ";
  }
  cout << endl;

  for(Y.end(); Y.hasCurrent(); Y.prev()) {
    cout << "<" << Y.currentKey() << ", " << (++Y.currentVal()) << ">"<< endl; 
  } 

  X.clear();
  
  cout << "X.size() = " << X.size() << endl  << X << endl;

  return 0;
}


