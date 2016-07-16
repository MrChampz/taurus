#include "sprite.h"

namespace Taurus
{
	namespace graphics
	{
		Sprite::Sprite(float x, float y, float z, float width, float height, const math::vec4& color)
			: Renderable2D(math::vec3(x, y, z), math::vec2(width, height), color)
		{

		}

		Sprite::~Sprite()
		{

		}
	}
}