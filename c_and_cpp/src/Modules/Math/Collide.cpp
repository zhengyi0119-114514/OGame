#define OGAME_EXPORT
#include "modules/math.hpp"
#include <math.h>

namespace ogame::math
{
bool OGAME_API IsCollide(const Circle &cLeft, const Circle &cRight)
{
    double dDistance = 0;
    dDistance = sqrt(static_cast<double>(pow(cLeft.Center().X() - cRight.Center().X(), 2) +
                                         pow(cLeft.Center().Y() - cRight.Center().Y(), 2)));
    return dDistance <=(cLeft.Radius()+cRight.Radius());
}
} // namespace ogame::math