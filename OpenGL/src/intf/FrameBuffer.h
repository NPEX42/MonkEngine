#pragma once
#include "glad/glad.h"
#include "Types.h"
#include <iostream>


namespace gl {

	class FrameBuffer {
	private:
		u32 m_fbo_id;
		u32 m_tex_id;
		u32 m_rbo_id;

		FrameBuffer(u32 fbo, u32 texture, u32 rbo) : m_fbo_id(fbo), m_tex_id(texture), m_rbo_id(rbo) {}
	public:
		static FrameBuffer Create(usize width, usize height);

		u32 fbo_id() { return m_fbo_id; }
		u32 color_id() { return m_tex_id; }
		u32 rbo_id() { return m_rbo_id; }

		void bind() {
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_id);
		}

		void unbind() {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	};
}