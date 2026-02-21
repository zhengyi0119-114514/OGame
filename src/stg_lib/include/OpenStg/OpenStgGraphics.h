#include <OpenStg/OpenStgDefine.h>
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
OG_EXTERN BOOL_T OG_API OgGpInit();
/**
 * @brief 退出图形模块
 */
OG_EXTERN void OG_API OgGpQuit();
/**
 * @brief 
 * 
 * @param code 错误码
 * @param pszBuffer 输出字符串地址
 * @param uLengthOfBuffer 输出字符串缓冲区长度
 * @return OG_EXTERN 
 */
OG_EXTERN void OG_API OgGpFormatErrorMessage(OG_ERROR_CODE_T code, char *pszBuffer, uint64_t uLengthOfBuffer);
#if defined __cplusplus
}
#endif
#endif