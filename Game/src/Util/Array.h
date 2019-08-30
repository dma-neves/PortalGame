#ifndef ARRAY
#define ARRAY

#include <iostream>
#include <memory>

template <typename T, int s>
class Array
{
public:
    Array() { elements = new T[s]; }
    ~Array() { delete[] elements; }

    T& operator[] (int index) { return elements[index]; }
    int size() { return s; }
    
    void reset()
    {
        delete[] elements;
        elements = new T[s];
    }

private:
    T* elements;
};

#endif