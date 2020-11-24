#include "../include/static/thread_pool.h"


thread_pool::thread_pool()
 : flag_shut{false}, cv{}, pool{}
{
  init(16, 8, 0);
}


thread_pool::~thread_pool()
{
    
}

void thread_pool::shutdown()
{
     flag_shut = true;
            cv.notify_all();
            pool.clear();
}

template <typename CALLABLE, typename... ARGS>
        auto run(CALLABLE&& fun, ARGS&&... args) noexcept(false)
        -> std::shared_future<decltype(fun(args...))>
        {
            if (static_cast<unsigned int>(running_count) >= pool_size) {
                expand();
            }

            running_count++;
            using ret_type = decltype(fun(args...));
            auto tp = std::make_shared<std::packaged_task<ret_type()>>(
                std::bind(std::forward<CALLABLE>(fun), std::forward<ARGS>(args)...)
            );
            auto ft = tp->get_future();
            fun_que.push([tp](){(*tp)();});
            cv.notify_one();
            return ft;
        }


 
        thread_pool::thread_pool(const unsigned int init_size, 
                    const unsigned int increase_size, 
                    const unsigned int max_size)
                    : flag_shut {false}
                    , cv {}
                    , pool {}
        {
            init(init_size, increase_size, max_size);
        }


 thread_pool::prt thread_pool::pool_ptr(
          const unsigned int init_size = 16,
          const unsigned int increase_size = 8,
          const unsigned int max_size = 0)
          {
              return std::make_shared<thread_pool>(init_size, increase_size, max_size);
          }

  void thread_pool::init(const unsigned int& init_size, 
                  const unsigned int& increase_size, 
                  const unsigned int& max_size)
                  {
                      if (init_size < 1 || (0 != max_size && init_size > max_size)) {
                          throw std::invalid_argument("init_size should be greater than 1 and less than or equal to max_size.");
                    }

                    this->max_size = max_size;
                    this->increase_size = increase_size;
                    pool_size = init_size;
                    running_count = 0;
                  }

    void thread_pool::add_thread(const unsigned int& size)
    {
       for (unsigned int i = 0; i < size; ++i) {
                auto thread_ = std::make_unique<std::thread>([this](){
                    std::mutex mtx_;
                    std::unique_lock<std::mutex> lck(mtx_);
                    for(;;) {
                        cv.wait(lck, [this]{ return !fun_que.empty() || flag_shut; });
                        if (flag_shut) break;
                        auto task_ = fun_que.pop();
                        if (!task_) {
                            running_count --;
                            continue;
                        }
                        task_();
                        running_count --;
                    }
                });
                thread_->detach();
                pool.emplace_back(move(thread_));
            }
    }

    void thread_pool::expand()
        {
            std::lock_guard<std::mutex> lock(mtx_pool);
            if (this->increase_size == 0 || (this->max_size != 0 && this->pool_size == this->max_size)) {
                throw std::logic_error("No idle thread available.");
            } else {
                auto sz = 0 == max_size 
                        ? increase_size
                        : max_size - pool_size > increase_size 
                        ? increase_size
                        : max_size - pool_size;
                add_thread(sz);
                pool_size += sz;
            }
        }

