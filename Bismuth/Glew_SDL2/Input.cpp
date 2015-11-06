#include "Input.h"
#include <iostream>


Input::Input() : mRx(0), mRy(0), mX(0), mY(0), mEnd(false)
{
	for (int i(0); i < SDL_NUM_SCANCODES; i++)
		mKeys[i] = false;

	for (int i(0); i < SDL_NUM_SCANCODES; i++)
		mRisingKeys[i] = false;

	for (int i(0); i < SDL_NUM_SCANCODES; i++)
		mRisingKeysAble[i] = true;

	for (int i = 0; i < NB_MOUSE_BUTTONS; i++)
		mMouseButtons[i] = false;
}

void Input::update()
{

	for (int i(0); i < SDL_NUM_SCANCODES; i++)
		mRisingKeys[i] = false;

	mRx = 0;
	mRy = 0;

	while (SDL_PollEvent(&mEvent))
	{
		switch (mEvent.type)
		{

		case SDL_KEYDOWN:
			
			mKeys[mEvent.key.keysym.scancode] = true;
			if (mRisingKeysAble[mEvent.key.keysym.scancode] == true) {
				mRisingKeys[mEvent.key.keysym.scancode] = true;
				mRisingKeysAble[mEvent.key.keysym.scancode] = false;
			}

			break;

		case SDL_KEYUP:
			mKeys[mEvent.key.keysym.scancode] = false;
			mRisingKeysAble[mEvent.key.keysym.scancode] = true;
			
			break;

		case SDL_MOUSEBUTTONDOWN:
			mMouseButtons[mEvent.button.button] = true;
			break;

		case SDL_MOUSEBUTTONUP:
			mMouseButtons[mEvent.button.button] = false;
			break;

		case SDL_MOUSEMOTION:
			mRx = mEvent.motion.xrel;
			mRy = mEvent.motion.yrel;

			mX = mEvent.motion.x;
			mY = mEvent.motion.y;
			break;

		case SDL_WINDOWEVENT:
			if (mEvent.window.event == SDL_WINDOWEVENT_CLOSE)
				mEnd = true;
			break;

		default:
			break;
		}
	}
}

bool Input::mouseMotion() const
{
	return !(mRx == 0 && mRy == 0);
}


Input::~Input()
{
}
