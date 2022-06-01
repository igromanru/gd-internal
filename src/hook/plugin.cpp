#include "plugin.h"

VOID SetupMenu( )
{
	ImVec2 WindowPos = ImGui::GetWindowPos( );
	ImVec2 WindowSize = ImGui::GetWindowSize( );

	auto pDrawList = ImGui::GetWindowDrawList( );

	pDrawList->AddRectFilled(
		ImVec2( WindowPos.x, WindowPos.y ),
		ImVec2( WindowSize.x + WindowPos.x, WindowPos.y + WindowSize.y ),
		IM_COL32( 45, 45, 48, 250 * ImGui::GetStyle( ).Alpha ), 15.f, 15.f );

	pDrawList->AddRectFilled(
		WindowPos,
		ImVec2( WindowPos.x + 120, WindowPos.y + WindowSize.y ),
		IM_COL32( 37, 37, 38, 255 * ImGui::GetStyle( ).Alpha ), 0, 0 );
}

BOOL CreateTab( const char* lol, INT TabIndex, INT Index )
{
	ImVec2 WindowPos = ImGui::GetWindowPos( );
	ImVec4 Active;
	if ( TabIndex == Index )
		Active = ImVec4( 62 / 255.f, 62 / 255.f, 64 / 255.f, 100 / 255.f );
	else Active = ImVec4( 62 / 255.f, 62 / 255.f, 64 / 255.f, 255 / 255.f );

	ImGui::PushStyleVar( ImGuiStyleVar_FrameRounding, 0 );
	ImGui::PushStyleColor( ImGuiCol_Button, Active );
	ImGui::PushStyleColor( ImGuiCol_ButtonHovered, Active );
	ImGui::PushStyleColor( ImGuiCol_ButtonActive, Active );

	auto pDrawList = ImGui::GetWindowDrawList( );
	if ( TabIndex == Index )
	{
		pDrawList->AddRectFilled(
		ImVec2( WindowPos.x + ImGui::GetCursorPosX( ) - 4, WindowPos.y + ImGui::GetCursorPosY( ) ),
		ImVec2( WindowPos.x + 2, WindowPos.y + ImGui::GetCursorPosY( ) + 40 ),
		IM_COL32( 238, 176, 35, 255 * ImGui::GetStyle( ).Alpha ), 0.f, 0.f );
	}
	BOOL Dawg = ImGui::Button( lol, ImVec2( ImGui::GetWindowWidth( ) - 3, 40 ) );

	ImGui::PopStyleColor( );
	ImGui::PopStyleColor( );
	ImGui::PopStyleColor( );
	ImGui::PopStyleVar( );

	return Dawg;

}