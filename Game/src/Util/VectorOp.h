#ifndef VectorOp
#define VectotOP

#include <vector>

class VectorOp
{
public:
    template <typename T>
    static int getIndex(std::vector<T*>& vec, T* element)
    {
        for(int i = 0; i < vec.size(); i++)
        {
            if(vec[i] == element) return i;
        }
        return -1;
    }
};

#endif