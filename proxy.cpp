#include <cstddef> // size_t

struct String {
    String(const char *str = "");
    String(size_t n, char c);
    ~String();

    String(const String &other);
    String &operator=(const String &other);

    void append(const String &other);

    struct Proxy
    {
    public:
        Proxy(const String& string, int start) : string_(string), start_(start), new_string_(nullptr)
        {};

        ~Proxy()
        {
            delete[] new_string_;
        }

        String operator[](int j)
        {
            int new_size = j - start_;

            new_string_ = new char[new_size + 1];
            int cnt = 0;

            for (int t = start_; t < j; cnt++, t++) {
                new_string_[cnt] = string_.str[t];
            }

            new_string_[new_size] = '\0';

            return String(new_string_);
        }

    private:
        const String& string_;
        int start_;
        char * new_string_;
    };

    Proxy operator[](int start) const
    {
        return Proxy(*this, start);
    }

    size_t size;
    char *str;
};