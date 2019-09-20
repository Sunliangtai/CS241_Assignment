#include "solve.h"

void solve(double a, double b, double c)
{
    double delt = b*b-4*a*c;
    double x1 = (-b+sqrt(delt))/2/a;
    double x2 = (-b-sqrt(delt))/2/a;
    cout << x1 << " " << x2 << '\n';
}
