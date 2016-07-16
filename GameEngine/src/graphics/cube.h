#pragma once

#include "gameobject.h"

namespace Taurus
{
	namespace graphics
	{
		class Cube : public GameObject
		{
		public:
			Cube(float x, float y, float width, float height, const math::vec4& color);
			~Cube();

		};
	}
}