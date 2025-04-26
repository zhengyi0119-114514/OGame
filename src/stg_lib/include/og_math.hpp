#ifndef OGAME_STGLIB_H
#define OGAME_STGLIB_H 1
#include <stdint.h>
#include <numbers>
namespace open_stg::module::math 
{
struct point
{
    double x;
    double y;
};
struct vector
{
    double x;
    double y;
    double theta;//rad
};
struct circle
{
    point center;
    double redius;
};
constexpr static double pi = std::numbers::pi_v<double>;
}
#endif // !OGAME_STGLIB_H
