#include <cstddef>

template <typename T>
struct Array
{
public:
    explicit Array(size_t size = 0, const T& value = T()) : size_(size), array(new T[size])
    {
        for (int i = 0; i < size; i++)
        {
            *(this->array + i) = value;
        }
    }

    Array(const Array & obj)
    {
        this->size_ = obj.size_;
        this->array = new T[obj.size_];

        for (int i = 0; i < size_; i++)
        {
            *(this->array + i) = *(obj.array + i);
        }
    }

    ~Array()
    {
        delete[] this->array;
    }

    Array& operator=(const Array & obj)
    {
        if (this != &obj)
        {
            delete[] this->array;

            this->size_ = obj.size_;

            this->array = new T[size_];

            for (int i = 0; i < size_; i++)
            {
                *(this->array + i) = *(obj.array + i);
            }
        }
        return *this;
    }

    size_t size() const
    {
        return size_;
    }

    T& operator[](size_t index)
    {
        return *(this->array + index);
    }

    const T& operator[](size_t index) const
    {
        return *(this->array + index);
    }

private:
    size_t size_;
    T* array;
};