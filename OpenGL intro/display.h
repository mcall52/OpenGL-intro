#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <string>

#pragma once
class Display
{
public:
	Display(int width, int height, const std::string& title);
	void Clear(float r, float g, float b, float a);
	void Update();
	virtual ~Display();
	bool IsClosed();
private:
	Display(const Display& other) {}
	void operator=(const Display& other) {}
	
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool isClosed;
};

#endif // DISPLAY_H