#include <OpenStg/OpenStgDefine.h>
#if !defined OPEN_STG_NETWORK_H
#define OPEN_STG_NETWORK_H 1
#if defined __cplusplus
extern "C"
{
#endif
/**
 * @brief 初始化网络子模块 
 * @param ufInitflag 初始化符号
 * @return BOOL_T 成功返回TRUE，失败返回FALSE 
 */
OG_EXTERN BOOL_T OG_API OgNwInit();
#if defined __cplusplus
}
#endif
#endif