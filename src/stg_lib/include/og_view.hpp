/**
 * @file og_view.hpp
 * @author ice_thorn
 * @brief MVVM View Component[MVVM 的视图部分]
 * @version Ciallo～(∠・ω< )⌒★
 * @date 2025-08-06
 *
 * Contains:
 * - Window and screen management[窗口和屏幕管理]
 * - Image output interfaces[图像输出接口]
 * - View object implementations[视图对象实现]
 */
#ifndef OGAME_STGLIB_VIEW_H
#define OGAME_STGLIB_VIEW_H 1
#include "og_macro.h"
#include "og_math_h.hpp"
#include "og_sdl3_h.hpp"
#include "og_templates_h.hpp"
#include <vector>

namespace OpenGame::View
{
/**
 * @brief Base output interface[基础输出接口]
 */
OG_INTERFACE IOutput
{
    virtual ~IOutput() noexcept = default; ///< Virtual destructor[虚析构函数]
};
OG_INTERFACE IInput
{
    virtual ~IInput() noexcept = default;
    Virtual Void HandleEvent(const SDL_Event &e, SDL_WindowID wid = 0) = 0;
    Virtual Void DoOperator() = 0;
};

/**
 * @brief Image output interface[图像输出接口]
 */
OG_INTERFACE IImageOutput : IOutput
{
    /**
     * @brief Print image to renderer[将图像输出到渲染器]
     * @param pRenderer SDL renderer pointer[SDL渲染器指针]
     */
    virtual void PrintToRenderer(SDL_Renderer * pRenderer,
                                 Math::Size sTargetSize = {Math::SIZE_UNDEFINED, Math::SIZE_UNDEFINED}) = 0;
    virtual ~IImageOutput() noexcept = default; ///< Virtual destructor[虚析构函数]
};
using SharedPtrIImageOutput = std::shared_ptr<IImageOutput>;
OG_INTERFACE IAudioOutput : IOutput
{
    virtual ~IAudioOutput() noexcept = default;
};
Using SharedPtrIAudioOutput = std::shared_ptr<IAudioOutput>;
/**
 * @brief Image view implementation[图像视图实现]
 */
CLASS Image : IImageOutput
{
  protected:
    sdl3_h::SharedPtrTexture m_spTexture;
    Math::Point m_spLocation{Math::SIZE_UNDEFINED, Math::SIZE_UNDEFINED}; ///< Image location[图像位置]
    Math::Size getTextureSize();

  public:
    /**
     * @brief Construct a new Image object[构造Image对象]
     * @param spSurface Shared surface pointer[共享表面指针]
     * @param location Image location[图像位置]
     * @param sSize Image size (default: undefined)[图像尺寸(默认:未定义)]
     */
    explicit Image(sdl3_h::SharedPtrSurface spSurface, SDL_Renderer * pRenderer, Math::Point location);
    explicit Image(sdl3_h::SharedPtrTexture spTexture, Math::Point spLocation);
    void ResetLocation(Math::Point spLocation) noexcept;
    void SetLocation(Math::Point p) noexcept;
    virtual void PrintToRenderer(SDL_Renderer * pRenderer,
                                 Math::Size sTargetSize = {Math::SIZE_UNDEFINED, Math::SIZE_UNDEFINED}) override;
};
CLASS RotatableImage : Image
{
  private:
    Double m_dAngleOfRevole;

  public:
    Explicit RotatableImage(sdl3_h::SharedPtrSurface spSurface, SDL_Renderer * pRenderer, Math::Point location,
                            double dAngleOfRevolve = 0.0);
    Explicit RotatableImage(sdl3_h::SharedPtrTexture spTexture, Math::Point spLocation, Double dAngleOfRevolve = 0.0);
    Void SetAngleOfRevolve(Double angleOfRotation); ///< [弧度制]
    Double GetAngleOfRevolve() const noexcept;      /// < [弧度制]
    Void ResetLocation(Math::Point pLocation) noexcept;
    Void SetLocation(Math::Point p) noexcept;
    Virtual Void PrintToRenderer(SDL_Renderer * pRenderer,
                                 Math::Size sTargetSize = {Math::SIZE_UNMEANING, Math::SIZE_UNMEANING}) override;
};

/**
 * @brief Thread-safe window screen management[线程安全的窗口屏幕管理]
 */
CLASS WindowScreen
{
  private:
    std::mutex m_Lock; ///< Mutex for thread safety[线程安全互斥锁]
    std::vector<SharedPtrIImageOutput> m_iImageViewObjects;
    Math::Size m_sWindowSize{};
    sdl3_h::SharedPtrRenderer m_pRenderer;

  public:
    Const Inline Static ConstExpr size_t ImagePoolReserveSize = 100;
    WindowScreen(sdl3_h::SharedPtrRenderer pRenderer);
    Void Init();
    Void PrintToRenderer(SDL_Renderer * pRenderer);
    Void AddObject(SharedPtrIImageOutput img);
    Void Clear();
};
// 灵感来源于(C#) System.EventArgs
STRUCT KeyBindingEventArgs
{
    SDL_WindowID WindowId{0}; ///< The value 0 is an invalid ID.
};
ENUM CLASS KeyboardEventType{
    UNKNOWN = 0,
    KEY_UP = SDL_EVENT_KEY_UP,
    KEY_DOWN = SDL_EVENT_KEY_DOWN,
};
STRUCT KeyboardEventArgs : KeyBindingEventArgs
{
    Const Bool *KeyboardState{NullPtr};
    KeyboardEventType Type;
    SDL_Scancode Scancode;
    Bool IsDown;
};
ENUM CLASS MouseClickEventType{
    UNKNOWN = 0,
    BUTTON_DOWN = SDL_EVENT_MOUSE_BUTTON_DOWN,
    BUTTON_UP = SDL_EVENT_MOUSE_BUTTON_UP,
};
STRUCT MouseClickEventArgs : KeyBindingEventArgs
{
    MouseClickEventType Type;
    Math::Point Location;
    SByte Clicks;
    Bool IsDown;
    SDL_MouseID MosueId;
};
enum CLASS KeyBindingTargetType
{
    MOUSE,
    MOUSE_WHEEL,
    KEYBOARD,
    GAMEPAD,
    FINGER,
};
STRUCT KeyBindingTarget
{
    KeyboardEventType Type;
    UNION
    {
        SDL_Scancode KeyboardScancode;
        Uint8 MouseKeyId;
        SDL_MouseWheelDirection MouseWheel;
        SDL_GamepadButton GamepadButton;
        LLInt Finger_EnterTextHere;
    };
};

CLASS KeyboardEventClassificationProcessor
{
  private:
    Int m_sKeyEventPoolSize{0};
    std::shared_ptr<EventHandler<KeyBindingEventArgs>> m_mEventHandlerPool{};
    size_t m_sEventHandlerPoolSize;

  public:
    Explicit KeyboardEventClassificationProcessor();
    Virtual ~KeyboardEventClassificationProcessor() NoExcept = Default;
    Void ProcessKeyboardButtonEvent(SDL_WindowID wid, Const SDL_KeyboardEvent & e);
    Void Binding(SDL_Scancode sc, EventHandler<KeyBindingEventArgs> h);
    Void ClearEventHandler();
};
CLASS EventClassificationProcessor
{
  private:
    ObjectPool<EventManager<KeyBindingEventArgs>> m_opEventPool;
    KeyboardEventClassificationProcessor m_kecpKeyboardEvent;

  public:
    Explicit EventClassificationProcessor();
    Virtual ~EventClassificationProcessor() NoExcept = Default;
    Void Init();
    Void ClassifyAndProcessEvents(SDL_WindowID wid); /// < 处理事件 
    Void Binding(KeyBindingTarget kbtTarget, EventHandler<KeyBindingEventArgs> eh);
    Void ClearEventHandler();
};
} // namespace OpenGame::View
#endif
