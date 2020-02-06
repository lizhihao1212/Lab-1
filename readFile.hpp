//
//  readFile.hpp
//  Operating System Lab1
//
//

#ifndef readFile_hpp
#define readFile_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include "linkList.hpp"
using namespace std;
class readFile{
public:
    int line;
    int lineOffset;
    int tokenlength;
    char* c;
    string warnging;
    
    readFile(){line = 0; lineOffset = 0; c = new char[1000];};
    void setlineOffset(char* prc);
    void getLine(ifstream &in);
    char getchar(ifstream &in);
    int getNum(ifstream &in);
    string getSymbol(ifstream &in);
    string getToken(ifstream &in);
    string getinstruction(ifstream &in);
    
    void checkDefList(linkList symbolTable, int moduleLength, int module, int instrNum);
};
#endif /* readFile_hpp */
