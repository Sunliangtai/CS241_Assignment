#include <iostream>
#include <stdlib.h>
#include <iomanip>
using namespace std;

class NewtonInterpolation
{
    private:
        int num=7;
        double Table_x[7]={0.1, 0.4, 1.0, 1.8, 2.9, 3.2, 3.8};
        double Table_fx[7]={4.2, 3.8, 2.5, 2.0, -2.0, 0.0, -0.3};
        double divided_difference_table[7][7];
    public:
        void DividedDifferenceTable()
        {
            for(int i=0;i<num;i++)
                divided_difference_table[i][0]=Table_fx[i];
            for(int i=1;i<num;i++)
                for(int j=i;j<num;j++)
                {
                    divided_difference_table[j][i] = (divided_difference_table[j][i-1]-divided_difference_table[j-1][i-1])/(Table_x[j]-Table_x[j-i]);
                }
            for(int i=0;i<num;i++)
            {
                for(int j=0;j<=i;j++)
                    cout << left << setw(12) << divided_difference_table[i][j];
                cout << '\n';
            }
        }
        void ApproximateValue(double x)
        {
            double answer=divided_difference_table[0][0];
            double temp;
            for(int i=1;i<num;i++)
            {
                temp=divided_difference_table[i][i];
                for(int j=0;j<i;j++)
                {
                    temp*=(x-Table_x[j]);
                }
                answer += temp;
            }
            cout << setprecision(5) << fixed << answer << '\n';
        }
};
int main()
{
    NewtonInterpolation solve;
    solve.DividedDifferenceTable();
    double temp;
    cout << "Input:";
    cin >> temp;
    while(!cin.fail())
    {
        solve.ApproximateValue(temp);
        cout << "Input:";
        cin >> temp;
    }
    system("pause");
    return 0;
}