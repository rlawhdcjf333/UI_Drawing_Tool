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
	
	RECT* mCurrentRect = nullptr;

	RECT rc;
	vector <RECT> mRectList;
	vector<RECT>::iterator mitr;
public:

	void Init();
	void Update();
	void Release();
	void Render(HDC hdc);

	void SetButtons(Buttons* Buttonsptr) { mButtons = Buttonsptr; }
	void EraseAll() { mRectList.clear(); mRectList.shrink_to_fit(); }
	void EraseElem();
	RECT** GetCurrentRect() { return &mCurrentRect; }
	vector<RECT>::iterator* Getitr() { return &mitr; }
	vector <RECT> GetRectList() { return mRectList; }
	vector<RECT>* const GetRectListPt() { return &mRectList; }
	void LoadRectList(RECT rc) { mRectList.push_back(rc); }

};


