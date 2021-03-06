#ifndef TRANSFORM_INCLUDED_H
#define TRANSFORM_INCLUDED_H

#include <glm/glm.hpp>
//#include <glm/gtx/transform.hpp>
#include "camera.h"
#include "matrixOp.h"

struct Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->pos = pos;
		this->rot = rot;
		this->scale = scale;
	}

	inline glm::mat4 GetModel() const
	{
		matrixOp matrixFactory;
		glm::mat4 posMat = matrixFactory.translate(pos);
		glm::mat4 scaleMat = matrixFactory.scale(scale);
		glm::mat4 rotX = matrixFactory.rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = matrixFactory.rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = matrixFactory.rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return posMat * rotMat * scaleMat;
	}

	inline glm::mat4 GetCarModel(glm::vec3 carRot) const
	{
		matrixOp matrixFactory;
		glm::mat4 posMat = matrixFactory.translate(pos);
		glm::mat4 scaleMat = matrixFactory.scale(scale);
		glm::mat4 rotX = matrixFactory.rotate(rot.x, glm::vec3(carRot.x, 0.0, 0.0));
		glm::mat4 rotY = matrixFactory.rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = matrixFactory.rotate(rot.z, glm::vec3(0.0, 0.0, carRot.z));
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return posMat * rotMat * scaleMat;
	}

	inline glm::mat4 GetMVP(const Camera& camera) const
	{
		glm::mat4 VP = camera.GetViewProjection();
		glm::mat4 M = GetModel();

		return VP * M;//camera.GetViewProjection() * GetModel();
	}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec3* GetRot() { return &rot; }
	inline glm::vec3* GetScale() { return &scale; }

	inline void SetPos(glm::vec3& pos) { this->pos = pos; }
	inline void SetRot(glm::vec3& rot) { this->rot = rot; }
	inline void SetScale(glm::vec3& scale) { this->scale = scale; }

	void multiply(Transform t2){
		pos.x *= t2.GetPos()->x;
		pos.y *= t2.GetPos()->y;
		pos.z *= t2.GetPos()->z;

		rot.x *= t2.GetRot()->x;
		rot.y *= t2.GetRot()->y;
		rot.z *= t2.GetRot()->z;

		scale.x *= t2.GetScale()->x;
		scale.y *= t2.GetScale()->y;
		scale.z *= t2.GetScale()->z;
	}
protected:
private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};

#endif
