#include "vec3.h"

namespace Taurus
{
	namespace math
	{
		vec3::vec3() 
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		vec3::vec3(const float& x, const float& y, const float& z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		vec3& vec3::add(const vec3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}

		vec3& vec3::subtract(const vec3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}

		vec3& vec3::multiply(const vec3& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;

			return *this;
		}

		vec3& vec3::divide(const vec3& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;

			return *this;
		}

		vec3& vec3::cross(const vec3& other)
		{
			vec3 r;

			r.x = y * other.z - z * other.y;
			r.y = z * other.x - x * other.z;
			r.z = x * other.y - y * other.x;

			return r;
		}

		vec3& vec3::normalize()
		{
			const float length = sqrtf(x * x + y * y + z * z);

			x /= length;
			y /= length;
			z /= length;

			return *this;
		}

		vec3 operator+(vec3 left, const vec3& right)
		{
			return left.add(right);
		}

		vec3 operator-(vec3 left, const vec3& right)
		{
			return left.subtract(right);
		}

		vec3 operator*(vec3 left, const float& right)
		{
			vec3 vc;
			vc.x = left.x * right;
			vc.y = left.y * right;
			vc.z = left.z * right;
			return vc;
		}

		vec3 operator*(vec3 left, const vec3& right)
		{
			return left.multiply(right);
		}

		vec3 operator/(vec3 left, const vec3& right)
		{
			return left.divide(right);
		}

		vec3& vec3::operator+=(const vec3& other)
		{
			return add(other);
		}

		vec3& vec3::operator-=(const vec3& other)
		{
			return subtract(other);
		}

		vec3& vec3::operator*=(const vec3& other)
		{
			return multiply(other);
		}

		vec3& vec3::operator/=(const vec3& other)
		{
			return divide(other);
		}

		bool vec3::operator==(const vec3& other)
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool vec3::operator!=(const vec3& other)
		{
			return !(*this == other);
		}

		std::ostream& operator<<(std::ostream& stream, const vec3& vector)
		{
			return stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")" << std::endl;
		}
	}
}