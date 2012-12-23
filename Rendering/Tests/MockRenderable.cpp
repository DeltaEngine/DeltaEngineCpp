#include "MockRenderable.h"

using namespace DeltaEngine::Rendering::Tests;

void MockRenderable::Render()
{
	NumRenders++;
}

int MockRenderable::NumRenders;