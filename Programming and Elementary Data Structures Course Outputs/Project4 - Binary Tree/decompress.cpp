//
// Created by 16979 on 2022/7/14.
//
#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[]) {
    //----------------------------------------determine the path for each character-----------------------------------//
    int i;
    string treeFile,binaryFile;
    treeFile=argv[1];
    binaryFile=argv[2];
    HuffmanTree hTree(treeFile);
    char temp;
    string temp2;
    vector<string> path;
    vector<char> letters;
    char a='a';
    for(i=0;i<26;i++){
        letters.push_back(a);
        a=a+1;
    }
    letters.push_back('\n');
    letters.push_back(' ');
    for(i=0;i<letters.size();i++){                            //find path for each 字母，如果不存在也没关系，path[i]变成-1而已
        temp2=letters[i];
        path.push_back(hTree.findPath(temp2));
    }

    //--------------------------------------------decompress the binary code in binaryFile----------------------------//
    ifstream fin1(binaryFile,ios::in);
    vector<char> wholeFile;
    while(fin1.get(temp)){                               //store the whole binary file letter by letter
        wholeFile.push_back(temp);
    }
    string paths;                                           //The path for each letter
    int j;
    for(i=0;i<wholeFile.size();i++){                        //when the letter is not ' ' or '\n', then store the data into paths
        if((wholeFile[i]!=' ')&&(wholeFile[i]!='\n')){      //binary文件中的空格和换行直接忽略了，每次循环之后清空path，每次一个字符一个字符的往path里塞东西直到遇到空格或者换行
            paths.push_back(wholeFile[i]);
        }
        else{
            for(j=0;j<path.size();j++){                     //和所有可能的字母的findpath有一样的时候就输出对应的letter
                if(path[j]==paths){
                    cout<<letters[j];
                }
            }
            while(!paths.empty()){
                paths.pop_back();                           //resize paths to 0
            }
        }
    }
    fin1.close();
}