#include <gtest/gtest.h>
#include "options.hpp"
#include <SDL_image.h>
using namespace open_stg::opt_h;
TEST(TestSurfacePool, ogmae_lib)
{
    image_resource_pool pool{};
    std::string surfaceName = "ogame.self.eye";
    uint32_t handleOfEyeImage = pool.add_surface(surfaceName, IMG_Load(R"PATH(./resources/img/eye)PATH"));
    ASSERT_EQ(pool.get_id_form_name(surfaceName), handleOfEyeImage);
    ASSERT_EQ(pool.get_surface_form_name(surfaceName).data(),pool.get_surface_form_id(handleOfEyeImage).Get());
    ASSERT_EQ(handleOfEyeImage,0);
    
    std::string surfaceName2 = surfaceName+'1';
    uint32_t handleOfEyeImage2 = pool.add_surface(surfaceName2,pool[0]);
    ASSERT_NE(handleOfEyeImage,handleOfEyeImage2);
}