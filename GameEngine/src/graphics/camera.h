#pragma once

#include "window.h"
#include "shader.h"
#include "../math/math.h"

namespace Taurus
{
	namespace graphics
	{
		using namespace Taurus;
		using namespace math;

		class Camera
		{
		private:
			Window m_Window;
			Shader m_Shader; 

			mat4 m_ViewMatrix;
			mat4 m_ProjMatrix;
			vec3 m_CamPos = vec3(0.0f, 0.0f, 5.0f);

			mat4 translate;
			mat4 rotate;
			quat::versor quaternion;

			float near = -1.0f;
			float far = 1.0f;
			float fov = 67.0f;
			float aspect = (float)m_Window.getWidth() / (float)m_Window.getHeight();

			float cam_speed = 0.1f;
			float cam_heading_speed = 0.100f;
			float cam_heading = 0.0f;

			vec4 fwd = vec4(0.0f, 0.0f, -1.0f, 0.0f);
			vec4 rgt = vec4(1.0f, 0.0f, 0.0f, 0.0f);
			vec4 up = vec4(0.0f, 1.0f, 0.0f, 0.0f);

		public:
			Camera(const Window& window, const Shader& shader);
			~Camera();

			void update(const vec3 move);
			void updateYaw(const float yaw);
			void updatePitch(const float pitch);
			void updateRoll(const float roll);

			inline float getCamSpeed() const { return cam_speed; }
			inline float getCamHeadingSpeed() const { return cam_heading_speed; }

		private:
			void init();
		};
	}
}