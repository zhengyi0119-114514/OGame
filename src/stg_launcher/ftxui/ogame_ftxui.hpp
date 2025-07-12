#include "ftxui/component/captured_mouse.hpp"     // for ftxui
#include "ftxui/component/component.hpp"          // for Toggle, Renderer, Vertical
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/screen_interactive.hpp" // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"

// Component OfficialScrollable(Component child)
// {
//     return Renderer(child, [child] { return child->Render() | vscroll_indicator | frame | flex; });
// }
