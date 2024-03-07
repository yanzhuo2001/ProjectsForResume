#include <string>
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char *argv[]) {
    const char *a[1]={"help"};
    const char *b[2]={"help","add"};
//    const char* aa=a[0];
//    const char* bb=b[0];
    int judge=0;
    if(strcmp(a[0],b[0])==0){
        judge=1;
    }
    cout<<judge<<endl;
    return 0;
}