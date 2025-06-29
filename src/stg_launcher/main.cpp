#include <SDL2/SDL.h>
#include <SDL2_gfxPrimitives.h>
#undef main
#include "ftxui/component/captured_mouse.hpp"     // for ftxui
#include "ftxui/component/component.hpp"          // for Toggle, Renderer, Vertical
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/screen_interactive.hpp" // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"                 // for text, hbox, vbox, Element
#include <format>
#include <iostream>
using namespace ftxui;
double DEFAULT_RATIOS[]{16.0 / 9.0, 16.0 / 10.0};
double DEVIATION = 0.02;
void getAndSelectDisplayMode(std::vector<SDL_DisplayMode> &displayModes)
{
    std::vector<SDL_DisplayMode> selectedDisplayModes{};
    int numModes{SDL_GetNumDisplayModes(0)};
    for (int mode = 0; mode < numModes; mode++)
    {
        displayModes.push_back({});
        SDL_GetDisplayMode(0, mode, &displayModes.at(mode));
    }

    for (auto defaultRatio : DEFAULT_RATIOS)
    {
        double max = defaultRatio * (1 + DEVIATION);
        double min = defaultRatio * (1 - DEVIATION);
        for (auto &displayMode : displayModes)
        {
            double ratio = (double)displayMode.w / (double)displayMode.h;
            if ((min < ratio) && (ratio < max))
            {
                selectedDisplayModes.push_back(displayMode);
            }
        }
    }

    displayModes = selectedDisplayModes;
}
std::vector<std::string> toString(const std::vector<SDL_DisplayMode> &displayModes)
{
    std::vector<std::string> texts{};
    {
        int i{};
        for (const SDL_DisplayMode &displayMode : displayModes)
        {
            ++i;
            texts.push_back(
                std::format("{:}:{:}x{:} {:}HZ", i, displayMode.w, displayMode.h, displayMode.refresh_rate));
        }
    }
    return std::move(texts);
}
Component OfficialScrollable(Component child)
{
    return Renderer(child, [child] { return child->Render() | vscroll_indicator | frame | flex; });
}
Component getGameInformationComponent()
{
    return Renderer([&]() {
        return vbox(text("OPEN_STG_GAME") | underlined | bold | color(Color::Red), separator(),
                    hbox(text("github page:"), text("https://github.com/zhengyi0119-114514/OGame.git") | underlined));
        ;
    });
}
Component getPlayerNameIdTabCompjonent(std::string &name)
{
    return Input(name,"PlayerName",InputOption{.multiline =false}) | CatchEvent([&](Event e)->bool{
        return e.is_character() && (!std::isalnum(e.character()[0]));
    });
}
int main(int argc, char **args)
{
    std::vector<std::string> tab{"information", "displayMode","playerOption"};

    int tabSelected = 0;
    auto tabMenu = OfficialScrollable(Menu(tab, &tabSelected));

    auto informationTab = getGameInformationComponent();
    std::string playerName{};
    auto playerNameTab = getPlayerNameIdTabCompjonent(playerName);

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
    std::vector<SDL_DisplayMode> displayModes{};
    getAndSelectDisplayMode(displayModes);
    auto displayModeChoices = toString(displayModes);
    int displayIndex = 0;
    Component displayTab = Radiobox(displayModeChoices, &displayIndex) | vscroll_indicator;

    auto tab_container =
        Container::Tab({OfficialScrollable(informationTab), OfficialScrollable(displayTab),OfficialScrollable(playerNameTab)}, &tabSelected);
    auto container = Container::Horizontal({tabMenu, tab_container});
    auto renderer = Renderer(container, [&] {
        return hbox({
                   tabMenu->Render(),
                   separator(),
                   tab_container->Render(),
               }) | border;
    });
    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);
}