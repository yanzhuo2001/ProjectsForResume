/*
 * This is an exercise of VE280 Lab 1, SU2022.
 */

#include <iostream>
using namespace std;


// EFFECTS: return the trace of the Laplacian of the weight matrix.
int traceLaplacian(int weight[][50], int size){
    int D[50][50]={};
    int L[50][50]={};
    int i=0;
    int j=0;
    int tr=0;
    if (size!=0){
        for (i = 0; i < size; i++){
            for (j = 0; j < size; j++){
                D[i][i]=D[i][i]+weight[i][j];
            }
        }
        for (i = 0; i < size; i++){
            for (j = 0; j < size; j++){
                L[i][j]=D[i][j]-weight[i][j];
            }
        }
        for (i = 0; i < size; i++){
            tr=L[i][i]+tr;
        }
    }
    else{
        tr=0;
    }
    return tr;
}


int main(){
    int size, trace;
    int weight[50][50] = {};
    cin >> size;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            cin >> weight[i][j];
    trace = traceLaplacian(weight, size);
    cout << trace << endl;
}
