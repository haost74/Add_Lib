#ifndef __HELLO_H__
#define __HELLO_H__

class Hello
{
public:
    void (*doo)(int);
    void print();
    void startPool(decltype(doo) func, int i);
    const unsigned GetCountThread();
};

#endif