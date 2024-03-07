//
// Created by 16979 on 2022/6/25.
//
#include "plugin.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <unistd.h>
#include <sys/wait.h>

class Add : public Plugin{
public:
    Add() : Plugin() {
        this->name = "add";
        this->author = "Meual";
        this->description = "add two integers";
        this->help = "Usage: add <integer> <integer>";
    }
    string response(const string &str) const override {
        stringstream ss(str);
        string buffer;
        int number1;
        int number2;
        ss >> buffer >> number1 >> number2;
        int result;
        result=number1+number2;
        string final=to_string(result);
        return final;
    }
    int matchRule(const string &str) const override {
        if ((str[0]=='a')&&(str[1]=='d')&&(str[2]=='d')&&(str[3]==' ')){
            return 1;
        }
        else{
            return 0;
        }
    }
    string toString() const override {
        string output = "Add operations is great --Meual";
        return output;
    }
};

extern "C" Plugin *create() {
    return new Add();
}

extern "C" int *destroy(Plugin *p) {
    delete p;
    return 0;
}