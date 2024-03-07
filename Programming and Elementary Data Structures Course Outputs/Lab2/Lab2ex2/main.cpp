#include <cmath>
#include <iostream>

using namespace std;

#define MAX_LEN 1024

int square[MAX_LEN][MAX_LEN];

void initSquare(int len) {
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            square[i][j] = 1;
        }
    }
}

// REQUIRES: the square with left-upper corner at (x,y)
//           and length len is within square[MAX_LEN][MAX_LEN]
// MODIFIES: square[y][x]
// EFFECTS: fully update the specified square
void updateSquare(int x, int y, int len) {
    int i=0;
    int ii=0;
    int l=len/2;//length of small square, when l=1, the loop should stop
    int j=y;//number of small square in one line
    int jj=0;
    int jjj=0;
    for(i=x;i<len;i++){
        for(ii=x;ii<len;ii++) {
            square[len - ii-1][i] = 0;
        }
    }
    int x1=x;
    int y0=x1;
    int x11=x1;
    int y00=x1;
    while(l!=0){
        l=l/2;
        j=j*2;
        x11=x1;
        y00=x1;//=4
        for(jjj=0;jjj<j;jjj++){
            for(jj=0;jj<j;jj++){
                for(i=x11-l;i<x11;i++){
                    for(ii=y00-l;ii<y00;ii++){
                        square[abs(len - ii -1)][i]=0;
                    }
                }
                x11=x11+x1;
            }
            x11=x1;
            y00=y00+y0;
        }
        x1=x1/2;
        y0=y0/2;
    }
}

void printSquare(int len) {
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            cout << square[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n=0;


    cin>>n;
    int len=pow(2,n);

    int x=len/2;
    int y=1;

    initSquare(len);
    updateSquare(x,y,len);
    printSquare(len);



    return 0;
}

