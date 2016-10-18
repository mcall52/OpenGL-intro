#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "matrixOp.h"

struct Camera
{
public:
	Camera()
	{

	}

	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		matrixOp matrixFactory;

		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, -1.0f, 0.0f);
		this->projection = matrixFactory.perspective(fov, aspect, zNear, zFar);
	}

	inline glm::mat4 GetViewProjection() const
	{
		matrixOp matrixFactory;
		return projection * matrixFactory.lookAt(pos, pos + forward, up);
	}

	void MoveForward(float amt)
	{
		pos += forward * amt;
	}

	//void MoveForward(bool pressed)
	//{
	//	while(pressed){
	//		pos += forward * 0.004f;
	//	}
	//}

	void MoveBack(float amt)
	{
		pos -= forward * amt;
	}

	void MoveRight(float amt)
	{
		pos -= glm::cross(up, forward) * amt;
	}

	void MoveLeft(float amt)
	{
		pos += glm::cross(up, forward) * amt;
	}

	void Pitch(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(up, forward));
		matrixOp matrixFactory;

		forward = glm::vec3(glm::normalize(matrixFactory.rotate(angle, right) * glm::vec4(forward, 0.0)));
		up = glm::normalize(glm::cross(forward, right));
	}

	void RotateY(float angle)
	{
		static const glm::vec3 UP(0.0f, 1.0f, 0.0f);
		matrixOp matrixFactory;

		glm::mat4 rotation = matrixFactory.rotate(angle, UP);

		forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
		up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	}

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};

#endif
