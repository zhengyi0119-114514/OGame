#include <OpenSTG/OpenStgBase.h>

#if !defined(OPEN_STG_STATIC_VARIABLE_H)
#define OPEN_STG_STATIC_VARIABLE_H
OG_MACRO_C_BLOCK_BEGIN

OG_MACRO_PRIVATE OgException OgPvInitializeStaticVarible(void);
OG_MACRO_PRIVATE OgException OgPvDestroyStaticVariable(void);

OG_MACRO_C_BLOCK_END
#endif
