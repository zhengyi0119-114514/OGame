#include <filesystem>
#include <memory>
#include <string_view>
#ifndef OGAME_STGLIB_SDL2_TTF_H
#define OGAME_STGLIB_SDL2_TTF_H 1
#include <SDL_ttf.h>
namespace open_stg::sdl2_h
{
class PtrTtfFont
{
  private:
    TTF_Font *m_pFont = nullptr;

  public:
    PtrTtfFont(TTF_Font *pFont);
    PtrTtfFont(std::filesystem::path file, int fontSize = 10);
    PtrTtfFont(std::string_view file, int fontSize = 10);
    PtrTtfFont(const PtrTtfFont &) = delete;
    PtrTtfFont(PtrTtfFont &&ref);
    void Swap(PtrTtfFont &ref);
    void swap(PtrTtfFont &ref);
    ~PtrTtfFont() noexcept;
    TTF_Font *operator->();
    const TTF_Font *operator->() const;
    TTF_Font &operator*();
    const TTF_Font &operator*() const noexcept;
    TTF_Font **operator&();
    TTF_Font *const *operator&() const noexcept;
    operator TTF_Font *() const;
    PtrTtfFont &operator=(const PtrTtfFont &) = delete;
    PtrTtfFont &operator=(PtrTtfFont &&rsh);
    TTF_Font *Get() const;
};
using ptr_ttf_font = PtrTtfFont;

class SharedPtrTtfFont
{
  private:
    std::shared_ptr<PtrTtfFont> m_ptr;

  public:
    // 构造函数
    SharedPtrTtfFont(TTF_Font *pFont);
    explicit SharedPtrTtfFont(PtrTtfFont *p);

    // 复制语义
    SharedPtrTtfFont(const SharedPtrTtfFont &) = default;
    SharedPtrTtfFont &operator=(const SharedPtrTtfFont &) = default;

    // 移动语义
    SharedPtrTtfFont(SharedPtrTtfFont &&) = default;
    SharedPtrTtfFont &operator=(SharedPtrTtfFont &&) = default;

    // 包装所有 PtrTtfFont 成员
    TTF_Font *operator->();
    const TTF_Font *operator->() const;
    TTF_Font &operator*();
    const TTF_Font &operator*() const;
    TTF_Font **operator&();
    TTF_Font *const *operator&() const;
    operator TTF_Font *() const;
    TTF_Font *Get() const;
};

} // namespace open_stg::sdl2_h
#endif
