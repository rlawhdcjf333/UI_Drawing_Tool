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

	//좌상단 메뉴 버튼 표시 여부
	bool showButtons;
	//파일 로드 여부
	bool failLoad;
	bool mLoadQ;

public:

	void Init();
	void Update();
	void Release();
	void Render(HDC hdc);

	void SetRECTSptr(RECTS* RECTSptr);
	bool GetShowButtons() { return showButtons; }

	bool GetLoadQ() { return mLoadQ; }

};

