#if !defined(OPEN_STG_MACRO_BASE_MACRO_H)
#define OPEN_STG_MACRO_BASE_MACRO_H 1
#if defined(_MSC_VER)
// MSVC style
#define OgMacroExtern __deslspec(dllimport)
#define OgMacroExport __declspec(dllexport)
#define OgMacroFunction __FUNCSIG__
#define OgMacroPrivate
#define OgMacroThreadLocal __declspec(thread)
#define OgMacroAlwaysInline __forceinline
#define OgMacroMsvc(Content) Content
#define OgMacroMsvcDeclspec(Content) __declspec(Content)
#define OgMacroGnu(Content)
#define OgMacroGnuAttribute(...)
#define OgMacroThreadLocal __declspec(thread)
#define OgMacroNoreturn __declspec(noreturn)
#elif defined(__GNUC__) || defined(__llvm__) || defined(__clang__)
#define OgMacroExtern extern
#define OgMacroExport __attribute__(())
#define OgMacroPrivate __attribute__((__visibility__("hidden")))
#define OgMacroAlwaysInline __attribute__((__always_inline__))
#define OgMacroFunction __PRETTY_FUNCTION__
#define OgMacroMsvc(content)
#define OgMacroMsvcDeclspec(content)
#define OgMacroGnu(content) content
#define OgMacroGnuAttribute(...) __attribute__((__VA_ARGS__))
#define OgMacroThreadLocal __thread
#define OgMacroNoreturn __attribute__((__noreturn__))
#else
#define OgMacroExtern extern
#define OgMacroExport __attribute__((__visibility__("default")))
#define OgMacroFunction __func__
#define OgMacroPrivate
#define OgMacroMsvc(content)
#define OgMacroMsvcDeclspec(content)
#define OgMacroGnu(content)
#define OgMacroGnuAttribute(...)
#if (__STDC_VERSION__ >= 202311L && !defined(__STDC_NO_THREADS__))
#define OgMacroThreadLocal thread_local
#elif (__STDC_VERSION__ >= 201112L && !defined(__STDC_NO_THREADS__))
#define OgMacroThreadLocal _Thread_local
#elif (__cplusplus >= 200806L)
#define OgMacroThreadLocal thread_local
#endif
#if (__STDC_VERSION__ >= 202311L)
#define OgMacroNoreturn [[noreturn]]
#elif (__STDC_VERSION__ >= 201112L)
#define OgMacroNoreturn _Noreturn
#else
#define OgMacroNoreturn
#endif
#endif
#if defined __cplusplus
#define OgMacroC(Content)
#define OgMacroCPP(Content) Content
#define OgMacroCBlockBegin \
    extern "C" \
    {
#define OgMacroCBlockEnd }
#define OgMacroStaticCast(Type, Value) static_cast<Type>((Value))
#define OgMacroConstantCast(Type, Value) const_cast<Type>((Value))
#define OgMacroDymanicCast(Type, Value) dymanic_cast<Type>((Value))
#else
#define OgMacroC(content) content
#define OgMacroCPP(content)
#define OgMacroCBlockBegin
#define OgMacroCBlockEnd
#define OgMacroStaticCast(Type, Value) ((Type)(Value))
#define OgMacroConstantCast(Type, Value) ((Type)(Value))
#define OgMacroDymanicCast(Type, Value) ((Type)(Value))
#endif
#endif
