#include "AppTests.h"
#include "OpenGLDeviceTests.h"

using namespace DeltaEngine::WindowsOpenGL::VisualTests;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//AppTests::ShowWindowAndStartRunner();
	AppTests::ShowColoredRectangle();
	//OpenGLDeviceTests::Show200x100PixelWindowWithDevice();
	//OpenGLDeviceTests::DrawRedRectangle();
	return 0;
}