#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;

int judge_Tetrahedral(int input){
    int input1=input*6;
    int i=0;
    int j=0;
    int result=0;
    while(i<=10000000){
        j++;
        i=j*(j+1)*(j+2);
        if(i==input1){
            result=1;
            break;
        }
    }
    return result;
}

int judge_Palindrome(int input){
    int result=0;
    int copy=input;
    int x=0;
    while(copy>0){
        x = x*10+copy%10;    //sum the number reversely
        copy = copy/10;        // delete the final number of copy
    }
    if(input==x){
        result=1;
    }
    else{
        result=0;
    }
    return result;
}

int judge_Selfdividing(int input){
    int i=0;
    int j=0;
    int result=1;
    int d[8];
    for (i = 0; i < 8; i++ ){
        d[i] = -1;
    }
    int copy=input;
    while(copy/10!=0){
        d[j]=copy%10;
        copy=copy/10;
        j++;
    }
    d[j]=copy;
    for(i=0;i<8;i++){
        if(d[i]==-1){
            break;
        }
        else if(d[i]!=0){
            if ((input % d[i])!= 0) {
                result = 0;
                break;
            }
        }
        else{
            result=0;
            break;
        }
    }
//    char digit[8]={};
//    itoa(input, digit, 8);
//    for(i=0;i<8;i++) {
//        if((digit[i]-48)!=0){
//            if (input % (digit[i]-48) != 0) {
//                result = 0;
//                break;
//            }
//        }
//        else{
//            result=0;
//            break;
//        }
//    }
    return result;
}

int judge_Boring(int input){
    int copy=input;
    int result=0;
    while(copy%2==0||copy%3==0||copy%5==0){
        if(copy%2==0){
            copy=copy/2;
        }
        else if(copy%3==0){
            copy=copy/3;
        }
        else if(copy%5==0){
            copy=copy/5;
        }
    }
    if(copy==1){
        result=1;
    }
    return result;
}

void print_prompt() {
    cout << "Please enter the integer and the test number: ";
}

int main() {
    print_prompt();
    int number=0;
    int mode=0;
    int output=0;
    cin>>number;
    cin>>mode;
    while(number<=0||number>10000000||mode<1||mode>4){
        print_prompt();
        cin>>number;
        cin>>mode;
    }
    if(mode==1){
        output= judge_Tetrahedral(number);
    }
    else if(mode==2){
        output= judge_Palindrome(number);
    }
    else if(mode==3){
        output= judge_Selfdividing(number);
    }
    else if(mode==4){
        output= judge_Boring(number);
    }
    cout<<output<<endl;
    return 0;
}
