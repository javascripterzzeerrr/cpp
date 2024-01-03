#include <iostream>
#include <map>

// 1. Основная идея и основной синтаксис

//template <typename T>
//class Vector {
//
//};
//
//template <typename T>
//using MyMap = std::map<T, T>;
//
//struct S {
//    template<typename T>
//    void foo(const T&) {
//
//    }
//};


// 2. Шаблоны со стороны компиляторов
//template <typename T>
//T GetMax(const T&, const T&) {
//
//}


// 3. Специализация шаблонов
template <typename T>
class Vector {

};

template <typename T>
class Vector<T*> {

};

int main() {
    std::map<std::string, int> map;
}