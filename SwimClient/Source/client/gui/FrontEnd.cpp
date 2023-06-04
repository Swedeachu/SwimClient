#include "FrontEnd.h"
#include "..\..\directX\DirectWrapper.h"

FrontEnd::FrontEnd(int width, int height) : width(width), height(height)
{
	CreateMainWindow();
	directWrapper.InitializeDirectX(hwnd, width, height);
	InitializeImGui();
}

FrontEnd::~FrontEnd()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void FrontEnd::Run()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		directWrapper.ClearRenderTarget();
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		DrawImGui();

		ImGui::Render();
		directWrapper.GetDeviceContext()->OMSetRenderTargets(1, directWrapper.GetRenderTargetViewAddress(), nullptr);
		directWrapper.GetDeviceContext()->ClearRenderTargetView(*directWrapper.GetRenderTargetViewAddress(), clearColor);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		directWrapper.Present();
	}
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

			// Handle other messages as needed

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void FrontEnd::CreateMainWindow()
{
	const wchar_t* className = L"win";

	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = GetModuleHandle(nullptr);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = className;

	RegisterClassEx(&wcex);

	hwnd = CreateWindowEx(
		0,
		className,
		L"Swim Client",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		nullptr,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);

	if (hwnd == nullptr)
	{
		throw std::runtime_error("Failed to create the main window.");
	}
}

void FrontEnd::InitializeImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(directWrapper.GetDevice(), directWrapper.GetDeviceContext());

	ImGui::StyleColorsDark();
}

void FrontEnd::DrawImGui()
{
	ImGui::Begin("Hello, ImGui!");

	ImGui::Text("Hello, ImGui!");
	ImGui::Text("This is a basic window.");

	ImGui::End();
}