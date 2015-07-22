#include <stdio.h>

#define STRING(msg) #msg

int main(int argc, char **argv) {
	const char *shaderSrc = STRING(
		attribute vec3 in_loc;

		void main() {
			gl_Position = vec(in_loc, 1);
		}
	);

	printf("%s", shaderSrc);
	return 0;
}

