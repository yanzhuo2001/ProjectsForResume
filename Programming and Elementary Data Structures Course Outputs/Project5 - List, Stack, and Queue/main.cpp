#include <algorithm>
#include <iostream>
#include <string>
#include "Dlist.h"
#include "Instr.h"

using namespace std;
const int M = 16;

class Stack{
private:
    Dlist<int> ope;
public:
    Stack();
    void push(int* x);
    int* pop();
    void print() const;
};

Stack::Stack() {
    Dlist<int> a;
    ope = a;
}

void Stack::push(int *x) {
    ope.insertBack(x);
}

int *Stack::pop() {
    return ope.removeBack();
}

void Stack::print() const {
    cout << ope << endl;
}

class Queue{
private:
    Dlist<Instr> instr;
public:
    Queue();
    void push(Instr* x);
    Instr* pop();
    void print() const;
};

Queue::Queue() {
    Dlist<Instr> a;
    instr = a;
}

void Queue::push(Instr* x) {
    instr.insertBack(x);
}

Instr *Queue::pop() {
    return instr.removeFront();
}

void Queue::print() const {
    cout << instr << endl;
}

void init(Stack & ops,Queue & instrs,int* mem){
    int n,m;
    int i;
    cin>>n;
    cin>>m;
    for (i=0; i<n; i++){
        int* op = new int;
        cin >> *op;
        ops.push(op);
    }
    for (i=0; i<m; i++){
        auto* it = new Instr;
        cin >> *it;
        instrs.push(it);
    }
    for (i=0; i<M; i++){
        cin >> mem[i];
    }
}

bool process(Stack & ops,Queue & instrs,Instr* it,int* mem){
    if (it->name==InstrName::HALT){
        return false;
    }
    if (it->name==InstrName::ADD){
        int* num1 = ops.pop();
        int* num2 = ops.pop();
        int* sum = new int(*num1+*num2);
        ops.push(sum);
        delete num1;
        delete num2;
    }
    else if (it->name==InstrName::NOR){
        int* num1 = ops.pop();
        int* num2 = ops.pop();
        int* result = new int(~(*num1|*num2));
        ops.push(result);
        delete num1;
        delete num2;
    }
    else if (it->name==InstrName::IFZ){
        int* num = ops.pop();
        if (*num==0){
            for (int i=0; i<it->parameter; i++){
                Instr* temp = instrs.pop();
                delete temp;
            }
        }
        delete num;
    }
    else if (it->name==InstrName::LOAD){
        int* num = ops.pop();
        ops.push(new int(mem[*num]));
        delete num;
    }
    else if (it->name==InstrName::STORE){
        int* address = ops.pop();
        int* value = ops.pop();
        mem[*address] = *value;
        delete address;
        delete value;
    }
    else if (it->name==InstrName::POP){
        int* temp = ops.pop();
        delete temp;
    }
    else if (it->name==InstrName::PUSHI){
        ops.push(new int(it->parameter));
    }
    else if (it->name==InstrName::NOOP) {

    }
    return true;
}

int main(int argc, char *argv[]){
    Stack ops;
    Queue instr;
    int i;
    int mem[M];
    init(ops,instr,mem);
    if (argc==2){
        while (true){
            Instr* it = instr.pop();
            bool flag = process(ops,instr,it,mem);
            delete it;
            if (!flag){
                break;
            }
        }
        ops.print();
        for (i=0; i<M; i++){
            cout << i << " ";
        }
        cout << endl;
    }
    else if (argc==1){
        while (true){
            Instr* it = instr.pop();
            bool flag = process(ops,instr,it,mem);
            cout << *it << endl;
            ops.print();
            instr.print();
            for (i=0; i<M; i++){
                cout << mem[i] << " ";
            }
            cout << endl;
            delete it;
            if (!flag){
                break;
            }
        }
    }
    return 0;
}
