#include "og_task_h.hpp"
#include <algorithm>
namespace open_stg::thread_h
{
template <typename TResult> func<TResult>::func(typename func<TResult>::func_ptr func)
{
    this->m_func = func;
}
template<typename TResult> TResult&& func<TResult>::run()
{
    return std::move(m_func());
}
template <typename TResult> TResult&& func<TResult>::operator()()
{
    return std::move(this->run());
}
template <typename TResult, typename TArg1>
func_1a<TResult, TArg1>::func_1a(typename func_1a<TResult, TArg1>::func_ptr func)
{
    this->m_func = func;
}

template <typename TResult, typename TArg1>
TResult&& func_1a<TResult, TArg1>::run(TArg1 arg1)
{
    return std::move(m_func(arg1));
}

template <typename TResult, typename TArg1>
TResult&& func_1a<TResult, TArg1>::operator()(TArg1 arg1)
{
    return std::move(this->run(arg1));
}
} // namespace open_stg::thread
