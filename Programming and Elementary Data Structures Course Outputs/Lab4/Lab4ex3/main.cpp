#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string command;
    getline(cin,command);
    int len=command.size();
    int i=0;
    for(i=0;i<len;i++){
        if(command[i]==','){
            command[i]=' ';
        }
    }
    istringstream instr(command);
    string name;
    int count=0;
    while(instr>>name){
        cout<<name<<endl;
        count++;
    }
    cout<<count<<endl;
    return 0;
}
