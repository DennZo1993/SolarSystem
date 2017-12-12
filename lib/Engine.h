#pragma once

#include <memory>
#include <string>

#include <GL/glew.h>
#include <glfw3.h>


// Window options.
struct TWindowOptions {
    TWindowOptions(size_t wndHeight = 0, size_t wndWidth = 0, const std::string& wndCaption = "")
        : height(wndHeight)
        , width(wndWidth)
        , caption(wndCaption)
    {}

    TWindowOptions& Height(size_t wndHeight) {
        height = wndHeight;
        return *this;
    }

    TWindowOptions& Width(size_t wndWidth) {
        width = wndWidth;
        return *this;
    }

    TWindowOptions& Caption(const std::string& wndCaption) {
        caption = wndCaption;
        return *this;
    }

public:
    size_t height;
    size_t width;
    std::string caption;
};


// Engine options.
struct TEngineOptions {
    TEngineOptions() {}
};


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