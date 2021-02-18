#include "pch.h"
#include "MainGame.h"
#include "UI.h"
#include "Image.h"
/*
Scene : �������� ������ ���̶�� ��
*/

/*
Initialize : �ʱ�ȭ
������ ������ �����ϱ� ���� �ʱ�ȭ �� ������ ���⼭ ����
���� �����ϱ� ���� �� �ѹ��� ����Ǵ� �Լ�
*/
void MainGame::Init()
{
	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);
	
	IMAGEMANAGER->LoadFromFile(L"Image", Resources(L"Image.bmp"), 600, 800, false);
	mImage = IMAGEMANAGER->FindImage(L"Image");


	mRects = new RECTS;
	mRects->Init();

	mButtons = new Buttons;
	mButtons->Init();

	mButtons->SetRECTSptr(mRects);
	mRects->SetButtons(mButtons);
}

/*
Release : �޸� ������ �� �ҷ��ִ� �Լ�
����Ƽ��� OnDestroy
�ش� Ŭ���� �ν��Ͻ��� �޸� ���� �� �� �� �ѹ� ȣ�����ִ� �༮
*/
void MainGame::Release()
{
	Random::ReleaseInstance();	//�̱��� �ν��Ͻ� ����

	SafeDelete(mBackBuffer);

	mRects->Release();
	SafeDelete(mRects);

	mButtons->Release();
	SafeDelete(mButtons);
}


void MainGame::Update()
{
	mButtons->Update();
	mRects->Update();
}


void MainGame::Render(HDC hdc)
{
	//������� HDC �����´�
	HDC backDC = mBackBuffer->GetHDC();
	//HDC ������ Ư�� ������ �о������ �༮
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ==================================================
	{
		RECT rc = { 0,0,WINSIZEX,WINSIZEY };
		HBRUSH newb = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
		HBRUSH oldb = (HBRUSH)SelectObject(backDC,newb);
		RenderRect(backDC, rc);
		SelectObject(backDC, oldb);
		DeleteObject(newb);

		if(mButtons->GetLoadQ())
		mImage->ScaleRender(backDC, 0, 0, WINSIZEX, WINSIZEY);


		mButtons->Render(backDC);
		mRects->Render(backDC);
	}
	//====================================================
	//�ĸ���� ������ ������ â�� ��� ����
	mBackBuffer->Render(hdc, 0, 0);
}



