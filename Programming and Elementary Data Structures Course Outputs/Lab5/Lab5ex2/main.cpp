#include "standardForm.h"
#include "standardForm.cpp"
#include <iostream>
#include <iomanip>


using namespace std;
int main() {
    float a1, b1, c1, x;
    std::cin >> a1 >> b1 >> c1 >> x;

    float a2, b2, c2;
    std::cin >> a2 >> b2 >> c2;

    QuadraticFunction f(a1, b1, c1);
    QuadraticFunction g(a2, b2, c2);

    cout << setprecision(1) << fixed;
    cout << "f(x)=" << f.getA() << "x^2+" << f.getB() << "x+" << f.getC() << endl;
    cout << "f(" << x << ")=" << f.evaluate(x) << endl;

    Root root1 = f.getRoot();
    cout << "f(x) has " << root1.realRootNum << " real roots." << endl;
    cout << "x1 = " << root1.roots[0].real << " + " << root1.roots[0].imaginary << "i" << endl;
    cout << "x2 = " << root1.roots[1].real << " + " << root1.roots[1].imaginary << "i" << endl;

    cout << f.intersect(g) << std::endl;
}