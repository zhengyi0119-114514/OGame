#ifndef OG_MACRO_H
#define OG_MACRO_H 1

// ==================== C++ 关键字宏定义 ====================
// 这些宏提供对标准C++关键字的别名，提高代码可读性和一致性
// 实际上是让“关键字”在LSP中的排名前一点

// 模板和泛型编程
#define TypeName typename

// 类型转换
#define StaticCast static_cast
#define ConstCast const_cast
#define DynamicCast dynamic_cast

#define NullPtr nullptr
#define StaticAssert static_assert
#define Static static
#define VAR auto // Form C#
#define AUTO auto
#define SizeOf sizeof
#define NameOf(identifier) #identifier


// ==================== 项目特定宏定义 ====================
// 这些宏提供项目特定的语义和约定

// 接口定义宏
#define OG_INTERFACE struct

// this指针解引用宏
#define RefThis (*this)

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
#if defined DEBUG || defined _DEBUG || defined debug
const constexpr static inline Bool IsDebug = true;
#else
const constexpr static inline Bool IsDebug = false;
#endif
#endif

#endif // OG_MACRO_H
