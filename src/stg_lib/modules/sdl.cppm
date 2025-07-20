module;
#include "sdl.hpp"
export module open_stg.sdl;
export namespace open_stg::sdl
{
    using ptr_window = open_stg::sdl2_h::ptr_window;
    using ptr_renderer = open_stg::sdl2_h::ptr_renderer;
    using ptr_surface = open_stg::sdl2_h::ptr_surface;
    using shared_ptr_window = open_stg::sdl2_h::SharedPtrWindow;
    using shared_ptr_renderer = open_stg::sdl2_h::SharedPtrRenderer;
    using shared_ptr_surface = open_stg::sdl2_h::SharedPtrSurface;
} // namespace open_stg::sdl
