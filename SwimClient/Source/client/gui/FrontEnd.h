#ifndef FRONTEND_H
#define FRONTEND_H

#include "..\..\helpers\stdafx.h"
#include "..\..\graphics\DirectWrapper.h"

class FrontEnd
{

public:

  FrontEnd(int width, int height);
  ~FrontEnd();

  void Run();

private:

  Graphics::DirectWrapper directWrapper;

  HWND hwnd;
  int width;
  int height;

  ID3D11Device* device = nullptr;
  ID3D11DeviceContext* deviceContext = nullptr;
  IDXGISwapChain* swapChain = nullptr;
  ID3D11RenderTargetView* renderTargetView = nullptr;

  FLOAT clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

  void CreateMainWindow();
  void InitializeImGui();
  void DrawImGui();

};

#endif // FRONTEND_H
