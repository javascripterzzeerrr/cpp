#include <iostream>

template<class T>
struct Array {
    // ...
    T* data_;
};

template<>
struct Array<bool> {
    static int const INTBITS = 8 * sizeof(int); // 32
    explicit Array(size_t size): size_(size), data_(new int[size_ / INTBITS + 1]) {}

    bool operator[](size_t i) const {
        return data_[i / INTBITS] & (1 << (i % INTBITS));
    }

private:
    size_t size_;
    int* data_;
};

// Полная специализация шаблонов: функции
template <class T>
void swap(T& a, T& b)
{
    T tmp(a); // конструктор копировования
    a = b;
    b = tmp;
}

template<>
void swap<Database>(Database& a, Database& b)
{
    a.swap(b);
}

template<class T>
void swap(Array<T>& A, Array<T>& b)
{
    a.swap(b);
}