#include "Graphics/OpenGL/OpenGLDrawing.h"
#include "Datatypes/Size.h"
#include "Platforms/WindowsOpenGL/App.h"
#include "Core/Exception.h"

namespace DeltaEngine { namespace WindowsOpenGL { namespace VisualTests
{
	class OpenGLDeviceTests
	{
	public:
		static void Show200x100PixelWindowWithDevice()
		{
			Platforms::App::Start<Graphics::Device, Platforms::Window>(
				[](std::shared_ptr<Graphics::Device> device, std::shared_ptr<Platforms::Window> window)
			{ 
				window->SetTotalSize(Datatypes::Size(200, 100));
				if (Datatypes::Point(0, 0.25f) != device->GetScreen()->GetTopLeft() ||
					Datatypes::Point(1, 0.75f) != device->GetScreen()->GetBottomRight())
					throw Core::Exception("ScreenSpace is not (0, 0.25, 1, 0.5) as expected from 200x100px");
			});
		}

		static void DrawRedRectangle()
		{
			std::shared_ptr<Graphics::Drawing> rememberDrawing;
			Platforms::App::Start<Graphics::Drawing>(
				[&](std::shared_ptr<Graphics::Drawing> drawing) { rememberDrawing = drawing; },
				[&]()
				{
					rememberDrawing->SetColor(Datatypes::Color::Red);
					rememberDrawing->DrawRectangle(Datatypes::Rectangle::One);
				});
		}
	};
}}}