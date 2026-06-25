#include <OpenSTG/OpenStgBase.Macro.h>
#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Exceptions.h>
#include <OpenSTG/OpenStgBase.Module.h>

#if !defined(OPEN_STG_MODULE_H)
#define OPEN_STG_MODULE_H 1
OG_MACRO_C_BLOCK_BEGIN

OG_MACRO_EXTERN OgException OgModuleRegister(const struct OgModule *pcModule);
OG_MACRO_EXTERN OgException OgModuleGetRegisteredModule(
    OgConstantString pcsModuleRegisteredName,
    const struct OgModule **pOutput);
OG_MACRO_EXTERN OgException OgModuleFree(const OgConstantString pcsModuleRegisteredName);
OG_MACRO_EXTERN OgException OgModuleLoad(const OgConstantString pcsModulePath);

OG_MACRO_C_BLOCK_END
#endif
