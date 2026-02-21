pub mod flag_defines;
pub mod navite_exception_module;

use std::ffi::{c_char, c_void};

use crate::extern_function::navite_exception_module::{HError, HNamespace};

/// 电磁打点计时器指针类型
pub type PtrElectromagneticDotTimer = *mut c_void;
/// 程序模块迭代器指针类型
pub type PtrProgramModuleIterator = *mut c_void;
/// 通用注册器指针类型
pub type PtrUniversalRegistrar = *mut c_char;
/// 通用注册器迭代器指针类型
pub type PtrUniversalRegistrarIterator = *mut c_void;
/// 私有程序模块指针类型
pub type PtrPrivateProgramModule = *mut c_void;

/// 销毁程序模块函数类型
pub type DestoryProgramModuleFunction = extern "C" fn();

pub type InitalzationFunction = extern "C" fn();
/// 模块附加信息释放函数类型
pub type ModuleAdditionalInformationReleaseFunction = extern "C" fn(*mut c_void);
/// 销毁成员函数类型
pub type DestoryMemberFuntion = extern "C" fn(mem: *mut c_void);
/// 格式化错误消息函数类型
pub type FormatErrorMessageFunction = extern "C" fn(
    error_code: navite_exception_module::HErrorCode,
    buffer: *mut c_char,
    buffer_length: u64,
);
/// 异常处理器函数类型
pub type ExceptionHandlerFunction = extern "C" fn(e: HError, is_recoverable_exception: BoolT);
/// 布尔类型 (对应 C 中的 BOOL_T)
pub type BoolT = u8;

/// 线程局部存储结构
#[repr(C)]
pub struct ThreadLocalStorageStruct {
    /// 通用缓冲区
    pub universal_buffer: [c_char; flag_defines::OPEN_STG_CONST_CHAR_BUFFER_LENGTH as usize],
    /// 附加错误消息
    pub additional_error_message:
        [c_char; flag_defines::OPEN_STG_CONST_ADDITIONAL_ERROR_MESSAGE_STRING_LENGTH as usize],
    /// 错误码
    pub errno: navite_exception_module::HError,
    /// 是否可恢复异常
    pub is_recoverable_exception: BoolT,
}

/// 程序模块结构
#[repr(C)]
pub struct ProgramModule {
    /// 版本控制，总应该初始化为 sizeof(OG_CR_PROGRAM_MODULE)
    pub size: i64,
    /// 模块注册标志
    pub module_registered_flag: flag_defines::ModuleRegisteredFlag,
    /// 模块显示名称，如果为 NULL，则会被设置为 module_registered_name
    pub module_display_name: *const c_char,
    /// 注册名称，必须是唯一的
    pub module_registered_name: *const c_char,
    /// 获取错误码对应的字符串描述函数
    pub format_error_message: FormatErrorMessageFunction,
    /// 模块的销毁函数
    pub destory_program_module: DestoryProgramModuleFunction,
    ///这个函数将会在依赖树构建完成后按依赖顺序调用
    pub post_initalzation_function: InitalzationFunction,
    /// 模块额外信息
    pub additional_data: *mut c_void,
    /// 模块额外信息释放函数
    pub free_func: ModuleAdditionalInformationReleaseFunction,
    /// 指向一个字符串数组，包含依赖项的注册名
    pub dependencies_registered_name: *const *const c_char,
    /// 指示 dependencies_registered_name 成员的个数
    pub dependency_number: u32,
    /// 模块空间名称
    pub module_namespace: navite_exception_module::HNamespace,
}

/// 通用注册器创建信息
#[repr(C)]
pub struct UniversalRegistrarInformation {
    /// 版本控制，总应该初始化为 sizeof(OG_CR_UNIVERSAL_REGISTRAR_INFORMATION)
    pub size: u64,
    /// 创建标志
    pub create_flag: flag_defines::UniversalRegistrarInformationFlag,
    /// 结构名称
    pub structure_name: *const c_char,
    /// 单位结构大小
    pub unit_structure_size: u32,
    /// 预分配结构数量
    pub pre_allocated_structure_count: u32,
    /// 销毁成员函数
    pub destory_member_function: DestoryMemberFuntion,
}

