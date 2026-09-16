//-----------------------------------------------------------------------------
// TestRender.cpp
//
// A simple demo of using the CRender class.

#include "CRender.h"

#include <stdlib.h>   // for rand()
#include <iostream>
#include <vector>

//-----------------------------------------------------------------------------
// todo: comment properly
class CRigidBody
{
    public:
        CRigidBody( CRender& arRender );

        //---Physics simulation---
        virtual void Update() = 0;
        
        //---Rendering---
        virtual void Draw() const = 0;

    protected:
        //---Consts---
        const float mDamping;   // energy loss on bounce
        const float mGravity;   // acceleration due to mGravity

        //---Physics properties---
        Color mColour;
        Vec2D mPosition;
        Vec2D mVelocity;

        //---Renderer---
        CRender& mrRender;
};

//-----------------------------------------------------------------------------
// todo: comment properly
class CBall: public CRigidBody
{
    public:
        CBall( CRender& arRender );
        
        //---Physics simulation---
        void Update();
        
        //---Rendering---
        void Draw() const;
       
    private:
        float mRadius;
};

//-----------------------------------------------------------------------------
// A box that falls and bounces like the balls do. It always stays upright: no
// rotation, so the bounce tests are just against its four edges.
class CBox: public CRigidBody
{
    public:
        CBox( CRender& arRender );

        //---Physics simulation---
        void Update();

        //---Rendering---
        void Draw() const;

    private:
        //---
        Vec2D mSize;
};

//-----------------------------------------------------------------------------
// todo: comment properly
class CSim
{
    public:
        CSim();
        ~CSim();
        
        void Run();
        
    private:
        static const int NumBalls;
        static const int NumBoxes;
        CRender mRender;

        std::vector<CRigidBody*> mBodies;
};



//-----------------------------------------------------------------------------
// todo: comment
int main()
{

    CSim MySim;
    
    MySim.Run();
   
    return 0;
}



//-----------------------------------------------------------------------------
CSim::CSim()
{
    for( int i=0; i<NumBoxes; ++i )
    {
        mBodies.push_back( new CBox( mRender ) );
    }
    for( int i=0; i<NumBalls; ++i )
    {
        mBodies.push_back( new CBall( mRender ) );
    }
}

//-----------------------------------------------------------------------------
CSim::~CSim()
{
    //---Cleanup---
    mRender.CloseWindow();
        
    for( int i=0; i<mBodies.size(); ++i )
    {
        delete mBodies[i];
    }
}

void CSim::Run()
{
    //---The main loop---
    while( !mRender.WindowShouldClose() ) 
    {
        mRender.BeginDrawing();

        for( int i=0; i<mBodies.size(); ++i )
        {
            mBodies[i]->Update();
            mBodies[i]->Draw();
        }
        mRender.EndDrawing();
    }
}

//-----------------------------------------------------------------------------
CRigidBody::CRigidBody( CRender& arRender )
    :   mPosition
        ({
            400.0f + (100.0f * (float(rand())/RAND_MAX - 0.5f)), 
            300.0f + (100.0f * (float(rand())/RAND_MAX - 0.5f))
        }),
        mVelocity( {4.0f + 4.0f * (float(rand())/RAND_MAX - 0.5f), 0.0f} ),
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

//-----------------------------------------------------------------------------
CBall::CBall( CRender& arRender )
    :   mRadius( 25.0f + 20.0f * (float(rand())/RAND_MAX - 0.5f)),
        CRigidBody( arRender )
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
    :   mSize( { 60.0f + 120.0f * (float(rand())/RAND_MAX), 40.0f + 80.0f * (float(rand())/RAND_MAX) } ),
        CRigidBody( arRender )
{

}

void CBox::Update()
{
    mVelocity.y += mGravity;

    mPosition.x += mVelocity.x;
    mPosition.y += mVelocity.y;

    // Bounce off floor
    if( mPosition.y + mSize.y > mrRender.GetScreenHeight() )
    {
        mPosition.y = mrRender.GetScreenHeight() - mSize.y;  // reposition at floor

        // Reverse velocity and add a small random variation
        const float RandomVelocityOffset = 5.0f * (float(rand())/RAND_MAX - 0.5f);
        mVelocity.y *= -mDamping;
        mVelocity.y += RandomVelocityOffset;
    }

    // Bounce off ceiling
    if( mPosition.y < 0 )
    {
        mPosition.y = 0;
        mVelocity.y *= -mDamping;
    }

    // Bounce off walls
    if( mPosition.x < 0 || mPosition.x + mSize.x > mrRender.GetScreenWidth() )
    {
        mVelocity.x *= -1;
    }
}
void CBox::Draw() const
{
    mrRender.DrawRectangle( mPosition, mSize, mColour );
}

//-----------
const int CSim::NumBalls = 500;
const int CSim::NumBoxes = 6;

