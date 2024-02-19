#include "Rendering/RenderEngine.hpp"

#include <stdexcept>
#include <iostream>

int main()
{
	try
	{
        RenderEngine engine;
        engine.Init();
        engine.Update();
    } catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}