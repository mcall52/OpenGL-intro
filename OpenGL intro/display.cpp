#include "display.h"
#include "transform.h"
#include <iostream>
#include "GL/glew.h"


Display::Display(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize!" << std::endl;
	}

	isClosed = false;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}


Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool Display::IsClosed() {
	return isClosed;
}

void Display::Update(Camera& camera, Transform& tire2, Transform& tire4)
{
	SDL_GL_SwapWindow(m_window);
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) {
			isClosed = true;
		}
		if (e.type == SDL_KEYDOWN){
			//switch statement about key being pressed
			handleKeyPress(camera, tire2, tire4, e.key.keysym.sym);
		}
		if (e.type == SDL_KEYUP){
			handleKeyRelease(camera, tire2, tire4, e.key.keysym.sym);
		}
	}
}

void Display::Clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::handleKeyPress(Camera& camera, Transform& tire2, Transform& tire4, SDL_Keycode key){
	switch (key)
	{
	case SDLK_w: camera.MoveForward(0.5f); break;
	case SDLK_s: camera.MoveBack(0.5f); break;
	case SDLK_a: camera.MoveLeft(0.5f); break;
	case SDLK_d: camera.MoveRight(0.5f); break;
	case SDLK_q: camera.RotateY(0.1f); break;
	case SDLK_e: camera.RotateY(-0.1f); break;
	case SDLK_r: camera.Pitch(0.1f); break;
	case SDLK_f: camera.Pitch(-0.1f); break;
	case SDLK_LEFT: tire2.SetRot(glm::vec3(0,1.0f,0));
					 tire4.SetRot(glm::vec3(0,4.14f,0)); break;
	case SDLK_RIGHT: tire2.SetRot(glm::vec3(0,-1.0f,0));
					 tire4.SetRot(glm::vec3(0,2.14f,0)); break;

	default:
		break;
	}
}

void Display::handleKeyRelease(Camera& camera, Transform& tire2, Transform& tire4, SDL_Keycode key){
	switch (key)
	{
	case SDLK_RIGHT: 
	case SDLK_LEFT:	 tire2.SetRot(glm::vec3(0,0,0));
					 tire4.SetRot(glm::vec3(0,3.14f,0)); break;

	default: break;
	}
}