#pragma once
#include "GameObject.h"
class Image;
class RECTS;
class Buttons;

class MainGame
{
	Image* mBackBuffer;	//후면버퍼(건들지마라)
	Image* mImage;
	RECTS* mRects;
	Buttons* mButtons;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

