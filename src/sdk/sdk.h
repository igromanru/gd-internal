#pragma once
#include "player.h" // GeometryDashPlayerMap
#include "playerobject.h"
#include "leveleditor.h"
#include "../hookmgr.h"

#define PlayerObjectOffset 0x224
extern VOID SetupSDK( );

namespace sdk
{
	namespace player
	{
		extern GeometryDashPlayerMap* base;
	}

	namespace playerobject
	{
		extern GeometryDashPlayerObject* base;
	}

	namespace leveleditor
	{
		extern GeometryDashLevelEditor* base;
	}

	extern BOOL IsPlayer( );
	extern BOOL IsEditing( );
}