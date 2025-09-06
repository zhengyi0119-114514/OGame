#include "og.hpp"
#include "og_abs.h"
namespace OpenGame::View
{
Void WindowScreen::PrintToRenderer(SDL_Renderer *pRenderer)
{
    For(auto iCurrent = m_iImageViewObjects.rbegin(),iEnd = m_iImageViewObjects.rend();iCurrent != iEnd;iCurrent++)
    {
        (*iCurrent)->PrintToRenderer(pRenderer);
    }
}
Void WindowScreen DOUBLE_COLON Init l_ r_ //拉坨大的
BEGIN_BLOCK
    m_iImageViewObjects DOT clear l_ r_ END_LINE
    m_iImageViewObjects DOT reserve l_ ImagePoolReserveSize r_ END_LINE
    i____ width NEXT height BEGIN_BLOCK END_BLOCK END_LINE;
    SDL_GetCurrentRenderOutputSize l_ m_pRenderer NEXT &width NEXT &height r_ END_LINE
    m_sWindowSize ASSIGN_VALUE Math DOUBLE_COLON Size BEGIN_BLOCK StaticCast LessThan Double MoreThan l_ width r_ NEXT StaticCast LessThan Double MoreThan l_ height r_ END_BLOCK END_LINE
END_BLOCK
Void WindowScreen DOUBLE_COLON AddObject l_ SharedPtrIImageOutput spiiop  r_
BEGIN_BLOCK
    m_iImageViewObjects DOT push_back l_ spiiop r_ END_LINE
END_BLOCK
Void WindowScreen DOUBLE_COLON Clear l_ r_
BEGIN_BLOCK
    m_iImageViewObjects DOT clear l_ r_ END_LINE
    m_iImageViewObjects DOT reserve l_ ImagePoolReserveSize r_ END_LINE
END_BLOCK
WindowScreen DOUBLE_COLON WindowScreen l_ sdl3_h DOUBLE_COLON SharedPtrRenderer sprRenderer r_ COLON m_pRenderer l_ sprRenderer r_
BEGIN_BLOCK
    Init l_ r_ END_LINE
END_BLOCK
} // namespace OpenGame::View