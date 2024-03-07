#include <iostream>
#include "mylist.h"
#include "mylist_impl.h"

using namespace std;
int main() {
    List<int> a, b;
    a.insertBack(5);
    a.insertBack(3); // a = 35
    b.insertBack(2);
    b.insertBack(4); // b = 42
    List<int> ab_sum = add(a, b); // ab_sum = 77
    ab_sum.print();
    return 0;
}
