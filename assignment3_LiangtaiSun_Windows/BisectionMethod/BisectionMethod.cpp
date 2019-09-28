#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <fstream>

using namespace std;

double  calc_fx(double x)
{
    return 10*x*x*x-8.3*x*x+2.295*x-0.21141;
}

int main()
{
    ofstream out("BisectionMethod.txt");
    double left = 0.28516, right = 0.400912;
    double mid = (left+right)/2;
    double answer = 0.29;
    double left_value = calc_fx(left);
    double right_value = calc_fx(right);
    int time = 0;
    while(fabs(left-right)>0.00001)
    { 
        cout << "x" << time++ << ": " << mid << '\n';
        out << fabs(mid-answer) << '\n';
        double mid_value = calc_fx(mid);
        if(left_value*mid_value>0) left = mid;
        else right = mid;
        mid = (left+right)/2;
    }
    cout << "final answer:" << mid << '\n';
    out << fabs(mid-answer);
    out.close();
    system("pause");
    return 0;
}