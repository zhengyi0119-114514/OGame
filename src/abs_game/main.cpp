
#if defined LIBSAFEC
#include <safec.h>
#endif
#define __STDC_WAND_LIB_EXT1__ 1
#include "open_game.hpp"

#include "sdl.hpp"
#include <SDL_image.h>
#include <boost/program_options.hpp>
#include <iostream>
#include <sdl_ttf.hpp>
#include <stdio.h>
#include <stdlib.h>


// import open_stg;
using namespace open_stg::sdl2_h;
using namespace open_stg::math_h;
using namespace boost::program_options;

int main(int argc, char **args)
{
    rectangles windowSize = {{}};
    options_description opt_doc{};
    opt_doc.add_options()("help", "")
        ("width", value<uint32_t>()->required(), "set window width")
        ("height", value<uint32_t>()->required(),"set window height")
        ("name",value<std::string>()->default_value(std::string("Alex")),"player name");
    variables_map vm{};
    store(parse_command_line(argc, args, opt_doc), vm);
    if (vm.count("help"))
    {
        std::cout << opt_doc << std::endl;
    }
    windowSize.width = vm["width"].as<uint32_t>();
    windowSize.height = vm["height"].as<uint32_t>();

    bool bOk = true;
    open_stg::InitOG_h(bOk);
    std::cout << "Init successfully" << std::endl;
    ptr_window pWin{SDL_CreateWindow("傻逼！傻逼！", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowSize.width,
                                     windowSize.height, SDL_WINDOW_VULKAN)};
    if (!pWin.Get())
    {
        fprintf_s(stderr, "Failed to open Window %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ptr_renderer pRend{SDL_CreateRenderer(pWin, -1, SDL_RENDERER_ACCELERATED)};
    if (!pRend.Get())
    {
        fprintf_s(stderr, "Failed to create Renderer %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    open_stg::opt_h::image_resource_pool pool;
    SDL_Surface *s = IMG_Load("./resources/img/eye.png");
    uint32_t eyeId = pool.add_surface("ogame.test.eye", shared_ptr_surface{s});
    open_stg::view_h::image img{pool, eyeId};
    while (true)
    {
        SDL_RenderClear(pRend);
        SDL_SetRenderDrawColor(pRend, 96, 128, 255, 255);
        SDL_Event event{};
        img.print_to_renderer(pRend.Get());

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                exit(EXIT_SUCCESS);
                break;
            default:
                break;
            }
        }
        SDL_RenderPresent(pRend);
    }
}