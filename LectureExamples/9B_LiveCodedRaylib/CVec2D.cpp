#include "CVec2D.h"


CVec2D& CVec2D::operator+=(const CVec2D& rhs) 
{
    x += rhs.x;
    y += rhs.y;
    return *this; // return the result by reference
}

