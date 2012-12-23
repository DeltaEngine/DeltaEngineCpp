#pragma once
#include <windows.h>

namespace DeltaEngine { namespace Graphics { namespace OpenGL { namespace Tests
{
	class OpenGLDeviceTests
	{
	public:
		static void DeviceDispose();
		static void DeviceSizeChanged();
		static void DrawColoredRectangle();
		static void DrawWhiteBox();
	};
}}}}