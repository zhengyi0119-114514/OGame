#include "og.hpp"
namespace open_stg::sdl3_h
{
void TtfFontManager::DestoryObject(TTF_Font *pFont)
{
    if (not pFont)
    {
        TTF_CloseFont(pFont);
    }
}
} // namespace open_stg::sdl3_h