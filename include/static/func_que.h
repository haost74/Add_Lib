#ifndef __func_que__
#define __func_que__

#include <thread>
#include <vector>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <algorithm>
#include <queue>
#include <atomic> 

class func_que
        {
            public:
              func_que()
                :mtx_{}, que_{}{}

            void push(std::function<void()> fun);
            std::function<void()> pop();
            bool empty();

            private:
            std::mutex mtx_;
            std::queue<std::function<void()>> que_;
        };

#endif