#include <Windows.h>
#include "hook.h"
#include "../inc.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"

// OpenGL Hook from https://github.com/adafcaefc/Universal-OpenGL-2-Kiero-Hook ,cleaned by me.


#define ORANGE_COLOR(Alpha)\
ImVec4( 238 / 255.f, 176 / 255.f, 35 / 255.f, Alpha / 255.f )

// Globals
bool GuiOpen = 1;
bool ShowWatermark = 1;
bool ShowFPS = 1;

ImFont* SmallImGuiFont = 0;
ImFont* MediumImGuiFont = 0;
ImFont* HugeImGuiFont = 0;


WNDPROC			o_WndProc = 0;
wglSwapBuffers_t o_wglSwapBuffers = 0;
HGLRC      g_WglContext = 0;
bool SettingsIgnoreMenu = 0;


int rmode = 1;
int firs = 255;
int seco = 0;
int thir = 0;

ImColor WatermarkRainbowColor;

//////////////////////////////////////////////

void RainbowLoop( )
{
	switch ( rmode )
	{
		case 1:
		{
			seco += 1;
			if ( seco >= 255 )
			{
				rmode = 2;
			}
		} break;

		case 2:
		{
			firs -= 2;
			if ( firs <= 0 )
			{
				rmode = 3;
			}
		} break;

		case 3:
		{
			thir += 2;
			if ( thir >= 255 )
			{
				rmode = 4;
			}
		} break;

		case 4:
		{
			seco -= 2;
			if ( seco <= 0 )
			{
				rmode = 5;
			}
		} break;

		case 5:
		{
			firs += 2;
			if ( firs >= 255 )
			{
				rmode = 6;
			}
		} break;

		case 6:
		{
			thir -= 2;
			if ( thir <= 0 )
			{
				rmode = 1;
			}
		} break;
	}
	WatermarkRainbowColor = ImColor( firs, seco, thir );
}

static void SetImGuiStyle( )
{

	ImGuiStyle* style = &ImGui::GetStyle( );
	ImVec4* colors = style->Colors;

	colors[ ImGuiCol_Text ] = ImVec4( 255 / 255.f, 255 / 255.f, 255 / 255.f, 255 / 255.f );
	colors[ ImGuiCol_TextDisabled ] = ImVec4( 62 / 255.f, 62 / 255.f, 64 / 255.f, 255 / 255.f );
	colors[ ImGuiCol_ScrollbarBg ] = ImVec4( 62 / 255.f, 62 / 255.f, 62 / 255.f, 255 / 255.f );
	colors[ ImGuiCol_ScrollbarGrab ] = ORANGE_COLOR( 200 );
	colors[ ImGuiCol_ScrollbarGrabHovered ] = ORANGE_COLOR( 230 );
	colors[ ImGuiCol_ScrollbarGrabActive ] = ORANGE_COLOR( 255 );

	colors[ ImGuiCol_CheckMark ] = ImVec4( 0.f, 0.f, 0.f, 1.f );
	colors[ ImGuiCol_FrameBg ] = ORANGE_COLOR( 200 );
	colors[ ImGuiCol_FrameBgHovered ] = ORANGE_COLOR( 230 );
	colors[ ImGuiCol_FrameBgActive ] = ORANGE_COLOR( 255 );

	colors[ ImGuiCol_SliderGrab ] = ORANGE_COLOR( 230 );
	colors[ ImGuiCol_SliderGrabActive ] = ORANGE_COLOR( 255 );
	colors[ ImGuiCol_Button ] = ORANGE_COLOR( 200 );
	colors[ ImGuiCol_ButtonHovered ] = ORANGE_COLOR( 230 );
	colors[ ImGuiCol_ButtonActive ] = ORANGE_COLOR( 255 );
	colors[ ImGuiCol_Separator ] = ImVec4( 1.f, 1.f, 1.f, 1.00f );

	style->FramePadding = ImVec2( 2, 2 );
	style->FrameRounding = 4;
	style->PopupRounding = 4;

	style->ChildRounding = 5.f;

	style->ScrollbarRounding = 6;
	style->GrabRounding = 4;
	style->TabRounding = 4;
}

