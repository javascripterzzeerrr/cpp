template <class Type>
struct Array {
    template <class Other>
    Array(Array<Other> const& other): data_(new Type[other.size()]), size_(other.size())
    {
        for (size_t i = 0; i != size_; ++i)
            data_[i] = other[i];
    }

    template<class Other>
    Array& operator=(Array<Other> const& other);
    // ...
};