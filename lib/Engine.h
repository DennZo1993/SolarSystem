#pragma once

#include <memory>
#include <string>

#include <GL/glew.h>
#include <glfw3.h>

#include "EngineOptions.h"


// Engine class.

class TEngine {
public:
    TEngine(const TEngineOptions& engineOpts, const TWindowOptions& windowOpts);
    ~TEngine();

public:
    void Init();

public:
    bool Running() const;
    void BeginMainLoopIteration();
    void EndMainLoopIteration();

protected:
    void InitWindow();

    void Destroy() noexcept;

private:
    // Options used to create the Engine.
    TEngineOptions EngineOptions;
    TWindowOptions WindowOptions;

    // Main window.
    struct TWindowDestroyer {
        void operator()(GLFWwindow* window) {
            glfwDestroyWindow(window);
        }
    };
    using TWindowPtr = std::unique_ptr<GLFWwindow, TWindowDestroyer>;

    TWindowPtr Window;
};