set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)

add_subdirectory(glfw)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
    glfw/include
)