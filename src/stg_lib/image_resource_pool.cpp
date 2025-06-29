#include "options.hpp"
#include "error_h.hpp"
using namespace open_stg::sdl2_h;
using namespace open_stg::error_h;

namespace open_stg::opt_h
{
image_resource_pool::image_resource_pool() : m_nameIdMap{}, m_surfacePool{},m_writeLock{}
{
}

uint32_t image_resource_pool::add_surface(std::string_view name, open_stg::sdl2_h::shared_ptr_surface surf)
{
    m_writeLock.lock();
    auto id = m_surfacePool.size();
    m_surfacePool.push_back(surf);
    m_nameIdMap.insert(std::pair<std::string, uint32_t>{std::string{name},id});
    m_writeLock.unlock();
    return id;
}

uint32_t image_resource_pool::get_id_form_name(std::string_view name)
{
    if(!m_nameIdMap.contains(std::string{name}))
    {
        throw name_not_exist_error{name};
    }
    return m_nameIdMap.at(std::string(name));
}

open_stg::sdl2_h::shared_ptr_surface image_resource_pool::get_surface_form_id(uint32_t id)
{  
    return m_surfacePool.at(id);
}

open_stg::sdl2_h::shared_ptr_surface image_resource_pool::get_surface_form_name(std::string_view name)
{
    return m_surfacePool[m_nameIdMap[std::string{name}]];
}

}