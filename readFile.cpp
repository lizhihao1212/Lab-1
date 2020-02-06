//
//  readFile.cpp
//  Operating System Lab1
//

#include "readFile.hpp"

void readFile::getLine(ifstream &in){
    delete []c;
    c = new char[1000];
    in.getline(c, 1000);
    if(c[0] == '\0' && in.eof()){
        return;
    }
    line++;
    lineOffset = 0;
    if(c[0] == '\0' && !in.eof()){
        in.getline(c, 1000);
        line++;
        lineOffset = 0;
    }
}

char readFile::getchar(ifstream &in){
    while(c[lineOffset] == '\0'){
        getLine(in);
    }
    int temp = lineOffset;
    lineOffset++;
    return c[temp];
}

string readFile::getToken(ifstream &in){
    char* prc = NULL;
    prc = strtok(NULL, " '\t''\n'");
    while(prc == NULL && !in.eof()){
        getLine(in);
        prc = strtok(c, " '\t''\n'");
    }
    if(prc == NULL && in.eof())
        return "1EOF";
    string s(prc);
    setlineOffset(prc);
    return s;
}

int readFile::getNum(ifstream &in){
    string s = getToken(in);
    if(!isdigit(s.at(0))){
        cout<<"Parse Error line "<<line<<" offset "<<lineOffset+1<<": NUM_EXPECTED"<<endl;
        exit(0);
    }
    if(s == "1EOF")
        return -1;
    lineOffset = lineOffset + (int)s.length();
    return stoi(s);
}

string readFile::getSymbol(ifstream &in){
    string s = getToken(in);
    if(isdigit(s.at(0)) || s == "1EOF"){
        cout<<"Parse Error line "<<line<<" offset "<<lineOffset+1<<": SYM_EXPECTED"<<endl;
        exit(0);
    }
    if((int)s.length()>16){
        cout<<"Parse Error line "<<line<<" offset "<<lineOffset+1<<": SYM_TOO_LONG"<<endl;
        exit(0);
    }
    lineOffset = lineOffset + (int)s.length();
    return s;
}

string readFile::getinstruction(ifstream &in){
    string s = getToken(in);
    if((s != "R" && s != "I" && s != "A" && s != "E") || s == "1EOF"){
        cout<<"Parse Error line "<<line<<" offset "<<lineOffset+1<<": ADDR_EXPECTED"<<endl;
        exit(0);
    }
    lineOffset = lineOffset + (int)s.length();
    return s;
}

void readFile::checkDefList(linkList symbolTable, int moduleLength, int module, int instrNum){
    listNode* checkDef = symbolTable.head;
    while(checkDef != NULL){
        if(stoi(checkDef->next->content) - moduleLength >= instrNum){
            cout<<"Warning: Module "<<module<<": "<<checkDef->content<<" too big "<<checkDef->next->content<<" (max="<<instrNum - 1<<") assume zero relative"<<endl;
            checkDef->next->content = to_string(moduleLength);
        }
        checkDef = checkDef -> next -> next;
    }
}

void readFile::setlineOffset(char *prc){
    while(c[lineOffset] != prc[0]){
        lineOffset++;
    }
}
