#include <string.h>
#include <stdlib.h>
#if !defined(OPEN_STG_MACRO_BASE_STRING_H)
#define OPEN_STG_MACRO_BASE_STRING_H 1
#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Exceptions.h>
OG_MACRO_C_BLOCK_BEGIN

inline OgBoolean OgStringIsNullOrEmpty(OgConstantString pcsString);
typedef struct OgStringEx
{
    OgString String;
    OgUnsignedIntegerSize StringSize;
    struct OgConstantAllocator *Allocator;
} OgStringEx;

OG_MACRO_EXTERN struct OgExceptionCollectionFormatException OgStringCopy(
    OG_MACRO_MSVC(_Out_z_) OgString const psDestination,
    OgSignedInteger64 iDestinationSize,
    OG_MACRO_MSVC(_In_z_) OgConstantString const pcsSource,
    OgSignedInteger64 iCharatersToCopy
) OG_MACRO_GNU_ATTRIBUTE(__nonnull__(1, 3), __nothrow__);

/**
 * @brief Append a copy of the null-terminated byte string pointed to by pcsSource to the end of the
 * null-terminated byte string pointed to by psDestination.The character pcsSource[0] replaces the
 * null terminator at the end of psDestination the resulting byte string is null-terminated.
 *
 * @note If iDestinationSize are less than 0,the behavior is undefined if the source and destination
 * strings overlap like "strcat" or "strncat".
 * @note If iCharatersToConnect are less than 0,copies the null-terminated byte string pointed to by
 * pcsSource,include the null terminator.
 *
 * @param[in,out] psDestination The pointer to the null-terminated byte string to append to.
 * @param iDestinationSize Minimum number of character to write,typically the size of the
 * destination buffer.
 * @param[in] pcsSource Pointer to the null-terminated byte string to copy from.
 * @param iCharatersToConnect Maximum number of character to copy.Default value is -1.
 */
OG_MACRO_EXTERN struct OgExceptionCollectionFormatException OgStringConnect(
    OG_MACRO_MSVC(_Inout_z_) OgString const psDestination,
    OgSignedInteger64 iDestinationSize,
    OG_MACRO_MSVC(_In_z_) OgConstantString const pcsSource,
    OgSignedInteger64 iCharatersToConnect
) OG_MACRO_GNU_ATTRIBUTE(__nonnull__(1, 3), __nothrow__);

#define OgStringGetEmptyString() ""

OG_MACRO_C_BLOCK_END
#if !defined(OPEN_STG_MACRO_BASE_STRING_INLINE_H)
#include <OpenSTG/OpenStgBase.String.Inline.h>
#endif
#endif
