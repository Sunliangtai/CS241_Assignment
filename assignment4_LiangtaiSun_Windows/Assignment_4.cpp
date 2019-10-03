#include <iostream>
#include <cstdlib>
#include <cmath>
#define EPS 1e-8
#define judge_end 0.001
#define max_iteration 10000
using namespace std;

int N;

bool judge_unique_Solution(double** matrix)
{
    double save[N][N+1];
    for(int i=0;i<N;i++)
        for(int j=0;j<N+1;j++)
            save[i][j] = matrix[i][j];
    for(int i=0;i<N-1;i++)
    {
        for(int j=i+1;j<N;j++)
        {
            double divider = save[j][i]/save[i][i];
            for(int k=i;k<N+1;k++)
                save[j][k] -= divider*save[i][k];
        }
    }
    bool flag = false;
    for(int i=0;i<N;i++)
        if(fabs(save[i][i]) <= EPS)
        {
            flag = true;
            break;
        }
    if(flag) return false;
    else return true;
}
void Gaussian_Elimination(double** matrix)
{
    int answer[N]={0};
    for(int i=0;i<N-1;i++)
    {
        for(int j=i+1;j<N;j++)
        {
            double divider = matrix[j][i]/matrix[i][i];
            for(int k=i;k<N+1;k++)
                matrix[j][k] -= divider*matrix[i][k];
        }
    }
     
    for(int i=N-1;i>=0;i--)
    {
        double temp = 0;
        for(int j=i+1;j<N;j++)
            temp += matrix[i][j]*answer[j];
        double save = (matrix[i][N]-temp)/matrix[i][i];
        if (save > 0 ) answer[i] = save + 0.5;
        else answer[i] = save - 0.5;
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
            judge += pow((answer[i]-answer_new[i]), 2);
        }
        judge = sqrt(judge);
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
    bool flag = judge_unique_Solution(matrix);
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
        case 1 : Gaussian_Elimination(matrix);break;
    }

    system("pause");
    return 0;
}