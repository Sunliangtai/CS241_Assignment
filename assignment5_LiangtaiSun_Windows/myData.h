#pragma once

using namespace std;

template<typename T>
struct myData
{
    T val;
    myData<T>* addr;

    myData() {}
    myData(const T& x):val(x) {}
    myData(const myData& t)
    {
        val = t.val;
        addr = t.addr;
    }
    void operator=(const myData& t)
    {
        val = t.val;
        addr = t.addr;
    }
};

template<typename T>
struct Cmp_by_value
{
    bool operator()(myData<T> a, myData<T> b)
    {
        return a.val < b.val;
    }
};

template<typename T>
struct Cmp_by_addr
{
    bool operator()(myData<T> a, myData<T> b)
    {
        return a.addr < b.addr;
    }
};
