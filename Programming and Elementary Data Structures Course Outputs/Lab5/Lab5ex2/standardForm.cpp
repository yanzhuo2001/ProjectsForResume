#include <cmath>
#include "standardForm.h"

QuadraticFunction::QuadraticFunction(float a_in, float b_in, float c_in){
    a=a_in;
    b=b_in;
    c=c_in;
}


float QuadraticFunction::getA() const {
    return a;
}

float QuadraticFunction::getB() const {
    return b;
}

float QuadraticFunction::getC() const {
    return c;
}

float QuadraticFunction::evaluate(float x) {
    float result;
    result=a*x*x+b*x+c;
    return result;
}

Root QuadraticFunction::getRoot() {
    float Delta=0;
    Delta=b*b-4*a*c;

    Root finalRoot;

    if(Delta==0){
        finalRoot.realRootNum=1;
        finalRoot.roots[0].real=(-b/(2*a));
        finalRoot.roots[0].imaginary=0;
        finalRoot.roots[1].real=(-b/(2*a));
        finalRoot.roots[1].imaginary=0;
    }
    else if(Delta<0){
        float im=((sqrt(-Delta))/(2*a));
        finalRoot.realRootNum=0;
        finalRoot.roots[0].real=((-b)/(2*a));
        finalRoot.roots[0].imaginary=-im;
        finalRoot.roots[1].real=((-b)/(2*a));
        finalRoot.roots[1].imaginary=im;
    }
    else{
        finalRoot.realRootNum=2;
        finalRoot.roots[0].real=((-b-(sqrt(Delta)))/(2*a));
        finalRoot.roots[0].imaginary=0;
        finalRoot.roots[1].real=((-b+(sqrt(Delta)))/(2*a));
        finalRoot.roots[1].imaginary=0;
    }
    return finalRoot;
}

bool QuadraticFunction::intersect(QuadraticFunction q){
    bool result=false;
    float a_f=a;
    float a_g=q.getA();
    float b_f=b;
    float b_g=q.getB();
    float c_f=c;
    float c_g=q.getC();
    float newA=a_f-a_g;
    float newB=b_f-b_g;
    float newC=c_f-c_g;
    float Delta=0;
    Delta=newB*newB-4*newA*newC;
    if(Delta>=0){
        result=true;
    }
    else{
        result= false;
    }
    return result;
}