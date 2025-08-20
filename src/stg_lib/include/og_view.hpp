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
#include "og_math_h.hpp"
#include "og_sdl3_h.hpp"
#include <functional>
#include <vector>

namespace open_stg::view_h
{
/**
 * @brief Base output interface[基础输出接口]
 */
struct IOutput
{
    virtual ~IOutput() noexcept = default; ///< Virtual destructor[虚析构函数]
};
struct IInput
{
    virtual ~IInput() noexcept = default;
    virtual void HandleEvent(const SDL_Event &e) = 0;
};
/**
 * @brief Image output interface[图像输出接口]
 */
struct IImageOutput : IOutput
{
    /**
     * @brief Print image to renderer[将图像输出到渲染器]
     * @param pRenderer SDL renderer pointer[SDL渲染器指针]
     */
    virtual void PrintToRenderer(SDL_Renderer *pRenderer,
                                 math_h::Size sTargetSize = {math_h::SIZE_UNDEFINED, math_h::SIZE_UNDEFINED}) = 0;
    virtual ~IImageOutput() noexcept = default; ///< Virtual destructor[虚析构函数]
};
using SharedPtrIImageOutput = std::shared_ptr<IImageOutput>;
struct IAudioOutput : public IOutput
{
    virtual ~IAudioOutput() noexcept = default;
};
using SharedPtrIAudioOutput = std::shared_ptr<IAudioOutput>;
/**
 * @brief Image view implementation[图像视图实现]
 */
class Image : public IImageOutput
{
  protected:
    sdl3_h::SharedPtrTexture m_spTexture;
    math_h::Point m_spLocation{math_h::SIZE_UNDEFINED, math_h::SIZE_UNDEFINED}; ///< Image location[图像位置]
    math_h::Size getTextureSize();

  public:
    /**
     * @brief Construct a new Image object[构造Image对象]
     * @param spSurface Shared surface pointer[共享表面指针]
     * @param location Image location[图像位置]
     * @param sSize Image size (default: undefined)[图像尺寸(默认:未定义)]
     */
    explicit Image(sdl3_h::SharedPtrSurface spSurface, SDL_Renderer *pRenderer, math_h::Point location);
    explicit Image(sdl3_h::SharedPtrTexture spTexture, math_h::Point spLocation);
    void ResetLocation(math_h::Point spLocation) noexcept;
    void SetLocation(math_h::Point p) noexcept;
    virtual void PrintToRenderer(SDL_Renderer *pRenderer,
                                 math_h::Size sTargetSize = {math_h::SIZE_UNDEFINED, math_h::SIZE_UNDEFINED}) override;
    virtual int32_t NumberOfRetentions() = 0;
};
class RotatableImage : public Image
{
  private:
    double m_dAngleOfRevole;

  public:
    explicit RotatableImage(sdl3_h::SharedPtrSurface spSurface, SDL_Renderer *pRenderer, math_h::Point location,
                            double dAngleOfRevolve = 0.0);
    explicit RotatableImage(sdl3_h::SharedPtrTexture spTexture, math_h::Point spLocation, double dAngleOfRevolve = 0.0);
    void SetAngleOfRevolve(double angleOfRotation); ///< [弧度制]
    double GetAngleOfRevolve() const noexcept;
    void ResetLocation(math_h::Point spLocation) noexcept;
    void SetLocation(math_h::Point p) noexcept;
    virtual void PrintToRenderer(SDL_Renderer *pRenderer,
                                 math_h::Size sTargetSize = {math_h::SIZE_UNMEANING, math_h::SIZE_UNMEANING}) override;
};
/**
 * @brief Thread-safe window screen management[线程安全的窗口屏幕管理]
 */
class WindowScreen
{
  private:
    std::mutex m_Lock; ///< Mutex for thread safety[线程安全互斥锁]
    std::vector<SharedPtrIImageOutput> m_iImageViewObjects;
    math_h::Size m_sWindowSize{};

  public:
    WindowScreen();
    /**
     * @brief Initialize window screen[初始化窗口屏幕]
     */
    void Init();
};
// Bit Flag
enum class KeyboardInputInformation
{
    NONE = 0x0000,
    CHECK_STATUS = 0x0001,
    KEY_UP = SDL_EVENT_KEY_UP,
    KEY_DOWN = SDL_EVENT_KEY_DOWN,
};

class KeyboardInputEvent : IInput
{
  public:
    using CallBack = std::function<void()>;
    explicit KeyboardInputEvent(SDL_Scancode sc, std::string_view strBindingId, CallBack fCallBack,
                                KeyboardInputInformation i);
    virtual void HandleEvent(const SDL_Event &e);
    std::string GetKeyName() const;
    const std::string &GetKeyboardBindingName() const noexcept;
    SDL_Scancode GetKey() const noexcept;
    void SetKey(SDL_Scancode sc) noexcept;

  private:
    KeyboardInputInformation m_kbiInformation{};
    std::string m_sKeyboardBindingId{};
    CallBack m_fCallBack{};
    SDL_Scancode m_scCode{SDL_SCANCODE_UNKNOWN};
};
} // namespace open_stg::view_h
#endif
