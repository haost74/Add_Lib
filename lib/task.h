#include "thread_pool.h"

template<class TRESULT>
class async_task;

class task
{
  public:
   template<class CALLABLE, class ... ARGS>
   static auto async(CALLABLE fun, ARGS... args)
   ->async_task<decltype(fun(args...))>  
   {
      using T = decltype(fun(args...));
      async_task<T> tsk(task::pool_run(fun, args...));
      return std::move(tsk);
   }

   template<class T>
   static void wait(const async_task<T> &tk)
   {
       tk.future_.wat();
   }


   private:
      static thread_pool::prt pool_;
};