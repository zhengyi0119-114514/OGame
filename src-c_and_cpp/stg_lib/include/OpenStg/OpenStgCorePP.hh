#include <OpenStg/OpenStgDefine.h>
#include <OpenStg/OpenStgMateProgramingPP.hh>
#include <functional>
#include <concepts>
#include <utility>
#include <stdexcept>
#if !defined OPEN_STG_CORE_PP_H
#define OPEN_STG_CORE_PP_H
#if defined __cplusplus
namespace OpenStg
{
namespace MateProgramming
{
template <bool bCondition, typename TTrue, typename TFalse>
using IfElse = Internal::IfElse_Type<bCondition, TTrue, TFalse>::Type;
template <bool bCondition, bool bTrue, bool bFalse>
const constexpr static inline bool IfElseBool = Internal::IfElseBool_Type<bCondition, bTrue, bFalse>::Value;
template <bool bCondition, bool bTrue, bool bFalse>
concept CIfElse = IfElseBool<bCondition, bTrue, bFalse>;
} // namespace MateProgramming
template <typename TCondition, typename TValue>
concept CCondition = requires(const TCondition &c, const TValue &v) {
    { c(v) } -> std::convertible_to<BOOL_T>;
};
template <typename T, typename... TParameter>
concept COperator = requires(const T &o, TParameter... args) {
    { o(args...) };
};
template <typename TValueType, typename TValueTypeReal = std::remove_all_extents_t<TValueType>,
          CCondition<const TValueTypeReal &> TCondition, COperator<const TValueTypeReal &> TTrueOperator,
          COperator<const TValueTypeReal &> TFalseOperator>
OG_ALWAYS_INLINE constexpr inline decltype(auto) DoOperatorIfElse(TValueType v, const TCondition &c,
                                                                  const TTrueOperator &to, const TFalseOperator &fo)
{
    if (c(v))
    {
        to(v);
    }
    else
    {
        fo(v);
    }
    return v;
}
OG_ALWAYS_INLINE inline constexpr size_t AlignSize(size_t sSize)
{
    if constexpr (sizeof(void *) == sizeof(uint64_t))
    {
        if (sSize >= sizeof(uint64_t) && (sSize % sizeof(uint64_t)) != 0)
        {
            sSize &= ~(sizeof(uint64_t) - 1);
            sSize += sizeof(uint64_t);
            return sSize;
        }
        else if (sizeof(uint32_t) < sSize && sSize <= sizeof(uint64_t))
        {
            return sizeof(uint64_t);
        }
        else if (sizeof(uint16_t) < sSize && sSize <= sizeof(uint32_t))
        {
            return sizeof(uint32_t);
        }
        else
        {
            return sSize;
        }
    }
    else if constexpr (sizeof(void *) == sizeof(uint32_t))
    {
        if (sSize >= sizeof(uint32_t) && (sSize % sizeof(uint32_t)) != 0)
        {
            sSize &= ~(sizeof(uint32_t) - 1);
            sSize += sizeof(uint32_t);
            return sSize;
        }
        else if (sizeof(uint16_t) < sSize && sSize <= sizeof(uint32_t))
        {
            return sizeof(uint32_t);
        }
        else
        {
            return sSize;
        }
    }
    else
    {
        return sSize;
    }
}
template <typename TUnit> struct AlignedUnit
{
    alignas(AlignSize(sizeof(TUnit)) % sizeof(void *)) BYTE_T rgBytes[AlignSize(sizeof(TUnit))];
    template <typename... TParameters> AlignedUnit(TParameters... arguments)
    {
        new (rgBytes) TUnit(std::forward(arguments)...);
    }
    inline const TUnit &Get() const noexcept
    {
        return *static_cast<const TUnit *>(static_cast<const void *>(rgBytes));
    }
    inline TUnit &Get() noexcept
    {
        return const_cast<TUnit &>(std::as_const(*this).Get());
    }
    ~AlignedUnit() noexcept
    {
        (&Get())->~TUnit();
    }
};

OG_ALWAYS_INLINE inline OG_ERROR_T ConverException(const std::exception &e)
{
    auto *p = &e;
    if (auto *pe = dynamic_cast<const std::bad_alloc *>(p); pe != nullptr)
    {
        return OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_STL_ALLOC_ERROR);
    }
    else if (auto *pe = dynamic_cast<const std::invalid_argument *>(p); pe != nullptr)
    {
        return OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_INVALID_PARAMETER);
    }
    else if (auto *pe = dynamic_cast<const std::out_of_range *>(p); pe != nullptr)
    {
        return OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_OUT_OF_RANGE);
    }
    throw e;
}
} // namespace OpenStg
#endif
#endif
