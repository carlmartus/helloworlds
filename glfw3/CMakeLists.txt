cmake_minimum_required(VERSION "2.8")

project(glfwtest C)
link_libraries(glfw3 m X11 dl pthread Xrandr Xxf86vm Xinerama Xcursor)
include_directories("glad/include")

add_executable(hello "main.c" "glad/src/glad.c")

