#include <iostream>
#include "ex1.h"

int dot(list_t v1, list_t v2){
    int outcome=0;
    int i;
    list_t v11=v1;
    list_t v22=v2;
    list_t v3=v1;
    list_t v4=v2;
    int counter1=0;
    int counter2=0;
    if(list_isEmpty(v1)|| list_isEmpty(v2)){
        outcome=0;
    }
    else{
        while(!list_isEmpty(v3)){
            v3= list_rest(v3);
            counter1++;
        }
        while(!list_isEmpty(v4)){
            v4= list_rest(v4);
            counter2++;
        }
        int n1[counter1];
        int n2[counter2];
        for(i=0;i<counter1;i++){
            n1[i]= list_first(v11);  //let v11 decreases one int for each i, and let this int store in the n1[i]
            list_rest(v11);
        }
        for(i=0;i<counter2;i++){
            n2[i]= list_first(v22);
            list_rest(v22);
        }
        if(counter1>counter2) {
            for (i = 0; i < counter2; i++) {
                outcome += n1[i] * n2[i];
            }
        }
        else{
            for(i=0;i<counter1;i++){
                outcome += n1[i]*n2[i];
            }
        }
    }
    return outcome;
}

list_t filter(list_t list, bool (*fn)(int)){
    int i;
    list_t listResult;
    listResult=list_make();
    list_t v1=list;
    list_t v3=list;
    int counter1=0;
    while(!list_isEmpty(v3)){   //count the number of elements in list
        v3= list_rest(v3);
        counter1++;
    }
    int n1[counter1];
    for(i=0;i<counter1;i++){
        n1[i]= list_first(v1);  //let v1 decreases one int for each i, and let this int store in the n1[i]
        list_rest(v1);
    }
    for(i=0;i<counter1;i++){
        if(fn(n1[i])){
            list_make(n1[i],listResult);
        }
    }
    return listResult;
}

bool is_palindrome_list(list_t list){
    bool result=false;
    int i;
    if(list_isEmpty(list)){
        result = true;
    }
    else {

        list_t v1=list;
        list_t v3=list;
        int counter1=0;
        while(!list_isEmpty(v3)){   //count the number of elements in list
            v3= list_rest(v3);
            counter1++;
        }
        if(counter1==1){
            result= true;
        }
        else{
            int n1[counter1];
            for(i=0;i<counter1;i++){
                n1[i]= list_first(v1);  //let v1 decreases one int for each i, and let this int store in the n1[i]
                list_rest(v1);
            }
            for(i=0;i<counter1;i++){
                if(n1[i]!=n1[counter1-1-i]){
                    result= false;
                    break;
                }
            }
        }
    }
    return result;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
