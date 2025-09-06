#include "og.hpp"
namespace OpenGame::sdl3_h
{
void TtfFontManager::DestoryObject(TTF_Font *pFont)
{
    if (not pFont)
    {
        TTF_CloseFont(pFont);
    }
}
} // namespace OpenGame::sdl3_h