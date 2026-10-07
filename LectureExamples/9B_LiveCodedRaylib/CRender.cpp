//-----------------------------------------------------------------------------
// CRender.cpp
//
// Implementation of the raylib wrapper. The :: prefix on the raylib calls says
// "the global one", distinguishing raylib's DrawCircle from our member function
// of the same name.
//-----------------------------------------------------------------------------

#include "CRender.h"

//-----------------------------------------------------------------------------
CRender::CRender()
    :
        mScreenWidth( 800 ),
        mScreenHeight( 600 )
{
    InitWindow( mScreenWidth, mScreenHeight, "TODO: Replace This Text" );
    SetTargetFPS( 60 );
}

int CRender::GetScreenWidth() const
{
    return mScreenWidth;
}

int CRender::GetScreenHeight() const
{
    return mScreenHeight;
}

bool CRender::WindowShouldClose()
{
    bool Result = ::WindowShouldClose();
    return Result;
}

void CRender::CloseWindow()
{
    ::CloseWindow();
}

void CRender::BeginDrawing()
{
    ::BeginDrawing();
    ::ClearBackground( BLACK );
}

void CRender::EndDrawing()
{
    ::EndDrawing();
}

void CRender::DrawCircle( CVec2D aPosition, int aRadius, Color aColor )
{
    ::DrawCircle( aPosition.x, aPosition.y, aRadius, aColor );
}

void CRender::DrawLine( CVec2D aStart, CVec2D aEnd, float aThickness, Color aColor )
{
    Vector2 Start = { aStart.x, aStart.y };
    Vector2 End = { aEnd.x, aEnd.y };

    ::DrawLineEx( Start, End, aThickness, aColor );
}

void CRender::DrawRectangle( CVec2D aTopLeft, CVec2D aSize, Color aColor )
{
    Vector2 TopLeft = { aTopLeft.x, aTopLeft.y };
    Vector2 Size = { aSize.x, aSize.y };

    ::DrawRectangleV( TopLeft, Size, aColor );
}
