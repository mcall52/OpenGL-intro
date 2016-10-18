#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <string>
#include "camera.h"
#include "transform.h"
#include "Scene.h"

#pragma once
class Display
{
public:
	Display(int width, int height, const std::string& title);
	void Clear(float r, float g, float b, float a);
	void Update(Camera& camera, Transform& tire2, Transform& tire4, Transform& car, Transform& lot);
	//void Display::Update(Scene& scene);
	virtual ~Display();
	bool IsClosed();
private:
	Display(const Display& other) {}
	void operator=(const Display& other) {}
	
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool isClosed;

	bool isTurnedLeft;
	bool isTurnedRight;

	void handleKeyPress(Camera& camera, Transform& tire2, Transform& tire4, Transform& car, Transform& lot, SDL_Keycode key);
	//void handleKeyPress(Scene& scene, SDL_Keycode key);
	void Display::handleKeyRelease(Camera& camera, Transform& tire2, Transform& tire4, Transform& car, Transform& lot, SDL_Keycode key);
	//void handleKeyRelease(Scene& scene, SDL_Keycode key);
	void driveForward(Camera& camera, Transform& lot, Transform& car);
	void driveBackward(Camera& camera, Transform& lot, Transform& car);
};

#endif // DISPLAY_H