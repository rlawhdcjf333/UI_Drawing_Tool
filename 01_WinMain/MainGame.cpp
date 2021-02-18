#include "pch.h"
#include "MainGame.h"
#include "UI.h"
#include "Image.h"
/*
Scene : 스테이지 단위를 씬이라고 함
*/

/*
Initialize : 초기화
앞으로 게임을 시작하기 전에 초기화 및 생성은 여기서 진행
게임 시작하기 전에 딱 한번만 실행되는 함수
*/
void MainGame::Init()
{
	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);
	
	mRects = new RECTS;
	mRects->Init();

	mButtons = new Buttons;
	mButtons->Init();

	mButtons->SetRECTSptr(mRects);
	mRects->SetButtons(mButtons);
}

/*
Release : 메모리 해제할 때 불러주는 함수
유니티라면 OnDestroy
해당 클래스 인스턴스가 메모리 해제 될 때 단 한번 호출해주는 녀석
*/
void MainGame::Release()
{
	Random::ReleaseInstance();	//싱글톤 인스턴스 삭제

	SafeDelete(mBackBuffer);

	mRects->Release();
	SafeDelete(mRects);

	mButtons->Release();
	SafeDelete(mButtons);
}


void MainGame::Update()
{
	mRects->Update();
	mButtons->Update();
}


void MainGame::Render(HDC hdc)
{
	//백버퍼의 HDC 가져온다
	HDC backDC = mBackBuffer->GetHDC();
	//HDC 영역을 특정 색으로 밀어버리는 녀석
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ==================================================
	{
		RECT rc = { 0,0,WINSIZEX,WINSIZEY };
		HBRUSH newb = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
		HBRUSH oldb = (HBRUSH)SelectObject(backDC,newb);
		RenderRect(backDC, rc);
		SelectObject(backDC, oldb);
		DeleteObject(newb);



		mButtons->Render(backDC);
		mRects->Render(backDC);
	}
	//====================================================
	//후면버퍼 내용을 윈도우 창에 고속 복사
	mBackBuffer->Render(hdc, 0, 0);
}



