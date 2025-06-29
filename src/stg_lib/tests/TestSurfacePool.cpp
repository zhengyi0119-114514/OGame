#include <gtest/gtest.h>
#include "options.hpp"
#include <SDL_image.h>
using namespace open_stg::opt_h;
TEST(TestSurfacePool, ogmae_lib)
{
    image_resource_pool pool{};

    pool.add_surface("ogame.self.eye", IMG_Load(R"PATH(./resources/img/eye)PATH"));
    ASSERT_EQ(pool.get_id_form_name("ogame.self.eye"), 1);
}