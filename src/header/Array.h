#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

// Generic Array template class to replace all specific array implementations
template <typename T>
class Array {
private:
    T* elements;
    int capacity;
    int size;

    void resize(int newCapacity);

public:
    Array() : capacity(10), size(0) {
        elements = new T[capacity];
    }

    ~Array() {
        delete[] elements;
    }

    // Copy constructor
    Array(const Array& other) : capacity(other.capacity), size(other.size);

    // Assignment operator
    Array& operator=(const Array& other);

    void add(const T& element);

    T& get(int index);

    const T& get(int index) const;

    int getSize() const;

    bool contains(const T& element);

    void remove(int index);
};

#endif // ARRAY_H
