#include <iostream>
#include <limits>
#include <ctime>
#include <vector>
#include <cstdlib>
using namespace std;
typedef float T; // Change the type here

template<typename T>
int Partition(vector<T> &A,int j,int left,int right)
{
    vector<T> save_left,save_right;
    T save = A[j];
    for(int i=left;i<right;i++)
    {
    	    if(i==j) continue;
        if(A[i]<A[j]) save_left.push_back(A[i]);
        else save_right.push_back(A[i]);
    }
    for(int i=left;i<left+save_left.size();i++)
        A[i] = save_left[i-left];
    int return_val = left+save_left.size();
    A[return_val] = save;
    for(int i=0;i<save_right.size();i++)
        A[i+return_val+1] = save_right[i];
    return return_val;
}

template<typename T>
void Quicksort(vector<T> &A,int left, int right)
{
    if(left>=right) return;
    int x = Partition(A, right-1, left, right);
    Quicksort(A, left, x);
    Quicksort(A, x+1, right);
}

template<typename T>
T Rselect(vector<T> &A, int i, int left, int right)
{
    if (left+1==right) return A[left];
    int divide = rand()%(right-left)+left	;
    int x = Partition(A, divide, left ,right);
    if(x == i) return A[x];
    else if(x > i) return Rselect(A, i, left, x);
    else return Rselect(A, i, x+1, right);
}

template<typename T>
T Dselect(vector<T> A, int i, int left, int right)
{
    if(left+1==right) return A[left];
    vector<T> save;
    for(int j=0;j<(right-left)/5;j++)
    {
        for(int k=0;k<5;k++)
        	    for(int t=k+1;t<5;t++)
        {
            if(A[5*j+k]>A[5*j+t])
            {
                T temp = A[5*j+k];
                A[5*j+k] = A[5*j+t];
                A[5*j+t] = temp;
            }
        }
        save.push_back(A[5*j+2]);
    }
    if((right-left)%5!=0)
    {
        int times = (right-left)/5;
        int mod_left = (right-left)%5;
        for(int j=times*5;j<times*5+mod_left;j++)
            for(int k=j+1;k<times*5+mod_left;k++)
            if(A[j]>A[k])
            {
                T temp = A[j];
                A[j] = A[k];
                A[k] = temp;
            }
        save.push_back(A[times*5+mod_left/2]);
    }
    T p = Dselect(save, (right-left)/10, 0, save.size());
    int pos = 0;
    for(int j=left;j<right;j++)
        if(A[j]==p)
        {
            pos = j;
            break;
        }
    int x=Partition(A, pos, left, right);
    if(x==i) return A[x];
    else if(x>i) return Rselect(A, i, left, x);
    else return Rselect(A, i, x+1, right);
}
int main()
{
    int x, r, round, i_th;
    
    // Q1:
    cout << "--------------------------------- "<< endl;
    cout << " Q1: Test Partition" << endl;
    cout << "--------------------------------- "<< endl;

    cout << "How many times you want to test Partition?"<<endl;
    cin >> round;
    // input 0 to skip this part
    for(int i = 0; i < round; ++i){
        // clear the input buffer, no need to change.
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        vector<T> data;
        cout << "Input values: " <<endl;
        while (cin >> x) {
            data.push_back(x);
        }

        cout << "Partition array by random select pivot" << endl;
        // to do :
        r = rand()%(data.size()); // n is the size of current array
        
        /*
         * to do ：print r and A[r];
         */
        cout << "r:" << r << "  A[r]:" << data[r] << '\n';
        /*
         * to do : Partition array by A[r]
         *         print the rearranged array
         */
        cout << "After Partiton the rearranged array :" << '\n';
        Partition(data, r, 0, data.size());
        for(int i=0;i<data.size();i++)
            cout << data[i] << " ";
        cout <<'\n';
    }
    
    // Q2:
    // clear the input buffer, no need to change.
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "--------------------------------- "<< endl;
    cout << " Q2: Test Quicksort " << endl;
    cout << "--------------------------------- "<< endl;

    cout << "How many times you want to test Quicksort?"<<endl;
    cin >> round;
    // ----- input 0 to skip this part
    for(int i = 0; i< round; ++i){
        // clear the input buffer, no need to change.
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        vector<T> data;
        cout << "Input values: " <<endl;
        while (cin >> x) {
            data.push_back(x);
        }
        cout << "Sort Array" << endl;
        Quicksort(data, 0, data.size());
        for(int i=0;i<data.size();i++)
            cout << data[i] << " ";
        cout << '\n';
    }
    
    // Q3:
    // clear the input buffer, no need to change.
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "--------------------------------- "<< endl;
    cout << " Q3: Test Rselect " << endl;
    cout << "--------------------------------- "<< endl;

    cout << "How many times you want to test Rselect?"<<endl;
    cin >> round;
    //input 0 to skip this part
    for(int i = 0; i < round; ++i){
        // clear the input buffer, no need to change.
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        vector<T> data;
        cout << "Input values: " <<endl;
        while (cin >> x) {
            data.push_back(x);
        }
        // to do:
        i_th = rand()%(data.size()) + 1; // n is the size of current array
        cout << "select i-th smallest element" << endl;
        cout << "i_th:" << i_th << "   " ;
        cout << "i_th smallest element:" <<  Rselect(data, i_th-1, 0, data.size()) << '\n';
    }
    
    
    // Q4:
    // clear the input buffer, no need to change.
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "--------------------------------- "<< endl;
    cout << " Q4: Test Dselect " << endl;
    cout << "--------------------------------- "<< endl;

    cout << "How many times you want to test Dselect?"<<endl;
    cin >> round;
    //input 0 to skip this part
    for(int i = 0; i< round; ++i){
        // clear the input buffer, no need to change.
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        vector<T> data;
        cout << "Input values: " <<endl;
        while (cin >> x) {
            data.push_back(x);
        }
        // to do :
        i_th = rand()%(data.size()) + 1; // n is the size of current array
        
        cout << "select i-th smallest element" << endl;
        cout << "i_th:" << i_th << "   " << "i_th smallest element:" <<  Dselect(data, i_th-1, 0,data.size()) << '\n';
    }
	    system("pause");
        return 0;
}
    