#include <iostream>
#include <iomanip>

using namespace std;

double ctok(double);
int main ()
{
    double c = 0; // declare input variable
    cout << " Celsius : ";
    cin >> c ; // retrieve temperature to input variable
    if(c<-273.15) cerr << "Error reporting!";
    else
    {
        double k = ctok (c) ; // convert temperature
        cout <<  " Kelvin : "<< k; // print out temperature
    }
    return 0;
}

double ctok (double c ) // converts Celsius to Kelvin
{
    double k = c + 273.15;
    return k ;
}
