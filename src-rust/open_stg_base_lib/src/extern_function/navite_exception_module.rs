pub type HError = u64;
pub type HErrorCode = u32;
pub type HNamespace = u32;

pub const OPEN_STG_NAMESPACE_CORE: HNamespace = 0x1;
pub const OPEN_STG_NAMESPACE_GRAPHICS: HNamespace = 0x2;
pub const OPEN_STG_NAMESPACE_NETWORK: HNamespace = 0x3;
pub const OPEN_STG_NAMESPACE_LOGIC: HNamespace = 0x4;

pub const OPEN_STG_ERROR_CODE_CORE_NO_ERROR: HErrorCode = 0x0;
pub const OPEN_STG_ERROR_CODE_CORE_CORE_STL_ALLOC_ERROR: HErrorCode = 0x1;
pub const OPEN_STG_ERROR_CODE_CORE_MEMORY_ERROR: HErrorCode = 0x2;
pub const OPEN_STG_ERROR_CODE_CORE_UNDEFINED_MEMORY_ERROR: HErrorCode = 0x3;
pub const OPEN_STG_ERROR_CODE_CORE_INVALID_PARAMETER: HErrorCode = 0x4;
pub const OPEN_STG_ERROR_CODE_CORE_MODULE_EXIST: HErrorCode = 0x5;
pub const OPEN_STG_ERROR_CODE_CORE_MODULE_NOT_EXIST: HErrorCode = 0x6;
pub const OPEN_STG_ERROR_CODE_CORE_NOT_INITIALIZED: HErrorCode = 0x7;
pub const OPEN_STG_ERROR_CODE_CORE_OUT_OF_RANGE: HErrorCode = 0x8;

#[inline]
pub const fn make_error(namespace: HNamespace, code: HErrorCode) -> HError {
    return (namespace as HError) << 32 | (code as HError);
}
#[inline]
pub const fn get_error_namespace(error: HError) -> HNamespace {
    (error >> 32) as HNamespace
}
#[inline]
pub const fn get_error_code(error: HError) -> HErrorCode {
    (error & 0xFFFFFFFF) as HErrorCode
}
