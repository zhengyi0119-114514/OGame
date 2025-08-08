//
// Created by IceThorn on 25-6-22.
//

#ifndef OGAME_STGLIB_TASK
#define OGAME_STGLIB_TASK
#include <pthread.h>
#include <functional>
namespace open_stg::thread_h
{
class ptr_pthread
{
  public:
    explicit ptr_pthread(pthread_t hThread);
    ptr_pthread(const ptr_pthread &) = delete;
    ptr_pthread(ptr_pthread &&other);
    ptr_pthread &operator=(const ptr_pthread &) = delete;
    ptr_pthread &operator=(ptr_pthread &&other);
    operator pthread_t * const &() const noexcept;
    pthread_t **operator&();
    pthread_t *const *operator&() const;
    pthread_t operator*() const;
    pthread_t *operator->() noexcept;
    pthread_t *Get();
    ~ptr_pthread();

  private:
    pthread_t *m_hThread{};
    void free();
};
using PtrThread = ptr_pthread;
template<typename TReturn,typename ...TArgs>
class Function
{
    operator std::function<TReturn(TArgs...)>();
};
} // namespace open_stg::thread_h

#endif // OGAME_STGLIB_TASK
