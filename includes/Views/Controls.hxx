#pragma once
#include "Base.hxx"
#include "Modules/Math.hh"
#include <SDL2pp/Surface.hh>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_events.h>
#include <SDL_ttf.h>
#include <cstddef>
#include <string>
#include <string_view>
namespace OGame::Views::Controls
{
class IControl : public virtual OGame::OGameObject
{
  public:
    virtual void Display(SDL_Surface *const &surface) = 0;
    virtual void HandleEvent(const SDL_Event& event)  = 0;
    virtual ~IControl() noexcept = default;
};
class ControlRIIA : public virtual OGame::OGameObject
{
  private:
    IControl* m_Control;
  public:
    ControlRIIA(IControl* page) { this->m_Control= page;}
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
    virtual void Display(SDL_Surface *const &surface) override;
    virtual ~Button() noexcept;
};
class Text : public virtual OGameObject,public virtual IControl
{
  private:
    Modules::Math::Point m_Position;
    OGame::Modules::Math::Rectangle m_Size;
    std::string m_Text;
    // static TTF_Font *const & s_TextFonts;
  public:
    Text(
        Modules::Math::Point position,
        std::string_view text,
        OGame::Modules::Math::Rectangle size
    );
    void SetText(std::string_view value);
    virtual void HandleEvent(const SDL_Event& event) override {};
    virtual void Display(SDL_Surface *const &surface) override;
    virtual ~Text() noexcept = default;
};
} // namespace OGame::Views::Controls