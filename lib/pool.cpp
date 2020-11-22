#include <iostream>
#include <thread>

#include "../include/static/pool.h"

void Hello::print()
{
    std::cout << "Hello Static Library!" << " 10 " << std::endl;
}

void Hello::startPool(decltype(doo) func, int i)
{
  if(func == nullptr) return;
  std::thread thr{func, i};
  thr.join();
}

const unsigned Hello::GetCountThread()
{
   return std::thread::hardware_concurrency();
}
