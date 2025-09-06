#ifndef OG_MACRO_H
#define OG_MACRO_H 1

// ==================== C++ 关键字宏定义 ====================
// 这些宏提供对标准C++关键字的别名，提高代码可读性和一致性

// 类型定义关键字
#define CLASS class
#define STRUCT struct
#define UNION union
#define ENUM enum
#define Void void

// 模板和泛型编程
#define TypeName typename
#define Concept concept
#define Requires requires

// 类型转换
#define StaticCast static_cast
#define ConstCast const_cast
#define DynamicCast dynamic_cast

// 面向对象特性
#define Virtual virtual
#define Override override
#define Final final
#define Delete delete

// 内存管理
#define OG_New new
#define OG_Delete delete

// 控制流
#define If if
#define Else else
#define While while
#define For for
#define Break break
#define Return return
#define Continue continue
#define Goto goto
#define Switch switch
#define Case case

// 其他关键字
#define Using using
#define Const const
#define ConstExpr constexpr
#define NoExcept noexcept
#define Explicit explicit
#define Default default
#define This this
#define NullPtr nullptr
#define StaticAssert static_assert
#define Inline inline
#define Static static
#define VAR auto // Form C#
#define AUTO auto

//  替代记号
#define BOOL_NOT not
#define BOOL_OR or
#define BOOL_AND and
#define NOT_EQUAL not_eq
#define EQUAL ==
#define BITOR bitor
#define XOR xor
#define MoreThan >
#define LessThan <

// ==================== 项目特定宏定义 ====================
// 这些宏提供项目特定的语义和约定

// 接口定义宏
#define OG_INTERFACE struct

// this指针解引用宏
#define RefThis (*This)

// ==================== 类型定义 ====================
// 提供明确大小的整数类型别名，确保跨平台一致性

// 布尔类型
typedef bool Bool;

// 有符号整数类型
typedef signed char SByte;          // 8位有符号整数
typedef signed short int SInt;      // 16位有符号整数
typedef signed int Int;             // 32位有符号整数
typedef signed long int LInt;       // 平台相关的有符号长整数
typedef signed long long int LLInt; // 64位有符号整数

// 无符号整数类型
typedef unsigned char Byte;            // 8位无符号整数
typedef unsigned short int USInt;      // 16位无符号整数
typedef unsigned int UInt;             // 32位无符号整数
typedef unsigned long int ULInt;       // 平台相关的无符号长整数
typedef unsigned long long int ULLInt; // 64位无符号整数

typedef float Float;
typedef double Double;
typedef long double LDouble;

#ifdef __cplusplus

template<TypeName T>
Using Ref = T&;
template<TypeName T>
Using Ptr = T*;

#if defined DEBUG || defined _DEBUG || defined debug
Const ConstExpr Static Inline Bool IsDebug = true;
#else
Const ConstExpr Static Inline Bool IsDebug = false;
#endif

#endif

#endif // OG_MACRO_H
