#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct {
    char name[16];
    int chinese_score;
    int math_score;
    int english_score;
    int total_score;
} Student;

int compare(const void* p1, const void* p2) {

    return ((*(Student*)p2).total_score-(*(Student*)p1).total_score);
}

int main() {

    int total=0;
    cin>>total;
    Student a[total];
    int i=0;
    for (i=0;i<total;i++){
        cin>>a[i].name;
        cin>>a[i].chinese_score;
        cin>>a[i].math_score;
        cin>>a[i].english_score;
    }
    for (i=0;i<total;i++){
        a[i].total_score=a[i].math_score+a[i].chinese_score+a[i].english_score;
    }

    // TODO: sort array with qsort()

    qsort(a, total, sizeof(a[0]), compare);

    // TODO: print result
    for (i=0;i<total;i++){
        cout<<a[i].name<<" "<<a[i].chinese_score<<" "<<a[i].math_score<<" "<<a[i].english_score<<endl;
    }
    return 0;
}