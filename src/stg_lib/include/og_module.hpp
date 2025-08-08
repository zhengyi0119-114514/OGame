/**
 * @file og_module.hpp
 * @author ice-THORN
 * @brief [MVVM的模型部分]
 * @version Ciallo～(∠・ω< )⌒★
 * @date 2025-08-06
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef OGAME_STGLIB_MOUDLE_H
#define OGAME_STGLIB_MOUDLE_H 1
#include "og_math_h.hpp"
#include "og_templates_h.hpp"
namespace open_stg::mod_h
{
struct IRegister
{
    virtual void registered() = 0;
    virtual uint32_t get() = 0;
};
class game_object
{
  public:
    virtual ~game_object() noexcept = default;
};
class scene
{
  protected:
    math_h::size m_sSize{
        math_h::SIZE_UNDEFINED,
        math_h::SIZE_UNDEFINED,
    };
    uint32_t m_uOperationsPerSecond = 60;
    virtual void wait_to_next_operation(IRegister *reg);

  public:
    scene() = default;
};
using Scene = scene;

// default mode
class stg_scene final : public scene
{
  private:
    using scene::m_sSize;
    using scene::m_uOperationsPerSecond;

  public:
    const constexpr static inline uint32_t OperationsPerSecond = 60;
    stg_scene();
};
using STGScene = stg_scene;
class stg_game_object : public game_object
{
  protected:
    uint32_t m_uGroup;
};

} // namespace open_stg::mod_h
#endif