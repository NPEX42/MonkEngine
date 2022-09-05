#include "Engine.h"
#include <iostream>

void GreetUser(std::string name) {
	printf("Hello, %s.\r\n", name.c_str());
}

void error_callback(int error, const char* description)
{
	std::cout << "Error: \n" << description << std::endl;
}

namespace nutmeg {
	void Init() {
		if (!glfwInit()) {
			printf("FATAL: Failed To Initialize GLFW...\r\n");
		}
		else {
			printf("INFO: GLFW Version %d.%d.%d\r\n", 
				GLFW_VERSION_MAJOR, 
				GLFW_VERSION_MINOR, 
				GLFW_VERSION_REVISION
			);

			glfwSetErrorCallback(&error_callback);
		}

		


	}

	void Cleanup() {
		glfwTerminate();
	}
}




double GetCurrentTime() {
	return glfwGetTime();
}
