#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include <string>

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv)
{
	Display display(800, 600, "Texture Mapper");
	std::string mesh_str(""), texture_str("");


	int DISPLAY_WHICH_MESH = 0;

	switch(DISPLAY_WHICH_MESH) {
		case 0 :
			mesh_str = "./res/colored_crayon_box.obj";
			texture_str = "./res/colored_crayon_box.png";
			break;
		case 1 :
			mesh_str = "./res/blue_crayon.obj";
			texture_str = "./res/green_crayon.png";
			break;
		case 2 :
			mesh_str = "./res/blue_crayon.obj";
			texture_str = "./res/blue_crayon.png";
			break;
		default:
			mesh_str = "./res/colored_crayon_box.obj";
			texture_str = "./res/colored_crayon_box.png";
			break;	
	}

	Mesh mesh(mesh_str);
	Texture texture(texture_str);
	Shader shader("./res/basicShader");
	int camera_distance;
	if (DISPLAY_WHICH_MESH <= 2 && DISPLAY_WHICH_MESH >= 0)
		camera_distance = -5;
	else
		camera_distance = -5;

	Camera camera(glm::vec3(0, 0, camera_distance), 70.0f, ((float)WIDTH / (float)HEIGHT), 0.01f, 1000.0f);
	Transform transform;

	float counter = 0.0f;

	while (!display.IsClosed()) 
	{
		display.Clear(0.0f, 0.30f, 0.0f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		shader.Bind();
		texture.Bind();
		shader.Update(transform, camera);
		mesh.Draw();
		display.Update();
		counter += 0.0001f;
	}
	return 0;
}