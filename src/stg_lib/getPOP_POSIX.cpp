#if __has_include("safec.h")
#include <safec.h>
#endif
#include "og_opt_h.hpp"
#include <filesystem>
#include <string_view>
namespace fs = std::filesystem;
namespace open_stg::opt_h
{
std::filesystem::path GetProgramOptionFileDirectory()
{
    std::string_view env{"HOME"};
    constexpr const size_t strSize = 1024;
    char buffer[strSize + 1];
    getenv_s(NULL, buffer, strSize, "HOME");
    auto path = std::filesystem::path{buffer} / ".config" / "open_game";
    if (!fs::exists(path))
    {
        fs::create_directory(path);
    }
    return path;
}
} // namespace open_stg::opt_h