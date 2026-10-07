//-----------------------------------------------------------------------------
// CRender.h
//
// A thin wrapper around the raylib graphics library. Everything raylib-specific
// is hidden behind this class, so the rest of the program never includes
// raylib.h and never sees a raylib type.


#ifndef CRENDER_H
#define CRENDER_H

#include "CVec2D.h"

#include "raylib.h"


//-----------------------------------------------------------------------------
class CRender
{
    public:
        //---Ctor/Dtor---
        CRender();

        //---Util---
        bool WindowShouldClose();
        void CloseWindow();

        //---Drawing---
        void BeginDrawing();
        void EndDrawing();

        void DrawCircle( CVec2D aPosition, int aRadius, Color aColor );
        void DrawLine( CVec2D aStart, CVec2D aEnd, float aThickness, Color aColor );
        void DrawRectangle( CVec2D aTopLeft, CVec2D aSize, Color aColor );

        //---Access to the window---
        int GetScreenWidth() const;
        int GetScreenHeight() const;

    private:
        //---The window---
        const int mScreenWidth;
        const int mScreenHeight;
};

#endif
