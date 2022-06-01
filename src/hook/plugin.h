#pragma once
#include <Windows.h>
#include "imgui/imgui.h"

#define BEGIN_TAB1(Name)\
ImGui::PushStyleColor(ImGuiCol_ChildBg,  ImVec4( 37 / 255.f, 37 / 255.f, 37 / 255.f, 255 / 255.f )); \
ImGui::BeginChild( Name, ImVec2( ImGui::GetWindowSize( ).x / 2 - 5, ImGui::GetWindowSize( ).y - ImGui::GetCursorPosY( ) ), 1 );\
ImGui::Text(Name);

#define BEGIN_TAB2(Name)\
ImGui::SameLine();\
ImGui::PushStyleColor(ImGuiCol_ChildBg,  ImVec4( 37 / 255.f, 37 / 255.f, 37 / 255.f, 255 / 255.f )); \
ImGui::BeginChild( Name, ImVec2( ImGui::GetWindowSize( ).x - ImGui::GetCursorPosX(), ImGui::GetWindowSize( ).y - ImGui::GetCursorPosY( ) ), 1 );\
ImGui::Text(Name);

#define BEGIN_TABMIDDLE(Name)\
ImGui::PushStyleColor(ImGuiCol_ChildBg,  ImVec4( 37 / 255.f, 37 / 255.f, 37 / 255.f, 255 / 255.f )); \
ImGui::BeginChild( Name, ImVec2( ImGui::GetWindowSize( ).x - ImGui::GetCursorPosX(), ImGui::GetWindowSize( ).y - ImGui::GetCursorPosY( ) ), 1 );\
ImGui::Text(Name);

#define END_TAB()\
ImGui::EndChild();\
ImGui::PopStyleColor( );



extern VOID SetupMenu( );
extern BOOL CreateTab( const char* lol, INT TabIndex, INT Index );

