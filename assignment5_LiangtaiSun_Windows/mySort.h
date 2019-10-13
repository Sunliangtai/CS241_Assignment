#pragma once

using namespace std;

template<class Iterator>
void mySort(Iterator first, Iterator last)
{
    Iterator temp=first;
    for(;temp!=last;++temp)
    {
        Iterator cmp = temp;
        do
        {
            ++cmp;
            if(*temp>*cmp)
            {
                Iterator save = temp;
                temp = cmp;
                cmp = save;
            }
        }while (cmp!=last);
    }
}

template<class Iterator, class Compare>
void mySort(Iterator first, Iterator last, Compare comp)
{
    Iterator temp=first;
    for(;temp!=last;++temp)
    {
        Iterator cmp = temp;
        do
        {
            ++cmp;
            if(comp(*cmp, *temp))
            {
                auto save = *cmp;
                *cmp = *temp;
                *temp = save;
            }
        }while (cmp!=last);
    }
}
