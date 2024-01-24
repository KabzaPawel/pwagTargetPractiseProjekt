#pragma once
#include "windowMode.h"

class Window
{
public:
	explicit Window(uint32_t width = Config::g_defaultWidth, uint32_t height = Config::g_defaultHeight, WindowMode mode = Config::g_defaultWindowMode, std::string title = Config::g_defaultWindowTitle);
	~Window();

#pragma region Inline functions
	void clearToColor(uint8_t red, uint8_t green, uint8_t blue) const
	{
		constexpr float inverseOfMaxValue = 1.0f / 255.0f;
		glClearColor(red * inverseOfMaxValue, green * inverseOfMaxValue, blue * inverseOfMaxValue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void clearToColorf(float red, float green, float blue) const
	{
		glClearColor(red, green, blue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void swapBuffers() const
	{
		glfwSwapBuffers(_glfwWindowPtr);
	}

	GLFWwindow*& getGLFWWindow()
	{
		return _glfwWindowPtr;
	}

	uint32_t getWidth() const
	{
		return _width;
	}

	uint32_t getHeight() const
	{
		return _height;
	}

	WindowMode getWindowMode() const
	{
		return _mode;
	}

	const std::string& getTitle() const
	{
		return _title;
	}
#pragma endregion

#pragma region Event system
	void attachEventManager(EventManager& manager);

	void windowCloseCallback(bool shouldCloseWindow);
	void windowResizeCallback(int width, int height);
	void keyCallback(int key, int scancode, int action, int mods);
	void mouseButtonCallback(int button, int action, int mods);
	void cursorPositionCallback(double x, double y);
#pragma endregion

private:
	void _initialize();
	void _initOpenGL() const;
	void _createGLFWWindow();
	void _createWindowedWindow();
	void _createFullscreenWindow();
	void _createWindowedFullscreenWindow();

	void _centerWindow() const;
	void _createWindowIcon();

	GLFWwindow* _glfwWindowPtr{};
	EventManager* _eventManager{};

	uint32_t _width;
	uint32_t _height;
	WindowMode _mode;
	std::string _title;
};