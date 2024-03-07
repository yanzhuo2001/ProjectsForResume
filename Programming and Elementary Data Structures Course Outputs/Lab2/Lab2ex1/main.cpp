#include <iostream>


using namespace std;


#define RANGE 100000


bool isPrime[RANGE + 1];


void generateIsPrime() {
    int i=0;
    int m=0;
    for (i=2; i<= RANGE; i=i+1){
        if (isPrime[i]){
            for (m=2; m*i<=RANGE; m++){
                isPrime[m*i] = false;
            }
        }
    }
}


int main() {
    isPrime[0]=false;
    isPrime[1]=false;
    isPrime[2]=true;
    int i=0;
    for (i=2; i<=RANGE; i++){
        isPrime[i] = true;
    }

    generateIsPrime();


    int total_numbers=0;
    cin>>total_numbers;
    int a[20];
    int prime[20];
    int number=0;
    int j=0;
    for(i=0;i<total_numbers;i++){
        cin>>number;
        a[i]=number;
    }

    for(i=0;i<total_numbers;i++){
        if(isPrime[a[i]]){
            prime[j]=a[i];
            j++;
        }
    }

    for(i=0;i<j;i++){
        cout << prime[i] <<" ";
    }

    return 0;
}
