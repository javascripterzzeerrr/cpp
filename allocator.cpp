#include <iostream>
#include <stdint.h>
#include <vector>

template <typename T>
class PoolAllocator {
public:
    using value_type = T;

    PoolAllocator(): pool_(reinterpret_cast<uint8_t*>(::operator new(pool_size_))), pool_begin_(pool_) {}
    ~PoolAllocator() { ::operator delete(pool_begin_); }

    T* allocate(size_t n) {
        size_t bytes = n * sizeof(T);
        auto memory_to_return = pool_;
        pool_ += bytes;

        return reinterpret_cast<T*>(memory_to_return);
    }

    void deallocate(T*, size_t) {
        return;
    }

    template<typename... Args>
    void construct(T* ptr, const Args&... args) {
        new(ptr) T(args...);
    }

    void destroy(T* ptr) noexcept {
        ptr->~T();
    }

private:
    const size_t pool_size_ = 100000;
    uint8_t* pool_ = nullptr;
    uint8_t* pool_begin_ = nullptr;
};

template <typename T>
struct Allocator {
    T* allocate(size_t n) {
        return ::operator new(n * sizeof(T));
    }

    void deallocate(T* ptr, size_t) {
        ::operator delete(ptr);
    }

    template<typename... Args>
    void construct(T* ptr, const Args&... args) {
        new(ptr) T(args...);
    }

    void destroy(T* ptr) noexcept {
        ptr->~T();
    }
};

int main() {
    std::vector<int, PoolAllocator<int>> v(10, PoolAllocator<int>());

    return 0;
}