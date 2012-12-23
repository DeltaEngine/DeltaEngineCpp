#pragma once
#include "Core/List.h"
#include "Core/Runner.h"
#include "Graphics/Drawing.h"
#include "Renderable.h"
#include "Hypodermic/AutowiredConstructor.h"

namespace DeltaEngine { namespace Rendering
{
	// Allows to render shapes, meshes or images on screen. Needs a graphic device.
	class RenderingLibrary Renderer : public Core::Runner, public virtual Core::IDisposable
	{
	public:
		typedef Hypodermic::AutowiredConstructor<Renderer(Graphics::Drawing*)> AutowiredSignature;
		Renderer(std::shared_ptr<Graphics::Drawing> draw);
		// Calling Dispose in the destructor is not needed, each Renderable disposes itself at the end
		~Renderer() {}
		void Dispose();

		void Run();
		void Add(Renderable* renderable);
		void Remove(Renderable* renderable);
		void DrawRectangle(const Datatypes::Rectangle& rect, const Datatypes::Color& color);
		int GetNumberOfVisibles() const { return visibles.GetCount(); }

	private:
		Core::List<Renderable*> visibles;
		std::shared_ptr<Graphics::Drawing> draw;
	};
}}