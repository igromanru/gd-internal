#pragma once
#include <Windows.h>
#include "hook/imgui/imgui.h"
#include <gl/GL.h>

#include <stdint.h>
#include <vector>

#include "sdk/sdk.h"

extern unsigned char ImGuiFont[ ];

extern ImFont* SmallImGuiFont;
extern ImFont* MediumImGuiFont;
extern ImFont* HugeImGuiFont;


extern uint8_t* PatternScan( void* module, const char* signature, int offset );

// menu.cpp
extern VOID RenderMain( );

// Some Globals
extern BOOL ReadyToEject;
extern HMODULE hModuleGlobal;

// Settings
extern bool SettingsIgnoreMenu;


extern bool GuiOpen;
extern bool ShowWatermark;
extern bool ShowFPS;
