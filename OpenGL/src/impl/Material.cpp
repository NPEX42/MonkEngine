#include "Material.h"
#include <fstream>
#include <string>
gl::Material::Material(const char* filepath)
	: m_ini(filepath)
{
	using namespace std;
	std::string vertexPath;

	mINI::INIStructure ini;
	m_ini.read(ini);

	m_shader.compileFromFile(ini["Shader"]["vertexPath"].c_str(), ini["Shader"]["fragmentPath"].c_str());
	int unit = 0;
	int max_units;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_units);
	for (pair<string, string> texture : ini["Textures"]) {
		if (unit > max_units) { cout << "Reached Maxium Texture Units." << endl; break; }


	}
}
