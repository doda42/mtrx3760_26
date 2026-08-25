// Design a directory of people's names and their Year of birth
//    A person’s name (key) associates with their birth Year (value)
// Compare two design options:
//    Hash table-based
//    Vector-based
// Build your own data structures

// If the directory got to have 1M entries, consider time to add an entry, 
// time to find an entry, and memory utilisation of each structure.

// For vector-based, consider the impact of sorting.


#include <iostream>
#include <string>

struct Person
{
  int Year;
  std::string Name;
};

//--Abstract base--
class CDirectory
{
  public:
    virtual void AddEntry( const char* pName, int Year ) = 0;   // adds an entry to the directory
    virtual int LookupEntry( const char* pName ) = 0;           // looks up an entry
};

//--Hash-based dir---
const int HashTableSize = 16; // todo: embed inside class
class CDirectoryHash : public CDirectory
{    
  public:

  private:    
    
};

//--Vector-based dir---
const int VectorMaxSize = 16;
class CDirectoryVector : public CDirectory
{    
  public:

  private:
};



int main()
{
  CDirectory* pMyDirectory = new CDirectoryVector;
//  CDirectory* pMyDirectory = new CDirectoryHash;

  pMyDirectory->AddEntry( "Bob", 2001 );
  pMyDirectory->AddEntry( "Alice", 1800 );
  pMyDirectory->AddEntry( "Darcy", 2004 );
  
  std::cout << "Bob " << pMyDirectory->LookupEntry( "Bob" ) << std::endl;

  delete pMyDirectory;
}


