#include <cstddef>

template <typename T>
class Array
{
public:
    explicit Array(size_t size = 0, const T& value = T());
    Array(const Array& other);
    ~Array();
    Array& operator=(Array other);
    void swap(Array &other);
    size_t size() const;
    T& operator[](size_t idx);
    const T& operator[](size_t idx) const;

private:
    size_t size_;
    T *data_;
};

/*
    bool less(int a, int b) { return a < b; }
    struct Greater { bool operator()(int a, int b) const { return b < a; } };
    Array<int> ints(3);
    ints[0] = 10;
    ints[1] = 2;
    ints[2] = 15;
    int min = minimum(ints, less); // в min должно попасть число 2
    int max = minimum(ints, Greater()); // в max должно попасть число 15
*/

template <typename T, typename Comp>
T minimum(T* p, Comp less)
{
    int sizeArr = p->size();

    T needItem = p[0];
    for (int i = 0; i < sizeArr; ++i) {
        if (less(p[i], needItem)) {
            needItem = p[i];
        }
    }

    return needItem;
}


//template <typename T>
//T minimum(T * p, Comp compare) {
//
//    int size_arr = p->size();
//
//    T need_item = p[0];
//
//    for (int i = 1; i < size_arr - 1; i++) {
//        if (compare(p[i], need_item)) {
//            need_item = p[i];
//        }
//    }
//
//    return need_item;
//}
