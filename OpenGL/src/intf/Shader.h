#pragma once
#include "glad/glad.h"
#include <stdint.h>
#include <iostream>
#include <unordered_map>
#include "Texture2D.h"

#define NM_GL_MAX_SHADER_LOG_SIZE 1024

namespace gl {


	class Shader {
	private:
		uint32_t m_shaderProgram;

		std::unordered_map<const char*, i32> m_uniforms;


		bool m_isValid;


		i32 findUniform(const char* name) {
			if (m_uniforms.find(name) != m_uniforms.end()) {
				return m_uniforms[name];
			}
			else {
				int loc = glGetUniformLocation(m_shaderProgram, name);

				m_uniforms[name] = loc;

				if (loc < 0) {
					std::cerr << "Failed To Locate Uniform '" << name << "'..." << std::endl;

					return -1;
				}

				
			}
		}

	public:
		Shader();
		Shader(std::string const &vertexSource, std::string const& fragmentSource);


		bool compileFromFile(const char* vertexPath, const char* fragmentPath);

		void bind();
		void unbind();

		bool isValid() {
			return m_isValid;
		}

		void setFloat1(const char* name, float x);
		void setFloat2(const char* name, float x, float y);
		void setFloat3(const char* name, float x, float y, float z);
		void setFloat4(const char* name, float x, float y, float z, float w);

		void setTexture(const char* name, gl::Texture2D* texture, u8 unit);



		i32 operator [](const char* name) {
			return findUniform(name);
		}
	};
}