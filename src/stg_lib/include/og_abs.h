/**
 * @file og_abs.h
 * @author zhengyi0119
 * @brief [一个专门用来搞代码抽象的头文件]
 * @version 0.1
 * @date 2025-08-24
 *
 */
#ifndef OPEN_STG_ABSTRACT
#define OPEN_STG_ABSTRACT 1
#include "og_macro.h"

#define l_ (
#define r_ )
#define lar_ ()
#define l__ [
#define r__ ]
#define BEGIN_BLOCK {
#define END_BLOCK }
#define EMPTY_BLOCK {}
#define END_LINE ;
#define NEXT ,
#define FAKE_FALSE 1
#define FAKE_TRUE 0
#define DOT .
#define COLON :
#define DOUBLE_COLON ::
#define ASSIGN_VALUE = 

typedef SByte i_;
typedef SInt i__;
typedef Int i____;
typedef LLInt i________;

typedef Byte u_;
typedef USInt u__;
typedef UInt u____;
typedef ULLInt u________;

#endif
