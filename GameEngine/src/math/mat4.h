#pragma once

#include "math_func.h"
#include "vec3.h"
#include "vec4.h"

namespace Taurus
{
	namespace math
	{
		struct mat4
		{
			union 
			{
				// 4 * 4 = 16
				float elements[16];
				vec4 columms[4];
			};

			mat4();
			mat4(float diagonal);

			inline vec4 getColumm(int index)
			{
				index *= 4;
				return vec4(elements[index], elements[index + 1], elements[index + 2], elements[index + 3]);
			}

			static mat4 identity();

			mat4& multiply(const mat4& other);
			friend vec4 operator*(mat4 left, const vec4& right);
			friend mat4 operator*(mat4 left, const mat4& right);
			mat4& operator*=(const mat4& other);

			static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
			static mat4 perspective(float fov, float aspectRatio, float near, float far);

			static mat4 translation(const vec3& translation);
			static mat4 rotation(float angle, const vec3& axis);
			static mat4 scale(const vec3& scale);

			static float determinant(const mat4& mm);
			static mat4 inverse(const mat4& mm);
		};
	}
}
