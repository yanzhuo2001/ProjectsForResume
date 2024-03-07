#include <iostream>
#include <cstring>


using namespace std;

bool isValidPassword(char password[]) {
    int judge=0;
    int coutera=0;//count the number of abcd
    int couterb=0;//count the number of number
    int couterc=0;//count the number of others
    int i=0;
    int l=strlen(password);
    for(i=0;i<l;i++){
        if((password[i]>=65&&password[i]<=90)||(password[i]>=97&&password[i]<=122)){
            coutera++;
        }
        else if(password[i]>=48&&password[i]<=57){
            couterb++;
        }
        else if(password[i]==' '){
            continue;
        }
        else{
            couterc++;
        }
    }
    if(coutera!=0&&couterb!=0&&couterc!=0){
        judge=1;
    }
    return judge;
}

int main() {
    char password[50]={};
    cin>>password;
    cout << isValidPassword(password) << endl;
    return 0;
}
