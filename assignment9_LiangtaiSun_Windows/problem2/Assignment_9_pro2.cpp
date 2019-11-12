#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>

#define group_cnt 1000
#define max_iteration 5000
#define mutation_rate 0.2
#define crossover_rate 0.5
#define mod 10000
using namespace std;

inline double f(double x)
{
    return x*sin(x);
}

struct number
{
    string num;
    double value;
    double fx;
    bool judge;
    double fitness;
    double fit_rate;
    number() {judge=0;}
    number (double vv)
    {
        value = vv;
        fx = f(value);
        judge = false;
    }
};

vector<number> group;
int iteration = 0;

inline number encode(double num)
{
    int left = int(fabs(num));
    double right = fabs(num) - left;
    number save(num);
    string left_code,right_code;
    if(num>=0) save.num += '0';
    else save.num += '1';
    while(left)
    {
        left_code += char('0'+left%2);
        left/=2;
    }
    for(int i=0;i<4-left_code.length();i++) save.num += '0';
    reverse(left_code.begin(), left_code.end());
    save.num += left_code;
    double right_after_dot = right - int(right);
    right_after_dot *= 10000;
    if(right_after_dot>double(2047))
    {
        right_after_dot/=10;
        save.judge = true;
    }
    int right_pro = int(right_after_dot);
    while(right_pro)
    {
        right_code += char('0'+right_pro%2);
        right_pro/=2;
    }
    for(int i=0;i<11-right_code.length();i++) save.num += '0';
    reverse(right_code.begin(),right_code.end());
    save.num += right_code;
    return save;
}

inline double decode(number save)
{
    bool judge;
    if(save.num[0]=='0') judge = true;
    else judge = false;
    string left = save.num.substr(1,4);
    string right = save.num.substr(5);
    double left_val = 0,right_val = 0;
    for(int i=0;i<4;i++)
    {
        if(left[i]=='1') left_val += pow(2,(3-i));
    }
    for(int i=0;i<11;i++)
    {
        if(right[i]=='1') right_val += pow(2,(10-i));
    }
    if(save.judge) right_val/=1000;
    else right_val /= 10000;
    double answer = left_val+right_val;
    if(judge) return answer;
    else return -1*answer;
}

inline void random_num()
{
    for(int i=0;i<group_cnt;i++)
    {
        number save;
        double ran_num = -1+16*(rand()%mod/double(mod+1));
        save = encode(ran_num);
        group.push_back(save);
    }
}

inline void fitness_calc()
{
    double fit_all = 0;
    for(int i=0;i<group.size();i++)
    {
        group[i].fitness = 1/pow(group[i].fx+15,3);
        fit_all += group[i].fitness;
    }
    for(int i=0;i<group.size();i++)
    {
        group[i].fit_rate = group[i].fitness/fit_all;
    }
}

inline void choose()
{
    vector<number> save;
    while(save.size()<group.size())
    {
        double rand_rate = rand()%mod/double(mod+1);
        double rate_cnt = 0;
        for(int i=0;i<group.size();i++)
        {
            rate_cnt += group[i].fit_rate;
            if(rate_cnt>=rand_rate)
            {
                save.push_back(group[i]);
                break;
            }
        }
    }
    group = save;
}

inline void crossover()
{
    int cnt=0;
    while(cnt++<group.size())
    {
        double rate = rand()*mod/double(mod+1);
        if(rate < crossover_rate)
        {
            while(true)
            {
                int num1,num2;
                num1 = rand()%group.size();
                do{
                    num2 = rand()%group.size();
                }while(num1==num2);
                bool flag = false;
                number save1,save2;
                save1 = group[num1];
                save2 = group[num2];
                int start,end;
                do{
                    start = rand()%16;
                    end = rand()%16;
                }while (end>start);
                save1.num = group[num1].num.substr(0,start)+group[num2].num.substr(start,end-start+1)+group[num1].num.substr(end+1);
                save2.num = group[num2].num.substr(0,start)+group[num1].num.substr(start,end-start+1)+group[num2].num.substr(end+1);
                save1.value = decode(save1);
                save2.value = decode(save2);
                if(save1.value<-1||save1.value>15||save2.value<-1||save2.value>15)
                    continue;
                save1.fx = f(save1.value);
                save2.fx = f(save2.value);
                group[num1] = save1;
                group[num2] = save2;
                break;
            }
        }
    }
}

inline void mutation()
{
    for(int i=0;i<group.size();i++)
    {
        double mut_rate = rand()%mod/double(mod+1);
        if(mut_rate<=mutation_rate)
        {
            if(group[i].num[0]=='0')
            {
                number save = group[i];
                int mut_pos = rand()%15+1;
                if(save.num[mut_pos]=='0') save.num[mut_pos]='1';
                else save.num[mut_pos] = '0';
                save.value = decode(save);
                save.fx = f(save.value);
                group[i] = save;
            }
            else{
                number save = group[i];
                int mut_pos = rand()%11+5;
                if(save.num[mut_pos]=='0') save.num[mut_pos] = '1';
                else save.num[mut_pos] = '0';
                save.value = decode(save);
                save.fx = f(save.value);
                group[i] = save;
            }
        }
    }
}

inline double print_max()
{
    int pos;
    double max_rate = 0;
    for(int i=0;i<group.size();i++)
    {
        if(group[i].fit_rate>max_rate)
        {
            max_rate = group[i].fit_rate;
            pos = i;
        }
    }
    cout << "Generation: " << iteration << " Result: " << group[pos].value << '\n';
    return group[pos].value;
}

bool terminate_or_not()
{
    double best_val = print_max();
    double fit_all = 0;
    for(int i=0;i<group.size();i++)
    {
        fit_all += group[i].value;
    }
    double avg_val = fit_all/group.size();
    if(fabs(best_val-avg_val)<1e-2) return true;
    else return false;
}
inline void run()
{
    random_num();
    fitness_calc();
    while(++iteration<=max_iteration)
    {
        choose();
        crossover();
        mutation();
        fitness_calc();
        if(terminate_or_not()) break;
    }
}
int main()
{
    srand((unsigned int)time(NULL));
    run();
    system("pause");
    return 0;
}