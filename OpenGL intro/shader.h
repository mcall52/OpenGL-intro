#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include "transform.h"
#include "camera.h"

#pragma once
class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();
	void Update(const Transform& transform, const Camera& camera);
	void UpdateTire(const Transform& transform, const Camera& camera, Transform& tire);


	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	enum
	{
		TRANSFORM_U,
		NUM_UNIFROMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFROMS];
};

#endif