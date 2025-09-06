//
// Created by IceThorn on 25-6-22.
//

#ifndef OGAME_STGLIB_TASK
#define OGAME_STGLIB_TASK
#include <pthread.h>
namespace OpenGame::Thread
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
using PtrPThread = ptr_pthread;
} // namespace OpenGame::Thread

#endif // OGAME_STGLIB_TASK
