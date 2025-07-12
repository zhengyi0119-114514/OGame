#include <SDL2/SDL.h>
#include <SDL2_gfxPrimitives.h>
#undef main
#include "ftxui/component/component.hpp"          // for Toggle, Renderer, Vertical
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/screen_interactive.hpp" // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"
#include <fstream>
#include "launcher_api.hpp"
using namespace ftxui;
Component OfficialScrollable(Component child)
{
    return Renderer(child, [child] { return child->Render() | vscroll_indicator | frame | flex; });
}
int main(int argc, char **args)
{
    std::vector<std::string> tabTitle{"OGame"
        ,"Display Mode",
        "Player Name"};
    int selectedTeb{};
    auto tabMenu = Menu(&tabTitle,&selectedTeb);
    //TabPage1
    auto tabPage1 = OfficialScrollable(Renderer([]() {
        std::fstream stream{"resources"};
        std::string fileText{"./resources/lang/game_information.txt"};
        std::string line{""};
        while (std::getline(stream, line))
        {
            fileText += line;
        }
        return vbox({ftxui::text("OGAME") | bold | underlined | color(Color::Red), separator(), text(fileText)});
    }));

    // TabPage2
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    int displayModesIndex{0};
    auto displayModes = GetAndSelectDisplayMode();
    auto tabPage2 = OfficialScrollable(Radiobox(RadioboxOption{
        .entries = ConstStringListRef(DisplayModeToStringVectoy(displayModes)), .selected = &displayModesIndex}));

    // TabPage3
    std::string sPlayerName{""};
    auto playerNameInput = Input(InputOption{sPlayerName});
    auto tabPage3 = OfficialScrollable({playerNameInput});

    auto tabContainer = Container::Tab({
        tabPage1,
        tabPage2,
        tabPage3
    },&selectedTeb);
    auto container = Container::Horizontal({
        tabMenu,tabContainer
    });
    auto renderer = Renderer(container,[&](){
        return hbox(tabMenu->Render(),separator(),tabContainer->Render()) | border;
    });
      auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);
}