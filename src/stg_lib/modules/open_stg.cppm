//
// Created by IceThorn on 25-6-22.
//
module;
#include "open_game.hpp"
export module open_stg;
export import open_stg.sdl;
export import open_stg.sdl.ttf;
export import open_stg.math;
export import open_stg.opt;
export import open_stg.error;
export import open_stg.task;

export namespace open_stg
{
    std::string OgInit(bool& bOK)
    {

        return ::open_stg::InitOG_h(bOK);
    }
    namespace view
    {
        using view_obj = ::open_stg::view_h::view_obj;
        using image = ::open_stg::view_h::image;
        using static_wallpeaper = ::open_stg::view_h::static_wallpeaper;
    }
    namespace mod
    {
        using ogame_obj = ::open_stg::mod_h::ogame_obj;
    }
}
