#ifndef GUI_WRAPPER_H
#define GUI_WRAPPER_H

#include "../helpers/stdafx.h"

namespace Graphics
{

	class GuiWrapper
	{

	public:

		static void DrawRectA(int x, int y, int w, int h, int r, ImU32 col, ImDrawCornerFlags flags = 0);

		static void DrawMessageA(ImFont* font, const char* text, int x, int y, ImU32 col = IM_COL32_WHITE);

		static void DrawImageA(ID3D11ShaderResourceView* image, int x, int y, int w, int h, ImU32 col = IM_COL32_WHITE);

	};

} // Graphics

#endif // GUI_WRAPPER_H