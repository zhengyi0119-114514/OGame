#include "include/options.hpp"
#include "options.hpp"
#include <cstdlib>
#include <filesystem>
#include <string_view>
namespace fs = std::filesystem;
namespace open_stg::opt_h
{
std::filesystem::path get_program_option_path()
{
    std::string_view env{"HOME"};
    std::filesystem::path path{std::getenv(env.data())};
    path /= ".config";
    path /= "game";
    if (!fs::exists(path))
    {
        fs::create_directory(path);
    }
    return path;
}
} // namespace open_stg::opt_h