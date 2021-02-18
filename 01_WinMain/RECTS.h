#pragma once
class Buttons;
class RECTS
{

	Buttons* mButtons;
	float mX;
	float mY;

	struct pointF {

		float mPointX;
		float mPointY;

	};

	pointF startPoint;
	pointF endPoint;
	
	RECT* mCurrentRect;

	RECT rc;

	vector <RECT> mRectList;

public:

	void Init();
	void Update();
	void Release();
	void Render(HDC hdc);

	void SetButtons(Buttons* Buttonsptr) { mButtons = Buttonsptr; }
	void EraseAll() { mRectList.clear(); mRectList.shrink_to_fit(); }
	void EraseElem(RECT* Rectptr);
	RECT* GetCurrentRect() { return mCurrentRect; }

	vector <RECT> GetRectList() { return mRectList; }
	void LoadRectList(RECT rc) { mRectList.push_back(rc); }

};


