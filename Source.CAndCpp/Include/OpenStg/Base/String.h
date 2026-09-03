#if !defined(OgBaseMacroHeaderTagString)
#define OgBaseMacroHeaderTagString 1
#include <OpenStg/Base/Base.h>

OgMacroCBlockBegin

enum OgBsStringException
{
    OgBsStrExcNone = 0, /**< No exception.*/
    OgBsStrExcOutOfRange = 0x00000001,
    OgBsStrExcInvaildArgument = 0x00000002,

    OgBsStrExcAyachiNene = 0x0d000721, /**< Ciallo～(∠・ω< )⌒★ */
};

enum OgBsStringManipulation
{
    OgBsStrManNone = 0,
    OgBsStrManFillNullOnFailure = 0x00000001,
};

extern OgSignedIntegerSize OgBsStringGetLength(OgConstantString pcsStr);
extern OgSignedIntegerSize OgBsStringGetCharacterCount(OgConstantString pcsStr);
/**
 * @brief Appends a string.
 *
 * Appends a copy of the null-terminated byte string pointed to by 'pcsSource' to the end of the
 * null-terminated byte string pointed to by 'psDestination'.
 *
 * @param pcsSource Pointer to the null-terminated byte string to copy from.
 * @param psDestination Pointer to the null-terminated byte string to append to.
 * @param sDestinationLength Maximum number of characters to write,
 *
 * @exception OgBsStrExcInvaildArgument 'pcsSource' is null.
 */
extern enum OgBsStringException OgBsStringConcat(
    OgConstantString pcsSource,
    OgString psDestination,
    OgSignedIntegerSize sDestinationLength,
    enum OgBsStringManipulation
);
extern enum OgBsStringException OgBsStringCopy();

#if defined OgMacroOptionsEnableUnicode && OgMacroOptionsEnableUnicode
extern OgSignedIntegerSize OgBsUtf8StringGetLength(OgConstantUtf8String pcsStr);
extern OgSignedIntegerSize OgBsUtf8StringGetCharacterCount(OgConstantUtf8String pcsStr);

extern OgSignedIntegerSize OgBsUtf16StringGetLength(OgConstantUtf16String pcsStr);
extern OgSignedIntegerSize OgBsUtf16StringGetCharacterCount(OgConstantUtf16String pcsStr);

extern OgSignedIntegerSize OgBsUtf32StringGetLength(OgConstantUtf32String pcsStr);
extern OgSignedIntegerSize OgBsUtf32StringGetCharacterCount(OgConstantUtf32String pcsStr);
#endif

OgMacroCBlockEnd
#endif
