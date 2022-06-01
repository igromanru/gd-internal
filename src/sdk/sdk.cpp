#include "sdk.h"

VOID SetupSDK( )
{
	UCHAR* PlayerGet = MgrGetPointerAddressFromPattern( "Player:Get", { 0x164 } );
	UCHAR* PlayerMap = MgrGetPointerAddress( PlayerGet, { 0x0 } );

	UCHAR* LevelEditor = MgrGetAddress( "sdk:LevelEditor", 0 );

	sdk::leveleditor::base =
		( GeometryDashLevelEditor* )MgrGetPointerAddress( LevelEditor,
			{ 0x168, 0x204, 0xe8, 0x8, 0xb4, 0xb4, 0x354 } ); // Cast address to GeometryDashLevelEditor


	sdk::player::base =
		( GeometryDashPlayerMap* )PlayerMap; // Cast address to PlayerMap

	sdk::playerobject::base =
		( GeometryDashPlayerObject* )MgrGetPointerAddress(
		PlayerMap + PlayerObjectOffset, { 0x0 }
	); // Cast address to PlayerObject

}

namespace sdk
{
	namespace player
	{
		GeometryDashPlayerMap* base = nullptr;
	}

	namespace playerobject
	{
		GeometryDashPlayerObject* base = nullptr;
	}

	namespace leveleditor
	{
		GeometryDashLevelEditor* base = nullptr;
	}

	BOOL IsEditing( )
	{
		SetupSDK( );
		if ( sdk::leveleditor::base != nullptr && ( UCHAR* )sdk::leveleditor::base != ( UCHAR* )0x000007B0 )
			return TRUE;
		return FALSE;
	}

	BOOL IsPlayer( )
	{
		SetupSDK( );
		if ( sdk::player::base != nullptr && sdk::playerobject::base != nullptr )
			return TRUE;

		return FALSE;
	}
}

