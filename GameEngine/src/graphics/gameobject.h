#pragma once
#include "buffers\buffer.h"
#include "buffers\indexbuffer.h"
#include "buffers\vertexarray.h"

#include "shader.h"
#include "../math/math.h"

namespace Taurus
{
	namespace graphics
	{
		struct VertexData3D
		{
			math::vec3 vertex;
			//math::vec4 color;
			unsigned int color;
		};

		class GameObject
		{
		protected:
			math::vec3 m_Position;
			math::vec2 m_Size;
			math::vec4 m_Color;

		public:
			GameObject(math::vec3 position, math::vec2 size, math::vec4 color)
				: m_Position(position), m_Size(size), m_Color(color)
			{
			}

			virtual ~GameObject()
			{
			}

			inline const math::vec3& getPosition() const { return m_Position; }
			inline const math::vec2& getSize() const { return m_Size; }
			inline const math::vec4& getColor() const { return m_Color; }
		};
	}
}
