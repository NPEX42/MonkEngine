#pragma once
#include "FrameBuffer.h"
#include "imgui.h"

namespace UI {
	class Viewport {
	
	private:
		gl::FrameBuffer m_fbo;

	public:

		

		static Viewport Create(int width, int height);
		Viewport(int width, int height);
		void begin(const char* name);
		void end();

		gl::FrameBuffer* framebuffer();

	};
}
