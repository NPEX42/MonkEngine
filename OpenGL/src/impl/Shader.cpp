#include "Shader.h"
#include "Shader.h"
#include "FileLoader.h"

bool gl::Shader::compileFromFile(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexSource = loadFileToString(vertexPath);
	std::string fragmentSource = loadFileToString(fragmentPath);;



	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


	std::cout << "==== Vertex Source ====" << std::endl;
	std::cout << vertexSource << std::endl;

	std::cout << "==== Fragment Source ====" << std::endl;
	std::cout << fragmentSource << std::endl;

	GLchar const* vertex_Source = vertexSource.c_str();
	GLint const vertex_Size = vertexSource.size();
	glShaderSource(vertexShader, 1, &vertex_Source, &vertex_Size);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[NM_GL_MAX_SHADER_LOG_SIZE];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, NM_GL_MAX_SHADER_LOG_SIZE, NULL, infoLog);
		std::cerr << "[ERROR] Vertex Shader Compilation Failed:" << std::endl << infoLog << std::endl;
	}
	GLchar const* fragment_Source = fragmentSource.c_str();
	GLint const fragment_Size = fragmentSource.size();
	glShaderSource(fragmentShader, 1, &fragment_Source, &fragment_Size);


	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, NM_GL_MAX_SHADER_LOG_SIZE, NULL, infoLog);
		std::cerr << "[ERROR] Fragment Shader Compilation Failed:" << std::endl << infoLog << std::endl;
	}

	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);


	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(m_shaderProgram, NM_GL_MAX_SHADER_LOG_SIZE, NULL, infoLog);
		std::cerr << "[ERROR] Program Linking Failed:" << std::endl << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	if (success) {
		std::cout << "Created Shader Successfully..." << std::endl;
	}
	else {
		std::cerr << "Failed To Create Shader, See Previous Log For Details" << std::endl;
	}

	m_isValid = (success > 0);

	return m_isValid;
}

void gl::Shader::bind() {
	glBindProgramPipeline(m_shaderProgram);
	glUseProgram(m_shaderProgram);
}

void gl::Shader::unbind() {
	glBindProgramPipeline(0);
	glUseProgram(0);
}

void gl::Shader::setFloat1(const char* name, float x)
{
	glUniform1f(findUniform(name), x);
}

void gl::Shader::setFloat2(const char* name, float x, float y)
{
	glUniform2f(findUniform(name), x, y);
}


void gl::Shader::setFloat3(const char* name, float x, float y, float z)
{
	glUniform3f(findUniform(name), x, y, z);
}

void gl::Shader::setFloat4(const char* name, float x, float y, float z, float w)
{
	glUniform4f(findUniform(name), x, y, z, w);
}

gl::Shader::Shader() : 
	m_shaderProgram(glCreateProgram()), m_isValid(false), m_uniforms(std::unordered_map<const char*, i32>())
{

}

gl::Shader::Shader(std::string const& vertexSource, std::string const& fragmentSource) : 
	m_shaderProgram(0), m_isValid(false), m_uniforms(std::unordered_map<const char*, i32>())
{

	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	m_shaderProgram = glCreateProgram();


	std::cout << "==== Vertex Source ====" << std::endl;
	std::cout << vertexSource << std::endl;

	std::cout << "==== Fragment Source ====" << std::endl;
	std::cout << fragmentSource << std::endl;

	GLchar const* vertex_Source = vertexSource.c_str();
	GLint const vertex_Size = vertexSource.size();
	glShaderSource(vertexShader, 1, &vertex_Source, &vertex_Size);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[NM_GL_MAX_SHADER_LOG_SIZE];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, NM_GL_MAX_SHADER_LOG_SIZE, NULL, infoLog);
		std::cerr << "[ERROR] Vertex Shader Compilation Failed:" << std::endl << infoLog << std::endl;
	}
	GLchar const* fragment_Source = fragmentSource.c_str();
	GLint const fragment_Size = fragmentSource.size();
	glShaderSource(fragmentShader, 1, &fragment_Source, &fragment_Size);


	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, NM_GL_MAX_SHADER_LOG_SIZE, NULL, infoLog);
		std::cerr << "[ERROR] Fragment Shader Compilation Failed:" << std::endl << infoLog << std::endl;
	}

	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);


	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(m_shaderProgram, NM_GL_MAX_SHADER_LOG_SIZE, NULL, infoLog);
		std::cerr << "[ERROR] Program Linking Failed:" << std::endl << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	if (success) {
		std::cout << "Created Shader Successfully..." << std::endl;
	}
	else {
		std::cerr << "Failed To Create Shader, See Previous Log For Details" << std::endl;
	}

	m_isValid = (success > 0);

}


void gl::Shader::setTexture(const char* name, gl::Texture2D* texture, u8 unit) {
	bind();
	texture->setTextureUnit(unit);
	glUniform1i(findUniform(name), unit);

	texture->bind();
}