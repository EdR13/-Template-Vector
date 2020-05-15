#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>
class Vector
{

private:
    size_t vectorSize;//Number of elements in the vector.
    size_t vectorCapacity;//Vector capacity.
    T* container; //Template type variable.

public:
    Vector()
    {
        vectorCapacity = 1;
        vectorSize = 0;
        container = new T[vectorCapacity];
    }
    Vector(const Vector& other)
    {
        vectorCapacity = 1;
        vectorSize = 0;
        container =  new T[vectorCapacity];
        for (size_t x = 0; x < other.size(); ++x)
        {
            push_back(other[x]);
        }
    }
    ~Vector()
    {
        clear();
    }
    size_t size();
    size_t capacity();
    void push_back(const T& element);
    void pop_back();
    void insert(size_t position, const T& element);
    void erase(size_t position);
    void clear();
    void resize();
    const T& at(size_t position);
    T& operator[] (size_t idx)
    {
        if(vacio())
        {
            throw range_error ("Trying [] on empty vector");
        }
        if(idx > vectorSize || idx < 0)
        {
            throw range_error ("Trying [] in non valid position");
        }
        return container[idx];
    }

    Vector& operator = (const Vector& other)
    {
        vectorCapacity = 1;
        vectorSize = 0;
        container =  new T[vectorCapacity];
        for (size_t x = 0; x < other.size(); ++x)
        {
            push_back(other[x]);
        }
        return *this;
    }
    bool vacio();
    bool lleno();
};


template <typename T>
bool Vector <T> :: vacio()
{
    return vectorSize == 0;
}

template <typename T>
bool Vector <T> :: lleno()
{
    return vectorSize == vectorCapacity;
}

template <typename T>
size_t Vector <T> :: size()
{
    return vectorSize;
}

template <typename T>
size_t Vector <T> :: capacity()
{
    return vectorCapacity;
}

template <typename T>
void Vector <T> :: resize()
{
    if(vectorSize+1 > vectorCapacity)
    {
        T* VectorTemporal = new T[vectorCapacity*2];
        for (size_t a(0); a < vectorCapacity; a++)
        {
            VectorTemporal[a] = container[a];
        }
        delete [] container;
        vectorCapacity *= 2;
        container = VectorTemporal;
    }
    if(vectorCapacity/2 > vectorSize)
    {
        T* VectorTemporal = new T[vectorCapacity/2];
        for (size_t a(0); a < vectorCapacity/2; a++)
        {
            VectorTemporal[a] = container[a];
        }
        delete [] container;
        vectorCapacity /= 2;
        container = VectorTemporal;

    }
}

template <typename T>
void Vector <T> :: push_back(const T& element)
{
    container[vectorSize] = element;
    ++vectorSize;
    if(vectorSize+1 > vectorCapacity)
    {
        resize();
    }
}

template <typename T>
void Vector <T> :: clear()
{
    delete [] container;
    vectorSize = 0;
    vectorCapacity = 1;
    container = new T[vectorCapacity];
}

template <typename T>
void Vector <T> :: pop_back()
{
    if(vacio())
    {
        throw range_error("Trying pop_back() on empty vector");
    }
    --vectorSize;
    if(vectorCapacity/2 > vectorSize)
    {
        resize();
    }
}


template <typename T>
void Vector <T> :: erase(size_t position)
{
    if(vacio())
    {
        throw range_error ("Trying erase() on empty vector");
    }
    if(position>vectorSize || position <0)
    {
        throw range_error ("Trying erase() in non valid position");
    }
    if(position == vectorSize)
    {
        pop_back();
    }
    else
    {
        for (size_t i = position; i < vectorSize-1; ++i)
        {
            container[i] = container[i+1];
        }
        --vectorSize;
    }
    if(vectorCapacity/2 > vectorSize)
    {
        resize();
    }
}

template <typename T>
const T& Vector <T> :: at(size_t position)
{
    if(vacio())
    {
        throw range_error ("Trying at() on empty vector");
    }
    if(position>vectorSize || position <0)
    {
        throw range_error ("Trying at() in non valid position");
    }
    return container[position];
}

template <typename T>
void Vector <T> :: insert(size_t position, const T& element)
{
    if(vacio())
    {
        throw range_error ("Trying insert() on empty vector");
    }
    if(position > vectorSize || position <0)
    {
        throw range_error ("Trying insert() in non valid position");
    }
    if(position == vectorSize)
    {
        push_back(element);
    }
    else
    {
        if(position == vectorCapacity)
        {
            resize();
        }
        for (size_t i = (vectorSize); i > position; --i)
        {
            container[i] = container[i-1];
        }
        container[position] = element;
        ++vectorSize;
    }

}
#endif // VECTOR_H
