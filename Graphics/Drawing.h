#pragma once
#include "Datatypes/Color.h"
#include "Datatypes/Rectangle.h"
#include "Device.h"
#include <memory>

namespace DeltaEngine { namespace Graphics
{
	// Allows to draw shapes or images on screen.
	class Drawing : public virtual Core::IDisposable
	{
	public:
		virtual void SetColor(const Datatypes::Color& color) = 0;
		virtual void DrawRectangle(const Datatypes::Rectangle& rect) = 0;
		const std::shared_ptr<Device> GetGraphicsDevice() const { return device; }

	protected:
		Drawing(std::shared_ptr<Device> device)
			: device(device) {}

	private:
		const std::shared_ptr<Device> device;
	};
}}