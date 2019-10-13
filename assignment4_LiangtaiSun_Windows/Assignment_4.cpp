#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define EPS 1e-8
#define judge_end 0.001
#define max_iteration 10000
using namespace std;

int N;

bool judge_unique_Solution(double** matrix)
{
    double minimum = 0x7fffffff;
    int min_x = -1;
    for(int i=0;i<N-1;i++)
    {
        min_x = -1;
        minimum = 0x7fffffff;
        for(int j=i;j<N;j++)
        {
            if(matrix[j][i]!=0&&fabs(matrix[j][i])<minimum)
            {
                min_x = j;
                minimum = fabs(matrix[j][i]);
            }
        }
        if(min_x==-1) return false;
        else if(min_x!=i)
        {
            double temp;
            for(int k=i;k<=N;k++)
            {
                temp = matrix[i][k];
                matrix[i][k] = matrix[min_x][k];
                matrix[min_x][k] = temp;
            }
        }
        for(int j=i+1;j<N;j++)
        {
            double divider = matrix[j][i]/matrix[i][i];
            for(int k=i;k<N+1;k++)
            {
                matrix[j][k] -= divider*matrix[i][k];
                if(fabs(matrix[j][k])<EPS) matrix[j][k] = 0;
            }
        }
    }
    bool flag = false;
    for(int i=0;i<N;i++)
        if(fabs(matrix[i][i]) <= EPS)
        {
            flag = true;
            break;
        }
    if(flag) return false;
    else return true;
}
void Gaussian_Elimination(double** matrix)
{
    float answer[N]={0};
    for(int i=N-1;i>=0;i--)
    {
        double temp = 0;
        for(int j=i+1;j<N;j++)
            temp += matrix[i][j]*answer[j];
        answer[i] = (matrix[i][N]-temp)/matrix[i][i];
    }
    cout << '\n' << "Results is: " << '\n';
    for(int i=0;i<N;i++)
        cout << answer[i] << ' ';
}
void Jacobi_Iteration(double** matrix)
{
    int iteration_time = 0;
    double answer[N]={0};
    double answer_new[N]={0};
    cout << '\n' << "Input the initial approximation x(0):" << '\n';
    for(int i=0;i<N;i++) cin >> answer[i];
    double judge = 0;
    do{
        if(iteration_time>max_iteration)
        {
            cerr << "Maximum number of iterations exceeded!";
            return;
        }
        for(int i=0;i<N;i++)
        {
            double temp = matrix[i][N];
            for(int j=0;j<N;j++)
            {
                if(j==i) continue;
                temp -= matrix[i][j]*answer[j];
            }
            answer_new[i] = temp/matrix[i][i];
        }
        judge = 0;
        for(int i=0;i<N;i++)
        {
            judge = max(fabs(answer[i]-answer_new[i]), judge);
        }
        iteration_time++;
        for(int i=0;i<N;i++)
            answer[i] = answer_new[i];
    }while(judge>=judge_end);
    cout << "Results is:" << '\n';
    for(int i=0;i<N;i++)
        cout << answer[i] << ' ';
}

int main()
{
    cout << "Input the number of equations and unknowns n: ";
    cin >> N;
    if(cin.fail())
    {
        cerr << "Invalid input!" << '\n';
        system("pause");
        return 0; 
    }
    cout << '\n' << "Input the augmented matrix of Ax=b as [A b]:" << '\n';
    double *matrix[N];
    for(int i=0;i<N;i++) matrix[i] = new double[N+1];
    int answer[N]={0};
    for(int i=0;i<N;i++)
        for(int j=0;j<N+1;j++)
            cin >> matrix[i][j];
    if(cin.fail())
    {
        cerr << "Invalid input!" << '\n';
        system("pause");
        return 0; 
    }
    cout << '\n';
    double *save[N];
    for(int i=0;i<N;i++) save[i] = new double[N+1];
    for(int i=0;i<N;i++)
        for(int j=0;j<N+1;j++)
            save[i][j] = matrix[i][j];
    bool flag = judge_unique_Solution(save);
    if(!flag)
    {
        cerr << "No unique solution exists!" << '\n';
        system("pause");
        return 0;
    }
    cout << "[0] Jacobi Iteration  [1] Gaussian Elimination" << '\n';
    cout << "Choose a method: ";
    int choose;
    cin >> choose;
    if(cin.fail())
    {
        cerr << "Invalid input!" << '\n';
        system("pause");
        return 0; 
    }
    switch(choose)
    {
        case 0 : Jacobi_Iteration(matrix);break;
        case 1 :  Gaussian_Elimination(save);break;
    }
    system("pause");
    return 0;
}