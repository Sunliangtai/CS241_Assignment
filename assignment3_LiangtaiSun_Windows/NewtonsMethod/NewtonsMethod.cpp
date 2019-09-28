#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <fstream>

using namespace std;

double calc_fx(double x)
{
    return 10*x*x*x-8.3*x*x+2.295*x-0.21141;
}
double clac_de_fx(double x)
{
    return 30*x*x-16.6*x+2.295;
}
int main()
{
    ofstream out("NewtonsMethod.txt");
    double x = 0.343036;
    double answer = 0.29;
    while (fabs(x-answer)>0.00001)
    {
        cout << x << '\n';
        out << fabs(x-answer) << '\n';
        x = x - calc_fx(x)/clac_de_fx(x);
    }
    cout << x << '\n';
    out << fabs(x-answer);
    out.close();
    system("pause");
    return 0;
}