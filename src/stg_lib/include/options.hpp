#ifndef OGAME_STGLIB_OPT_H
#define OGAME_STGLIB_OPT_H
#include <filesystem>
#include <vector>
#include <string>
#include <string_view>
#include <map>
#include "sdl.hpp"
#include <mutex>
namespace open_stg::opt_h
{
std::filesystem::path get_program_option_path();
class image_resource_pool
{
  public:
    constexpr const static inline uint32_t invalid_id = 1'145'141'919;
    explicit image_resource_pool();
    uint32_t add_surface(std::string_view name, open_stg::sdl2_h::shared_ptr_surface surf);
    uint32_t get_id_form_name(std::string_view name);
    open_stg::sdl2_h::shared_ptr_surface get_surface_form_id(uint32_t id);
    open_stg::sdl2_h::shared_ptr_surface get_surface_form_name(std::string_view name);

  private:
    std::map<std::string, uint32_t> m_nameIdMap;
    std::vector<open_stg::sdl2_h::shared_ptr_surface> m_surfacePool;
    std::mutex m_writeLock;
};
}
#endif