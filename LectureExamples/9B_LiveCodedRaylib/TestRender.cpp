//-----------------------------------------------------------------------------
// TestRender.cpp
//
// A simple demo of using the CRender class.

#include "CRender.h"
#include "CVec2D.h"

#include <stdlib.h>   // for rand()
#include <iostream>
#include <vector>


//--Fwd decl---
class CSim;

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

        //---Physics properties---
        Color mColour;
        CVec2D mPosition;
        CVec2D mVelocity;

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
        CVec2D mSize;
};

//-----------------------------------------------------------------------------
// todo: comment properly
class CSim
{
    public:
        ~CSim();

        static CSim* GetInstance();    // single point of access
        void Init();  // todo: investigate how to have a constructor work here        

        void Run();
        float GetGravity() const;
        
    private:
        //---Consts---
        // todo: without a constructor how do i do consts?!
        float mGravity;   // acceleration due to mGravity
        int mNumBalls;
        int mNuMBoxes;
        
        //---
        CRender mRender;
        std::vector<CRigidBody*> mBodies;

        //---Singleton---
        static CSim* instance;         // static pointer to instance
        CSim(const CSim&);             // not implemented so you can't copy
        void operator=(const CSim&);   // not implemented so you can't assign
        CSim() { }                     // private so you can't instantiate
};
CSim* CSim::instance = 0;   // Init to 0 when the program starts

//--Single point of access---------------------
CSim* CSim::GetInstance()
{
  if( instance == 0 ) { // true on first call only
    instance = new CSim();       // instantiation happens exactly once
  }
  return instance;
}


//-----------------------------------------------------------------------------
// todo: comment
int main()
{
    CSim::GetInstance()->Init();
    CSim::GetInstance()->Run();

    return 0;
}



//-----------------------------------------------------------------------------
void CSim::Init()
{
    mGravity = 0.5f;
    mNumBalls = 500;
    mNuMBoxes = 6;

    for( int i=0; i<mNuMBoxes; ++i )
    {
        mBodies.push_back( new CBox( mRender ) );
    }
    for( int i=0; i<mNumBalls; ++i )
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

float CSim::GetGravity() const
{
    return mGravity;
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
    mVelocity.y += CSim::GetInstance()->GetGravity();
    mPosition += mVelocity;

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
    mVelocity.y += CSim::GetInstance()->GetGravity();

    mPosition += mVelocity;
    
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



