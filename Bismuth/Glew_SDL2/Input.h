#include <SDL.h>

#pragma once

#define NB_MOUSE_BUTTONS 3

class Input
{
public:
	Input();
	~Input();
	void update();
	bool end() const { return mEnd; }
	bool getKey(const SDL_Scancode key) const { return mKeys[key]; }
	bool getRisingKey(const SDL_Scancode key) const { return mRisingKeys[key]; }
	bool getMouseButton(const int button) const { return mMouseButtons[button]; }

	int getRX() const { return mRx; }
	int getRY() const { return mRy; }
	int getX() const { return mX; }
	int getY() const { return mY; }
	bool mouseMotion() const;

private:
	SDL_Event mEvent;
	bool mKeys[SDL_NUM_SCANCODES];
	bool mRisingKeys[SDL_NUM_SCANCODES];
	bool mRisingKeysAble[SDL_NUM_SCANCODES];
	bool mEnd;

	bool mMouseButtons[NB_MOUSE_BUTTONS];


	int mRx;
	int mRy;

	int mX;
	int mY;
};

