//
// Created by 16979 on 2022/7/10.
//

#include "node.h"
#include <iostream>

using namespace std;

Node::Node(int _value, int _n) {
    value=_value;
    child_num=0;
    n=_n;
    parent= nullptr;
    height=0;
    children= new Node*[_n];
}

void Node::addChild(Node *child) {
    if((this->child_num)<(this->n)){
        this->children[child_num]=child;
        this->child_num++;
        Node * temp_parent = this;
        Node * temp_child = child;
        while (temp_parent != nullptr)
        {
            if (temp_parent->height - 1 < temp_child->height)
            {
                temp_parent->height = temp_child->height + 1;
            }
            temp_parent = temp_parent->parent;
            temp_child = temp_child->parent;
        }
    }
    else{
        throw tooManyChildren();
    }
}

void Node::addChild(int _value) {
    if((this->child_num)<(this->n)) {
        Node *pa = new Node(_value, n);
        pa->parent = this;
        addChild(pa);
    }
    else{
        throw tooManyChildren();
    }
}

int Node::getHeight() {
    return (this->height);
}

void Node::traverse()
{
    cout << this->value << " ";
    int i;
    for (i = 0; i <(this-> child_num); i++)
    {
        if(this->children[i]!= nullptr){
            (this->children[i])->traverse();
        }
    }
}

bool Node::isequal(Node *node1, Node *node2)
{
    bool judge1=node1 == nullptr;
    bool judge2=node2 == nullptr;
    int i;
    if (judge1 && judge2) {
        return true;
    }
    else if ((judge1&&(!judge2))||(judge2&&(!judge1))) {
        return false;
    }
    else if (node1->value != node2->value || node1->child_num != node2->child_num || node1->n != node2->n || node1->height != node2->height){
        return false;
    }
    else {
        for (i = 0; i < node1->child_num; i++)
        {
            if(!isequal(node1->children[i], node2->children[i]))
            {
                return false;
            }
        }
    }
    return true;
}

bool Node::contain_helper_compare(Node* sub, Node* root){
    int i;
    if (sub == nullptr)  {
        return true;
    }
    else if (sub != nullptr && root == nullptr) {
        return false;
    }
    else if (sub->value == root->value) {
        if (sub->n > root->n) {
            return false;
        }
        else {
            int array[root->n];
            for (i=0; i< root->n; i++){
                array[i] = contain_helper_compare(sub->children[i],root->children[i]);
            }
            for (i=0; i< root->n; i++){
                if (array[i] == 0) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

bool Node::contain_helper(Node* sub, Node* root){
    Node* current_node = root;
    if (sub == nullptr) {
        return true;
    }
    else if (sub != nullptr && root == nullptr) {
        return false;
    }
    else if (sub->value == root->value && contain_helper_compare(sub,root)) {
        return true;
    }
    else  {
        for(int i=0; i<root->child_num; ++i){
            current_node = root->children[i];
            if (contain_helper(sub, current_node)) {
                return true;
            }
        }
    }
    return false;
}

bool Node::contain(Node* sub){
    return contain_helper(sub, this);
}

Node &Node::operator[](int i) {
    if(i>=(this->child_num)||i<0){
        throw invalidIndex();
    }
    else{
        return *(this->children[i]);
    }
}

Node::~Node() {
    int i;
    for(i=0;i<this->child_num;i++){
        delete children[i];
    }
    delete [] children;
}



