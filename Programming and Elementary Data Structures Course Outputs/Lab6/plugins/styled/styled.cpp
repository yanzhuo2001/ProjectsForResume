//
// Created by 16979 on 2022/6/25.
//

#include "plugin.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <unistd.h>
#include <sys/wait.h>

class Styled : public Plugin{
public:
    Styled() : Plugin() {
        this->name = "styled";
        this->author = "Second Lobster";
        this->description = "1";
        this->help = "1";
    }
    string response(const string &str) const override {
        return "You are not playing Warcraft 3, guys...";
    }
    int matchRule(const string &str) const override {
        if(str=="WhosYourDaddy"){
            return 1;
        }
        else {
            return 0;
        }
    }
    string toString() const override {
        string output = "Second Lobster writes styled because he thinks it is fun";
        return output;
    }
};

extern "C" Plugin *create() {
    return new Styled;
}

extern "C" int *destroy(Plugin *p) {
    delete p;
    return 0;
}