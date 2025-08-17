/**
 * @file og_interface.hpp
 * @author iCe_tHoRn
 * @brief
 * @version Ciallo～(∠・ω< )⌒★
 * @date 1145-14-19
 *
 */
#ifndef OGAME_STGLIB_INTERFACE_H
#define OGAME_STGLIB_INTERFACE_H 1
#include <map>
#include <memory>
#include <string>
namespace open_stg::interface_h
{
struct Tag
{
    virtual ~Tag() noexcept = default;
};
template <typename TProperty>
struct PropertyReferenceTag
{
    
};
} // namespace open_stg::interface_h
#endif
