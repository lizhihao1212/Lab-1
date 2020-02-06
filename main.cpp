//
//  main.cpp
//  Operating System Lab1
#include <iostream>
#include <fstream>
#include "linkList.hpp"
#include "readFile.hpp"
#include "printMemMap.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    string c = string(argv[1]);//string(argv[1]);
    ifstream pass1(c, ifstream::in);
    readFile read;
    linkList symbolTable;
    linkList warningList;
    int moduleNum = 0;
    int module = 1;
    while(!pass1.eof()){
        int defNum = read.getNum(pass1);
        if(defNum > 16){
            cout<<"Parse Error line "<<read.line<<" offset "<<read.lineOffset + 1 - to_string(defNum).length()<<": TOO_MANY_DEF_IN_MODULE"<<endl;
            exit(0);
        }
        if(defNum == -1)
            break;
        for(int i = 0; i < defNum; i++){
            string symbol = read.getSymbol(pass1);
            if(symbolTable.isContain(symbol)){
                warningList.addNode(symbol);
                warningList.addNode(" Error: This variable is multiple times defined; first value used");
                read.getNum(pass1);
                continue;
            }
            symbolTable.addNode(symbol);
            symbolTable.addNode(to_string(read.getNum(pass1) + moduleNum));
        }
        int useNum = read.getNum(pass1);
        if(useNum > 16){
            cout<<"Parse Error line "<<read.line<<" offset "<<read.lineOffset + 1 - to_string(useNum).length()<<": TOO_MANY_USE_IN_MODULE"<<endl;
            exit(0);
        }
        for(int i = 0; i < useNum; i++){
            read.getSymbol(pass1);
        }
        int instrNum = read.getNum(pass1);
        if(instrNum >= 510){
            cout<<"Parse Error line "<<read.line<<" offset "<<read.lineOffset + 1 - to_string(instrNum).length()<<": TOO_MANY_INSTR"<<endl;
            exit(0);
        }
        for(int i = 0; i < instrNum; i++){
            read.getinstruction(pass1);
            read.getNum(pass1);
        }
        read.checkDefList(symbolTable, moduleNum, module, instrNum);
        moduleNum = moduleNum + instrNum;
        module++;
    }
    pass1.close();
    
    cout<<"Symbol Table"<<endl;
    
    listNode* temp = symbolTable.head;
    while(temp != NULL){
        string symbol = temp -> content;
        cout<<temp->content<<'=';
        temp = temp -> next;
        cout<<temp->content;
        if(warningList.isContain(symbol)){
            listNode* warnhead = warningList.head;
            while(warnhead->content != symbol){
                warnhead = warnhead -> next;
            }
            warnhead = warnhead ->next;
            cout<<warnhead -> content;
        }
        temp = temp -> next;
        cout<<endl;
    }
    cout<<endl;
    
    ifstream pass2(c, ifstream::in);
    cout<<"Memory Map"<<endl;
    readFile read2;
    linkList globelUseList;
    linkList localUselist;
    linkList localDefList;
    printMem memoryMap;
    moduleNum = 0;
    while(!pass2.eof()){
        int defNum = read2.getNum(pass2);
        if(defNum == -1)
            break;
        for(int i = 0; i < defNum; i++){
            string symbol = read2.getSymbol(pass2);
            if(!memoryMap.nonUsedDef.isContain(symbol)){
                memoryMap.nonUsedDef.addNode(symbol);
                memoryMap.nonUsedDef.addNode(to_string(memoryMap.moudule));
            }
            //memoryMap.nonUsedDef.addNode(to_string(memoryMap.moudule));
            read2.getNum(pass2);
        }
        int useNum = read2.getNum(pass2);
        for(int i = 0; i < useNum; i++){
            string symbol = read2.getSymbol(pass2);
            globelUseList.addNode(symbol);
            localUselist.addNode(symbol);
            memoryMap.nonUseLocal.addNode(symbol);
            memoryMap.nonUseLocal.addNode(to_string(memoryMap.moudule));
        }
        int instrNum = read2.getNum(pass2);
        memoryMap.modLength = instrNum;
        memoryMap.beginAddress = moduleNum;
        for(int i = 0; i < instrNum; i++){
          string instruction = read2.getinstruction(pass2);
	  int number = read2.getNum(pass2);
	  memoryMap.printMemMap(instruction, number, symbolTable, localUselist);
        }
        moduleNum = moduleNum + instrNum;
        memoryMap.printNonUseSymbol();
        localUselist.cleanUP();
        memoryMap.nonUseLocal.cleanUP();
        memoryMap.moudule++;
    }
    cout<<endl;
    memoryMap.checkDefineList(globelUseList);
    memoryMap.printNonUseDef();
    return 0;
}



