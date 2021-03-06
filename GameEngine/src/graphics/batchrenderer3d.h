#pragma once

#include <cstddef>
#include "renderer2d.h"
#include "buffers\indexbuffer.h"

namespace Taurus
{
	namespace graphics
	{

#define RENDERER_MAX_SPRITES	10000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX 1

		class BatchRenderer3D : public Renderer2D
		{
		private:
			GLuint m_VAO;
			GLuint m_VBO;
			IndexBuffer* m_IBO;
			GLuint m_IndexCount;
			VertexData* m_Buffer;

		public:
			BatchRenderer3D();
			~BatchRenderer3D();

			void begin();
			void submit(const Renderable2D* renderable) override;
			void end();
			void flush() override;

		private:
			void init();
		};
	}
}