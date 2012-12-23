#include "Graphics/OpenGL/OpenGLDrawing.h"
#include "Datatypes/Size.h"
#include "Platforms/HypodermicResolver.h"
#include "Platforms/Windows/Win32Window.h"
#include "GL/glew.h"
#include <windows.h>
#include "Platforms/WindowsOpenGL/App.h"
#include "OpenGLDeviceTests.h"

using namespace DeltaEngine::Datatypes;
using namespace DeltaEngine::Platforms;
using namespace DeltaEngine::Platforms::Windows;
using namespace DeltaEngine::Graphics;
using namespace DeltaEngine::Graphics::OpenGL;
using namespace DeltaEngine::Graphics::OpenGL::Tests;

void OpenGLDeviceTests::DeviceDispose()
{
	App::Start<Device>([](std::shared_ptr<Device> device)
	{ 
		device->Dispose();
	});
}

// Example integration test! Will create an OpenGL window and check the size, then close.
void OpenGLDeviceTests::DeviceSizeChanged()
{
	App::Start<Device, Window>([](std::shared_ptr<Device> device, std::shared_ptr<Window> window) 
	{ 
		window->SetTotalSize(Size(100, 100));
		window->Close();
	});
}

// Visual test, which is called manually in Program.cpp!
void OpenGLDeviceTests::DrawColoredRectangle()
{
	std::shared_ptr<Drawing> rememberDrawing;
	App::Start<Drawing>([&](std::shared_ptr<Drawing> drawing) { rememberDrawing = drawing; }, [&]()
	{
		rememberDrawing->SetColor(Color::Red);
		rememberDrawing->DrawRectangle(Rectangle::One);
	});
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_CLOSE)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void OpenGLDeviceTests::DrawWhiteBox()
{
	WNDCLASSEX data = {0};
	data.cbSize = sizeof(data);
	data.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	data.lpfnWndProc = (WNDPROC)WndProc;
	data.cbClsExtra = NULL;
	data.cbWndExtra = NULL;
	data.hInstance = (HINSTANCE)32;
	data.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	data.hCursor = LoadCursor(NULL, IDC_ARROW);
	data.hbrBackground = NULL;
	data.lpszMenuName = NULL;
	data.lpszClassName = L"OpenGL";

	Win32Window* window = new Win32Window(data);
	OpenGLDevice* openGLDevice = new OpenGLDevice(std::shared_ptr<Window>(window));
	OpenGLDrawing* openGLDrawing = new OpenGLDrawing(std::shared_ptr<OpenGLDevice>(openGLDevice));

	openGLDevice->Run();

	openGLDrawing->SetColor(Color::White);
	openGLDrawing->DrawRectangle(DeltaEngine::Datatypes::Rectangle(0.0f, 0.0f, 0.5f, 0.5f));

	openGLDevice->Present();
}