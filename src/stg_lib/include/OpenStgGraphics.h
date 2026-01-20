#include <OpenStgDefine.h>
#if !defined OPEN_STG_GRAPHICS_H
#define OPEN_STG_GRAPHICS_H 1
#if defined __cplusplus
extern "C"
{
#endif
/**
 * @brief 初始化OpenStg的图形部分
 * @param ufInitFlag 指示初始化的BitFalg
 * @return BOOL_T 成功返回TRUE，失败返回FALSE 
 */
OG_EXTERN BOOL_T OG_CDECL OgGpInit(uint64_t ufInitFlag);
#if defined __cplusplus
}
#endif
#endif