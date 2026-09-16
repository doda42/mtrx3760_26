//-----------------------------------------------------------------------------
// CRender.h
//
// A thin wrapper around the raylib graphics library. Everything raylib-specific
// is hidden behind this class, so the rest of the program never includes
// raylib.h and never sees a raylib type.
//
//
// INSTALLING RAYLIB ON YOUR OWN MACHINE (you have sudo)
//
//     sudo add-apt-repository ppa:texus/raylib
//     sudo apt update
//     sudo apt install libraylib5-dev
//
// Find the raylib header and read it. It is a single file listing every
// function raylib offers, one per line, each with a comment. Worth a look.
//
//     sudo updatedb
//     locate raylib.h
//
// The updatedb is only necessary once, to update your search database.
// Locate reports something like /usr/include/raylib.h, which you can open
// with your favourite editor.
//
//
// INSTALLING RAYLIB ON A LAB MACHINE (you do not have sudo)
//
// apt needs root, so build raylib from source and install it into your own
// home directory instead. This takes about a minute.
//
// It does not matter where you unpack the source, because the finished library
// is installed into $HOME/raylib either way. Start from your home directory,
// and keep the source tree out of your project folder so you do not submit it.
//
//     cd $HOME
//     git clone --depth 1 --branch 5.5 https://github.com/raysan5/raylib.git raylib-src
//     cd raylib-src
//     cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$HOME/raylib -DBUILD_EXAMPLES=OFF
//     cmake --build build -j$( nproc )
//     cmake --install build
//
// You only need to do that once. The raylib-src folder can be deleted
// afterwards if you want the space back; $HOME/raylib is the part that matters.
// Now change back into the folder holding your own source files to build.
//
// The header is then in your home directory, and you can read it with:
//
//     less $HOME/raylib/include/raylib.h
//
// raylib builds as a static library, so no further setup is needed to run it.
//
//
// BUILDING
//
// The build command differs between the two cases above. See TestRender.cpp for
// both versions.
//-----------------------------------------------------------------------------

#ifndef CRENDER_H
#define CRENDER_H

#include "raylib.h"

//-----------------------------------------------------------------------------
struct Vec2D
{
    float x;
    float y;
};

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

        void DrawCircle( Vec2D aPosition, int aRadius, Color aColor );
        void DrawLine( Vec2D aStart, Vec2D aEnd, float aThickness, Color aColor );
        void DrawRectangle( Vec2D aTopLeft, Vec2D aSize, Color aColor );

        //---Access to the window---
        int GetScreenWidth() const;
        int GetScreenHeight() const;

    private:
        //---The window---
        const int mScreenWidth;
        const int mScreenHeight;
};

#endif
