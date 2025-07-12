#include "sdl.hpp"
namespace open_stg::sdl2_h {

SharedPtrWindow::SharedPtrWindow(SDL_Window *pWin) : 
    m_window(std::make_shared<PtrWindow>(pWin)) {}

const SDL_Window* SharedPtrWindow::operator->() const {
    return m_window->operator->();
}

SDL_Window* SharedPtrWindow::operator->() {
    return m_window->operator->();
}

const SDL_Window& SharedPtrWindow::operator*() const {
    return m_window->operator*();
}

SDL_Window& SharedPtrWindow::operator*() {
    return m_window->operator*();
}

SharedPtrWindow::operator SDL_Window*() const noexcept {
    return m_window->Get();
}

SDL_Window* SharedPtrWindow::Get() const {
    return m_window->Get();
}

SharedPtrRenderer::SharedPtrRenderer(SDL_Renderer *pRend) : 
    m_renderer(std::make_shared<PtrRenderer>(pRend)) {}

const SDL_Renderer* SharedPtrRenderer::operator->() const {
    return m_renderer->operator->();
}

SDL_Renderer* SharedPtrRenderer::operator->() {
    return m_renderer->operator->();
}

const SDL_Renderer& SharedPtrRenderer::operator*() const {
    return m_renderer->operator*();
}

SDL_Renderer& SharedPtrRenderer::operator*() {
    return m_renderer->operator*();
}

SharedPtrRenderer::operator SDL_Renderer*() const noexcept {
    return m_renderer->Get();
}

SDL_Renderer* SharedPtrRenderer::Get() const {
    return m_renderer->Get();
}

SDL_Renderer* SharedPtrRenderer::data() const {
    return Get();
}

SDL_Renderer* SharedPtrRenderer::get() const {
    return Get();
}

SharedPtrSurface::SharedPtrSurface(SDL_Surface *pSurf) : 
    m_surface(std::make_shared<PtrSurface>(pSurf)) {}

const SDL_Surface* SharedPtrSurface::operator->() const {
    return m_surface->operator->();
}

SDL_Surface* SharedPtrSurface::operator->() {
    return m_surface->operator->();
}

const SDL_Surface& SharedPtrSurface::operator*() const {
    return m_surface->operator*();
}

SDL_Surface& SharedPtrSurface::operator*() {
    return m_surface->operator*();
}

SharedPtrSurface::operator SDL_Surface*() const noexcept {
    return m_surface->Get();
}

SDL_Surface* SharedPtrSurface::Get() const {
    return m_surface->Get();
}

SharedPtrTexture::SharedPtrTexture(SDL_Texture* pTex) : 
    m_texture(std::make_shared<PtrTexture>(pTex)) {}
const SDL_Texture& SharedPtrTexture::operator*() const {
    return m_texture->operator*();
}

SDL_Texture& SharedPtrTexture::operator*() {
    return m_texture->operator*();
}

SharedPtrTexture::operator SDL_Texture*() const noexcept {
    return m_texture->Get();
}

SDL_Texture* SharedPtrTexture::Get() const {
    return m_texture->Get();
}

} // namespace open_stg::sdl2_h
