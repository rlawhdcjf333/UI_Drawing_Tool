#pragma once
#include "GameObject.h"
class Image;
class RECTS;
class Buttons;

class MainGame
{
	Image* mBackBuffer;	//�ĸ����(�ǵ�������)
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

