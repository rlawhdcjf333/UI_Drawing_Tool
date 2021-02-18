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

	showButtons = true;

}

void Buttons::Update()
{
	if (showButtons) {
		if (Input::GetInstance()->GetKeyDown(VK_LBUTTON)) {
			RECT rc;
			POINT cursor = { _mousePosition.x, _mousePosition.y };

			rc = mButtonList.find(L"내보내기")->second;
			if (PtInRect(&rc, cursor)) {

				ofstream fout("rectList.txt");

				for (RECT elem : mRects->GetRectList()) {

					fout << to_string(elem.left) << endl
						<< to_string(elem.top) << endl
						<< to_string(elem.right) << endl
						<< to_string(elem.bottom) << endl;
				}

				fout.close();
			}

			rc = mButtonList.find(L"지우기")->second;
			if (PtInRect(&rc, cursor)) { mRects->EraseElem(mRects->GetCurrentRect()); }

			rc = mButtonList.find(L"모두 지우기")->second;
			if (PtInRect(&rc, cursor)) { mRects->EraseAll(); }

			rc = mButtonList.find(L"불러오기")->second;
			if (PtInRect(&rc, cursor)) {

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

		}
	}

	if (Input::GetInstance()->GetKeyDown(VK_TAB)) {

		showButtons = !showButtons;
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

	}
}
