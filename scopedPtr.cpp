struct Expression;
struct Number;
struct BinaryOperation;

struct ScopedPtr
{
    // реализуйте следующие методы:
    explicit ScopedPtr(Expression* ptr = 0) : ptr_(ptr)
    {};

    ~ScopedPtr()
    {
        delete ptr_;
    }

    Expression* get() const
    {
        return ptr_;
    }

    Expression* release()
    {
        Expression* copy = ptr_;
        ptr_ = nullptr;

        return copy;
    }

    void reset(Expression *ptr = 0)
    {
        delete ptr_;
        ptr_ = ptr;
    }

    Expression& operator*() const
    {
        return *ptr_;
    }

    Expression* operator->() const
    {
        return ptr_;
    }


private:
    // запрещаем копирование ScopedPtr
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Expression* ptr_;
};