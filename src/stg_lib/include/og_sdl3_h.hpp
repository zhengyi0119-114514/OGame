/**
 * @file sdl3.hpp
 * @author Ciallo～(∠・ω< )⌒★
 * @brief SDL3 wrapper and utilities[SDL3封装和工具类]
 * @version iCEtHORN
 * @date 2025-08-07
 *
 * Contains:
 * - SDL object management[SDL对象管理]
 * - Smart pointers for SDL resources[SDL资源的智能指针]
 * - Renderer and window utilities[渲染器和窗口工具]
 */

#ifndef OGAME_STGLIB_SDL3_H
#define OGAME_STGLIB_SDL3_H 1
#include "og_macro.h"
#include "og_math_h.hpp"
#include "og_templates_h.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <concepts>
#include <filesystem>
#include <memory>
#include <utility>
#if __has_include("windows.h")
#include <windows.h>
#endif
namespace OpenGame::SDL3
{
/**
 * @brief Initialize SDL module[初始化SDL模块]
 */
void InitSdlModule();

/**
 * @brief Quit SDL module[退出SDL模块]
 */
void QuitSdlModule();
enum class Colorspace
{
    Unknow = SDL_COLORSPACE_UNKNOWN,
    // sRGB is a gamma corrected colorspace, and the default colorspace for SDL rendering and 8-bit RGB surfaces
    SRGB = SDL_COLORSPACE_SRGB, ///<  Equivalent to DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709
    // This is a linear colorspace and the default colorspace for floating point surfaces. On Windows this is the scRGB
    // colorspace, and on Apple platforms this is kCGColorSpaceExtendedLinearSRGB for EDR content
    SRGBLinear = SDL_COLORSPACE_SRGB_LINEAR, /// < Equivalent to DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709
    // HDR10 is a non-linear HDR colorspace and the default colorspace for 10-bit surfaces
    HDR10 = SDL_COLORSPACE_HDR10,                  // < Equivalent to DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020
    JPEG = SDL_COLORSPACE_JPEG,                    //< Equivalent to DXGI_COLOR_SPACE_YCBCR_FULL_G22_NONE_P709_X601
    BT601Limited = SDL_COLORSPACE_BT601_LIMITED,   //< Equivalent to DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P601
    BT601Full = SDL_COLORSPACE_BT601_FULL,         //< Equivalent to DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P601
    BT709Limited = SDL_COLORSPACE_BT709_LIMITED,   //< Equivalent to DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P709
    BT709Full = SDL_COLORSPACE_BT601_FULL,         //< Equivalent to DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P709
    BT2020Limited = SDL_COLORSPACE_BT2020_LIMITED, //< Equivalent to DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P2020
    BT2020Full = SDL_COLORSPACE_BT2020_FULL,       //< Equivalent to DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P2020
    RGB_Default = SRGB,
    YUV_Default = BT601Limited,
};
/**
 * @brief 一个指向SDL_Surface的智能指针，带有额外的附加功能
 *
 */
class Surface : PtrSdlObjectTemplate<SDL_Surface>
{
  protected:
    virtual void _DestroyObject(SDL_Surface *) override;

  public:
    using PtrSdlObjectTemplate<SDL_Surface>::PtrSdlObjectTemplate;
    /**
     * @brief Create surface form file
     */
    Surface(std::filesystem::path pImagerPath);
    /**
     * @brief Allocate a new surface with a specific pixel format and existing pixel
     * data.
     *
     * No copy is made of the pixel data. Pixel data is not managed automatically;
     * you must free the surface before you free the pixel data.
     *
     * Pitch is the offset in bytes from one row of pixels to the next, e.g.
     * `width*4` for `SDL_PIXELFORMAT_RGBA8888`.
     *
     * You may pass NULL for pixels and 0 for pitch to create a surface that you
     * will fill in with valid values later.
     *
     */
    Surface(Int iSurfaceWidth, Int iSurfaceHeigt, SDL_PixelFormat pf);
    /**
     * @brief Get the colorspace used by a surface.
     *
     * The colorspace defaults to SDL_COLORSPACE_SRGB_LINEAR for floating point
     * formats, SDL_COLORSPACE_HDR10 for 10-bit formats, SDL_COLORSPACE_SRGB for
     * other RGB surfaces and SDL_COLORSPACE_BT709_FULL for YUV textures.
     *
     * @param cs surface the SDL_Surface structure to query.
     */
    void SetColorspace(Colorspace cs);
    /**
     * @brief  * Get the colorspace used by a surface.
     *
     * The colorspace defaults to SDL_COLORSPACE_SRGB_LINEAR for floating point
     * formats, SDL_COLORSPACE_HDR10 for 10-bit formats, SDL_COLORSPACE_SRGB for
     * other RGB surfaces and SDL_COLORSPACE_BT709_FULL for YUV textures.
     *
     * @return
     */
    Colorspace GetColorspace() const;

