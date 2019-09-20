#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <cmath>

using namespace std;

class rational
{
    friend ostream& operator<<(ostream &out, const rational &r)
    {
        if(r.denominaor==1) out << r.numerator;
        else out << r.numerator << '/' << r.denominaor;
        return out;
    }
    private:
        int numerator;//分子
        int denominaor;//分母
    public:
        rational(int num=0, int den=1)
        {
            numerator = num, denominaor = den;
        }
        void set(int num=0, int den=1)
        {
            numerator = num, denominaor = den;
        }
        void approximate(rational &r)
        {
            if(r.numerator==0)
            {
                r.denominaor = 1;
                return;
            }
            int min_r = min(abs(r.numerator), abs(r.denominaor));
            for(int i=2;i<=min_r;i++)
            {
                if(abs(r.numerator)%i==0&&abs(r.denominaor)%i==0)
                {
                    r.numerator/=i;
                    r.denominaor/=i;
                    min_r = min(abs(r.numerator), abs(r.denominaor));
                    i--;
                }
            }
        }
        rational operator+(const rational r1)
        {
            rational temp(numerator*r1.denominaor+denominaor*r1.numerator, denominaor*r1.denominaor);
            approximate(temp);
            return temp;
        }
        rational operator*(const rational r1)
        {
            rational temp(numerator*r1.numerator, denominaor*r1.denominaor);
            approximate(temp);
            return temp;
        }
        rational operator-(const rational r1)
        {
            rational temp = *this + (rational(-1)*r1);
            approximate(temp);
            return temp;
        }
        rational operator/(const rational r1)
        {
            rational temp(numerator*r1.denominaor, denominaor*r1.numerator);
            approximate(temp);
            return temp;
        }
        rational& operator=(const rational &r)
        {
            numerator = r.numerator;
            denominaor = r.denominaor;
            return *this;
        }
        bool operator==(const rational &r)
        {
            if(numerator==r.numerator&&denominaor==r.denominaor)
                return true;
            else return false;
        }
};
int main()
{
    int temp;
    int start=-1;
    rational dividend[4],divisor[4],Quotient[4],Remainder[4];
    rational answer;
    for(int i=0;i<4;i++)
    {
        cin >> temp;
        if(cin.fail())
        {
            cerr << "error" << '\n';
            system("pause");
            return 0;
        }
        else {
            dividend[i].set(temp);
            if(i==0&&temp==0)
            {
                cerr << "error" << '\n';
                system("pause");
                return 0;
            }
        }
    }
    for(int i=0;i<4;i++)
    {
        cin >> temp;
        if(cin.fail())
        {
            cerr << "error";
            system("pause");
            return 0;
        }
        else 
        {
            if(temp!=0&&start==-1) start=i;
            divisor[i].set(temp);
        }
    }
    for(int i=0;i<=start;i++)
    {
        answer = dividend[i]/divisor[start];
        Quotient[i]=answer;
        for(int j=i;j<=3-start+i;j++)
        {
            dividend[j] = dividend[j] - answer*divisor[start+j-i];
        }
    }
    bool flag = false;
    for(int i=0;i<3;i++)
    {
        if(!(Quotient[i]==rational(0))&&!flag) flag = true;
        if(flag) cout << Quotient[i] << ' ';
        else continue;
    }
    cout << '\n';
    flag = false;
    for(int i=0;i<4;i++)
    {
        if(!(dividend[i]==rational(0))&&!flag) flag = true;
        if(flag) cout << dividend[i] << ' ';
        else continue;
    }
    cout << '\n';
    system("pause");
    return 0;
}