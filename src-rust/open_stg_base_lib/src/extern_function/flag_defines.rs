pub type ModuleRegisteredFlag = u64;

pub const OPEN_STG_CONST_CHAR_BUFFER_LENGTH: u64 = 256;
pub const OPEN_STG_CONST_ADDITIONAL_ERROR_MESSAGE_STRING_LENGTH: u64 = 128;

pub type UniversalRegistrarInformationFlag = u64;
pub const OPEN_STG_FLAG_UNIVERSAL_REGISTRAR_NONE: UniversalRegistrarInformationFlag =
    0x0000000000000000;
pub const OPEN_STG_FLAG_UNIVERSAL_REGISTRAR_NOT_INITIALIZED: UniversalRegistrarInformationFlag =
    0x0000000000000001;

pub const OPEN_STG_REGISTRAR_NAME_CORE: &'static str = "ice_thorn.core.cirno_baka";
