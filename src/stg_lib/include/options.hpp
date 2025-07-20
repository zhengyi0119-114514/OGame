/**
 * @file options.hpp
 * @author IceThorn :(
 * @brief
 * @date 2025-07-19
 * :( :( 写这段的时候差点气死 🐎的
 */
#ifndef OGAME_STGLIB_OPT_H
#define OGAME_STGLIB_OPT_H
#include "sdl.hpp"
#include <filesystem>
#include <map>
#include <mutex>
#include <string>
#include <string_view>
#include <vector>

namespace open_stg::opt_h
{
std::filesystem::path get_program_option_path();
/**
 * @brief Object Pool for image(Surface) [为Surface准备的对象池]
 * @date 2025/7/19
 */
class image_resource_pool
{
  public:
    /**
     * @brief Construct a new image resource pool object
     */
    explicit image_resource_pool();
    /**
     * @brief [将Surface以<name>注册入对象池并返回该Surface的句柄/id。] \n
     * [使用句柄访问Surface比使用名字访问快]
     * @param name Surface的注册名
     * @param surf
     * @return uint32_t Surface的句柄
     * @exception open_stg::error_h::name_exist_error [若名称存在,抛出]
     */
    uint32_t add_surface(std::string_view name, open_stg::sdl2_h::shared_ptr_surface surf);
    /**
     * @brief Get the id form name object
     *
     * @param name
     * @return uint32_t [Surface的句柄/id]
     * @exception name_not_exist_error NULL
     */
    uint32_t get_id_form_name(std::string_view name) const;
    open_stg::sdl2_h::shared_ptr_surface &get_surface_form_id(uint32_t id);
    const open_stg::sdl2_h::shared_ptr_surface &get_surface_form_id(uint32_t id) const;
    open_stg::sdl2_h::shared_ptr_surface &get_surface_form_name(std::string_view name);
    const open_stg::sdl2_h::shared_ptr_surface &get_surface_form_name(std::string_view name) const;
    /**
     * @brief same as get_surface_form_name
     *
     * @param name
     * @return open_stg::sdl2_h::shared_ptr_surface&
     */
    open_stg::sdl2_h::shared_ptr_surface &operator[](std::string_view name);
    open_stg::sdl2_h::shared_ptr_surface &operator[](uint32_t handle_or_id);
    /**
     * @brief same as get_surface_form_name
     *
     * @param name
     * @return const open_stg::sdl2_h::shared_ptr_surface&
     */
    const open_stg::sdl2_h::shared_ptr_surface &operator[](std::string_view name) const;
    const open_stg::sdl2_h::shared_ptr_surface &operator[](uint32_t handle_or_id) const;

  private:
    std::map<std::string, uint32_t> m_nameIdMap;
    std::vector<open_stg::sdl2_h::shared_ptr_surface> m_surfacePool;
    std::mutex m_writeLock;
};
} // namespace open_stg::opt_h
#endif