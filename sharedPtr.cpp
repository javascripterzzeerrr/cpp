#include <iostream>
#include <assert.h>

/* Segmentation fault */

struct Expression;
struct Number;
struct BinaryOperation;

struct Expression
{
    virtual ~Expression() { }
    virtual double evaluate() const = 0;
};

struct Number : Expression
{
    Number(double value)
            : value_(value)
    {}

    double value() const
    { return value_; }

    double evaluate() const
    { return value_; }

private:
    double value_;
};

struct StoragePtr
{
private:
    int counter_;
public:
    StoragePtr() : counter_(0)
    {}

    ~StoragePtr()
    {}

    void AddUser()
    {
        counter_++;
    }

    void DeleteUser()
    {
        counter_--;
    }

    int getCounter()
    {
        return counter_;
    }
};

struct SharedPtr
{
private:
    StoragePtr * counterReference_;
    Expression * data_;

    void clearMemory()
    {
        // если указатель не нулевой
        if (data_)
        {
            if (counterReference_->getCounter() != 0)
            {
                counterReference_->DeleteUser();
            }
            else if (counterReference_->getCounter() <= 0)
            {
                delete counterReference_;
                delete data_;
            }
        }
    }

    void InitCounterReference()
    {
        counterReference_ = new StoragePtr(); // инициализация, количество ссылок 0
        counterReference_->AddUser(); // инициализация счетчика ссылок в 1
    }
public:
    // в конструкторе SharedPtr от ненулевого указателя мы инициализируем счетчик ссылок в 1 (конструктор создает первый SharedPtr, который хранит указатель),
    explicit SharedPtr(Expression *ptr = 0)
    {
        if (ptr)  {
            data_ = ptr;
            InitCounterReference();
        }
    }

    ~SharedPtr()
    {
        clearMemory();
    }

    // в конструкторе копирования мы увеличиваем счетчик ссылок на 1, если копируемый SharedPtr содержит ненулевой указатель (конструктор копирования создает еще один SharedPtr с указателем на тот же самый объект),
    SharedPtr(const SharedPtr & obj)
    {
        std::cout << "OBJ => " << " data_ = " << obj.get() << " counter_ = " << obj.count() << std::endl;
        // если копируем от чего-то полезного
        if (obj.data_ && obj.counterReference_)
        {
            obj.counterReference_->AddUser();
            data_ = obj.data_;
            counterReference_ = obj.counterReference_;
        }
        else {
            SharedPtr(0);
        }
    }

    // оператор присваивания уменьшает счетчик ссылок левого операнда на 1, если внутри левого SharedPtr хранится ненулевой указатель, увеличивает счетчик правого SharedPtr на 1, если в правом SharedPtr хранится ненулевой указатель (обычное дело для оператора присваивания — сначала освобождаем старые ресурсы, потом выделяем новые, но при этом нужно быть особенно внимательным с присваиванием самому себе).
    SharedPtr& operator=(const SharedPtr & obj)
    {
        if (this != &obj)
        {
            clearMemory();

            if (obj.data_)
            {
                // копируем данные и увеличивает количество ссылок на данные
                obj.counterReference_->AddUser();
                data_ = obj.data_;
                counterReference_ = obj.counterReference_;
            }
        }
        return *this;
    }

    Expression* get() const
    {
        return data_;
    }

    void reset(Expression *ptr = 0)
    {
        counterReference_->DeleteUser();

        if (counterReference_->getCounter() == 0)
        {
            delete counterReference_;
            delete data_;
        }

        data_ = ptr;
        InitCounterReference();
    }

    Expression& operator*() const
    {
        return *(get());
    }

    Expression* operator->() const
    {
        return get();
    }

    int count() const {
        if (counterReference_->getCounter()) return counterReference_->getCounter();
        return 0;
    }
};

//struct SharedPtr
//{
// реализуйте следующие методы
//
// explicit SharedPtr(Expression *ptr = 0)
// ~SharedPtr()
// SharedPtr(const SharedPtr &)
// SharedPtr& operator=(const SharedPtr &)
// Expression* get() const
// void reset(Expression *ptr = 0)
// Expression& operator*() const
// Expression* operator->() const
//};

int main(){

    Number *n16 = new Number(16.0);
    Number *n32 = new Number(32.0);
    Number *n42 = new Number(42.0);

    std::cout<<"------------------"<<std::endl;
    std::cout<<"Test 1. SharedPtr p1(n32)"<<std::endl;
    SharedPtr p1(n32);
    std::cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 2. SharedPtr p2 = p1"<<std::endl;
    SharedPtr p2 = p1;
    std::cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
    std::cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 3. SharedPtr p3(p1)"<<std::endl;
    SharedPtr p3(p1);
    std::cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
    std::cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
    std::cout<<"p3.count() = "<<p3.count()<<";  (size_t) p3.get(): "<<(size_t)p3.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 4. p3.reset(n16)"<<std::endl;
    p3.reset(n16);
    std::cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
    std::cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
    std::cout<<"p3.count() = "<<p3.count()<<";  (size_t) p3.get(): "<<(size_t)p3.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 5. p3.reset(0)"<<std::endl;
    p3.reset(NULL);
    std::cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
    std::cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
    std::cout<<"p3.count() = "<<p3.count()<<";  (size_t) p3.get(): "<<(size_t)p3.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 6. p1 = p1"<<std::endl;
    p1 = p1;
    std::cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
    std::cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
    std::cout<<"p3.count() = "<<p3.count()<<";  (size_t) p3.get(): "<<(size_t)p3.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 7. p3.~SharedPtr()"<<std::endl;
    p3.~SharedPtr();
    std::cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
    std::cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 8. p1.reset(n42)"<<std::endl;
    p1.reset(n42);
    std::cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
    std::cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 9. p1.~SharedPtr()"<<std::endl;
    p1.~SharedPtr();
    std::cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 10. p2.~SharedPtr()"<<std::endl;
    p2.~SharedPtr();
    std::cout<<"------------------"<<std::endl;

//    std::cout<<"Test 11. SharedPtr p4(NULL)"<<std::endl;
    SharedPtr p4(n16);
//    std::cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
//    std::cout<<"------------------"<<std::endl;
//
//    std::cout<<"Test 12. SharedPtr p5(NULL)"<<std::endl;
    SharedPtr p5(n32);
//    std::cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
//    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 13. p5 = p4"<<std::endl;
    p5 = p4;
    std::cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    std::cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 14. SharedPtr p6(p4)"<<std::endl;
    SharedPtr p6(p4);
    std::cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    std::cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    std::cout<<"p6.count() = "<<p6.count()<<";  (size_t) p6.get(): "<<(size_t)p6.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 15. p6.reset(n16)"<<std::endl;
    p6.reset(n16);
    std::cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    std::cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    std::cout<<"p6.count() = "<<p6.count()<<";  (size_t) p6.get(): "<<(size_t)p6.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 16. p5 = p6"<<std::endl;
    p5 = p6;
    std::cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    std::cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    std::cout<<"p6.count() = "<<p6.count()<<";  (size_t) p6.get(): "<<(size_t)p6.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 17. p6 = p4"<<std::endl;
    p6 = p4;
    std::cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    std::cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    std::cout<<"p6.count() = "<<p6.count()<<";  (size_t) p6.get(): "<<(size_t)p6.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 18. p5.reset(NULL)"<<std::endl;
    p5.reset(NULL);
    std::cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    std::cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    std::cout<<"p6.count() = "<<p6.count()<<";  (size_t) p6.get(): "<<(size_t)p6.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    return 0;
}