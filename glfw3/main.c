#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {

	if (!glfwInit()) {
		return 1;
	}

	GLFWwindow *win = glfwCreateWindow(640, 480, "GLFW test", NULL, NULL);
	if (!win) {
		return 1;
	}

	// Activate OpenGL context
	glfwMakeContextCurrent(win);

	// Load glad
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

	while (!glfwWindowShouldClose(win)) {
		glfwPollEvents();
	}

	glfwDestroyWindow(win);
	glfwTerminate();

	return 0;
}

