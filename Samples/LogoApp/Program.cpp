#include "LogoGame.h"
#include "Platforms/WindowsOpenGL/App.h"

using namespace DeltaEngine::Platforms;
using namespace LogoApp;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	App::Start<LogoGame>();
	return 0;
}