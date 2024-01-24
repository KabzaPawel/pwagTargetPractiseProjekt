#include "pch.h"
#include "application.h"

int main()
{
	Debug::LogSuccess("Starting Target Practise - PWAG project");

	if (glfwInit() == GLFW_TRUE)
	{
		Application app;
		app.run();

		glfwTerminate();
	}
}