VOID InitializeHook( )
{

	WNDCLASSEX windowClass;
	windowClass.cbSize = sizeof( WNDCLASSEX );
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle( NULL );
	windowClass.hIcon = NULL;
	windowClass.hCursor = NULL;
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = L"GeometryDashInternal";
	windowClass.hIconSm = NULL;

	::RegisterClassEx( &windowClass );

	auto hWnd = ::CreateWindow( windowClass.lpszClassName, L"GeometryDashInternal-Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL );

	MH_Initialize( );

	if ( MH_CreateHook(
		get_wglSwapBuffers( ), h_wglSwapBuffers, ( void** )&o_wglSwapBuffers ) != MH_OK )
		goto error;

	if ( MH_EnableHook( get_wglSwapBuffers( ) ) != MH_OK )
		goto error;

	return;

error:
	MessageBoxA( 0, "Couldn't create or enable SwapBuffers hook!", "Error", 0 );

}


LRESULT CALLBACK HookedWndProc(
		CONST HWND	hWnd,
		UINT		uMsg,
		WPARAM		wParam,
		LPARAM		lParam )
{
	if ( GetAsyncKeyState( VK_INSERT ) & 1 )
	{
		Sleep( 1 );
		GuiOpen = !GuiOpen;
	}

	ImGui_ImplWin32_WndProcHandler( hWnd, uMsg, wParam, lParam );
	if ( !GuiOpen || SettingsIgnoreMenu )
		return CallWindowProc( o_WndProc, hWnd, uMsg, wParam, lParam );

	return 1;
}



VOID InitOpenGL2( IN HDC hDc )
{
	static bool Initialized = 0;
	if ( Initialized )
		return;
	Initialized = 1;


	auto tStatus = 1;

	auto hWnd = WindowFromDC( hDc );
	auto wLPTR = SetWindowLongPtr( hWnd, GWLP_WNDPROC, ( LONG_PTR )HookedWndProc );
	if ( !wLPTR )
		MessageBoxA( 0, "Couldn't SetWindowLongPtr", "Error", 0 );

	o_WndProc = ( WNDPROC )wLPTR;
	g_WglContext = wglCreateContext( hDc );

	IMGUI_CHECKVERSION( );
	ImGui::CreateContext( );

	tStatus &= ImGui_ImplWin32_Init( hWnd );


	// Load some cool fonts
	ImGuiIO& io = ImGui::GetIO( );
	SmallImGuiFont = io.Fonts->AddFontFromMemoryTTF( ( void* )ImGuiFont, 135304, 14.f );
	MediumImGuiFont = io.Fonts->AddFontFromMemoryTTF( ( void* )ImGuiFont, 135304, 18.f );
	HugeImGuiFont = io.Fonts->AddFontFromMemoryTTF( ( void* )ImGuiFont, 135304, 28.f );

	tStatus &= ImGui_ImplOpenGL2_Init( );

}


float AlphaCalc( float n )
{
	n = ( n > 0.0f ) * n + !( n > 0.0f ) * 0.0f;
	return ( n < 1.0f ) * n + !( n < 1.0f ) * 1.0f;
}

VOID AlphaBlending( )
{
	static float freq { 1 / 0.25f };

	ImGuiStyle& style = ImGui::GetStyle( );
	if ( GuiOpen )
	{
		if ( style.Alpha < 1.f )
			style.Alpha = AlphaCalc( style.Alpha + freq * ImGui::GetIO( ).DeltaTime );
		RenderMain( );
	}
	else
	{
		if ( style.Alpha > 0.f )
		{
			RenderMain( );
			style.Alpha = AlphaCalc( style.Alpha + -freq * ImGui::GetIO( ).DeltaTime );
		}
	}
}

VOID RenderWin32( )
{
	ImGui_ImplWin32_NewFrame( );
	ImGui::NewFrame( );


	SetImGuiStyle( );

	AlphaBlending( ); // Show Main Menu
	if ( ShowWatermark )
	{
		RainbowLoop( );
		{
			RECT rekt = { 0 };
			GetWindowRect( FindWindowA( 0, "Geometry Dash" ), &rekt );

			auto draw = ImGui::GetBackgroundDrawList( );
			const char wm[ 9 ] = "internal";
			draw->AddText(
				HugeImGuiFont, 26.0f, ImVec2( 5.f, (float)( rekt.bottom - rekt.top - 67 ) ),
				WatermarkRainbowColor, wm );
		}
	}
	if ( ShowFPS )
	{
		RECT rekt = { 0 };
		GetWindowRect( FindWindowA( 0, "Geometry Dash" ), &rekt );

		auto draw = ImGui::GetBackgroundDrawList( );
		static char wm[ 1337 ];
		sprintf( wm, "FPS: %f", ImGui::GetIO( ).Framerate );

		float width = (float)( rekt.right - rekt.left );
		draw->AddRectFilled(
		ImVec2( width - 127, 18 ),
		ImVec2( width - 15, 35 ),
		IM_COL32( 45, 45, 48, 250 ), 15.f, 15 );

		draw->AddText(
			SmallImGuiFont, 14.0f, ImVec2( (float)( rekt.right - rekt.left ) - 120, 20 ),
			ImColor( 1.f, 1.f, 1.f, 1.f ), wm );
	}

	ImGui::EndFrame( );
	ImGui::Render( );
}

VOID RenderOpenGL2(
		IN  HGLRC 	  WglContext,
		IN  HDC		  hDc )
{
	auto tStatus = 1;

	auto o_WglContext = wglGetCurrentContext( );
	tStatus &= wglMakeCurrent( hDc, WglContext );

	ImGui_ImplOpenGL2_NewFrame( );
	RenderWin32( );
	ImGui_ImplOpenGL2_RenderDrawData( ImGui::GetDrawData( ) );

	tStatus &= wglMakeCurrent( hDc, o_WglContext );
}

BOOL __stdcall h_wglSwapBuffers(
		IN  HDC hDc )
{
	InitOpenGL2( hDc );
	RenderOpenGL2( g_WglContext, hDc );

	return o_wglSwapBuffers( hDc );
}

wglSwapBuffers_t* get_wglSwapBuffers( )
{
	auto hMod = GetModuleHandleA( "OPENGL32.dll" );
	if ( !hMod )
		return NULL;

	return ( wglSwapBuffers_t* )GetProcAddress( hMod, "wglSwapBuffers" );
}

VOID UnloadHooks( )
{
	MH_DisableHook( MH_ALL_HOOKS );
}


