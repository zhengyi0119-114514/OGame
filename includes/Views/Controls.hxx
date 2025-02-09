#pragma once
#include "Base.hxx"
#include "Modules/Math.hh"
#include <SDL2pp/Surface.hh>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_surface.h>
#include <SDL_events.h>
#include <SDL_ttf.h>
#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
namespace OGame::Views::Controls
{
class IControl : public virtual OGame::OGameObject
{
  public:
    virtual void Display(SDL_Renderer *const &renderer) = 0;
    virtual void HandleEvent(const SDL_Event& event)  = 0;
    virtual const Modules::Math::Point& Position() const = 0;
    virtual const Modules::Math::Rectangle& Size() const =0;
    virtual void OnClick(const Modules::Math::Point& mouse) {};
    virtual ~IControl() noexcept = default;
};
class ControlRIIA : public virtual OGame::OGameObject
{
  private:
    IControl* m_Control;
  public:
    ControlRIIA(IControl* control) { this->m_Control= control;}
    ControlRIIA(const ControlRIIA& p) = delete;
    ControlRIIA(ControlRIIA&& p) {std::swap(this->m_Control,p.m_Control);}
    ControlRIIA& operator=(const ControlRIIA& rsh) = delete;
    ControlRIIA& operator=(ControlRIIA&& rsh) {std::swap(this->m_Control,rsh.m_Control); return *this;}
    virtual ~ControlRIIA() noexcept {delete this->m_Control; this->m_Control = NULL;}
    IControl* Get() const {return this->m_Control;}
    bool IsNull() const {return this->m_Control == NULL;}
};
class Button : public virtual OGameObject, public virtual IControl 
{
  private:
    SDL2pp::Surface m_ButtonSuface;
    Modules::Math::Point& m_Position;
    Modules::Math::Rectangle& m_Size;
  public:
    Button(
        const Modules::Math::Point& position,
        const Modules::Math::Rectangle& size,
        std::string text
    );
    virtual void HandleEvent(const SDL_Event& event) override;
    virtual void Display(SDL_Renderer *const &renderer) override;
    virtual const Modules::Math::Point& Position() const override {return this->m_Position;};
    Modules::Math::Point& Position() {return this->m_Position;}
    virtual const Modules::Math::Rectangle& Size() const override {return this->m_Size;};
    Modules::Math::Rectangle& Size() {return this->m_Size;}
    virtual ~Button() noexcept;
};
class Text : public virtual OGameObject,public virtual IControl
{
  protected:
    Modules::Math::Point m_Position;
    Modules::Math::Rectangle m_Size;
    uint32_t m_FontSize;
    std::string m_Text;
    SDL_Color m_TextColor;
    // static TTF_Font *const & s_TextFonts;
  public:
    Text(
        Modules::Math::Point position,
        std::string_view text,
        uint32_t size = 20
    );
    void SetText(std::string_view value);
    const std::string& GetText() {return this->m_Text;}
    uint32_t FontSize() const noexcept {return this->m_FontSize;}
    uint32_t& FontSize() noexcept {return m_FontSize;}
    const SDL_Color& TextColor() const noexcept {return this->m_TextColor;}
    SDL_Color& TextColor() noexcept {return this->m_TextColor;}
    const OGame::Modules::Math::Point& Position() const override {return this->m_Position;};
    Modules::Math::Point& Position() noexcept {return this->m_Position;};
    virtual void HandleEvent(const SDL_Event& event) override {};
    virtual void Display(SDL_Renderer *const &renderer) override;
    virtual ~Text() noexcept = default;
    virtual const Modules::Math::Rectangle& Size() const override {return m_Size;};
};
class FormatText: public virtual Text
{
  public:
    using Text::Text;
    virtual void Display(SDL_Renderer *const &renderer) override;
};
} // namespace OGame::Views::Controls