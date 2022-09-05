#pragma once

#include <stdint.h>
#include <iostream>
#include "glad/glad.h"
#include "Buffer.h"
#include "Shader.h"
#include "FrameBuffer.h"


void WireframeRender() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void FilledRender() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

namespace gl {
	int MaxVertexAttributes() {
		int max_units;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_units);

		return max_units;
	}

	int GetInt(uint32_t param) {
		int value;
		glGetIntegerv(param, &value);
		return value;
	}

	bool GetBool(uint32_t param) {
		GLboolean value;
		glGetBooleanv(param, &value);
		return value;
	}
}