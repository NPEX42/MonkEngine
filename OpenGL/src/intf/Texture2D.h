#pragma once
#include "glad/glad.h"
#include "stb_image/stb_image.h"
#include <stdint.h>
#include "Types.h"

namespace gl {

	struct Pixel {
		u8 red;
		u8 green;
		u8 blue;
		u8 alpha;
	};

	const Pixel BLACK = Pixel { 0, 0, 0, 255 };
	const Pixel WHITE = Pixel { 255, 255, 255, 255 };

	class Texture2D {
	private:
		uint32_t m_id = 0;
		int m_width, m_height;
		Texture2D(uint32_t id, int width, int height) : m_id(id), m_width(width), m_height(height) {}

	public:
		Texture2D(int width, int height, cstr_t data);
		Texture2D();
		static Texture2D Load(const cstr_t path);

		int width();
		int height();

		void	setPixel(int x, int y, char r, char g, char b, float a);
		char*	getPixel(int x, int y);

		uint32_t glHandle();



		void destroy();

		~Texture2D() { destroy(); }


		void bind() {
			glBindTexture(GL_TEXTURE_2D, m_id);
		}

		void setTextureUnit(u8 unit) {
			glBindTextureUnit(GL_TEXTURE0 + unit, glHandle());
		}

		void setPixelData(usize width, usize height, void* pixels);
	};
}