//------------------------------------------------------------------------------
#pragma once
#include <eight/core/alloc/stack.h>
#include <eight/core/macro.h>
namespace eight {
//------------------------------------------------------------------------------

class Scope : NonCopyable
{
public:
	Scope( StackAlloc&, const char* name );
	Scope( Scope&, const char* name );
	~Scope();
	const u8* Tell() const;
	void Unwind();
	void Seal();
	bool Sealed() const;
	//See new.h for keywords (macros) to 
	template<class T> void* New();                          //no c,    d
	template<class T> T* New( uint count );                 //   c,    d
	template<class T> T* New( uint count, const T& init );  //   c,    d
	template<class T> T* Alloc();                           //no c, no d
	template<class T> T* Alloc( uint count );               //no c, no d
	template<class T> T* Alloc( uint count, const T& init );//   c, no d
	                 u8* Alloc( uint size, uint align=0 );
					 
	u32 Capacity() const { return alloc.Capacity(); }
private:
	Scope( Scope& );
	template<class T> static void DestructorCallback(void* p);
	template<class T> T* AllocObject();
	template<class T> T* AllocObject( uint count );

	const static uint alignment = 16;

	StackAlloc& alloc;
	const void* parent;
	const u8* base;
	struct Destructor
	{
		void (*fn)(void*);
		Destructor* next;
		void* object;
	}* destructList;
	const char* name;
};

//------------------------------------------------------------------------------
#include "scope.hpp"
} // namespace eight
//------------------------------------------------------------------------------
