//
// Created by 16979 on 2022/7/28.
//

#ifndef __DLISTIMPL_H__
#define __DLISTIMPL_H__

#include "Dlist.h"

template <class T>
bool Dlist<T>::isEmpty() const{
    bool judge=false;
    if (first==nullptr){
        judge=true;
    }
    return judge;
}

template <class T>
void Dlist<T>::insertFront(T* op){
    node* newnode = new node{nullptr, nullptr, op};
    if (isEmpty()){ // When list is empty, create a new node
        first=newnode;
        last=newnode;
    }
    else if (first==last){// When there is only one node in list, set first as a new node whose previous is nullptr and update last's previous
        newnode->next=last;
        first=newnode;
        last->prev =newnode;
    }
    else{// When more than one node in list, set first's previous to be a new node whose next is first and set first as the new node
        newnode->next=first;
        first->prev=newnode;
        first=newnode;
    }
}

template <class T>
void Dlist<T>::insertBack(T *op){
    node* newnode = new node{nullptr,nullptr,op};
    if (isEmpty()){// When list is empty, create a node whose nest and previous are both nullptr
        first=newnode;
        last=newnode;
    }
    else if (first==last){// When there is only one node is list, set last as a new node whose next is nullptr and update first's next
        newnode->prev=first;
        last=newnode;
        first->next=newnode;
    }
    else{// When more than one node in list, set last's next to be a new node whose previous is last and set last as the new node
        newnode->prev=last;
        last->next=newnode;
        last=newnode;
    }
}

template <class T>
T* Dlist<T>::removeFront(){
    if (isEmpty()){
        throw EmptyList();
    }
    else{
        T* temp=first->op; // Hold the pointer to op
        node* hold=first; // Hold first
        if (first==last){// When only one node in list, just set first and last to be nullptr
            first=nullptr;
            last=nullptr;
        }
        else{// When more than one node in list, set first to the next of current first and the previous of it to nullptr
            first=first->next;
            first->prev = nullptr;
        }
        delete hold;
        return temp;
    }
}

template <class T>
T* Dlist<T>::removeBack(){
    if (isEmpty()){
        throw EmptyList();
    }
    else{
        T* temp=last->op; // Hold the pointer to op
        node* hold=last; // Hold last
        if (first==last){// When only one node in list, just set first and last to be nullptr
            last=nullptr;
            first=nullptr;
        }
        else{
            // When more than one node in list, set last to the prev of current last and the next of it to nullptr
            last=last->prev;
            last->next=nullptr;
        }
        delete hold;
        return temp;
    }
}

template <class T>
Dlist<T>::Dlist(){
    first=nullptr;
    last=nullptr;
}

template <class T>
Dlist<T>::Dlist(const Dlist<T> & l){
    copyAll(l);
}

template <class T>
Dlist<T> & Dlist<T>::operator=(const Dlist<T> &l){
    removeAll(); // Remove all existing nodes first
    copyAll(l);
    return *this;
}

template <class T>
Dlist<T>::~Dlist(){
    removeAll();
}

template <class T>
void Dlist<T>::removeAll(){
    node* current=first;
    node* next=nullptr; // Store the next node of cur
    while (current != nullptr){
        next = current->next;
        delete current->op;
        delete current;
        current = next;
    }
    first=nullptr;
    last=nullptr;// Set the list as empty
}

template <class T>
void Dlist<T>::copyAll(const Dlist<T> & l){
    first=nullptr;
    last=nullptr;
    node* cur=l.first;
    while (cur!=nullptr){
        T* op=new T(*cur->op);
        insertBack(op); // The pointer must be a deep copy of op
        cur=cur->next;
    }
}

#endif
