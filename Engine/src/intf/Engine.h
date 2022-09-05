#pragma once
#include <stdint.h>
#include <stdio.h>
#include <string>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "stb_image/stb_image.h"

// Common Engine Includes
#include "Logger.h"



void GreetUser(std::string name);

double GetCurrentTime();


namespace nutmeg {
	void Init();
	void Cleanup();
}

