// Design a directory of people's names and their Year of birth
//    A person’s name (key) associates with their birth Year (value)
// Compare two design options:
//    Hash table-based
//    Vector-based : unsorted
//    --TODO EXAM QUESTION-->> Vector-based : sorted
// Build your own data structures

// If the directory got to have 1M entries, consider time to add an entry, 
// time to find an entry, and memory utilisation of each structure.

// For vector-based, consider the impact of sorting.

// This is as we built it in lecture, starting from DirectoryCompareScaffold.cpp
// There's much more to explore following this same vein


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

//--Vector-based dir---
const int VectorMaxSize = 16; // todo: move this inside the class ("encapsulate everything")
class CDirectoryVector : public CDirectory
{    
  public:
    CDirectoryVector() : mNumStored(0) {}
    void AddEntry( const char* pName, int Year )
    {
      Person NewPerson;
      NewPerson.Name = pName;
      NewPerson.Year = Year;
      mPeople[mNumStored] = NewPerson;
      ++mNumStored;
    }
    int LookupEntry( const char* pName )
    {
      int Result = -1;
      for( int i=0; i<mNumStored; ++i )
      {
        if( mPeople[i].Name == pName )
        {
          Result = mPeople[i].Year;
        }
      }
      return Result;
    }
    
  private:
    Person mPeople[VectorMaxSize]; // why prefer to two arrays?
    int mNumStored;
};


//--Hash-based dir---
const int HashTableSize = 16; // todo: embed inside class
const int HashTableMask = 0xF;
class CDirectoryHash : public CDirectory
{    
  public:
    void AddEntry( const char* pName, int Year )
    {
      // 1) compute hash of key pName
      int Hash = HashFunction( pName );
      std::cout << pName << " hashes to : " << Hash << std::endl;
      
      // 2) store value at that hash index
      mHashTable[Hash] = Year;
    }
    
    int LookupEntry( const char* pName )
    {
      int Result = -1;

      // 1) compute hash of key pName
      int Hash = HashFunction( pName );      

      // 2) lookup value at that hash index
      Result = mHashTable[Hash];

      return Result;
    }

  private:
    int HashFunction( const char* pName ); // needs to return ints within range 0..HashTableTableSize-1    
    int mHashTable[HashTableSize];
};



int main()
{
//  CDirectory* pMyDirectory = new CDirectoryVector;
  CDirectory* pMyDirectory = new CDirectoryHash;

  pMyDirectory->AddEntry( "Bob", 2001 );
  pMyDirectory->AddEntry( "Alice", 1800 );
  pMyDirectory->AddEntry( "Darcy", 2004 );
  
  std::cout << "Bob " << pMyDirectory->LookupEntry( "Bob" ) << std::endl;

  delete pMyDirectory;
}



// returns hash in range 0..TableSize
int CDirectoryHash::HashFunction( const char* pName ) 
{ 
  int Result = 0;
  for( int i=0; pName[i] != 0; ++i )
  {
    Result ^= pName[i];    
  }
  
  Result = Result & HashTableMask;
  
  return Result;  
} 
