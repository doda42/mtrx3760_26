#ifndef __VEC2D_H
#define __VEC2D_H

//-----------------------------------------------------------------------------
class CVec2D
{
    public:
    
        CVec2D& operator+=(const CVec2D& rhs);

    // todo: private?
        float x;
        float y;
};

#endif
