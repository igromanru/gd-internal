#pragma once
#include <Windows.h>
#include "inc.h"

#include <string>

extern VOID
LoadHookMgr( );

extern UCHAR* MgrGetAddress( std::string hookName, const char* ModuleName );
extern UCHAR* MgrGetPointerAddress( UCHAR* Addy, std::vector<unsigned int> offsets );
extern UCHAR* MgrGetPointerAddressFromPattern( std::string hookName, std::vector<unsigned int> offsets );

extern BYTE* MgrPatchAddress( UCHAR* Addy, BYTE Bytes[ ], INT Size );