#include "pch.h"
#include "RECTS.h"
#include "Buttons.h"

void RECTS::Init()
{
	mX = 0; mY = 0; 
}

void RECTS::Update()
{
	mX = _mousePosition.x;
	mY = _mousePosition.y;

	if (!mButtons->GetShowButtons()) {
		if (Input::GetInstance()->GetKeyDown(VK_LBUTTON)) {
			startPoint = { mX, mY };
		}
		if (Input::GetInstance()->GetKey(VK_LBUTTON)) {

			endPoint = { mX,mY };
			rc = { (int)startPoint.mPointX, (int)startPoint.mPointY, (int)endPoint.mPointX, (int)endPoint.mPointY };
		}

		if (Input::GetInstance()->GetKeyUp(VK_LBUTTON)) {

			mRectList.push_back(rc);

			if (rc.left == rc.right or rc.top == rc.bottom) {

				mRectList.pop_back();
			}

			rc = {};

		}
	}
}

void RECTS::Release()
{
}

void RECTS::Render(HDC hdc)
{
	if (mRectList.size()) {

		wstring num = L"�� rect ���� : " + to_wstring(mRectList.size());
		TextOutW(hdc, 1000, 0, num.c_str(), num.size());

		HBRUSH newb = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldb = (HBRUSH)SelectObject(hdc, newb);
		for (RECT elem : mRectList) {

			RenderRect(hdc, elem);
		}
		SelectObject(hdc, oldb);
		DeleteObject(newb);

	}

	if (&rc) {
		HBRUSH newb = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldb = (HBRUSH)SelectObject(hdc, newb);
		RenderRect(hdc, rc);
		SelectObject(hdc, oldb);
		DeleteObject(newb);
	}

	if (mCurrentRect) {

		RECT LT = RectMakeCenter(mCurrentRect->left, mCurrentRect->top, 10, 10);
		RECT RT = RectMakeCenter(mCurrentRect->right, mCurrentRect->top, 10, 10);
		RECT LB = RectMakeCenter(mCurrentRect->left, mCurrentRect->bottom, 10, 10);
		RECT RB = RectMakeCenter( mCurrentRect->right, mCurrentRect->bottom, 10,10);

		RenderRect(hdc, LT);
		RenderRect(hdc, RT);
		RenderRect(hdc, LB);
		RenderRect(hdc, RB);
	}
	

}

void RECTS::EraseElem()
{
	if (mRectList.size() == 0) {
		return;
	}
	if (mCurrentRect == nullptr) {
		mRectList.pop_back();
		return;
	}
	else {
		mRectList.erase(mitr);
		mCurrentRect = nullptr;
	}
}