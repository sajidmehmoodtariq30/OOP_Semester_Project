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

    void resize(int newCapacity) {
        T* newElements = new T[newCapacity];
        for (int i = 0; i < size; i++) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
    }

public:
    Array() : capacity(10), size(0) {
        elements = new T[capacity];
    }

    ~Array() {
        delete[] elements;
    }

    // Copy constructor
    Array(const Array& other) : capacity(other.capacity), size(other.size) {
        elements = new T[capacity];
        for (int i = 0; i < size; i++) {
            elements[i] = other.elements[i];
        }
    }

    // Assignment operator
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] elements;
            capacity = other.capacity;
            size = other.size;
            elements = new T[capacity];
            for (int i = 0; i < size; i++) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    void add(const T& element) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        elements[size++] = element;
    }

    T& get(int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Error: Index out of range" << std::endl;
            // Return first element as fallback (not ideal but matches original behavior)
            return elements[0];
        }
        return elements[index];
    }

    const T& get(int index) const {
        if (index < 0 || index >= size) {
            std::cerr << "Error: Index out of range" << std::endl;
            return elements[0];
        }
        return elements[index];
    }

    int getSize() const {
        return size;
    }

    bool contains(const T& element) const {
        for (int i = 0; i < size; i++) {
            if (elements[i] == element) {
                return true;
            }
        }
        return false;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Error: Index out of range" << std::endl;
            return;
        }
        for (int i = index; i < size - 1; i++) {
            elements[i] = elements[i + 1];
        }
        size--;
    }
};

#endif // ARRAY_H
