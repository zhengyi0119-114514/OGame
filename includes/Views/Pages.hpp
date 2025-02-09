#include "Base.hxx"
#include "Views/Controls.hxx"
#include <SDL2pp/Color.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <cstddef>
#include <memory>
#include <utility>
#include <vector>
namespace OGame::Views::Pages
{
class Page : public virtual OGame::OGameObject
{
  public:
    virtual void EnterMainLoop()  =0;
    virtual ~Page() noexcept;
};
class BasicPage : public virtual Page
{
  protected:
    std::vector<std::shared_ptr<Controls::ControlRIIA>> m_ControlList;
    SDL2pp::Color m_BackGroundColor;
    std::shared_ptr<SDL2pp::Renderer> mp_ShareRenderer;

  public:
    BasicPage(std::shared_ptr<SDL2pp::Renderer> r);
    BasicPage(SDL_Window *const &window);
    virtual void EnterMainLoop() override;
    virtual ~BasicPage() noexcept;
    void SetBackgroungColor(Uint8 r,Uint8 g, Uint8 b);
    void AddControl(std::shared_ptr<OGame::Views::Controls::ControlRIIA> control);
    static void Wait(double fps);
};
class LoadingPage : public virtual BasicPage{};
class GamePage : BasicPage{};
class PageRIIA final: public virtual OGameObject
{
  private:
    Page* m_Page;
  public:
    PageRIIA(Page* page) { this->m_Page= page;}
    PageRIIA(const PageRIIA& p) = delete;
    PageRIIA(PageRIIA&& p) {std::swap(this->m_Page,p.m_Page);}
    PageRIIA& operator=(const PageRIIA& rsh) = delete;
    PageRIIA& operator=(PageRIIA&& rsh) {std::swap(this->m_Page,rsh.m_Page); return *this;}
    virtual ~PageRIIA() noexcept {delete this->m_Page;}
    Page* Get() const {return this->m_Page;}
    bool IsNull() const {return this->m_Page == NULL;}
};
} // namespace OGame::Views::Pages