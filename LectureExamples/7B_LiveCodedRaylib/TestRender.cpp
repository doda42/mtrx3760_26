//-----------------------------------------------------------------------------
// TestRender.cpp
//
// A simple demo of using the CRender class.

#include "CRender.h"

#include <stdlib.h>   // for rand()
#include <iostream>
#include <vector>

//-----------------------------------------------------------------------------
class CBall
{
    public:
        //---Ctor/Dtor---    
        CBall( CRender& arRender );
        
        //---Physics simulation---
        void Update();
        
        //---Rendering---
        void Draw() const;
       
    private:
        //---
        Vec2D mPosition;
        Vec2D mVelocity;
        float mRadius;

        //---Consts---
        const float mDamping;   // energy loss on bounce

        // TODO: mGravity really isn't part of the ball, put somewhere better
        const float mGravity;   // acceleration due to mGravity

        Color mColour;

        //---Renderer---
        CRender& mrRender;        
};

//-----------------------------------------------------------------------------
// A static, semi-transparent box drawn behind the balls, mostly to show off
// CRender::DrawRectangle.
class CBox
{
    public:
        //---Ctor/Dtor---
        CBox( CRender& arRender );

        //---Rendering---
        void Draw() const;

    private:
        Vec2D mTopLeft;
        Vec2D mSize;
        Color mColour;

        //---Renderer---
        CRender& mrRender;
};

//-----------------------------------------------------------------------------
int main()
{
    const int NumBalls = 500;
    const int NumBoxes = 6;
    CRender Render;
    std::vector<CBall*> Balls;
    std::vector<CBox*> Boxes;

    for( int i=0; i<NumBoxes; ++i )
    {
        Boxes.push_back( new CBox( Render ) );
    }

    for( int i=0; i<NumBalls; ++i )
    {
        Balls.push_back( new CBall( Render ) );
    }
    
    //---The main loop---
    while( !Render.WindowShouldClose() ) 
    {
        Render.BeginDrawing();

        for( int i=0; i<NumBoxes; ++i )
        {
            Boxes[i]->Draw();
        }

        for( int i=0; i<NumBalls; ++i )
        {
            Balls[i]->Update();
            Balls[i]->Draw();
        }                        
        Render.EndDrawing();
    }
    
    //---Cleanup---
    Render.CloseWindow();
        
    for( int i=0; i<NumBalls; ++i )
    {
        delete Balls[i];
    }

    for( int i=0; i<NumBoxes; ++i )
    {
        delete Boxes[i];
    }
    
    return 0;
}


//-----------------------------------------------------------------------------
CBall::CBall( CRender& arRender )
    :   mPosition
        ({
            400.0f + (100.0f * (float(rand())/RAND_MAX - 0.5f)), 
            300.0f + (100.0f * (float(rand())/RAND_MAX - 0.5f))
        }),
        mVelocity( {4.0f + 4.0f * (float(rand())/RAND_MAX - 0.5f), 0.0f} ),
        mRadius( 25.0f + 20.0f * (float(rand())/RAND_MAX - 0.5f)),
        mDamping( 0.97f ),
        mGravity( 0.5f ),
        mColour
        { 
            (unsigned char)(rand()%255), 
            (unsigned char)(rand()%255), 
            (unsigned char)(rand()%255), 
            128 
        },
        mrRender( arRender )
{
    
}

void CBall::Update()
{
    mVelocity.y += mGravity;

    // Update position // TODO: use or program a vector that knows how to mPosition += mVelocity;
    mPosition.x += mVelocity.x;
    mPosition.y += mVelocity.y;

    // Bounce off floor
    if( mPosition.y + mRadius > mrRender.GetScreenHeight() ) 
    {
        mPosition.y = mrRender.GetScreenHeight() - mRadius;  // reposition at floor
        
        // Reverse velocity and add a small random variation
        const float RandomVelocityOffset = 5.0f * (float(rand())/RAND_MAX - 0.5f);
        mVelocity.y *= -mDamping;
        mVelocity.y += RandomVelocityOffset;
    }

    // Bounce off ceiling
    if (mPosition.y - mRadius < 0) 
    {
        mPosition.y = mRadius;
        mVelocity.y *= -mDamping;
    }

    // Bounce off walls
    if (mPosition.x - mRadius < 0 || mPosition.x + mRadius > mrRender.GetScreenWidth()) 
    {
        mVelocity.x *= -1;
    }
}


void CBall::Draw() const
{
    mrRender.DrawCircle( mPosition, mRadius, mColour );
}


//-----------------------------------------------------------------------------
CBox::CBox( CRender& arRender )
    :   mTopLeft
        ({
            arRender.GetScreenWidth() * (float(rand())/RAND_MAX),
            arRender.GetScreenHeight() * (float(rand())/RAND_MAX)
        }),
        mSize( { 60.0f + 120.0f * (float(rand())/RAND_MAX), 40.0f + 80.0f * (float(rand())/RAND_MAX) } ),
        mColour
        {
            (unsigned char)(rand()%255),
            (unsigned char)(rand()%255),
            (unsigned char)(rand()%255),
            64
        },
        mrRender( arRender )
{

}


void CBox::Draw() const
{
    mrRender.DrawRectangle( mTopLeft, mSize, mColour );
}
