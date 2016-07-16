#include "quat.h"

namespace Taurus
{
	namespace math
	{
		float quat::dot(const versor& q, const versor& r)
		{
			return q.x * r.x + q.y * r.y + q.z * r.z + q.w * r.w;
		}

		quat::versor quat::slerp(versor& q, versor& r, float t)
		{
			float dp = dot(q, r);

			if (fabs(dp) >= 1.0f)
			{
				return q;
			}

			float sin_omega = sin(acos(dp));
			versor result;
			if (fabs(sin_omega < 0.001f))
			{
				result.x = (1.0f - t) * q.x + t * r.x;
				result.y = (1.0f - t) * q.y + t * r.y;
				result.z = (1.0f - t) * q.z + t * r.z;
				result.w = (1.0f - t) * q.w + t * r.w;

				return result;
			}

			float omega = acos(dp);
			float a = sin((1.0f - t) * omega) / sin_omega;
			float b = sin(t * omega) / sin_omega;
			
			result.x = q.x * a + r.x * b;
			result.y = q.y * a + r.y * b;
			result.z = q.z * a + r.z * b;
			result.w = q.w * a + r.w * b;

			return result;
		}

		/* create a unit quaternion q from an angle in degrees a, and an axis x,y,z */
		void quat::createVersor(versor& q, float a, float x, float y, float z) {
			float rad = toRadians(a);
			q.x = cosf(rad / 2.0f);
			q.y = sinf(rad / 2.0f) * x;
			q.z = sinf(rad / 2.0f) * y;
			q.w = sinf(rad / 2.0f) * z;
		}

		/* convert a unit quaternion q to a 4x4 matrix m */
		void quat::quatToMat4(mat4& m, versor& q) {
			float w = q.x;
			float x = q.y;
			float y = q.z;
			float z = q.w;
			m.elements[0] = 1.0f - 2.0f * y * y - 2.0f * z * z;
			m.elements[1] = 2.0f * x * y + 2.0f * w * z;
			m.elements[2] = 2.0f * x * z - 2.0f * w * y;
			m.elements[3] = 0.0f;
			m.elements[4] = 2.0f * x * y - 2.0f * w * z;
			m.elements[5] = 1.0f - 2.0f * x * x - 2.0f * z * z;
			m.elements[6] = 2.0f * y * z + 2.0f * w * x;
			m.elements[7] = 0.0f;
			m.elements[8] = 2.0f * x * z + 2.0f * w * y;
			m.elements[9] = 2.0f * y * z - 2.0f * w * x;
			m.elements[10] = 1.0f - 2.0f * x * x - 2.0f * y * y;
			m.elements[11] = 0.0f;
			m.elements[12] = 0.0f;
			m.elements[13] = 0.0f;
			m.elements[14] = 0.0f;
			m.elements[15] = 1.0f;
		}

		/* normalise a quaternion in case it got a bit mangled */
		void quat::normaliseQuat(versor& q) {
			// norm(q) = q / magnitude (q)
			// magnitude (q) = sqrt (w*w + x*x...)
			// only compute sqrt if interior sum != 1.0
			float sum = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
			// NB: floats have min 6 digits of precision
			const float thresh = 0.0001f;
			if (fabs(1.0f - sum) < thresh) {
				return;
			}
			float mag = sqrt(sum);
			
			q.x = q.x / mag;
			q.y = q.y / mag;
			q.z = q.z / mag;
			q.w = q.w / mag;
		}

		/* multiply quaternions to get another one. result=R*S */
		void quat::multQuatQuat(versor& result, versor& r, versor& s) {
			result.x = s.x * r.x - s.y * r.y - s.z * r.z - s.w * r.w;
			result.y = s.x * r.y + s.y * r.x - s.z * r.w + s.w * r.z;
			result.z = s.x * r.z + s.y * r.w + s.z * r.x - s.w * r.y;
			result.w = s.x * r.w - s.y * r.z + s.z * r.y + s.w * r.x;
			// re-normalise in case of mangling
			normaliseQuat(result);
		}
	} 
}