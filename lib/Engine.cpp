#include "Engine.h"
#include "Exception.h"


TEngine::TEngine(const TEngineOptions& engineOpts, const TWindowOptions& windowOpts)
	: EngineOptions(engineOpts)
	, WindowOptions(windowOpts)
{
}


TEngine::~TEngine() {
	Destroy();
}


void TEngine::Destroy() noexcept {
	glfwTerminate();
}


void TEngine::Init() {
	glfwInit();

	InitWindow();
}


void TEngine::InitWindow() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	Window.reset(glfwCreateWindow(WindowOptions.width,
								  WindowOptions.height,
								  WindowOptions.caption.c_str(),
								  nullptr,
								  nullptr));

	if (!Window)
		throw TEngineException("Failed to initialize window");

	glfwMakeContextCurrent(Window.get());

	glewExperimental = GL_TRUE;
	auto glewInitResult = glewInit();
	if (glewInitResult)
		throw TEngineException("Failed to initialize GLEW, code: " + std::to_string(glewInitResult));
  
	glViewport(0, 0, WindowOptions.width, WindowOptions.height);
}


// Main loop functions


bool TEngine::Running() const {
	return true;
}


void TEngine::BeginMainLoopIteration() {
	glfwPollEvents();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


void TEngine::EndMainLoopIteration() {
	glfwSwapBuffers(Window.get());
}