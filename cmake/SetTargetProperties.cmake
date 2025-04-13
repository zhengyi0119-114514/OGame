set_target_properties(open_stg_lib PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS TRUE
    C_STANDARD 17
    C_STANDARD_REQUIRED TRUE
    C_EXTENSIONS TRUE
)
target_compile_features(
    open_stg_lib PUBLIC
    cxx_std_20
    cxx_constexpr
    cxx_nullptr
    c_std_17
)