    /**
     * @brief et the palette used by a surface.
     *
     * Setting the palette keeps an internal reference to the palette, which can
     * be safely destroyed afterwards.
     *
     * A single palette can be shared with many surfaces.
     *
     *
     * @return true on success or false on failure; call SDL_GetError() for more
     *          information.
     */
    SDL_Palette *CreatePalette();
    /**
     * @brief Set the palette used by a surface.
     *
     * Setting the palette keeps an internal reference to the palette, which can
     * be safely destroyed afterwards.
     *
     * A single palette can be shared with many surfaces.
     *
     *
     * @param palette
     */
    void SetPalette(SDL_Palette *palette);
};
class Texture : PtrSdlObjectTemplate<SDL_Texture>
{
};
class Renderer : PtrSdlObjectTemplate<SDL_Renderer>
{
  protected:
    virtual void _DestroyObject(SDL_Renderer *) override;

  public:
    using PtrSdlObjectTemplate<SDL_Renderer>::Get;
    using PtrSdlObjectTemplate<SDL_Renderer>::swap;
    virtual ~Renderer() noexcept;
    Renderer(const Renderer &rlv) = delete;
    Renderer(Renderer &&rrv);
    explicit Renderer(SDL_Renderer &pRend);
    Renderer &operator=(const Renderer &rsh) = delete;
    Renderer &operator=(Renderer &&rsh);
};
enum class WindowFlags
{
    None = 0,
    FullScreen = SDL_WINDOW_FULLSCREEN,     //< fullscreen window at desktop resolution
    Hidden = SDL_WINDOW_HIDDEN,             //< window is not visible
    Minimized = SDL_WINDOW_MINIMIZED,       //< window is minimized
    Maximized = SDL_WINDOW_MAXIMIZED,       //< window is maximized
    AlwaysOnTop = SDL_WINDOW_ALWAYS_ON_TOP, //< window should always be above others

    Borderless = SDL_WINDOW_BORDERLESS, //< no window decoration
    Resizable = SDL_WINDOW_RESIZABLE,   //< window can be resized

    OpenGL = SDL_WINDOW_OPENGL,                       //<  window usable with an OpenGL context
    Vulkan = SDL_WINDOW_VULKAN,                       //< window usable with a Vulkan instance
    Metal = SDL_WINDOW_METAL,                         //< window usable with a Metal instance
    HighPixelDensity = SDL_WINDOW_HIGH_PIXEL_DENSITY, //< window uses high pixel density back buffer if possible

    MouseGrabbed = SDL_WINDOW_MOUSE_GRABBED,       //<  window has mouse focus
    MouseCapture = SDL_WINDOW_MOUSE_CAPTURE,       //< window has mouse captured (unrelated to MOUSE_GRABBED)
    InputFocus = SDL_WINDOW_INPUT_FOCUS,           //< window has input focus
    KeyboardGrabbed = SDL_WINDOW_KEYBOARD_GRABBED, //< window has grabbed keyboard input
    MouseFocus = SDL_WINDOW_MOUSE_FOCUS,           //< window has grabbed mouse focus

    External = SDL_WINDOW_EXTERNAL, //< window not created by SDL
    Modal = SDL_WINDOW_MODAL,       //< window is modal
    Utility = SDL_WINDOW_UTILITY,   //< window should be treated as a utility window, not showing in the task bar and
                                    // window list
    Tooltip = SDL_WINDOW_TOOLTIP,   //< window should be treated as a tooltip and does not get mouse or keyboard focus,
                                    // requires a parent window
    PopupMenu = SDL_WINDOW_POPUP_MENU,    //< window should be treated as a popup menu, requires a parent window
    Transparent = SDL_WINDOW_TRANSPARENT, //< window with transparent buffer
};

constexpr static inline Uint64 WindowFlagsExNotFocusable = SDL_WINDOW_NOT_FOCUSABLE; //< window should not be focusable
class Window : PtrSdlObjectTemplate<SDL_Window>
{
  protected:
    virtual void _DestroyObject(SDL_Window *) override;

