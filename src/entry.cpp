#include <Windows.h>
#include <stdio.h>

#include "hook/imgui/imgui.h"
#include "hook/hook.h"
#include "hook/plugin.h"

#include "inc.h"

BOOL ReadyToEject = 0;
HMODULE hModuleGlobal = 0;

DWORD WINAPI Initialize( )
{
#ifdef _DEBUG
	AllocConsole( );

	SetConsoleTitle( L"Internal Console" );
	FILE* fpstdin = stdin, * fpstdout = stdout, * fpstderr = stderr;
	freopen_s( &fpstdin, "CONIN$", "r", stdin );
	freopen_s( &fpstdout, "CONOUT$", "w", stdout );
	freopen_s( &fpstderr, "CONOUT$", "w", stderr );
#endif
	
	while ( !ReadyToEject )
		Sleep( 100 );

	GuiOpen = 0;
#ifdef _DEBUG
	fclose( fpstdin );
	fclose( fpstdout );
	fclose( fpstderr );
	FreeConsole( );
#endif

	UnloadHooks( ); // Unload all hooks

	// Restore old WNDPROC
	SetWindowLongPtr( FindWindowA( 0, "Geometry Dash" ), GWLP_WNDPROC, ( LONG_PTR )o_WndProc );
	
	FreeLibraryAndExitThread( hModuleGlobal, 1 );

}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch ( dwReason )
	{
		case DLL_PROCESS_ATTACH:
			hModuleGlobal = hMod;

			DisableThreadLibraryCalls( hMod );
			CreateThread( 0, 0, LPTHREAD_START_ROUTINE( Initialize ), 0, 0, 0 );

			InitializeHook( ); // Initialize ( FIRST TO BE CALLED!! )
			LoadHookMgr( );    // Load Hook Manager
			SetupSDK( );	   // Setup SDK
			
			break;
		case DLL_PROCESS_DETACH:
			
			break;
	}
	return TRUE;
}