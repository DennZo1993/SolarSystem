#include <iostream>
#include <glm/glm.hpp>

#include "Engine.h"
#include "Exception.h"
#include "Shader.h"


int main() {
    try {
        TEngine engine(// Engine options
                       TEngineOptions(),
                       // Window options
                       TWindowOptions().Width(500)
                                       .Height(500)
                                       .Caption("Solar System"));

        // Init core stuff.
        engine.Init();

        // Load and compile shaders.
        TShader shader;
        shader.LoadVertexShader("../../shaders/common.vert");
        shader.LoadFragmentShader("../../shaders/common.frag");
        shader.Build();

        // Main loop.
        while (engine.Running()) {
            engine.BeginMainLoopIteration();

            shader.Use();

            engine.EndMainLoopIteration();
        }
    } catch (const TShaderException& shaderException) {
        std::cout << "Shader exception caught!" << std::endl
                  << shaderException.what() << std::endl;
        return 1;
    } catch (const TEngineException& engineException) {
        std::cout << "Engine exception caught!" << std::endl
                  << engineException.what() << std::endl;

        return 1;
    }

    return 0;
}