//
// Created by 16979 on 2022/7/19.
//

#ifndef INTLIST_IMPL_H
#define INTLIST_IMPL_H

#include <iostream>
#include "mylist.h"

template<class T>
void List<T>::removeAll() {
    Node_t<T> * temp;
    while(first!= nullptr){
        temp=first;
        first=first->next;
        delete temp;
    }
    first = last = nullptr;
}

template <class T>
void List<T>::copyFrom(const List<T> &l)
{
    first = nullptr;
    last = nullptr;
    Node_t<T>* current = l.first;
    while (current!=nullptr)
    {
        insertBack(current->val);
        current = current->next;
    }
}

template<class T>
bool List<T>::isEmpty() const {
    if(first== nullptr){
        return true;
    }
    else{
        return false;
    }
}

template<class T>
void List<T>::insertBack(T val) {
    Node_t<T> * add=new Node_t<T>{nullptr,val};
    if(isEmpty()){
        first=add;
    }
    else if(last== first){
        first->next = add;
    }
    else{
        last->next=add;
    }
    last=add;
}

template<class T>
T List<T>::removeFront() {
    if (isEmpty())
        throw EmptyList();
    else{
        T result = first->val;
        Node_t<T>* p = first;
        first = first->next;
        delete p;
        return result;
    }
}

template<class T>
const Node_t<T> *List<T>::returnFront() const {
    return first;
}

template <class T>
void List<T>::print()
{
    Node_t<T>* itr = first;
    while(itr){
        std::cout << itr->val;
        itr = itr->next;
    }
    std::cout << "\n";
}

template<class T>
List<T>::List() {
    first=nullptr;
    last= nullptr;
}

template<class T>
List<T>::List(const List &l) {
    copyFrom(l);
}

template<class T>
List<T> & List<T>::operator=(const List<T> &l)
{
    removeAll();
    copyFrom(l);
    return *this;
}

template<class T>
List<T>::~List() {
    removeAll();
}

bool isLarger(const List<int> &a, const List<int> &b)
{
    bool result;
    int judge=0;
    List<int> L1(a);
    List<int> L2(b);
    const Node_t<int> *pa=L1.returnFront();
    const Node_t<int> *pb=L2.returnFront();
    while (pa!=nullptr && pb!=nullptr){
        int temp1 = L1.removeFront();
        int temp2 = L2.removeFront();
        if (temp1 < temp2){
            judge=1;
        }
        else if (temp1 > temp2){
            judge=0;
        }
        pa=L1.returnFront();
        pb=L2.returnFront();
    }
    if (pa==nullptr && pb==nullptr){
        if(judge==1){
            result= false;
        }
        else{
            result= true;
        }
    }
    else if (pa==nullptr){
        result= false;
    }
    else{
        result= true;
    }
    return result;
}

void calculateCarry(List<int> & result,int * pc,const int & sum)
{
    if (sum >= 10){
        result.insertBack(sum-10);
        *pc = 1;
    }
    else{
        result.insertBack(sum);
        *pc = 0;
    }
}

List<int> add(const List<int> &a, const List<int> &b)
{
    List<int> result;
    List<int> cpA(a); List<int> cpB(b);
    int carry = 0;
    int *pc=&carry;
    int sum;
    while (cpA.returnFront()!=nullptr && cpB.returnFront()!=nullptr){
        sum=cpA.removeFront() + cpB.removeFront() + carry;
        calculateCarry(result,pc,sum);
    }
    if (cpA.returnFront()==nullptr && cpB.returnFront()==nullptr){
        if (carry==1){
            result.insertBack(1);
        }
    }
    else if (cpA.returnFront()==nullptr){
        while (cpB.returnFront()!=nullptr){
            sum=cpB.removeFront() + carry;
            calculateCarry(result,pc,sum);
        }
        if (carry==1){
            result.insertBack(1);
        }
    }
    else{
        while (cpA.returnFront()!=nullptr){
            sum=cpA.removeFront() + carry;
            calculateCarry(result,pc,sum);
        }
        if (carry==1){
            result.insertBack(1);
        }
    }
    return result;
}

#endif //INTLIST_IMPL_H