  public:
    using PtrSdlObjectTemplate<SDL_Window>::Get;
    using PtrSdlObjectTemplate<SDL_Window>::swap;
    Window(const Window &) = delete;
    explicit Window(SDL_Window *pWin);
    Window &operator=(const Window &rsh);
    /**
     * @brief 调用SDL_CreateWindow创建Window
     *
     * @param svTitle the title of the window, in UTF-8 encoding.
     *
     * @param iWindowWidth the width of the window.
     *
     * @param iWindowHeight the height of the window.
     *
     * @param wfFlag  	0, or one or more WindowFlag OR'd together.
     *
     * @param wfexFlag 0 or WindowFlagsExNotFocusable.
     *
     * @exception OpenGame::Error::InitException
     *
     */
    explicit Window(std::string_view svTitle, int iWindowWidth, int iWindowHeight, WindowFlags wfFlag,
                    Uint64 wfexFlag = 0);
    /**
     * @brief Get the size of a window's client area.
     *
     * @return Math::Size
     *
     * @exception OpenGame::Error::SDLException
     *
     */
    Math::Size<int> GetSize() const;
    /**
     * @brief Request that the size of a window's client area be set.
     *
     * @exception OpenGame::Error::SDLException
     *
     * @param s Window size
     *
     */
    void SetSize(Math::Size<int> s);
    /**
     * @brief Get the size of a window's client area, in pixels.
     *
     * @return Math::Size
     *
     * @exception OpenGame::Error::SDLException
     *
     */
    Math::Size<int> GetSizeInPixels() const;
    /**
     * @brief Get the numeric ID of a window.
     *
     * @return SDL_WindowID
     *
     * @exception OpenGame::Error::SDLException
     *
     */
    SDL_WindowID GetWindowID() const;
    /**
     * @brief Get the window flags.
     *
     * @return SDL_WindowFlags
     *
     */
    SDL_WindowFlags GetFlags() const;
    /**
     * @brief Get the title of a window.
     *
     * @return const char*
     *
     */
    const char *GetTitle() const;
    /**
     * @brief Set the title of a window.
     *
     * @exception OpenGame::Error::SDLException
     *
     */
    void SetTitle(std::string_view svTitle);
    /**
     * @brief Get the maximum size of a window's client area.
     *
     * @return Math::Size<int>
     *
     */
    Math::Size<int> GetMaximumSize() const;
    /**
     * @brief Set the maximum size of a window's client area.
     *
     * @exception OpenGame::Error::SDLException
     *
     * @param s
     */
    void SetMaximunSize(const Math::Size<int> s);
    /**
     * @brief Get the minimum size of a window's client area.
     *
     * @exception OpenGame::Error::SDLException
     *
     * @return Math::Size<int>
     *
     */
    Math::Size<int> GetMinimumSize() const;
    /**
     * @brief Set the user-resizable state of a window.
     *
     * @exception OpenGame::Error::SDLException
     *
     * @param bResizable
     */
    void SetResizable(Bool bResizable);
    /**
     * @brief Set the minimum size of a window's client area.
     *
     * @exception OpenGame::Error::SDLException
     *
     * @param s
     *
     */
    void SetMinimumSize(const Math::Size<int> s);
    /**
     * @brief Get a window's keyboard grab mode.
     *
     * @exception OpenGame::Error::SDLException
     *
     * @return Bool
     *
     */
    Bool IsKeyboardGrab() const;
    /**
     * @return SDL_Point
     *
     * @brief Get the position of a window.
     *
     * @return SDL_Point
     *
     */
    SDL_Point GetPosition() const;
    /**
     * @return SDL_Point
     *
     * @brief Request that the window's position be set.
     *
     */
    void SetPosition(const SDL_Point &p);
    /**
     * @brief Get the properties associated with a window.
     *
     * @return SDL_PropertiesID
     *
     */
    SDL_PropertiesID GetProperties() const;
    /**
     * @brief Set a window's keyboard grab mode.
     *
     * @exception OpenGame::Error::SDLException
     *
     * @param bGrabbed
     *
     */
    void SetKeyboardGrab(Bool bGrabbed);
    /**
     * @brief Set whether the window may have input focus.
     *
     * @exception OpenGame::Error::SDLException
     *
     * @param bFocusable
     *
     */
    void SetFocusable(Bool bFocusable);
    /**
     * @brief Request that the window be made as large as possible.
     *
     * @exception OpenGame::Error::SDLException
     *
     */
    void Maximize();
    /**
     * @brief Request that the window be minimized to an iconic representation.
     *
     * @exception OpenGame::Error::SDLException
     *
     */
    void Minimize();
    /**
     * @brief Show a window.
     *
     * @exception OpenGame::Error::SDLException
     *
     */
    void Show();
    /**
     * @brief Hide a window.
     *
     * @exception OpenGame::Error::SDLException
     *
     */
    void Hide();
    /**
     * @brief Set the window to always be above the others.
     *
     * @exception OpenGame::Error::SDLException
     *
     * @param bAlwaysOnTop
     *
     */
    void SetAlwaysOnTop(Bool bAlwaysOnTop);
    /**
     * @brief Request that a window be raised above other windows and gain the input focus.
     *
     * @exception OpenGame::Error::SDLException
     *
     */
    void Raise();
    /**
     * @brief Request that the size and position of a minimized or maximized window be restored.
     *
     * @exception OpenGame::Error::SDLException
     *
     */
    void Restore();
#if defined WIN32
    /**
     * @brief Get HWND
     *
     * @return HWND
     */
    HWND GetWin32WndObject() const;
#endif
    virtual ~Window() noexcept;
};
class TrueTypeFont : PtrSdlObjectTemplate<TTF_Font>
{
};
Bool inline IsInRange(const SDL_FRect &r, const SDL_FPoint &p)
{
    return ((p.x > r.x) && (p.x < (r.x + r.w))) && ((p.y > r.y) && (p.y < (r.y + r.w)));
}
} // namespace OpenGame::SDL3
#endif
