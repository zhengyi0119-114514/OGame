#pragma once
#include "Base.hxx"
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_events.h>
#include <cstddef>
namespace OGame::Views::Controls
{
class IControl : public virtual OGame::OGameObject
{
  public:
    virtual void Display(SDL_Renderer *const &pRenderer) = 0;
    virtual void HandleEvent(const SDL_Event& event) const = 0;
    virtual ~IControl() noexcept;
};
class ControlRIIA : public virtual OGame::OGameObject
{
  private:
    IControl* m_Page;
  public:
    ControlRIIA(IControl* page) { this->m_Page= page;}
    ControlRIIA(const ControlRIIA& p) = delete;
    ControlRIIA(ControlRIIA&& p) {std::swap(this->m_Page,p.m_Page);}
    ControlRIIA& operator=(const ControlRIIA& rsh) = delete;
    ControlRIIA& operator=(ControlRIIA&& rsh) {std::swap(this->m_Page,rsh.m_Page); return *this;}
    virtual ~ControlRIIA() noexcept {delete this->m_Page; this->m_Page = NULL;}
    IControl* Get() const {return this->m_Page;}
    bool IsNull() const {return this->m_Page == NULL;}
};
} // namespace OGame::Views::Controls