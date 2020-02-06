//
//  linkList.cpp
//  Operating System Lab1
//
//

#include "linkList.hpp"

linkList::linkList(string s){
    listNode* node = new listNode;
    node->content = s;
    node->next = NULL;
    head = node;
}

void linkList::addNode(string s){
    listNode* node = new listNode;
    node->content = s;
    node->next = NULL;
    if(head == NULL){
        head = node;
        return;
    }
    listNode* list = head;
    while(list->next!= NULL){
        list = list->next;
    }
    list->next = node;
}

void linkList::cleanUP(){
    head = NULL;
}

void linkList::deleteNode(string s){
    listNode* pre = head;
    listNode* del = head->next;
    if(!isContain(s))
        return;
    if(head->content == s){
        head = head->next;
        return;
    }
    else{
        while(del != NULL){
            if(del->content == s)
                pre->next = del->next;
            pre = pre -> next;
            del = del -> next;
        }
    }
}

void linkList::deleteTwoNode(string s){
    if(!isContain(s))
        return;
    listNode* pre = head;
    listNode* del = head->next;
    if(head->content == s){
        head = head ->next->next;
        return;
    }
    while(del != NULL){
        if(del->content == s){
            pre ->next = del ->next -> next;
            return;
        }
        pre = pre -> next;
        del = del -> next;
    }
}

bool linkList::isContain(string s){
    listNode* ifcontain = head;
    while(ifcontain != NULL){
        if(ifcontain -> content == s)
            return true;
        ifcontain = ifcontain -> next;
    }
    return false;
}
