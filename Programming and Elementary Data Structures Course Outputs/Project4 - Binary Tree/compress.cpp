//
// Created by 16979 on 2022/7/15.
//

#include "binaryTree.h"
#include "huffmanTree.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool com1(Node* n1,Node* n2)          //to help the sort procedure, determine which node is smaller
{
    if (n1->getnum()<n2->getnum()){
        return false;
    }
    else if (n1->getnum()>n2->getnum()){
        return true;
    }
    else{
        return (n1->getstr()>n2->getstr());
    }
}

int main(int argc, char *argv[])
{
    string fileName;
    if (argc==2){
        fileName = argv[1];
    }
    else if(argc==3){
        fileName = argv[2];
    }
    ifstream fin1;
    fin1.open(fileName,ios::in);
    char ch;
    vector<Node*> nodes;                                //to store all the nodes into one vector
    while (fin1.get(ch)){
        char temp[2]={ch,'\0'};
        string s(temp);
        bool judge=true;
        int i;
        for (i=0; i<nodes.size(); i++)
        {
            if (nodes[i]->getstr()==s)             //if the node's str part is the same as s, then just add one no the num part
            {
                nodes[i]->incnum();
                judge=false;
                break;
            }
        }
        if (judge)
        {
            Node* newNode = new Node(s,1);
            nodes.push_back(newNode);
        }
    }
    fin1.close();
    while (nodes.size()>1)                                          //每次去掉两个元素加进去一个元素，每次少一个元素
    {
        sort(nodes.begin(),nodes.end(),com1);
        Node* mergedNode =Node::mergeNodes(nodes[nodes.size()-2],nodes[nodes.size()-1]);
        nodes.pop_back();
        nodes.pop_back();
        nodes.push_back(mergedNode);
    }
    HuffmanTree huffmanTree(nodes[0]);
    if (argc==3){
        huffmanTree.printTree();
    }
    else if (argc==2)
    {
        ifstream fin2;
        fin2.open(fileName,ios::in);
        while (fin2.get(ch))
        {
            char temp[2]={ch,'\0'};
            string s(temp);
            cout << huffmanTree.findPath(s) << " ";
        }
        fin2.close();
    }
    return 0;
}