#pragma once

#include <math.h>
#include "math.h"

namespace Taurus
{
	namespace math
	{
		struct quat
		{
			struct versor
			{
				double x, y, z, w;
			};

			static float dot(const versor& q, const versor& r);
			versor slerp(versor& q, versor& r, float t);

			static void createVersor(versor& q, float a, float x, float y, float z);
			static void quatToMat4(mat4& m, versor& q);
			static void normaliseQuat(versor& q);
			static void multQuatQuat(versor& result, versor& r, versor& s);

		};
	}
}