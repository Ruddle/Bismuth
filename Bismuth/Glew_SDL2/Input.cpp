#include "Input.h"
#include <iostream>
#include "glm.hpp"

using namespace glm;

Input::Input(int screenW, int screenH) : mRx(0), mRy(0), mX(0), mY(0), mEnd(false), mScreenW(screenW), mScreenH(screenH)
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
			notifySelect();
			break;

		case SDL_MOUSEBUTTONUP:
			mMouseButtons[mEvent.button.button] = false;
			notifyDeselect();
			break;

		case SDL_MOUSEMOTION:
			mRx = mEvent.motion.xrel;
			mRy = mEvent.motion.yrel;

			mX = mEvent.motion.x;
			mY = mEvent.motion.y;
			notifyMove();
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

void Input::notifySelect()
{
	for (auto it = mObservers.begin(); it != mObservers.end(); it++)
		(*it)->select(vec2(mX / mScreenW - 1/2 , -mY / mScreenH - 1/2));
}

void Input::notifyDeselect()
{
	for (auto it = mObservers.begin(); it != mObservers.end(); it++)
		(*it)->deselect(vec2(mX / mScreenW - 1 / 2, -mY / mScreenH - 1 / 2));
}

void Input::notifyMove()
{
	for (auto it = mObservers.begin(); it != mObservers.end(); it++)
		(*it)->move(vec2(mX / mScreenW - 1 / 2, -mY / mScreenH - 1 / 2), vec2(mRx / mScreenW - 1 / 2, -mRy / mScreenH - 1 / 2));
}
