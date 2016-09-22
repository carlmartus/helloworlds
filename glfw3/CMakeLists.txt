cmake_minimum_required(VERSION "2.8")

set(CMAKE_C_FLAGS "-Wall -Wextra -std=gnu11 -fvisibility=hidden")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--exclude-libs,ALL")

project(glfwtest C)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	link_libraries(m X11 dl pthread Xrandr Xxf86vm Xinerama Xcursor)
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
endif()

include_directories("glad/include")

link_libraries(glfw3)
add_executable(hello "main.c" "glad/src/glad.c")

