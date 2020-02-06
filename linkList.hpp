//
//  linkList.hpp
//  Operating System Lab1
//

#ifndef linkList_hpp
#define linkList_hpp
#include <iostream>
#include <stdio.h>
using namespace std;

struct listNode{
    string content;
    listNode* next;
};

class linkList{
public:
    listNode* head;
    int size;
    linkList(string s);
    linkList(){ head = NULL;};
    ~linkList(){ head = NULL;};
    void addNode(string s);
    void cleanUP();
    void deleteNode(string s);
    void deleteTwoNode(string s);
    bool isContain(string s);
};

#endif /* linkList_hpp */
