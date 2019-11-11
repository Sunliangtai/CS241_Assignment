#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <cstring>
#include <vector>

#define max_iteration 5000
#define chromosome_num 50
#define mutaion_rate 0.1
#define mod 10000
using namespace std;

const string GENES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 1234567890,.-;:_!\"#%&/()=?@${[]}";
const int genes = GENES.length();
const string target = "Hello, World! 19/11/09";
const int length = target.length();
struct chrom
{
    string chromosome;
    int fitness;
    double fit_rate;
    chrom() {}
    chrom(string cc):chromosome(cc) {fitness=fit_rate=0;}
    chrom(string cc,int ff,int rr):chromosome(cc),fitness(ff),fit_rate(rr) {}
};


vector<chrom> all_chrom;
int iteration=0;

inline void random_str()
{
    all_chrom.clear();
    for(int i=0;i<chromosome_num;i++)
    {
        string save;
        for(int j=0;j<length;j++)
        {
            int pos = rand()%genes;
            save += GENES[pos];
        }
        all_chrom.push_back(chrom(save));
    }
}

inline void fitness_calc()
{
    int fitness_all = 0;
    for(int i=0;i<all_chrom.size();i++)
    {
        all_chrom[i].fitness = 0;
        for(int j=0;j<length;j++)
        {
            if(all_chrom[i].chromosome[j]==target[j]) all_chrom[i].fitness++;
        }
        fitness_all += all_chrom[i].fitness;
    }
    for(int i=0;i<all_chrom.size();i++)
    {
        all_chrom[i].fit_rate = all_chrom[i].fitness/double(fitness_all);
    }
}

inline void choose()
{
    vector<chrom> tmp;
    int cnt = 0;
    int cnt_all=0;
    for(int i=0;i<all_chrom.size();i++)
        if(all_chrom[i].fit_rate!=0) cnt_all++;
    while(cnt++<cnt_all)
    {
        double rate = (rand()%mod)/double(mod+1);
        double rate_sum = 0;
        for(int i=0;i<all_chrom.size();i++)
        {
            rate_sum+=all_chrom[i].fit_rate;
            if(rate_sum>=rate)
            {
                tmp.push_back(all_chrom[i]);
                break;
            }
        }
    }
    all_chrom = tmp;
}

inline string print_max()
{
    int position;
    double rate=0;
    for(int i=0;i<all_chrom.size();i++)
    {
        if(all_chrom[i].fit_rate>rate)
        {
            rate = all_chrom[i].fit_rate;
            position = i;
        }
    }
    cout<< "Generation: " << iteration << " String: " << all_chrom[position].chromosome << '\n';
    return all_chrom[position].chromosome;
}

inline void crossover()
{
    while (all_chrom.size()<chromosome_num)
    {
        int num1,num2;
        num1 = rand()%all_chrom.size();
        do{
            num2 = rand()%all_chrom.size();
        }while(num1==num2);
        string save;
        for(int i=0;i<length;i++)
        {
            int pos = rand()%2;
            if(all_chrom[num1].chromosome[i]==target[i])
            {
                save += all_chrom[num1].chromosome[i];
                continue;
            }
            if(all_chrom[num2].chromosome[i]==target[i])
            {
                save += all_chrom[num2].chromosome[i];
                continue;
            }
            if(rand==0) save += all_chrom[num1].chromosome[i];
            else save+= all_chrom[num2].chromosome[i];
        }
        all_chrom.push_back(chrom(save));
    }
}

inline void mutation()
{
    for(int i=0;i<all_chrom.size();i++)
    {
        double rate = rand()%mod/double(mod+1);
        if(rate<mutaion_rate)
        {
            bool flag = false;
            while(!flag)
            {
                int mut_pos = rand()%length;
                int pos = rand()%genes;
                if(all_chrom[i].chromosome[mut_pos]==target[mut_pos]) continue;
                all_chrom[i].chromosome[mut_pos] = GENES[pos];
                flag = true;
            }
        }
    }
}

void run()
{
    random_str();
    fitness_calc();
    while(++iteration<=max_iteration)
    {
        choose();
        crossover();
        mutation();
        fitness_calc();
        string max_chrom = print_max();
        if(max_chrom==target) break;
    }
}

int main()
{
    srand(time(NULL));
    run();
    system("pause");
    return 0;
}