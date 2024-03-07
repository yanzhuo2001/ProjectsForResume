#include <iostream>

using namespace std;

const int MAXSIZE = 10;
int n=-1;
int the_position_opened[10];

bool canWin(int count, const int arr[], int position) {
    n++;
    int judge;
    int judge1=0;
    int judge2=0;
    int p=position;
    int v=arr[p];    //v is the value at arr[p]
    the_position_opened[n]=position;
    for(int i=0;i<n;i++){     //judge if the position p+v and p-v have both been opened
        if(the_position_opened[i]==(p+v)){
            judge1=1;
        }
        if(the_position_opened[i]==(p-v)){
            judge2=1;
        }
    }
    judge=judge1+judge2;      //if judge==2, then recursion stops
    if(v==280){
        return true;
    }
    else if ((((p+v)>count||(p+v)<0)&&((p-v)>count||(p-v)<0))||(judge==2)){  //if both p+v and p-v are outside the range, then recursion stops
        return false;
    }
    else if(((p+v)>count)||((p+v)<0)){
        canWin(count,arr, p-v);
    }
    else if(((p-v)>count)||((p-v)<0)){
        canWin(count,arr, p+v);
    }
    else{
        canWin(count,arr, p+v);
        canWin(count,arr, p-v);
    }
    return true;

}

int main() {
    int count;
    cin >> count;
    int arr[MAXSIZE];
    for (int i = 0; i < count; ++i) {
        cin >> arr[i];
    }
    int position;
    cin >> position;

    cout << canWin(count, arr, position);
}
