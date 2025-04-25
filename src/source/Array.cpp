#include "../header/Array.h"

void Array::resize(int newCapacity) {
    T* newElements = new T[newCapacity];
    for (int i = 0; i < size; i++) {
        newElements[i] = elements[i];
    }
    delete[] elements;
    elements = newElements;
    capacity = newCapacity;
}

Array::Array(const Array& other) : capacity(other.capacity), size(other.size) {
    elements = new T[capacity];
    for (int i = 0; i < size; i++) {
        elements[i] = other.elements[i];
    }
}

Array& Array::operator=(const Array& other) {
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

void Array::add(const T& element) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    elements[size++] = element;
}

T& Array::get(int index) {
    if (index < 0 || index >= size) {
        std::cerr << "Error: Index out of range" << std::endl;
        // Return first element as fallback (not ideal but matches original behavior)
        return elements[0];
    }
    return elements[index];
}

const T& Array::get(int index) const {
    if (index < 0 || index >= size) {
        std::cerr << "Error: Index out of range" << std::endl;
        return elements[0];
    }
    return elements[index];
}

int Array::getSize() const {
    return size;
}

bool Array::contains(const T& element) const {
    for (int i = 0; i < size; i++) {
        if (elements[i] == element) {
            return true;
        }
    }
    return false;
}

void Array::remove(int index) {
    if (index < 0 || index >= size) {
        std::cerr << "Error: Index out of range" << std::endl;
        return;
    }

    for (int i = index; i < size - 1; i++) {
        elements[i] = elements[i + 1];
    }
    size--;
}