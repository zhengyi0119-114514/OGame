#if !defined(OPEN_STG_MACRO_BASE__MACRO_H)
#define OPEN_STG_MACRO_BASE_MACRO_H 1

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
#define OG_MACRO_MSVC(content) content
#define OG_MACRO_MSVC_DECLSPEC(content) __declspec(content)
#define OG_MACRO_GNU(content)
#define OG_MACRO_GNU_ATTRIBUTE(...)
#else
#if defined(__GNUC__) || defined(__llvm__) || defined(__clang__)
#define OG_MACRO_PRIVATE __attribute__((__visibility__("hidden")))
#define OG_MACRO_ALWAYS_INLINE __attribute__((__always_inline__))
#define OG_MACRO_FUNCTION __PRETTY_FUNCTION__
#define OG_MACRO_MSVC(content)
#define OG_MACRO_MSVC_DECLSPEC(content)
#define OG_MACRO_GNU(content) content
#define OG_MACRO_GNU_ATTRIBUTE(...) __attribute__((__VA_ARGS__))
#else
#define OG_MACRO_FUNCTION __FUNCTION__
#define OG_MACRO_PRIVATE
#define OG_MACRO_MSVC(content)
#define OG_MACRO_MSVC_DECLSPEC(content)
#define OG_MACRO_GNU(content)
#define OG_MACRO_GNU_ATTRIBUTE(...)
#endif
#if __STDC_VERSION__ >= 201112L && __STDC_VERSION__ < 202311L
#include <stdnoreturn.h>
#define OG_MACRO_NORETURN noreturn
#else
#define OG_MACRO_NORETURN
#endif

#if (defined(__cplusplus) && __cplusplus >= 201103L) || (__STDC_VERSION__ >= 202311L)
#define OG_MACRO_THREAD_LOCAL thread_local
#elif __STDC_VERSION__ >= 201112L
#define OG_MACRO_THREAD_LOCAL _Thread_local
#else
#if (defined(__GNUC__))
#define OG_MACRO_THREAD_LOCAL __thread
#else
static_assert(
    false, "No thread local support.")
#endif
#endif
#endif

#if defined __cplusplus
#define OG_MACRO_C(content)
#define OG_MACRO_CPP(content) content
#define OG_MACRO_C_BLOCK_BEGIN \
    extern "C" \
    {
#define OG_MACRO_C_BLOCK_END }
#else
#define OG_MACRO_C(content) content
#define OG_MACRO_CPP(content)
#define OG_MACRO_C_BLOCK_BEGIN
#define OG_MACRO_C_BLOCK_END
#endif
#endif
