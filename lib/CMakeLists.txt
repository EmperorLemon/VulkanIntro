set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)

set(LLGL_ENABLE_EXCEPTIONS ON)
set(LLGL_ENABLE_DEBUG_LAYER ON)
set(LLGL_BUILD_RENDERER_VULKAN ON)
set(LLGL_BUILD_RENDERER_DIRECT3D11 OFF)
set(LLGL_BUILD_RENDERER_NULL OFF)

add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(spdlog)
add_subdirectory(LLGL)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
    glfw/include
    glm
    spdlog/include
    ${Vulkan_INCLUDE_DIRS}
)