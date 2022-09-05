#pragma once

#include "OpenGL.h"
#include "maths/Vertex.h"
#include <array>
#define MAX_VERTICES 16384

namespace monk {

	namespace gfx {
		using namespace maths;

		class Renderer2D {
		private:
			static Vertex m_vertices[MAX_VERTICES];
			static TexCoords m_tex_coords[MAX_VERTICES];
			static Color m_vertex_colors[MAX_VERTICES];
			static u32 m_length;
			static gl::VertexBuffer m_vertices_buffer;
			static gl::VertexBuffer m_texcoord_buffer;
			static gl::VertexBuffer m_color_buffer;

		public:
			static void addMesh(Vertex* vertices, TexCoords* uvs, Color* colors, size_t length);
			static void flush();
		};
	}

}
