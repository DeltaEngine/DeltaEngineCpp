#pragma once
#include "Graphics\Drawing.h"
#include "Core\List.h"

namespace DeltaEngine { namespace Graphics { namespace Tests 
{
	class MockDrawing : public Drawing
	{
	public:
		MockDrawing(std::shared_ptr<Device> device)
			: Drawing(device), results() {}

		void Dispose() {}

		void SetColor(const Datatypes::Color& color)
		{
			results.Add(color.ToString());
		}

		void DrawRectangle(const Datatypes::Rectangle& rect)
		{
			results.Add(rect.ToString());
		}
		
		Core::String GetResult()
		{
			return results.ToText();
		}

	private:
		Core::List<Core::String> results;
	};
}}}