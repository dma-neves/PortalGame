#ifndef ARRAY
#define ARRAY

template <typename T, int s>
class Array
{
public:
    Array() { elements = new T[s]; }

    T& operator[] (int index) { return elements[index]; }
    int size() { return s; }

private:
    T* elements;
};

#endif