#include "Window.hpp"

#include <iostream>
#include <GLFW/glfw3.h>

void Test()
{
	glfwInit();
	std::cout << "Test Complete!" << std::endl;
	glfwTerminate();
}