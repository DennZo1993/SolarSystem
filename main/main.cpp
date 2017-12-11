#include <iostream>
#include <glm/glm.hpp>

#include "Engine.h"


int main() {
	TEngine engine(// Engine options
				   TEngineOptions(),
				   // Window options
				   TWindowOptions().Width(500)
								   .Height(500)
								   .Caption("Solar System"));

	// Init stuff.
	engine.Init();

	// Main loop.
	while (engine.Running()) {
		engine.BeginMainLoopIteration();

		engine.EndMainLoopIteration();
	}

	return 0;
}