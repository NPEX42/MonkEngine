

#include "Texture2D.h"

gl::Texture2D::Texture2D(int width, int height, char* data)
{
	m_width = width;
	m_height = height;
	glGenTextures(1, &m_id);
	glBindTexture(GL_IMAGE_2D, m_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

}

gl::Texture2D::Texture2D() : m_id(0)
{
	m_width = 1;
	m_height = 1;
	glGenTextures(1, &m_id);
	glBindTexture(GL_IMAGE_2D, m_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	char data[4] = {255, 0, 255, 255};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, &data);

}

gl::Texture2D gl::Texture2D::Load(const cstr_t path)
{
	uint32_t id = 0;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed To Load Texture '%s' (%s)\r\n", path, stbi_failure_reason());
	}
	stbi_image_free(data);

	return Texture2D(id, width, height);
}

int gl::Texture2D::width()
{
	return m_width;
}

int gl::Texture2D::height()
{
	return m_height;
}

void gl::Texture2D::setPixel(int x, int y, char r, char g, char b, float a)
{
}

uint32_t gl::Texture2D::glHandle()
{
	return m_id;
}

void gl::Texture2D::destroy() {
	glDeleteTextures(1, &m_id);
}

void gl::Texture2D::setPixelData(usize width, usize height, void* pixels) {
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}
