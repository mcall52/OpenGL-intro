#pragma once

#include <glm\glm.hpp>
#include <math.h>

class matrixOp{
public:
	matrixOp(){
	}

	glm::mat4 translate(glm::vec3 pos){
		//glm::mat4 mat(1.0f,0.0f,0.0f,pos.x,
		//			  0.0f,1.0f,0.0f,pos.y,
		//			  0.0f,0.0f,1.0f,pos.z,
		//			  0.0f,0.0f,0.0f,1.0f);
		//return mat;

		//or

		glm::mat4 mat(1.0f);

		mat[3][0] = pos.x;
		mat[3][1] = pos.y;
		mat[3][2] = pos.z;

		return mat;
	}

	glm::mat4 rotate(float rot, glm::vec3 angle){
		// |cos() -sin() sin()  0|
		// |sin()  cos() -sin() 0|
		// |-sin() sin() cos()  0|
		// |  0     0     0     1|

		glm::mat4 mat(1.0f);
		float cos_val = std::cos(rot);
		float sin_val = std::sin(rot);

		if(angle.x > 0){
			mat[1][1] = cos_val;
			mat[2][1] = -sin_val;
			mat[1][2] = sin_val;
			mat[2][2] = cos_val;
		}
		else if(angle.y > 0){
			mat[0][0] = cos_val;
			mat[2][0] = sin_val;
			mat[0][2] = -sin_val;
			mat[2][2] = cos_val;
		}
		else{
			mat[0][0] = cos_val;
			mat[1][0] = -sin_val;
			mat[0][1] = sin_val;
			mat[1][1] = cos_val;
		}

		return mat;
	}

	glm::mat4 scale(glm::vec3 scale){
		glm::mat4 mat(1.0f);

		mat[0][0] = scale.x;
		mat[1][1] = scale.y;
		mat[2][2] = scale.z;

		return mat;
	}

	glm::mat4 lookAt(glm::vec3 pos, glm::vec3 forward, glm::vec3 up){
		glm::vec3 zaxis = glm::normalize(pos - forward);
		glm::vec3 xaxis = glm::normalize(glm::cross(zaxis, up));
		glm::vec3 yaxis = glm::cross(zaxis, xaxis);

		glm::mat4 mat(1.0f);

		mat[0][0] = xaxis.x;
		mat[1][0] = xaxis.y;
		mat[2][0] = xaxis.z;
		mat[3][0] = glm::dot(xaxis, -pos);

		mat[0][1] = yaxis.x;
		mat[1][1] = yaxis.y;
		mat[2][1] = yaxis.z;
		mat[3][1] = glm::dot(yaxis, -pos);
		
		mat[0][2] = zaxis.x;
		mat[1][2] = zaxis.y;
		mat[2][2] = zaxis.z;
		mat[3][2] = glm::dot(zaxis, -pos);

		return mat;
	}

	glm::mat4 perspective(float fov, float aspect, float zNear, float zFar){
		float f = 1 / tan(fov / 2);
		glm::mat4 perspectiveProjection = glm::mat4();
		
		perspectiveProjection[0][0] = f / aspect;
		perspectiveProjection[1][1] = f;
		perspectiveProjection[2][2] = (zFar + zNear) / (zNear - zFar);
		perspectiveProjection[2][3] = -1;
		perspectiveProjection[3][2] = (2 * zNear * zFar) / (zNear - zFar);
		
		return perspectiveProjection;
	}

private:


};