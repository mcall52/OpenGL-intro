#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include "Scene.h"
#include <string>

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv)
{
	Display display(800, 600, "Texture Mapper");
	std::string car_mesh, tire_mesh, lot_mesh, lego_mesh,
		car_texture, tire_texture, lot_texture, lego_texture;

	car_mesh = "./res/p2files/car.obj";
	car_texture = "./res/p2files/car.bmp";

	tire_mesh = "./res/p2files/tire.obj";
	tire_texture = "./res/p2files/tire.bmp";

	lot_mesh = "./res/p2files/ParkingLot.obj";
	lot_texture = "./res/p2files/ParkingLot.bmp";

	lego_mesh = "./res/LegoMan.obj";
	lego_texture = "./res/gold.jpg";

	//Mesh mesh(mesh_str);
	Mesh car_m(car_mesh);
	Mesh tire1_m(tire_mesh);
	Mesh tire2_m(tire_mesh);
	Mesh tire3_m(tire_mesh);
	Mesh tire4_m(tire_mesh);
	Mesh lot_m(lot_mesh);
	Mesh lego_m(lego_mesh);

	//Texture texture(texture_str);
	Texture car_t(car_texture);
	Texture tire1_t(tire_texture);
	Texture tire2_t(tire_texture);
	Texture tire3_t(tire_texture);
	Texture tire4_t(tire_texture);
	Texture lot_t(lot_texture);
	Texture lego_t(lego_texture);

	Shader shader("./res/basicShader");
	int camera_distance;
	//if (DISPLAY_WHICH_MESH <= 2 && DISPLAY_WHICH_MESH >= 0)
		camera_distance = -5;
	//else
	//	camera_distance = -5;

	Camera camera(glm::vec3(0, 1, camera_distance), 70.0f, ((float)WIDTH / (float)HEIGHT), 0.01f, 1000.0f);
	Transform transform;

	Transform carTransform(glm::vec3(0,0,0.05), glm::vec3(0,0,0), glm::vec3(1,1,1));
	Transform tire1Transform(glm::vec3(.4,.15,.52), glm::vec3(0,0,0), glm::vec3(0.25,0.25,0.25));
	Transform tire2Transform(glm::vec3(.4,.15,-.5), glm::vec3(0,0,0), glm::vec3(0.25,0.25,0.25));
	Transform tire3Transform(glm::vec3(-.4,.15,.52), glm::vec3(0,3.14,0), glm::vec3(0.25,0.25,0.25));
	Transform tire4Transform(glm::vec3(-.4,.15,-.5), glm::vec3(0,3.14,0), glm::vec3(0.25,0.25,0.25));
	Transform lotTransform(glm::vec3(5.3,0,-6), glm::vec3(0,2.1,0), glm::vec3(1,1,1));
	Transform legoTransform(glm::vec3(.2,.5,0), glm::vec3(0,3.14,0), glm::vec3(.15,.15,.15));

	float counter = 0.0f;

	//Scene scene(camera, tire4Transform, tire2Transform, tire3Transform, tire1Transform, carTransform, lotTransform);

	while (!display.IsClosed()) 
	{
		display.Clear(0.0f, 0.0f, 1.0f, 1.0f);
		shader.Update(transform, camera);
		shader.Bind();
		
		//parent tires to car
		//multiply each tire Transform by car transform
		//tire1Transform.multiply(carTransform);
		//tire2Transform.multiply(carTransform);
		//tire3Transform.multiply(carTransform);
		//tire4Transform.multiply(carTransform);

		car_t.Bind();
		shader.Update(carTransform, camera);
		car_m.Draw();

		tire1_t.Bind();
		shader.UpdateTire(carTransform, camera, tire1Transform);
		tire1_m.Draw();
		
		tire2_t.Bind();
		//shader.Update(tire2Transform, camera);
		shader.UpdateTire(carTransform, camera, tire2Transform);
		tire2_m.Draw();

		tire3_t.Bind();
		//shader.Update(tire3Transform, camera);
		shader.UpdateTire(carTransform, camera, tire3Transform);
		tire3_m.Draw();

		tire4_t.Bind();
		//shader.Update(tire4Transform, camera);
		shader.UpdateTire(carTransform, camera, tire4Transform);
		tire4_m.Draw();

		lot_t.Bind();
		shader.Update(lotTransform, camera);
		lot_m.Draw();

		lego_t.Bind();
		shader.UpdateTire(carTransform, camera, legoTransform);
		lego_m.Draw();

		display.Update(camera, tire2Transform, tire4Transform, carTransform, lotTransform);
		//display.Update(scene);

	}
	return 0;
}