#if !defined(OPEN_STG_MACRO_BASE_TYPE_AND_MACRO_H)
#define OPEN_STG_MACRO_BASE_TYPE_AND_MACRO_H 1

#if OPEN_STG_MACRO_IS_WINDOWS
#define OG_MACRO_EXTERN __deslspec(dllimport)
#define OG_MACRO_EXPORT __declspec(dllexport)
#else
#define OG_MACRO_EXTERN extern
#define OG_MACRO_EXPORT
#endif
#if defined(_MSC_VER)
#define OG_MACRO_FUNCTION __FUNCSIG__
#define OG_MACRO_PRIVATE
#define OG_MACRO_THREAD_LOCAL __declspec(thread)
#define OG_MACRO_ALWAYS_INLINE __forceinline
#else
#if defined(__GNUC__) || defined (__llvm__)
#define OG_MACRO_PRIVATE __attribute__((visibility("hidden")))
#define OG_MACRO_ALWAYS_INLINE __attribute__((__always_inline__))
#define OG_MACRO_FUNCTION __PRETTY_FUNCTION__
#else
#define OG_MACRO_FUNCTION __FUNCTION__
#define OG_MACRO_PRIVATE
#endif
#if (defined(__cplusplus) && __cplusplus >= 201103L) || __STDC_VERSION__ >= 202311L
#define OG_MACRO_THREAD_LOCAL thread_local
#elif __STDC_VERSION__ >= 201112L
#define OG_MACRO_THREAD_LOCAL _Thread_local
#else
#if (defined(__GNUC__))
#define OG_MACRO_THREAD_LOCAL __thread
#else
static_assert(
    false,
    "No thread local support.")
#endif
#endif
#endif

#if defined __cplusplus
#define OG_MACRO_C extern "C"
#define OG_MACRO_CPP
#define OG_MACRO_C_BLOCK_BEGIN                                                                     \
    extern "C"                                                                                     \
    {
#define OG_MACRO_C_BLOCK_END }
#else
#define OG_MACRO_C
#define OG_MACRO_CPP
#define OG_MACRO_C_BLOCK_BEGIN
#define OG_MACRO_C_BLOCK_END
#endif
#endif
