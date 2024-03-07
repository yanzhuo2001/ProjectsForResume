#include "factoredForm.h"

QuadraticFunction::QuadraticFunction(float a_in, float b_in, float c_in){
    float Delta=0;
    a=a_in;
    Delta=b_in*b_in-4*a_in*c_in;
    Root finalRoot;
    if(Delta==0.0){
        finalRoot.realRootNum=1;
        finalRoot.roots[0].real=(-b_in/(2*a_in));
        finalRoot.roots[0].imaginary=0;
        finalRoot.roots[1].real=(-b_in/(2*a_in));
        finalRoot.roots[1].imaginary=0;
    }
    else if(Delta<0.0){
        float im=((sqrt(-Delta))/(2*a_in));
        finalRoot.realRootNum=0;
        finalRoot.roots[0].real=((-b_in)/(2*a_in));
        finalRoot.roots[0].imaginary=-im;
        finalRoot.roots[1].real=((-b_in)/(2*a_in));
        finalRoot.roots[1].imaginary=im;
    }
    else{
        finalRoot.realRootNum=2;
        finalRoot.roots[0].real=((-b_in-(sqrt(Delta)))/(2*a_in));
        finalRoot.roots[0].imaginary=0;
        finalRoot.roots[1].real=((-b_in+(sqrt(Delta)))/(2*a_in));
        finalRoot.roots[1].imaginary=0;
    }
    r1=finalRoot.roots[0];
    r2=finalRoot.roots[1];
}


float QuadraticFunction::getA() const {
    return a;
}

float QuadraticFunction::getB() const {
    float b1=-a*(r1.real+r2.real);
    return b1;
}

float QuadraticFunction::getC() const {
    float c=0;
    if(r1.imaginary!=0.0){
        float c1=r1.real*r2.real;
        float cc=-r1.imaginary*r2.imaginary;
        c=a*(c1+cc);
    }
    else{
        c=a*r1.real*r2.real;
    }
    return c;
}

float QuadraticFunction::evaluate(float x) {
    float result=0;
    result=getA()*x*x+getB()*x+getC();
    return result;
}

Root QuadraticFunction::getRoot() {
    Root finalRoot;
    if(r1.imaginary!=0.0){
        finalRoot.realRootNum=0;
        finalRoot.roots[0]=r1;
        finalRoot.roots[1]=r2;
    }
    else{
        if(r1.real==r2.real){
            finalRoot.realRootNum=1;
            finalRoot.roots[0]=r1;
            finalRoot.roots[1]=r2;
        }
        else{
            finalRoot.realRootNum=2;
            finalRoot.roots[0]=r1;
            finalRoot.roots[1]=r2;
        }
    }
    return finalRoot;
}

bool QuadraticFunction::intersect(QuadraticFunction q) {
    bool result=false;
    float a_f=getA();
    float a_g=q.getA();
    float b_f=getB();
    float b_g=q.getB();
    float c_f=getC();
    float c_g=q.getC();
    float newA=a_f-a_g;
    float newB=b_f-b_g;
    float newC=c_f-c_g;
    float Delta=0;
    Delta=newB*newB-4*newA*newC;
    if(Delta>=0.0){
        result=true;
    }
    else{
        result= false;
    }
    return result;
}