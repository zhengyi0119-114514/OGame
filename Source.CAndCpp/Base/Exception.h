#include <OpenSTG/OpenStgBase.h>
#if !defined(OPEN_STG_EXCEPTION_H)
#define OPEN_STG_EXCEPTION_H 1
#define OPEN_STG_CONST_MINIMUN_STRING_LENGTH 64
#define OPEN_STG_CONST_MAXIMUN_STRING_LENGTH 64

OgMacroPrivate struct OgExceptionCollectionFormatException
    OgPrivateExceptionStructureOutOfRangeFormatMessage(
        OgPVoid pvExceptionSource,
        OgUnsignedIntegerSize uDestinationBufferSize,
        OgString psDestinationBuffer
    );
OgMacroPrivate struct OgExceptionCollectionFormatException
    OgPrivateExceptionStructureOutOfRangeGetExceptionMessageLength(
        OgPVoid pvExceptionSource, OgUnsignedIntegerSize *const puMessageLength
    );
OgMacroPrivate struct OgExceptionCollectionFormatException
    OgPrivateExceptionStructureOutOfRangeSerialize(
        OgPVoid pvExceptionSource,
        OgPVoid pvDestinationBuffer,
        OgUnsignedIntegerSize puDestinationBufferSize
    );
OgMacroPrivate struct OgExceptionCollectionFormatException
    OgPrivateExceptionStructureOutOfRangeDeserialize(
        OgPVoid pvDestinationBuffer,
        OgUnsignedIntegerSize puDestinationBufferSize,
        OgPVoid pvSourceBuffer,
        OgUnsignedIntegerSize puSourceBufferSize
    );
OgMacroPrivate OgConstantString OgPrivateExceptionStructureOutOfRangeGetExceptionName(void);
OgMacroExport const struct OgExceptionInformation *OgExceptionStructureOutOfRangeGetInformation(void);
OgMacroPrivate OgConstantString OgExceptionStructureInvalidArgumentGetExceptionName(void);
OgMacroExport const struct OgExceptionInformation *OgExceptionStructureInvalidArgumentGetInformation(
    void
);
OgMacroExport const struct OgExceptionInformation *OgExceptionStructureUndefineBehaviorGetInformation(
    void
);
OgMacroExport const struct OgExceptionInformation *OgExceptionStructureUndefineBehaviorGetInformation(
    void
);
OgMacroExport OgMacroNoreturn void OgExceptionPanic(OgConstantString pcsDescription);
#endif
