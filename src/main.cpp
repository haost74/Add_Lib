#include "../include/static/pool.h"
#include <iostream>

void printStand();

void foo(int i)
{
   std::cout << i + 10 << '\n';
}

int main(int argc, char *argv[])
{
    Hello hi;
    hi.print();
    hi.startPool(foo, 10);
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