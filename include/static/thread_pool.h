#ifndef __thread_pool_cpp__
#define __thread_pool_cpp__

#include <thread>
#include <vector>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <algorithm>
#include <queue>
#include <atomic> 

#include "../include/static/func_que.h"

class thread_pool
{
    public:
    //std::vector<std::unique_ptr<std::thread>> pool;

    thread_pool();
     explicit thread_pool(const unsigned int init_size, 
                    const unsigned int increase_size = 8, 
                    const unsigned int max_size = 0)noexcept(false);

    using prt = std::shared_ptr<thread_pool>;
    static prt pool_ptr(
          const unsigned int init_size = 16,
          const unsigned int increase_size = 8,
          const unsigned int max_size = 0);


      //---------------------------------


      void init(const unsigned int& init_size, 
                  const unsigned int& increase_size, 
                  const unsigned int& max_size);

      //----------------------------------

      void add_thread(const unsigned int& size);

      private:
        unsigned int max_size;
        unsigned int increase_size;
        unsigned int pool_size;     // we do not want to lock the pool every time expanding it.
        std::atomic<unsigned int> running_count;

        bool flag_shut;
        std::mutex mtx_pool;
        std::condition_variable cv;

        func_que fun_que;
        std::vector<std::unique_ptr<std::thread>> pool;

        void expand();
        
};



#endif

