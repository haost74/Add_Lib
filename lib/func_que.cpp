#include "../include/static/func_que.h"

class func_que
        {
            public:
              func_que()
                :mtx_{}, que_{}{}

            void push(std::function<void()> fun) 
            {
                std::lock_guard<std::mutex> lck(mtx_);
                que_.push(fun);
            }
            std::function<void()> pop()
            {
                std::lock_guard<std::mutex> lck(mtx_);
                if (0 == que_.size()) return nullptr;
                auto ret = que_.front();
                que_.pop();
                return std::move(ret);
            }
            bool empty()
            {
                std::lock_guard<std::mutex> lck(mtx_);
                return que_.empty();
            }

            private:
            std::mutex mtx_;
            std::queue<std::function<void()>> que_;
        };

