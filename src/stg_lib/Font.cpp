#include "sdl_ttf.hpp"
#include <SDL_ttf.h>
#include <utility>
#ifdef LIBSAFEC
#include <safec.h>
#endif // LIBSAFEC
#define __STDC_WANT_LIB_EXT1__ 1
#include <stddef.h>
#include <stdlib.h>

namespace open_stg::sdl2_h
{
PtrTtfFont::PtrTtfFont(TTF_Font *pFont) : m_pFont(pFont)
{
}
ptr_ttf_font::~PtrTtfFont() noexcept
{
    if (m_pFont != nullptr)
    {
        TTF_CloseFont(m_pFont);
    }
}
ptr_ttf_font::PtrTtfFont(std::filesystem::path file, int fontSize)
{
    m_pFont = TTF_OpenFont(file.string().c_str(), fontSize);
}
ptr_ttf_font::PtrTtfFont(std::string_view file, int fontSize)
{
    m_pFont = TTF_OpenFont(file.data(), fontSize);
}
ptr_ttf_font::PtrTtfFont(ptr_ttf_font &&ref)
{
    this->swap(ref);
}
void ptr_ttf_font::Swap(ptr_ttf_font &ref)
{
    std::swap(this->m_pFont, ref.m_pFont);
}
void ptr_ttf_font::swap(ptr_ttf_font &ref)
{
    Swap(ref);
}
TTF_Font *ptr_ttf_font::operator->()
{
    return m_pFont;
}
const TTF_Font *ptr_ttf_font::operator->() const
{
    return m_pFont;
}
TTF_Font &ptr_ttf_font::operator*()
{
    return *m_pFont;
}
const TTF_Font &ptr_ttf_font::operator*() const noexcept
{
    return *m_pFont;
}
TTF_Font **ptr_ttf_font::operator&()
{
    return &m_pFont;
}
TTF_Font *const *ptr_ttf_font::operator&() const noexcept
{
    return &m_pFont;
}
ptr_ttf_font::operator TTF_Font *() const
{
    return m_pFont;
}
PtrTtfFont &ptr_ttf_font::operator=(ptr_ttf_font &&rsh)
{
    ptr_ttf_font obj{std::move(rsh)};
    this->swap(obj);
    return *this;
}
TTF_Font* ptr_ttf_font::Get() const
{
    return m_pFont;
}
} // namespace open_stg::sdl2_h
