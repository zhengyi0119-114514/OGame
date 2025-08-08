#include "og_view.hpp"
#include "og.hpp"
#include <gtest/gtest.h>
using namespace open_stg;
using namespace open_stg::view_h;
using namespace std;
class testViewObject
{
  private:
    std::string str;

  public:
    testViewObject(std::string_view str = "傻逼") : str{str}
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
    operator std::string &()
    {
        return str;
    }
    bool operator!=(const testViewObject &rsh) const
    {
        return str != rsh.str;
    }
    bool operator==(const testViewObject &rsh) const
    {
        return !(*this != rsh);
    }
};
using pool = open_stg::object_pool<testViewObject>;
using moveOnlyPool = open_stg::ObjectPool<std::unique_ptr<int>>;
TEST(TestViewObjectPool, ogmae_lib)
{
    // INIT TEST
    {
        pool p{};
        ASSERT_EQ(p.size(), 0);
        ASSERT_THROW(p.at("gtest"), std::out_of_range);
    }
    // ADD TEST
    {
        // INIT
        pool p{{"1", {"1"}}, {"2", {"2"}}};

        {
            pool p1{std::vector<pool::name_obj_pair>{{"1", {"1"}}, {"2", {"2"}}}};
        }
        ASSERT_EQ(p.size(), 2);

        // ADD OBJECT
        p.add_object("3", {"3"});
        ASSERT_EQ(p.size(), 3);
        p.add_multiple_object({{"4", {"4"}}, {"5", {"5"}}});
        ASSERT_EQ(p.size(), 5);
        p.add_multiple_object(std::vector<pool::name_obj_pair>{{"6", {"6"}}, {"7", {"7"}}});
        ASSERT_EQ(p.size(), 7);
        p.emplace_object("8");
        ASSERT_EQ(p.size(), 8);

        // TEST AT
        {
            auto pair = p.at("1");
            ASSERT_EQ(pair.first, 0);
            ASSERT_EQ(pair.second, testViewObject{"1"});
            ASSERT_EQ(p.at(0), pair.second);
        }

        {
            ASSERT_THROW(p.at(p.size()), std::out_of_range);
        }
        // [死锁测试]
        {
            p.add_multiple_object_ts({{"9", {}}});
            p.add_object_ts("10", {});
            p.emplace_object("11");
        }
        // 迭代器测试
        for (const auto &child : p)
        {
            child->Str();
        }
        // moveOnlyTest
        {
            moveOnlyPool p;
            p.emplace_object("1", std::move(std::make_unique<int>(1)));
        }
    }
}
