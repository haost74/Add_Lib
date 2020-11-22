#include "../include/static/pool.h"
#include "../include/static/task.h"
#include "../include/static/thread_pool.h"
#include <iostream>


void printStand();
void foo();

template<class T, class T1>
auto sum1(const T &lhs, const T1 &rhs) -> decltype(lhs + rhs);

void foo(int i)
{
   std::cout << i + 10 << '\n';
}

int main(int argc, char *argv[])
{
    int s = 100;
    int i = 5;
    const int & ss = s;
    const int & iref = i;
    auto mon = sum1<int , int>(ss, iref);

    Hello hi;
    hi.print();
    //hi.startPool(foo, 10);

    foo();

    std::cout << hi.GetCountThread() << '\n';

    hi.startPool([](int i)->void
    {
        std::cout << i << '\n';
    }, 55);


    return 0;
}

void printStand()
{
     if (__cplusplus == 201703L) std::cout << "C++17\n";
    else if (__cplusplus == 201402L) std::cout << "C++14\n";
    else if (__cplusplus == 201103L) std::cout << "C++11\n";
    else if (__cplusplus == 199711L) std::cout << "C++98\n";
    else std::cout << "pre-standard C++\n";
}

void initAuto()
{
    int i{};
    auto iref = &i;
    int &ref = i;
    auto aref = ref;

    int &&ref2 = std::move(i);
    auto aRef2 = ref2;

    double b{};
    double v1 = b;
    double &v2 = v1;
    decltype(v1) v3 = b;
    decltype((v1)) v4 = (b);
    decltype(v2) v5 = v2;
}

void foo()
{
     unsigned i = 0;
    auto f = [&i](unsigned lhs, unsigned rhs) -> bool
    {
        ++i;
        return lhs > rhs;
    };

    decltype(f) g = f;
    bool res = f(10, 88);
    std::cout << static_cast<bool>(res) << '\n';
}

template<class T, class T1>
auto sum1(const T &lhs, const T1 &rhs) -> decltype(lhs + rhs)
{
    return lhs + rhs;
}

class Some
{
    int *ref_p, *ref_q;
  public:
    Some():Some(nullptr, nullptr){}
    Some(int *p, int *q):ref_p{p}, ref_q{q}{}
};

//если возможно то компилятор помечает как noexept
//для конструкторов копирования скопирут поля для перемещения переместит объекты 
//можно помечать default
//конструктор копирования
//конструктор перемещения
//оператор копирования
//оператор перемещения
//деструктор 
class SomeClass
{
private:
    std::string m_name, m_surname;
public:
    SomeClass() = default;
    SomeClass(const SomeClass &other) = default;
    SomeClass& operator=(const SomeClass &other) = default;
    ~SomeClass();
};
//удаляет вызов конструкторов
class SomeClass1
{
private:
    std::string m_name, m_surname;
public:
    SomeClass1() = default;
    SomeClass1(const SomeClass1 &other) = delete;
    SomeClass1& operator=(const SomeClass1 &other) = delete;
    ~SomeClass1();
};
