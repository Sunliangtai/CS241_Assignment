#include "solve.h"

class Illegal_input {};
class Less_than_zero {};
int main()
{
    try{
        double a,b,c;
        cin >> a >> b >> c;
        if(cin.fail()) throw Illegal_input();
        if(a==0) throw Illegal_input();
        if((b*b-4*a*c)<0) throw Less_than_zero();

        solve(a,b,c);
        return 0;
    }catch(Illegal_input)
    {
        cerr << "Illegal inputs!";
        exit(0);
    }
    catch(Less_than_zero)
    {
        cerr << "b^2-4ac is less than zero!";
        exit(0);
    }
    return 0;
}
