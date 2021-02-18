#include "pch.h"
#include "Buttons.h"
#include "RECTS.h"
#include <fstream>

void Buttons::Init()
{
	int buttonWidth=100;

	RECT temp = { 0,0, buttonWidth,30 };
	mButtonList.insert(make_pair(L"내보내기", temp));

	temp = { buttonWidth,0,buttonWidth*2,30 };
	mButtonList.insert(make_pair(L"지우기", temp));

	temp = { buttonWidth*2,0,buttonWidth*3,30 };
	mButtonList.insert(make_pair(L"모두 지우기", temp));

	temp = { buttonWidth * 3,0,buttonWidth * 4,30 };
	mButtonList.insert(make_pair(L"불러오기", temp));

	temp = { buttonWidth * 4,0, buttonWidth * 5 , 30 };
	mButtonList.insert(make_pair(L"이미지로드", temp));

	showButtons = true;


}

void Buttons::Update()
{
	if (showButtons) {
		if (Input::GetInstance()->GetKeyDown(VK_LBUTTON)) {
			RECT rc;
			//POINT cursor = { _mousePosition.x, _mousePosition.y };
			//rc = mButtonList.find(L"지우기")->second;
			rc = mButtonList.find(L"내보내기")->second;
			if (PtInRect(&rc, _mousePosition)) {

				ofstream fout("rectList.txt");

				for (RECT elem : mRects->GetRectList()) {

					fout << to_string(elem.left) << endl
						<< to_string(elem.top) << endl
						<< to_string(elem.right) << endl
						<< to_string(elem.bottom) << endl;
				}

				fout.close();
			}
			else if (PtInRect(&(rc = mButtonList.find(L"지우기")->second), _mousePosition)) 
			{ mRects->EraseElem(); }
			else if(PtInRect(&(rc = mButtonList.find(L"모두 지우기")->second), _mousePosition)) { mRects->EraseAll(); }
			else if (PtInRect(&(rc = mButtonList.find(L"불러오기")->second), _mousePosition)) {

				ifstream fin("rectList.txt");
				if (fin.is_open()) {

					mRects->EraseAll();
					vector <int> v;
					string tmp;
					int tmpint;

					while (fin) {

						getline(fin, tmp);
						if (tmp.size()) {
							tmpint = stoi(tmp);
							v.push_back(tmpint);
						}

					}


					for (int i = 0; i < v.size(); i += 4) {
						RECT rc = { v[i], v[i + 1], v[i + 2], v[i + 3] };
						mRects->LoadRectList(rc);
					}

				}

				fin.close();
			}
			else if (PtInRect(&(rc = mButtonList.find(L"이미지로드")->second), _mousePosition)) {

				if (!IMAGEMANAGER->FindImage(L"Image")) {
					failLoad = true;
					return;
				}
				else mLoadQ = !mLoadQ;
			}
			else {
				if (mRectList->size()) {
					if ((*mCurrentRect) == NULL) {
						*mitr = mRectList->end() - 1;
					}
					else {
						if (!PtInRect((*mCurrentRect), _mousePosition)) {
							*mitr = mRectList->end() - 1;
						}
					}
					// itr이 시작 점이 아닐경우
					if ((*mitr) != mRectList->begin()) {
						for (; *mitr > mRectList->begin(); --(*mitr)) {
							RECT* rc = &(**mitr);
							if (PtInRect(rc, _mousePosition)) {
								if (*mCurrentRect == rc) {
									*mCurrentRect = nullptr;
								}
								else {
									*mCurrentRect = rc;
									break;
								}
							}
						}
					}
					// itr이 시작 위치일때
					if (*mitr == mRectList->begin()) {
						RECT* rc = &(**mitr);
						if (PtInRect(rc, _mousePosition)) {
							if (*mCurrentRect == rc) {
								*mCurrentRect = nullptr;
							}
							else {
								*mCurrentRect = rc;
							}
						}
					}

				}
			}
		}
	}

	if (Input::GetInstance()->GetKeyDown(VK_TAB)) {

		showButtons = !showButtons;
		failLoad = 0;
	}
}

void Buttons::Release()
{
	
}

void Buttons::Render(HDC hdc)
{
	if (showButtons) {

		ButtonIter iter = mButtonList.begin();

		SetBkMode(hdc, TRANSPARENT);
		HBRUSH newb = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
		HBRUSH oldb = (HBRUSH)SelectObject(hdc, newb);

		for (; iter != mButtonList.end(); iter++) {

			RenderRect(hdc, iter->second);
			DrawTextW(hdc, iter->first.c_str(), iter->first.size(), &iter->second, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		}

		SelectObject(hdc, oldb);
		DeleteObject(newb);

		if (failLoad) {
			wstring noImage = L"로드할 이미지가 없습니다";
			TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, noImage.c_str(), noImage.size());
		}

	}
}

void Buttons::SetRECTSptr(RECTS* RECTSptr)
{
	mRects = RECTSptr;
	mRectList = mRects->GetRectListPt();
	mitr = mRects->Getitr();
	mCurrentRect = mRects->GetCurrentRect();
	}
