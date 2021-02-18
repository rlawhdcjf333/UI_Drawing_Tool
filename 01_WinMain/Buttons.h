#pragma once
class RECTS;
class Buttons
{

	typedef map<wstring, RECT>::iterator ButtonIter;
	map <wstring, RECT> mButtonList;
	RECTS* mRects;
	vector<RECT>* mRectList;
	vector<RECT>::iterator* mitr ;
	RECT** mCurrentRect;
	bool showButtons;

public:

	void Init();
	void Update();
	void Release();
	void Render(HDC hdc);

	void SetRECTSptr(RECTS* RECTSptr);
	bool GetShowButtons() { return showButtons; }

};

