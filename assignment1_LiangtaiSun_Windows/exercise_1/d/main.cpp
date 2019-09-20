#include <iostream>
#include <iomanip>
#include <stdlib.h>
using namespace std ;

double ctok(double);
int main ()
{
    double c = 0; // declare input variable
    cout << " Celsius : ";
    cin >> c ; // retrieve temperature to input variable
    double k = ctok (c) ; // convert temperature
    cout <<  " Kelvin : "<< k ; // print out temperature
    return 0;
}

double ctok (double c ) // converts Celsius to Kelvin
{
    if(c<-273.15)
    {
        cerr << "Error reporting!" ;
        exit(0);
    }
    else
    {
        double k = c + 273.15;
        return k ;
    }
}
