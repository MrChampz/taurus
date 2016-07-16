#include "graphics\window.h"
#include "graphics\camera.h"
#include "graphics\shader.h"
#include "math\math.h"
#include "utils\fileutils.h"

#include "graphics\buffers\buffer.h"
#include "graphics\buffers\indexbuffer.h"
#include "graphics\buffers\vertexarray.h"

#include "graphics\simple2drenderer.h"
#include "graphics\batchrenderer2D.h"

#include "graphics\sprite.h"
#include "graphics\static_sprite.h"

#include "utils\timer.h"

#include <time.h>

#define BATCH_RENDERER 1

int main()
{
	using namespace Taurus;
	using namespace graphics;
	using namespace math;
	using namespace utils;

	Window window("Taurus Engine", 960, 540);
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	Camera camera(window, shader);

	//mat4 proj = mat4::perspective(67.0f, 960 / 540, -1.0f, 1.0f);
	//shader.setUniformMat4("pr_matrix", proj);

	std::vector<Renderable2D*> sprites;

	srand(time(NULL));

	for (float y = 0; y < 9.0f; y += 0.2)
	{
		for (float x = 0; x < 16.0f; x += 0.2)
		{
			sprites.push_back(new 
#if BATCH_RENDERER
			Sprite
#else
			StaticSprite
#endif
			(x, y, 0.0, 0.16, 0.16, math::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)
#if !BATCH_RENDERER
			, shader
#endif
			));
		}
	}

#if BATCH_RENDERER
	BatchRenderer2D renderer;
#else
	Simple2DRenderer renderer;
#endif

	shader.setUniform2f("light_pos", vec2(0.0f, 0.0f));
	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	while (!window.closed())
	{
		window.clear();
#if BATCH_RENDERER
		renderer.begin();
#endif
		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.submit(sprites[i]);
		}
#if BATCH_RENDERER
		renderer.end();
#endif

		renderer.flush();
		window.update();
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			//printf("%d fps\n", frames);
			frames = 0;
		}

		bool cam_moved = false;
		vec3 move(0.0, 0.0, 0.0);
		float camYaw = 0.0f;
		float camPitch = 0.0f;
		float camRoll = 0.0f;

		if (window.isKeyPressed(GLFW_KEY_A))
		{
			move.x -= camera.getCamSpeed() * time.elapsed();
			cam_moved = true;
		}
		
		if (window.isKeyPressed(GLFW_KEY_D))
		{
			move.x += camera.getCamSpeed() * time.elapsed();
			cam_moved = true;
		}
		
		if (window.isKeyPressed(GLFW_KEY_PAGE_UP))
		{
			move.y += camera.getCamSpeed() * time.elapsed();
			cam_moved = true;
		}

		if (window.isKeyPressed(GLFW_KEY_PAGE_DOWN))
		{
			move.y -= camera.getCamSpeed() * time.elapsed();
			cam_moved = true;
		}

		if (window.isKeyPressed(GLFW_KEY_W))
		{
			move.z -= camera.getCamSpeed() * time.elapsed();
			cam_moved = true;
		}

		if (window.isKeyPressed(GLFW_KEY_S))
		{
			move.z += camera.getCamSpeed() * time.elapsed();
			cam_moved = true;
		}

		if (window.isKeyPressed(GLFW_KEY_LEFT))
		{
			camYaw += camera.getCamHeadingSpeed() * time.elapsed();
			cam_moved = true;

			camera.updateYaw(camYaw);
		}

		if (window.isKeyPressed(GLFW_KEY_RIGHT))
		{
			camYaw -= camera.getCamHeadingSpeed() * time.elapsed();
			cam_moved = true;

			camera.updateYaw(camYaw);
		}

		if (window.isKeyPressed(GLFW_KEY_UP))
		{
			camPitch += camera.getCamHeadingSpeed() * time.elapsed();
			cam_moved = true;

			camera.updatePitch(camPitch);
		}

		if (window.isKeyPressed(GLFW_KEY_DOWN))
		{
			camPitch -= camera.getCamHeadingSpeed() * time.elapsed();
			cam_moved = true;

			camera.updatePitch(camPitch);
		}

		if (window.isKeyPressed(GLFW_KEY_Z))
		{
			camRoll -= camera.getCamHeadingSpeed() * time.elapsed();
			cam_moved = true;

			camera.updateRoll(camRoll);
		}

		if (window.isKeyPressed(GLFW_KEY_C))
		{
			camRoll += camera.getCamHeadingSpeed() * time.elapsed();
			cam_moved = true;

			camera.updateRoll(camRoll);
		}

		if (cam_moved)
		{
			camera.update(move);
		}
	}

	return 0;
}