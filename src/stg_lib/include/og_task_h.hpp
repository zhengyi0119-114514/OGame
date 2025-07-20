//
// Created by IceThorn on 25-6-22.
//

#ifndef OGAME_STGLIB_TASK
#define OGAME_STGLIB_TASK
#include <pthread.h>
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
template <typename TResult> class func
{
  public:
    using func_ptr = TResult (*)();
    func(typename func<TResult>::func_ptr func);
    TResult &&run();
    TResult &&operator()();

  private:
    func_ptr m_func;
};
template <typename TResult, typename TArg1> class func_1a
{
  public:
    using func_ptr = TResult (*)(TArg1);
    func_1a(typename func_1a<TResult, TArg1>::func_ptr func);
    TResult &&run(TArg1 arg1);
    TResult &&operator()(TArg1 arg1);

  private:
    typename func_1a<TResult, TArg1>::func_ptr m_func;
};
// template <typename TResult> class task
// {
//   public:
//     using func_ptr = func_1a<TResult,std::any>;
//     static task<TResult> Run(std::any arg);
// };
} // namespace open_stg::thread_h

#endif // OGAME_STGLIB_TASK
