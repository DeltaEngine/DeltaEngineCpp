#include "CppUnitTest.h"
#include "Core/Tests/CppUnitTestCoreSupport.h"
#include "DeltaEngine.Platforms.Windows.h"
#include <windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DeltaEngine::Core;
using namespace DeltaEngine::Datatypes;

namespace DeltaEngine { namespace Platforms { namespace Windows { namespace Tests
{
	int WINAPI WinMain(HINSTANCE appHandle, HINSTANCE previousAppHandle, LPSTR cmdArgumentsLine,
		int appWindowShowState)
	{
		return 0;
	}

	LRESULT CALLBACK WndProc(HWND	windowHandle, UINT windowMessage, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProc(windowHandle, windowMessage, wParam, lParam);
	}

	TEST_CLASS(Win32WindowTests)
	{
	public:
		Win32WindowTests()
			: window(Win32Window(BuildWindowData("Win32WindowTests"))) {}

		~Win32WindowTests()
		{
			window.Close();
		}

		TEST_METHOD_CLEANUP(Win32Window_Cleanup)
		{
			// When running all tests at once one test usually fails. This sleep prevents the failure.
			Sleep(10);
		}

		BEGIN_INTEGRATION_TEST(Win32Window_Title)
		{
			window.SetTitle("Test");
			Assert::IsTrue(window.GetTitle() == "Test");
		}
		END_INTEGRATION_TEST

		BEGIN_INTEGRATION_TEST(Win32Window_DefaultSize)
		{
			auto size = Size(800, 600);
			Assert::IsTrue(size == window.GetTotalSize());
			Assert::IsTrue(size > window.GetViewportSize());
		}
		END_INTEGRATION_TEST

		BEGIN_INTEGRATION_TEST(Win32Window_SetSize)
		{
			auto size = Size(500, 450);
			window.SetTotalSize(size);
			Assert::IsTrue(size == window.GetTotalSize());
			Assert::IsTrue(size > window.GetViewportSize());
		}
		END_INTEGRATION_TEST

		BEGIN_INTEGRATION_TEST(Win32Window_IsVisible)
		{
			Assert::IsTrue(window.GetIsVisible());
		}
		END_INTEGRATION_TEST

		BEGIN_INTEGRATION_TEST(Win32Window_IsHandleSet)
		{
			Assert::AreNotEqual((int)window.GetHandle(), 0);
		}
		END_INTEGRATION_TEST

		BEGIN_INTEGRATION_TEST(Win32Window_SetBackgroundColor)
		{
			window.SetBackgroundColor(Color::White);
			Assert::IsTrue(Color::White == window.GetBackgroundColor());
		}
		END_INTEGRATION_TEST

		BEGIN_INTEGRATION_TEST(Win32Window_SetIsFullScreen)
		{
			window.SetIsFullscreen(true);
			Assert::IsTrue(window.GetIsFullscreen());
		}
		END_INTEGRATION_TEST

		BEGIN_INTEGRATION_TEST(Win32Window_IsClosing)
		{
			Assert::IsFalse(window.GetIsClosing());
			window.Close();
			Assert::IsTrue(window.GetIsClosing());
		}
		END_INTEGRATION_TEST

	private:
		Win32Window window;

		WNDCLASSEX BuildWindowData(char* name)
		{
			WNDCLASSEX data = {0};
			data.cbSize = sizeof(data);
			data.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			data.lpfnWndProc = (WNDPROC)WndProc;
			data.cbClsExtra = NULL;
			data.cbWndExtra = NULL;
			data.hInstance = (HINSTANCE)GetModuleHandle(NULL);
			data.hIcon = LoadIcon(NULL, IDI_WINLOGO);
			data.hCursor = LoadCursor(NULL, IDC_ARROW);
			data.hbrBackground = NULL;
			data.lpszMenuName = NULL;
			data.lpszClassName = String(name).ToWString().c_str();
			return data;
		}
	};
}}}}