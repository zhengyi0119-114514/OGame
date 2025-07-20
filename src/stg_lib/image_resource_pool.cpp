#include "options.hpp"
#include "error_h.hpp"
#include <utility>
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
    if(m_nameIdMap.contains(std::string{name}))
    {
        throw open_stg::error_h::name_exist_error(name);
    }
    auto id = m_surfacePool.size();
    m_surfacePool.push_back(surf);
    m_nameIdMap.insert(std::pair<std::string, uint32_t>{std::string{name},(uint32_t)id});
    m_writeLock.unlock();
    return id;
}

uint32_t image_resource_pool::get_id_form_name(std::string_view name) const
{
    if(!m_nameIdMap.contains(std::string{name}))
    {
        throw name_not_exist_error{name};
    }
    return m_nameIdMap.at(std::string(name));
}

const open_stg::sdl2_h::shared_ptr_surface& image_resource_pool::get_surface_form_id(uint32_t id) const
{  
    return m_surfacePool.at(id);
}
shared_ptr_surface& image_resource_pool::get_surface_form_id(uint32_t id_or_handle)
{
    return const_cast<shared_ptr_surface&>(std::as_const(*this).get_surface_form_id(id_or_handle));
}
const open_stg::sdl2_h::shared_ptr_surface& image_resource_pool::get_surface_form_name(std::string_view name) const
{
    return get_surface_form_id(m_nameIdMap.at(std::string{name}));
}
shared_ptr_surface& image_resource_pool::get_surface_form_name(std::string_view name)
{
    return const_cast<shared_ptr_surface&>(std::as_const(*this).get_surface_form_name(name));
}
shared_ptr_surface& image_resource_pool::operator[](std::string_view name)
{
    return get_surface_form_name(name);
}
const shared_ptr_surface& image_resource_pool::operator[](std::string_view name) const
{
    return get_surface_form_name(name);
}
shared_ptr_surface& image_resource_pool::operator[](uint32_t id_or_handle)
{
    return get_surface_form_id(id_or_handle);
}
const shared_ptr_surface& image_resource_pool::operator[](uint32_t id_or_handle) const
{
    return get_surface_form_id(id_or_handle);
}
}