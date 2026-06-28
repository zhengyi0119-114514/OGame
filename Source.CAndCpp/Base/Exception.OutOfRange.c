#include "Exception.h"
#include <stdio.h>

// static const struct OgExceptionInformation s_eiOutOfRangeException
//     = {OgExceptionOutOfRangeFormatExceptionMessageWarpper,
//        OgExceptionOutOfRangeGetExceptionMessageLengthWrapper, NULL, NULL,
//        OgExceptionOutOfRangeGetExceptionName};
// {
//     OgExceptionFormattingException e = {};
//     e.Type = OgExceptionEnumFormatingExceptionItemNone;
//     // Check arugement:
//     if (poorException == NULL)
//     {
//         e.Type = OgExceptionEnumFormatingExceptionItemInvalidArgument;
//         e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
//             "struct OgExceptionStructureOutOfRange *poorException", OgStringGetEmptyString());
//         return e;
//     }
//     if (psDestinationBuffer == NULL)
//     {
//         e.Type = OgExceptionEnumFormatingExceptionItemInvalidArgument;
//         e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
//             "OgString psDestinationBuffer", OgStringGetEmptyString());
//         return e;
//     }
//     OgUnsignedInteger64 uCharaterWritten = 0;
//     OgString psNextStringStart = psDestinationBuffer;
//     // Print type name.
//     int iStatus = 0;
//     iStatus = snprintf(
//         psNextStringStart, uDestinationBufferSize, "Throw Exception :%s\n",
//         OgExceptionOutOfRangeGetExceptionName());
//     if (iStatus < 0)
//     {
//         e.Type = OgExceptionEnumFormatingExceptionItemUndefineBehavior;
//         e.UndefineBehavior = OgExceptionStructureUndefineBehaviorCreate(
//             "snprintf function return a negative number.");
//         return (e);
//     }
//     uCharaterWritten += (OgUnsignedInteger64)(iStatus);
//     psNextStringStart += iStatus;
//     // NOTE: For the terminating null character
//     if (uCharaterWritten >= uDestinationBufferSize - 1)
//     {
//         e.Type = OgExceptionEnumFormatingExceptionItemOutOfRange;
//         e.OutOfRange = OgExceptionStructureOutOfRangeCreateWithInteger64(
//             "OgUnsignedInteger64 uDestinationBufferSize;OgString psDestinationBuffer",
//             (OgSignedInteger64)uDestinationBufferSize, 0, "We need longer destination buffer.");
//         goto CleanUp;
//     }
//     goto PrintMinimumValue;
//     // print description
//     // Minimum
// PrintMinimumValue:
//     if (poorException->MinimumValue[0] == '\0')
//     {
//         goto PrintMaximumValue;
//     };
//     iStatus = 0;
//     iStatus = snprintf(
//         psNextStringStart, uDestinationBufferSize - uCharaterWritten, "Minimum value:%s\n",
//         poorException->MinimumValue);
//     if (iStatus < 0)
//     {
//         e.Type = OgExceptionEnumFormatingExceptionItemUndefineBehavior;
//         e.UndefineBehavior = OgExceptionStructureUndefineBehaviorCreate(
//             "snprintf function return a negative number.");
//         return (e);
//     }
//     uCharaterWritten += (OgUnsignedInteger64)(iStatus);
//     psNextStringStart += iStatus;
//     if (uCharaterWritten >= uDestinationBufferSize)
//         goto SnprintfException;
// PrintMaximumValue:
//     if (poorException->MaximumValue[0] == '\0')
//     {
//         goto PrintDebugInformation;
//     }
//     iStatus = 0;
//     iStatus = snprintf(
//         psNextStringStart, uDestinationBufferSize - uCharaterWritten, "Maximum value:%s\n",
//         poorException->MaximumValue);
//     if (iStatus < 0)
//         goto SnprintfException;
//
// PrintDebugInformation:
// ReturnValue:
//     return e;
// CleanUp:
//     memset((OgPVoid)psDestinationBuffer, 0, uDestinationBufferSize);
//     e.Type = OgExceptionEnumFormatingExceptionItemNone;
//     return (e);
// SnprintfException:
//     e.Type = OgExceptionEnumFormatingExceptionItemUndefineBehavior;
//     e.UndefineBehavior
//         = OgExceptionStructureUndefineBehaviorCreate("snprintf function return a negative number.");
//     return (e);
// }
// OG_MACRO_EXPORT OgExceptionFormattingException OgExceptionOutOfRangeGetExceptionMessageLength(
//     struct OgExceptionStructureOutOfRange *poorException,
//     OgUnsignedInteger64 *const puMessageLength);

OG_MACRO_PRIVATE OgConstantString OgExceptionStructureOutOfRangeGetExceptionName()
{
    return ("OpenStg.Base.Exception.OutOfRangeException");
}
OG_MACRO_EXTERN struct OgExceptionInformation *OgExceptionStructureOutOfRangeGetInformation(void);
