//
//  printMemMap.hpp
//  Operating System Lab1
//

#ifndef printMemMap_hpp
#define printMemMap_hpp
#include <iostream>
#include <stdio.h>
#include "linkList.hpp"
using namespace std;
class printMem{
public:
    string prefix;
    int count;
    int moudule;
    int modLength;
    int beginAddress;
    string EndingWarning;
    linkList nonUsedDef;
    linkList nonUseLocal;
    
    printMem(){prefix = "00"; count = 0; moudule = 1; modLength = 0; EndingWarning = "";};
    void printMemMap(string instr, int code, linkList symbolTable, linkList localUseList);
    void printR(string instr, int code, linkList symbolTable, linkList localUseList);
    void printI(string instr, int code, linkList symbolTable, linkList localUseList);
    void printA(string instr, int code, linkList symbolTable, linkList localUseList);
    void printE(string instr, int code, linkList symbolTable, linkList localUseList);
    void printResult(string warning, int code);
    void printNonUseDef();
    void printNonUseSymbol();
    
    void checkDefineList(linkList localUseList);
    void checkUseList();
};

#endif /* printMemMap_hpp */
