#if !defined OPEN_STG_MATE_PP_H
#define OPEN_STG_MATE_PP_H 1
#if defined __cplusplus
namespace OpenStg::MateProgramming::Internal
{
template <bool bCondition, typename TTrue, typename TFalse> class IfElse_Type;
template <typename TTrue, typename TFalse> class IfElse_Type<true, TTrue, TFalse>
{
  public:
    using Type = TTrue;
};
template <typename TTrue, typename TFalse> class IfElse_Type<false, TTrue, TFalse>
{
  public:
    using Type = TFalse;
};
template <bool bCondition, bool bTrue, bool bFalse> class IfElseBool_Type;
template <bool bTrue, bool bFalse> class IfElseBool_Type<true, bTrue, bFalse>
{
  public:
    constexpr const inline static bool Value = bTrue;
};
template <bool bTrue, bool bFalse> class IfElseBool_Type<false, bTrue, bFalse>
{
  public:
    constexpr const inline static bool Value = bFalse;
};
}; // namespace OpenStg::MateProgramming::Internal
#endif
#endif