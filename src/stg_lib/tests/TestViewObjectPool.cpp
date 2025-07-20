#include "templates_h.hpp"
#include <gtest/gtest.h>
using namespace open_stg;
using namespace open_stg::view_h;
using namespace std;
class testViewObject : public open_stg::view_h::view_obj
{
  private:
    std::string str;

  public:
    testViewObject(std::string_view str) : str{str}
    {
    }

    std::string &Str()
    {
        return str;
    }
    const std::string &Str() const
    {
        return str;
    }
    auto operator<=>(const testViewObject &rsh) const
    {
        return str <=> rsh.str;
    }
    operator std::string&()
    {
        return str;
    }
    bool operator!=(const testViewObject &rsh) const
    {
        return str != rsh.str;
    }
    virtual void print_to_renderer(SDL_Renderer *rend)
    {

    }

};
template class open_stg::view_h::view_obj_pool<testViewObject>;
using pool = open_stg::view_h::view_obj_pool<testViewObject>;
TEST(TestViewObjectPool,ogmae_lib)
{
    {
        pool p{};
        ASSERT_EQ(p.size(),0);
        ASSERT_THROW(p.at("gtest"),error_h::name_not_exist_error);
    }
    {
    }
}
