#include "GuiWrapper.h"

namespace Graphics
{

	ImVec2 referencePoint = ImVec2(20, 20);

  void GuiWrapper::DrawRectA(int x, int y, int w, int h, int r, ImU32 col, ImDrawCornerFlags flags)
  {
    ImDrawList* DrawList = ImGui::GetBackgroundDrawList();
    x += referencePoint.x;
    y += referencePoint.y;
    DrawList->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), col, r, flags);
  }

  void GuiWrapper::DrawMessageA(ImFont* font, const char* text, int x, int y, ImU32 col)
  {
    ImDrawList* DrawList = ImGui::GetBackgroundDrawList();
    x += referencePoint.x;
    y += referencePoint.y;
    DrawList->AddText(ImVec2(x, y), col, text);
  }

  void GuiWrapper::DrawImageA(ID3D11ShaderResourceView* image, int x, int y, int w, int h, ImU32 col)
  {
    ImDrawList* DrawList = ImGui::GetBackgroundDrawList();
    x += referencePoint.x;
    y += referencePoint.y;
    DrawList->AddImage(image, ImVec2(x, y), ImVec2(x + w, y + h), ImVec2(0, 0), ImVec2(1, 1), col);
  }

}