#pragma once

using namespace std;

template<typename Elem>
class myArray
{
    private:
        int now_size;
        int max_size;
        Elem* array;
    public:
        class iterator
        {
            friend class myArray;
            private:
                myArray& myAr;
                int pos;
            public:
                iterator()
                {
                    pos = -1;
                }
                iterator(myArray& temp , int x=-1):myAr(temp), pos(x) {}
                Elem& operator*()
                {
                    return myAr[pos];
                }
                void set(int x)
                {
                    pos = x;
                }
                bool operator!=(const iterator& x)
                {
                    return pos!=x.pos;
                }
                iterator operator++()
                {
                    pos++;
                    return *this;
                }
                void operator=(const iterator& temp)
                {
                    pos = temp.pos;
                    myAr = temp.myAr;
                }
        };
        myArray()
        {
            now_size = 0;
            max_size = 10;
            array = new Elem[max_size];
        }
        myArray(const myArray& another)
        {
            now_size = another.now_size;
            max_size = another.max_size;
            array = new Elem[max_size];
            for(int i=0;i<now_size;i++) array[i] = another.array[i];
        }
        iterator begin()
        {
            iterator temp(*this, 0);
            return temp;
        }
        iterator end()
        {
            iterator temp(*this, now_size-1);
            return temp;
        }
        void doubleSpace()
        {
            Elem* save = new Elem[max_size];
            for(int i=0;i<max_size;i++) save[i] = array[i];
            max_size *= 2;
            delete [] array;
            array = new Elem[max_size];
            for(int i=0;i<max_size/2;i++) array[i] = save[i];
            delete [] save;
        }
        void operator=(const myArray& another)
        {
            if(&array==&another.array) return;
            delete [] array;
            now_size = another.now_size;
            max_size = another.max_size;
            array = new Elem[max_size];
            for(int i=0;i<now_size;i++) array[i] = another.array[i];
        }
        Elem& operator[](const int i)
        {
            return array[i];
        }
        void push_back(const Elem& x)
        {
            if(now_size==max_size) doubleSpace();
            array[now_size++] = x;
        }
        void pop_back()
        {
            if(now_size==0) return;
            now_size--;
        }
        int size()
        {
            return now_size;
        }
        int capacity()
        {
            return max_size;
        }
};