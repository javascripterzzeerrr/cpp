#include <iostream>
#include <vector>
#include <list>
#include <type_traits>

void* operator new(size_t n) {
    std::cout << "in new\n";

    void* ptr = malloc(n);

    if (ptr == nullptr) {
        throw std::bad_alloc();
    }
    return ptr;
}

void* operator new[](size_t n) {
    std::cout << "in array new\n";

    return malloc(n);
}

void operator delete[](void* ptr) {
    std::cout << "in delete\n";

    free(ptr);
}

void operator delete(void* ptr) {
    std::cout << "in delete\n";

    free(ptr);
}

struct S {
private:
    S() {
        std::cout << "Private default S()\n";
    }

public:
    friend void* operator new(size_t, S* p);
    int x = 0;

//    static void* operator new(size_t n) {
//        std::cout << "in S new\n";
//
//        return malloc(n);
//    }
//
//    static void operator delete(void* ptr) {
//        std::cout << "in S delete\n";
//
//        free(ptr);
//    }
};

//void* operator new(size_t, S* p) {
//    return p;
//}

int main() {
//    S* ptr = new S();
//    delete(ptr);

    // std::vector<int> v(10);

//    S* p = reinterpret_cast<S*>(operator new(sizeof(S)));
//
//    new(p) S();
//
//    operator delete(p);

    S* p = new S();
    delete p;
}