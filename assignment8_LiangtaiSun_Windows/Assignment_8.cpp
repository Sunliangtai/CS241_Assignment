#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;


class LCS {
public:
    int LCS_(int i,int j)
    {
        if(result[i][j]!=-1) return result[i][j];
        if(s1[i-1]==s2[j-1]) result[i][j] = 1+LCS_(i-1,j-1);
        else result[i][j] = max(LCS_(i-1,j), LCS_(i,j-1));
        return result[i][j];
    }
    int LongestCommonSubsequence(string text1, string text2) {
        s1 = text1;
        s2 = text2;
        result = new int*[text1.size()+1];
        for(int i=0;i<=text1.size();i++) result[i] = new int[text2.size()+1];
        for(int i=0;i<=text1.size();i++) result[i][0] = 0;
        for(int i=0;i<=text2.size();i++) result[0][i] = 0;
        for(int i=1;i<=text1.size();i++)
            for(int j=1;j<=text2.size();j++)
            result[i][j] = -1;
        for(int i=1;i<=text1.size();i++)
            for(int j=1;j<=text2.size();j++)
            LCS_(i,j);
        return result[text1.size()][text2.size()];
    }
private:
    int **result;
    string s1,s2;
};


class WIS {
public:
    int WeightedIntervalScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit) {
        n = startTime.size();
        Job = new job[n];
        for(int i=0;i<n;i++)
            Job[i]=job(startTime[i], endTime[i], profit[i]);
        sort(Job, Job+n);
        int profit_sum[n];
        for(int i=0;i<n;i++) profit_sum[i] = Job[i].profit;
        for(int i=1;i<n;i++)
            for(int j=0;j<=i-1;j++)
            {
                if(Job[i].startTime>=Job[j].endTime)
                {
                    if(profit_sum[j]+Job[i].profit>profit_sum[i])
                        profit_sum[i] = profit_sum[j]+Job[i].profit;
                }
            }
        int maximum_profit = 0;
        for(int i=0;i<n;i++)
            if(profit_sum[i]>maximum_profit) maximum_profit=profit_sum[i];
        return maximum_profit;
    }
private:
    struct job
    {
        int startTime, endTime;
        int profit;
        job() {startTime=endTime=profit=0;}
        job(int ss,int ee,int pp):startTime(ss), endTime(ee), profit(pp) {}
        bool operator<(const job&jj)
        {
            return endTime<jj.endTime;
        }
        job& operator=(const job&jj)
        {
            startTime=jj.startTime;
            endTime=jj.endTime;
            profit=jj.profit;
            return *this;
        }
    };
    job* Job;
    int n;
};


class KP {
public:
    int KnapsackProblem(vector<int> &weight, vector<int> &value, int W) {
        n = weight.size();
        result = new int*[n+1];
        for(int i=0;i<n+1;i++) result[i] = new int[W+1]{0};
        for(int i=1;i<=n;i++)
            for(int j=1;j<=W;j++)
            {
                if(j<weight[i-1])
                {
                    result[i][j] = result[i][j-1];
                }
                else{
                    result[i][j] = max(result[i-1][j-weight[i-1]]+value[i-1], result[i-1][j]);
                }
            }
        return result[n][W];
    }
private:
    int **result;
    int n;
};


// For testing
int main(int argc, const char * argv[]) {
    
    //*********** Test Longest Common Subsequence ***********//
    string text1 = "springtime";
    string text2 = "printing";
    LCS lcs = LCS();
    cout << "Test Longest Common Subsequence..." << endl;
    cout << lcs.LongestCommonSubsequence(text1, text2) << endl;
    cout << "The expected output: 6" << endl;
    cout << endl;
    
    //********** Test Weighted Interval Scheduling **********//
    vector<int> startTime = {1,2,3,4,6};
    vector<int> endTime = {3,5,9,6,9};
    vector<int> profit = {20,20,100,70,60};
    WIS wis = WIS();
    cout << "Test Weighted Interval Scheduling..." << endl;
    cout << wis.WeightedIntervalScheduling(startTime, endTime, profit) << endl;
    cout << "The expected output: 150" << endl;
    cout << endl;
    
    //*************** Test Knapsack Problem ****************//
    vector<int> weight = {1, 2, 5, 6, 7};
    vector<int> value = {1, 6, 18, 22, 28};
    int W = 11;
    KP kp = KP();
    cout << "Test Knapsack Problem..." << endl;
    cout << kp.KnapsackProblem(weight, value, W) << endl;
    cout << "The expected output: 40" << endl;
    cout << endl;
    system("pause");
    return 0;
}