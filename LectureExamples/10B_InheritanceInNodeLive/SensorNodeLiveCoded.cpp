// A start on the node design for the fire sensor problem
// See FireSensorProblemStatement.txt
//
// In this example we'll use a stand-in CNode that knows how to "publish" by
// printing to the screen as a stand-in for ROS 2. This allows for lightweight
// development during the early design stage for this project.

#include "HardwareEmulator.h"

#include <iostream>
#include <string>
#include <sstream>

//---Pretend-Node--------------------------------------------------------------
// A minimalist class to stand in for ROS in small examples
class CNode
{
  protected:
    void Publish( std::string Message );
};

// base class
class FireDetector: public CNode, public ISensorCallable
{
  public:
    FireDetector() { Publish( "hello world" ); }
    void Callback( int Value ) = 0;
  private:
  // normally would have a publisher here
    
};

class FireDetCamera: public FireDetector
{
  public:
    void Callback( int Value )
    {
      // do some processing on value here
      std::stringstream MyStr;
      MyStr << "Camera-based detector is publishing value " << Value;
      Publish( MyStr.str() );
    }
};

class FireDetPD: public FireDetector
{
  public:
    void Callback( int Value )
    {
      // do some processing on value here
      std::stringstream MyStr;
      MyStr << "Photodiode is publishing value " << Value*2;
      Publish( MyStr.str() );
    }
};


//-----------------------------------------------------------------------------
int main()
{
  std::cout << "Which type? 0 or 1" << std::endl;
  int type;
  std::cin >> type;
  
  FireDetector* pDet = NULL;
  
  bool StatusOk = true;
  
  switch( type )
  {
    case 0: pDet = new FireDetCamera;
    break;

    case 1: pDet = new FireDetPD;
    break;

    default: std::cout << "unavailable" << std::endl;
    StatusOk = false;
  }
  
  if( StatusOk )
  {
    CHardwareEmulator MyEmulator( *pDet );
    
    // wait for a bit to let some events happen
    std::this_thread::sleep_for(std::chrono::seconds(5));
  }
  
  delete pDet;
  
  return 0;
}


//-----------------------------------------------------------------------------
void CNode::Publish( std::string Message )
{
  std::cout << Message << std::endl;
}
