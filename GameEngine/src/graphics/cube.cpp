#include "cube.h"

namespace Taurus
{
	namespace graphics
	{
		Cube::Cube(float x, float y, float width, float height, const math::vec4& color)
			: GameObject(math::vec3(x, y, 0), math::vec2(width, height), color)
		{

		}

		Cube::~Cube()
		{

		}
	}
}