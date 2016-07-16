#include "camera.h"

namespace Taurus
{
	namespace graphics
	{
		Camera::Camera(const Window& window, const Shader& shader)
			: m_Window(window), m_Shader(shader)
		{
			init();
		}

		Camera::~Camera()
		{

		}

		void Camera::init()
		{
			m_ProjMatrix = mat4::perspective(fov, aspect, near, far);

			translate = mat4::translation(vec3(-m_CamPos.x, -m_CamPos.y, -m_CamPos.z));

			quat::createVersor(quaternion, -cam_heading, 0.0f, 1.0f, 0.0f);
			quat::quatToMat4(rotate, quaternion);

			m_ViewMatrix = rotate * translate;

			m_Shader.setUniformMat4("vw_matrix", m_ViewMatrix);
			m_Shader.setUniformMat4("pr_matrix", m_ProjMatrix);
		}

		void Camera::update(const vec3 move)
		{
			quat::quatToMat4(rotate, quaternion);

			m_CamPos = m_CamPos + vec3(fwd.x, fwd.y, fwd.z) * -move.z;
			m_CamPos = m_CamPos + vec3(up.x, up.y, up.z) * move.y;
			m_CamPos = m_CamPos + vec3(rgt.x, rgt.y, rgt.z) * move.x;
			mat4 translate = mat4::translation(vec3(m_CamPos));

			// checking for fp errors
			//	printf ("dot fwd . up %f\n", fwd * up);
			//	printf ("dot rgt . up %f\n", rgt * up);
			//	printf ("dot fwd . rgt %f\n", fwd * rgt);

			system("cls");

			printf("\nvw_matrix ");
			for (int i = 0; i < 16; i++) {
				printf("%f, ", m_ViewMatrix.elements[i]);
			}

			m_ViewMatrix = mat4::inverse(rotate) * mat4::inverse(translate);

			printf("\nvw_matrix inverse ");
			for (int i = 0; i < 16; i++) {
				printf("%f, ", m_ViewMatrix.elements[i]);
			}

			m_Shader.setUniformMat4("vw_matrix", m_ViewMatrix);
		}

		void Camera::updateYaw(const float yaw)
		{
			quat::versor qYaw;
			qYaw.x = 0.0f;
			qYaw.y = 0.0f;
			qYaw.z = 0.0f;
			qYaw.w = 0.0f;
			quat::createVersor(qYaw, yaw, up.x, up.y, up.z);
			quat::multQuatQuat(quaternion, qYaw, quaternion);

			quat::quatToMat4(rotate, quaternion);
			fwd = rotate * vec4(0.0, 0.0, -1.0, 0.0);
			rgt = rotate * vec4(1.0, 0.0, 0.0, 0.0);
			up = rotate * vec4(0.0, 1.0, 0.0, 0.0);
		}

		void Camera::updatePitch(const float pitch)
		{
			quat::versor qPitch;
			qPitch.x = 0.0f;
			qPitch.y = 0.0f;
			qPitch.z = 0.0f;
			qPitch.w = 0.0f;
			quat::createVersor(qPitch, pitch, rgt.x, rgt.y, rgt.z);
			quat::multQuatQuat(quaternion, qPitch, quaternion);

			quat::quatToMat4(rotate, quaternion);
			fwd = rotate * vec4(0.0, 0.0, -1.0, 0.0);
			rgt = rotate * vec4(1.0, 0.0, 0.0, 0.0);
			up = rotate * vec4(0.0, 1.0, 0.0, 0.0);
		}

		void Camera::updateRoll(const float roll)
		{
			quat::versor qRoll;
			qRoll.x = 0.0f;
			qRoll.y = 0.0f;
			qRoll.z = 0.0f;
			qRoll.w = 0.0f;
			quat::createVersor(qRoll, roll, up.x, up.y, up.z);
			quat::multQuatQuat(quaternion, qRoll, quaternion);

			quat::quatToMat4(rotate, quaternion);
			fwd = rotate * vec4(0.0, 0.0, -1.0, 0.0);
			rgt = rotate * vec4(1.0, 0.0, 0.0, 0.0);
			up = rotate * vec4(0.0, 1.0, 0.0, 0.0);
		}

		/*
		void Camera::initCameraTransform(const math::vec3& target, const math::vec3& up)
		{
			math::vec3 n = target;
			n.normalize();

			math::vec3 u = up;
			u.normalize();

			u = u.cross(target);

			math::vec3 v = n.cross(u);


		}

		math::mat4& Camera::getProjectionMatrix()
		{
			float range = tan(fov * 0.5f) * near;
			float Sx = (2.0f * near) / (range * aspect + range * aspect);
			float Sy = near / range;
			float Sz = (far + near) / (far - near);
			float Pz = -(2.0f * far * near) / (far - near);

			math::mat4 proj = math::mat4();
			proj.elements[0] = Sx;
			proj.elements[1] = 0.0f;
			proj.elements[2] = 0.0f;
			proj.elements[3] = 0.0f;

			proj.elements[4] = 0.0f;
			proj.elements[5] = Sy;
			proj.elements[6] = 0.0f;
			proj.elements[7] = 0.0f;

			proj.elements[8] = 0.0f;
			proj.elements[9] = 0.0f;
			proj.elements[10] = Sz;
			proj.elements[11] = -1.0f;

			proj.elements[12] = 0.0f;
			proj.elements[13] = 0.0f;
			proj.elements[14] = Pz;
			proj.elements[15] = 0.0f;
		}
		*/
	}
}