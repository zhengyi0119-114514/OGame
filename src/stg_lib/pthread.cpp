#include "include/og_task_h.hpp"
#include "og_task_h.hpp"
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <stdlib.h>
#include <utility>

namespace open_stg::thread_h
{
ptr_pthread::ptr_pthread(pthread_t hThread)
{
    m_hThread = (pthread_t *)malloc(sizeof(pthread_t));
    memset((void *)m_hThread, 0, sizeof(pthread_t));
    *m_hThread = hThread;
}
void ptr_pthread::free()
{
    if (m_hThread)
    {
        pthread_detach(*m_hThread);
        ::free(m_hThread);
    }
}
ptr_pthread::~ptr_pthread()
{
    free();
}
ptr_pthread::ptr_pthread(ptr_pthread &&other)
{
    free();
    std::swap(m_hThread, other.m_hThread);
}
ptr_pthread &ptr_pthread::operator=(ptr_pthread &&other)
{
    ptr_pthread new_one(std::move(other));
    std::swap(this->m_hThread, other.m_hThread);
    return *this;
}
ptr_pthread::operator pthread_t * const &() const noexcept
{
    return m_hThread;
}
pthread_t* ptr_pthread::operator->() noexcept
{
    return m_hThread;
}
pthread_t* ptr_pthread::Get()
{
    return m_hThread;
}
pthread_t** ptr_pthread::operator&()
{
    return &m_hThread;
}
pthread_t*const* ptr_pthread::operator&() const
{
    return &m_hThread;
}
pthread_t ptr_pthread::operator*() const
{
    return *m_hThread;
}
} // namespace open_stg::thread