unsafe extern "C" {
    /// 创建"电磁打点计时器"
    ///
    /// 该函数会且仅会分配内存和写入时间表，所以想要开始计时功能请调用
    /// `OgCrRefreshElectromagneticDotTimer()` 函数
    ///
    /// # 注意
    /// 该函数应与 `OgCrDestoryElectromagneticDotTimer()` 函数成对调用
    ///
    /// # 参数
    /// * `iDotFrequency` - 频率，即一秒内任务数，值 < 1 时无效
    ///
    /// # 返回
    /// * 成功时返回电磁打点计时器指针
    /// * 参数无效时返回 NULL
    pub unsafe fn OgCrCreateElectromagneticDotTimer(
        iDotFrequency: i8,
    ) -> PtrElectromagneticDotTimer;

    /// 销毁"电磁打点计时器"
    ///
    /// # 注意
    /// 该函数应与 `OgCrCreateElectromagneticDotTimer()` 函数成对调用
    ///
    /// # 参数
    /// * `pEdt` - 电磁打点计时器指针
    pub unsafe fn OgCrDestoryElectromagneticDotTimer(pEdt: PtrElectromagneticDotTimer);

    /// 计算队列中的任务数
    ///
    /// # 参数
    /// * `pEdt` - 电磁打点计时器指针
    ///
    /// # 返回
    /// * 队列中的任务数
    pub unsafe fn OgCrElectromagneticDotTimerPullTask(pEdt: PtrElectromagneticDotTimer) -> i64;

    /// 等待直到下一个任务加入队列，并清空队列
    ///
    /// # 参数
    /// * `pEdt` - 电磁打点计时器指针
    pub unsafe fn OgCrElectromagneticDotTimerSkipATimeStamp(pEdt: PtrElectromagneticDotTimer);

    /// 初始化并清空队列
    ///
    /// # 参数
    /// * `pEdt` - 电磁打点计时器指针
    pub unsafe fn OgCrRefreshElectromagneticDotTimer(pEdt: PtrElectromagneticDotTimer);

    /// 初始化 Core 部分组件
    ///
    /// 初始化 TLS 结构，模块注册器结构
    ///
    /// # 返回
    /// * 成功时返回 TRUE，否则返回 FALSE
    pub unsafe fn OgCrInit() -> BoolT;

    /// 获取 TLS(线程局部存储)结构的指针
    ///
    /// 不应该为 NULL
    ///
    /// # 注意
    /// * 在 POSIX 环境中，若获取的值为 NULL，则会自动分配内存
    /// * 在 Windows 中，未使用 Pthreads 实现，使用了原生 DllMain() 实现
    ///
    /// # 返回
    /// * 线程局部存储结构的指针
    pub unsafe fn OgCrGetTLSStruct() -> *const ThreadLocalStorageStruct;

    /// 返回一个长度为 OPEN_STG_CONST_UNIVERSAL_BUFFER_LENGTH 的 BYTE 缓冲区
    ///
    /// # 注意
    /// 即 `ThreadLocalStorageStruct` 结构的 `universal_buffer` 可读写字段
    ///
    /// # 返回
    /// * 字符缓冲区指针
    pub unsafe fn OgCrGetCharBuffer() -> *mut c_char;

    /// 创建通用注册器
    ///
    /// # 参数
    /// * `puri` - 必须不为 NULL
    ///
    /// # 返回
    /// * 创建成功的通用注册器，返回 NULL 时设置错误
    pub unsafe fn OgCrCreateUniversalRegistrar(
        puri: *const UniversalRegistrarInformation,
    ) -> PtrUniversalRegistrar;

    /// 在注册器中预订(预分配)指定数量的空位
    ///
    /// # 参数
    /// * `pur` - 通用注册器指针，必须不为 NULL
    /// * `reserve_count` - 预订空位数
    ///
    /// # 返回
    /// * 成功时返回 TRUE，错误时返回 FALSE
    pub unsafe fn OgCrUniversalRegistrarReserveItems(
        pur: PtrUniversalRegistrar,
        reserve_count: u32,
    ) -> BoolT;

    /// 在通用注册器中分配一个新项
    ///
    /// # 参数
    /// * `pur` - 通用注册器指针，必须不为 NULL
    /// * `pOutput` - 返回分配的指针
    ///
    /// # 返回
    /// * 成功时返回非负数(即该对象在容器的索引)，错误时返回负数
    pub unsafe fn OgCrUniversalRegistrarAllocateItem(
        pur: PtrUniversalRegistrar,
        pOutput: *mut *mut c_void,
    ) -> i64;

    /// 分配预分配的项
    ///
    /// # 参数
    /// * `pur` - 通用注册器指针，必须不为 NULL
    /// * `pre_allocated_index` - 预分配项的索引
    /// * `pOutput` - 返回分配的指针
    ///
    /// # 返回
    /// * 成功时返回非负数(即该对象在容器的索引)，错误时返回负数
    pub unsafe fn OgCrUniversalRegistrarAllocatePreallocatedItem(
        pur: PtrUniversalRegistrar,
        pre_allocated_index: u32,
        pOutput: *mut *mut c_void,
    ) -> i64;

    /// 获取通用注册器中指定索引的项
    ///
    /// # 参数
    /// * `pur` - 通用注册器指针，必须不为 NULL
    /// * `index` - 项的索引
    ///
    /// # 返回
    /// * 成功时返回项的指针，失败时返回 NULL，索引无效或索引无内容返回 NULL
    pub unsafe fn OgCrUniversalRegistrarGetItem(
        pur: PtrUniversalRegistrar,
        index: u64,
    ) -> *mut c_void;

    /// 释放通用注册器中指定索引的项
    ///
    /// 如果创建时 `destory_member_function` 不为 NULL 则调用
    /// 受 `OPEN_STG_FLAG_UNIVERSAL_REGISTRAR_NOT_INITIALIZED` 标志影响
    ///
    /// # 参数
    /// * `pur` - 通用注册器指针，必须不为 NULL
    /// * `index` - 要释放的项的索引
    ///
    /// # 返回
    /// * 当参数 `pur` 为 NULL 时返回 TRUE
    /// * `index` 对应的位置不存在返回 TRUE
    /// * 正常时返回 TRUE，否则返回 FALSE
    pub unsafe fn OgCrUniversalRegistrarFreeItem(pur: PtrUniversalRegistrar, index: u64) -> BoolT;
    /// 获取通用注册器中的已分配内存的结构数
    ///
    /// # 参数
    /// * `pur` - 通用注册器指针，必须不为NULL
    ///
    /// # 返回
    /// * 当参数pur为NULL时返回-1，否则返回已分配内存的结构数
    ///
    pub unsafe fn OgCrUniversalRegistrarGetReservedItemCount(pur: PtrUniversalRegistrar) -> u64;

    /// 获取通用注册器中的已分配的结构数
    ///
    /// # 参数
    /// * `pur` - 通用注册器指针，必须不为NULL
    ///
    /// # 返回
    /// * 当参数pur为NULL时返回-1，否则返回已分配的结构数
    ///
    pub unsafe fn OgCrUniversalRegistrarGetAllocatedItemCount(pur: PtrUniversalRegistrar) -> u64;

    /// 销毁通用注册器
    ///
    /// # 参数
    /// * `pur` - 通用注册器指针，必须不为 NULL
    pub unsafe fn OgCrDestoryUniversalRegistrar(pur: PtrUniversalRegistrar);

    /// 创建通用注册器迭代器
    ///
    /// # 参数
    /// * `pur` - 通用注册器指针，必须不为 NULL
    ///
    /// # 返回
    /// * 成功时返回迭代器指针，失败时返回 NULL
    pub unsafe fn OgCrCreateUniversalRegistrarIterator(
        pur: PtrUniversalRegistrar,
    ) -> PtrUniversalRegistrarIterator;

    /// 获取该项，移动通用注册器迭代器到下一项
    ///
    /// # 参数
    /// * `puri` - 通用注册器迭代器指针，必须不为 NULL
    ///
    /// # 返回
    /// * 输出当前项的指针，错误时返回 NULL
    pub unsafe fn OgCrUniversalRegistrarIteratorNext(
        puri: PtrUniversalRegistrarIterator,
    ) -> *mut c_void;

    /// 释放通用注册器迭代器
    ///
    /// # 参数
    /// * `puri` - 通用注册器迭代器指针，必须不为 NULL
    pub unsafe fn OgCrDestoryUniversalRegistrarIterator(puri: PtrUniversalRegistrarIterator);

    /// 向程序注册模块
    ///
    /// # 参数
    /// * `pModule` - 必须非 NULL 的注册模块
    /// * `puNamespaceOutput` - 输出命名空间
    ///
    /// # 返回
    /// * 错误时返回 FALSE
    pub unsafe fn OgCrRegisterProgramModule(
        pModule: *const ProgramModule,
        puNamespaceOutput: *mut u32,
    ) -> BoolT;

    /// 注销指定名称的模块
    ///
    /// # 注意
    /// 用于热重载，仅注销模块，不卸载对应动态库
    ///
    /// # 参数
    /// * `pszModuleRegisteredName` - 模块注册名
    ///
    /// # 返回
    /// * 成功时返回 TRUE，错误时返回 FALSE
    pub unsafe fn OgCrUnregisterProgramModule(pszModuleRegisteredName: *const c_char) -> BoolT;

    /// 获取全局模块注册器的迭代器
    ///
    /// # 返回
    /// * 失败时返回 NULL，否则返回一个可用指针
    pub unsafe fn OgCrCreateProgramModuleRegistrarIterator() -> PtrProgramModuleIterator;

    /// 将迭代器中的指针移动至下一个模块，并返回其指向的模块内容
    ///
    /// # 注意
    /// 不会返回模块的 `dependencies_registered_name` 和 `dependency_number` 成员
    ///
    /// # 参数
    /// * `pIterator` - 创建的迭代器
    /// * `pOutput` - 返回的模块内容
    ///
    /// # 返回
    /// * 成功时返回 TRUE，无下一个模块时返回 FALSE
    pub unsafe fn OgCrProgramModuleRegistrarIteratorNext(
        pIterator: PtrProgramModuleIterator,
        pOutput: *mut ProgramModule,
    ) -> BoolT;

    /// 销毁模块注册器迭代器
    ///
    /// # 参数
    /// * `pIterator` - 要销毁的迭代器
    pub unsafe fn OgCrDestoryProgramModuleRegistrarIterator(pIterator: PtrProgramModuleIterator);

    /// 通过空间名称获取模块指针
    ///
    /// # 参数
    /// * `namespace` - 目标模块空间名称
    ///
    /// # 返回
    /// * 目标模块指针
    pub unsafe fn OgCrGetProgramModulePointerByNamespace(
        namespace: HNamespace,
    ) -> PtrPrivateProgramModule;

    /// 通过模块注册名获取模块指针
    ///
    /// # 参数
    /// * `registered_name` - 模块注册名
    ///
    /// # 返回
    /// * 目标模块指针
    pub unsafe fn OgCrGetProgramModulePointerByRegistrerdName(
        registered_name: *const c_char,
    ) -> PtrPrivateProgramModule;

    /// 通过模块指针获取模块附加数据
    ///
    /// # 参数
    /// * `ptr_module` - 目标模块指针
    ///
    /// # 返回
    /// * 目标模块附加数据
    pub unsafe fn OgCrGetProgramModuleAdditionalData(
        ptr_module: PtrPrivateProgramModule,
    ) -> *mut c_void;

    /// 将错误码转化为字符串
    ///
    /// # 参数
    /// * `code` - 错误码
    /// * `pszBuffer` - 输出字符串缓冲区
    /// * `uLengthOfBuffer` - 缓冲区的长度
    pub unsafe fn OgCrFormatErrorMessage(
        code: navite_exception_module::HErrorCode,
        pszBuffer: *mut c_char,
        uLengthOfBuffer: u64,
    );

    /// 将错误码转化为字符串
    ///
    /// # 注意
    /// 格式化函数由模块提供
    ///
    /// # 参数
    /// * `code` - 错误码
    /// * `pszBuffer` - 输出字符串缓冲区
    /// * `uLengthOfBuffer` - 缓冲区的长度
    pub unsafe fn OgFormatErrorMessage(
        code: navite_exception_module::HError,
        pszBuffer: *mut c_char,
        uLengthOfBuffer: u64,
    );

    /// 设置 OG_ERRNO 和 OG_ERROR_RECOVERABLE
    ///
    /// # 参数
    /// * `ec` - 错误代码
    pub unsafe fn OgCrSetRecoverableError(ec: HError);

    /// 设置不可恢复错误
    ///
    /// # 参数
    /// * `ec` - 错误代码
    pub unsafe fn OgCrSetIrreversibleError(ec: HError);

    /// 设置异常处理器
    ///
    /// # 注意‘
    /// 在 `OgCrSetRecoverableError` 和 `OgCrSetIrreversibleError` 被调用时调用
    ///
    /// # 参数
    /// * `f` - 异常处理器函数
    pub unsafe fn OgCrSetErrorHandler(f: ExceptionHandlerFunction);

    /// 打印调用堆栈
    pub unsafe fn OgCrPrintStackTrace();
}

/// 将 BoolT 转换为 bool
///
/// # 参数
/// * `b` - BoolT 值
///
/// # 返回
#[inline]
pub fn bool_t_as_bool(b: BoolT) -> bool {
    b != 0
}
