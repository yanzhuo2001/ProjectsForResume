#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct apple{
    string name;
    float money;
    float weight;
    float price;
};


int main(int argc,char* argv[]) {
    string filename;
    filename=argv[1];
    ifstream fin;
    fin.open(filename);
    int line=1;
    char c;
    while(fin.get(c)){ //to get the number of lines
        if(c=='\n'){
            line++;
        }
    }
    fin.close();
    fin.open(filename);
    apple a[line];
    int i=0;
    for(i=0;i<line;i++){
        fin>>a[i].name;
        fin>>a[i].money;
        fin>>a[i].weight;
    }
    for(i=0;i<line;i++){
        a[i].price=(a[i].money/ a[i].weight);
    }
    int signal=0;
    for(i=1;i<line;i++){
        if(a[i].price<=a[signal].price){
            signal=i;
        }
    }
    cout.setf(ios::fixed);
    cout<<a[signal].name<<" "<<fixed<< setprecision(2)<<a[signal].money<<" "<<fixed<< setprecision(2)<<a[signal].weight<<endl;

    fin.close();

    return 0;
}
