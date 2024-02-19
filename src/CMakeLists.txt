add_subdirectory(RENDERING)

set(SOURCES

src/main.cpp

${RENDERING}

src/Logger/Logger.hpp
src/Logger/Logger.cpp

src/Window/Window.hpp
src/Window/Window.cpp

PARENT_SCOPE)