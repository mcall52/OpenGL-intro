#pragma once
#include "camera.h"
#include "transform.h"

class Scene
{
public:
	Scene(Camera& camera, Transform& tireFD, Transform& tireFP, Transform& tireRD, Transform& tireRP, Transform& car, Transform& building)
	{
		this->camera = camera;
		this->tireFD = tireFD;
		this->tireFP = tireFP;
		this->tireRD = tireRD;
		this->tireRP = tireRP;
		this->car = car;
		this->building = building;
	}

	~Scene(void){};

	Camera* getCamera(){
		return &camera;
	}
	Transform* getTireFD(){
		return &tireFD;
	}
	Transform* getTireFP(){
		return &tireFP;
	}
	Transform* getTireRD(){
		return &tireRD;
	}
	Transform* getTireRP(){
		return &tireRP;
	}
	Transform* getCar(){
		return &car;
	}
	Transform* getBuilding(){
		return &building;
	}

private:
	Camera camera;
	Transform tireFD;
	Transform tireFP;
	Transform tireRD;
	Transform tireRP;
	Transform car;
	Transform building;
};

