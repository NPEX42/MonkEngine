#pragma once
#include "Shader.h"
#include "ini.h"
namespace gl {
	class Material {
	private:
		Shader m_shader;
		mINI::INIFile m_ini;

	public:
		Material(const char* filepath);


	};
}