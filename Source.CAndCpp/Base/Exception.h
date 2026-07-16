#include <OpenSTG/OpenStgBase.h>
#if !defined(OPEN_STG_EXCEPTION_H)
#define OPEN_STG_EXCEPTION_H 1
#define OPEN_STG_CONST_MINIMUN_STRING_LENGTH 64
#define OPEN_STG_CONST_MAXIMUN_STRING_LENGTH 64

OG_MACRO_PRIVATE OgConstantString OgExceptionStructureOutOfRangeGetExceptionName(void);
OG_MACRO_EXTERN struct OgExceptionInformation *OgExceptionStructureUndefineBehaviorGetInformation(
    void
);
OG_MACRO_PRIVATE OgConstantString OgExceptionStructureInvalidArgumentGetExceptionName(void);
OG_MACRO_EXTERN struct OgExceptionInformation *OgExceptionStructureInvalidArgumentGetInformation(
    void
);
#endif
