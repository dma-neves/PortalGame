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

private:
    T* elements;
};

#endif