#include "VulkanAPI/VulkanApp.hpp"

#include <stdexcept>
#include <iostream>

int main()
{
	try
	{
		VulkanApp app;
		app.Run();
    } catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}