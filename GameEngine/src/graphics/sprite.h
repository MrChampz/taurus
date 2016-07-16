#pragma once

#include "renderable2d.h"

namespace Taurus
{
	namespace graphics
	{
		class Sprite : public Renderable2D
		{
		public:
			Sprite(float x, float y, float z, float width, float height, const math::vec4& color);
			~Sprite();

		};
	}
}