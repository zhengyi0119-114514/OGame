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
ptr_ttf_font::PtrTtfFont(ptr_ttf_font &&ref) noexcept
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
ptr_ttf_font::operator TTF_Font *() const
{
    return m_pFont;
}
PtrTtfFont &ptr_ttf_font::operator=(ptr_ttf_font &&rsh) noexcept
{
    ptr_ttf_font obj{std::move(rsh)};
    this->swap(obj);
    return *this;
}
TTF_Font *ptr_ttf_font::Get() const
{
    return m_pFont;
}

TTF_Font *ptr_ttf_font::data() const
{
    return Get();
}

TTF_Font *ptr_ttf_font::get() const
{
    return Get();
}
} // namespace open_stg::sdl2_h

namespace open_stg::sdl2_h
{
// SharedPtrTtfFont 实现
SharedPtrTtfFont::SharedPtrTtfFont(TTF_Font *pFont) : m_ptr(std::make_shared<PtrTtfFont>(pFont))
{
}

SharedPtrTtfFont::SharedPtrTtfFont(PtrTtfFont *p) : m_ptr(p)
{
}

TTF_Font *SharedPtrTtfFont::operator->()
{
    return m_ptr->operator->();
}
const TTF_Font *SharedPtrTtfFont::operator->() const
{
    return m_ptr->operator->();
}
TTF_Font &SharedPtrTtfFont::operator*()
{
    return m_ptr->operator*();
}
const TTF_Font &SharedPtrTtfFont::operator*() const
{
    return m_ptr->operator*();
}
SharedPtrTtfFont::operator TTF_Font *() const
{
    return *m_ptr;
}
TTF_Font *SharedPtrTtfFont::Get() const
{
    return m_ptr->Get();
}
TTF_Font *shared_ttf_font::get() const
{
    return Get();
}
TTF_Font *shared_ttf_font::data() const
{
    return Get();
}
} // namespace open_stg::sdl2_h
