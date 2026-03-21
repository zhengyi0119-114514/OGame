#include <stdlib.h>
#include <limits>
#include <exception>
#if OPEN_STG_MACRO_IS_WINDOWS
#include <windows.h>
#endif
#if !defined OPEN_STG_ALLOCATOR_H
#define OPEN_STG_ALLOCATOR_H 1
#if defined __cplusplus
namespace OpenStg::Core
{
template <typename T> class StdlibAllocator
{
  public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    constexpr inline StdlibAllocator() noexcept = default;
    ~StdlibAllocator() noexcept = default;
    inline T *allocate(size_type n)
    {
        return static_cast<T *>(malloc(n * sizeof(T)));
    }
    inline void deallocate(T *p, size_type) noexcept
    {
        free(static_cast<void *>(p));
    }
    inline size_type max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }
};
template <typename T, size_t sAlignment = sizeof(void *)> class StdlibAlignedAllocator
{
  public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    constexpr inline StdlibAlignedAllocator() noexcept = default;
    ~StdlibAlignedAllocator() noexcept = default;
    inline T *allocate(size_type uSize)
    {
#if defined __unix
        void *p = nullptr;
        posix_memalign(&p, sAlignment, uSize);
        return static_cast<void *>(p);
#elif OPEN_STG_MACRO_IS_WINDOWS
        return _aligned_malloc(uSize, sAlignment);
#else
        return static_cast<T *>(aligned_alloc(sAlignment, uSize));
#endif
    }
    inline void deallocate(T *p, size_type) noexcept
    {
#if OPEN_STG_MACRO_IS_WINDOWS
        _aligned_free(static_cast<void *>(p));
#else
        free(static_cast<void *>(p));
#endif
    }
    inline size_type max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }
};
#if OPEN_STG_MACRO_IS_WINDOWS
template <typename T, SIZE_T sInitialSize = 1024 * 1024, SIZE_T sMaximumSize = 0, bool bEnableExcute = false,
          bool bSerialize = true>
class Win32APIHeapAllocator
{
  private:
    HANDLE m_hHeap = NULL;

  public:
    using value_type = T;
    using size_type = SIZE_T;
    using difference_type = ptrdiff_t;
    inline Win32APIHeapAllocator(HANDLE hHeap = GetProcessHeap())
    {
        m_hHeap = hHeap;
    }
    inline ~Win32APIHeapAllocator() noexcept = default;
    constexpr inline T *allocate(size_type uSize)
    {
        return static_cast<T *>(HeapAlloc(m_hHeap, HEAP_ZERO_MEMORY, uSize));
    }
    constexpr inline void deallocate(T *p, size_type)
    {
        HeapFree(m_hHeap, 0, static_cast<void *>(p));
    }
    constexpr inline size_type max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }
};
#endif
} // namespace OpenStg::Core
#endif
#endif