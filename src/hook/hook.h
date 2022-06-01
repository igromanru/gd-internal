#pragma once
#include <Windows.h>

#include "minhook/include/MinHook.h"

#include <GL/gl.h> //Open Gl


extern VOID InitializeHook( );
extern VOID UnloadHooks( );

extern WNDPROC			o_WndProc;

//

typedef BOOL( __stdcall* wglSwapBuffers_t ) (
	HDC hDc
);
wglSwapBuffers_t* get_wglSwapBuffers( );
BOOL __stdcall h_wglSwapBuffers(
		IN  HDC hDc );

typedef LRESULT( CALLBACK* WNDPROC ) (
	IN  HWND   hwnd,
	IN  UINT   uMsg,
	IN  WPARAM wParam,
	IN  LPARAM lParam
);

extern LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
);