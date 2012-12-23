#include "LogoGame.h"

using namespace LogoApp;
using namespace DeltaEngine::Core;
using namespace DeltaEngine::Datatypes;
using namespace DeltaEngine::Platforms;
using namespace DeltaEngine::Rendering;

LogoGame::LogoGame(std::shared_ptr<Renderer> render, std::shared_ptr<Time> time,
	std::shared_ptr<Window> window)
	: box(std::make_shared<ColoredRectangle>(render, Point::Half, Size::Half, Color::Red)),
	time(time.get()),
	window(window.get())
{
	window->SetBackgroundColor(Color::CornflowerBlue);
	moveDirection = Point::UnitX;
}

void LogoGame::Run()
{
	box->Rect.SetCenter(box->Rect.GetCenter() + moveDirection * time->GetCurrentDelta());
	if (box->Rect.GetLeft() <= 0.0f)
		SetMoveDirectionAndChangeColor(Point::UnitX);
	else if (box->Rect.GetLeft() > 0.5f)
		SetMoveDirectionAndChangeColor(-Point::UnitX);
}

void LogoGame::SetMoveDirectionAndChangeColor(const Point& newDirection)
{
	window->SetTitle(String::Format("LogoGame Fps: %i", time->GetFps()));
	moveDirection = newDirection;
	box->Color = Color::GetRandomBrightColor();
}