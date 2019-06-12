#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <Windows.h>
#include <string>
#include<array>

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(0);	// 一開始的loading進度為0%
		//
		// 開始載入資料
		//
		LoadBitmap();
		LoadAudio();
		isStartHover = false;
		isIntroHover = false;
		isIntroClick = false;
		isAboutClick = false;
		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
		//

		//CAudio::Instance()->Load(AUDIO_START, "Sounds\\start.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Play(AUDIO_START, true);		// 撥放 WAVE

	}

	void CGameStateInit::OnBeginState()
	{
		CAudio::Instance()->Resume();
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_SPACE = ' ';
		const char KEY_Q = 0x51;
		if (nChar == KEY_Q)
		{
			if(CAudio::Instance()->GetIsPlay())
				CAudio::Instance()->SetIsPlay(false);
			else
				CAudio::Instance()->SetIsPlay(true);

			for (int i = 0; i < AUDIO_END; i++)
			{
				CAudio::Instance()->Pause();
			}
		}
		if (nChar == KEY_SPACE)
		{
			CAudio::Instance()->Stop(AUDIO_START);	// 停止 WAVE
			GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN

		}

		else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		long x = point.x;
		long y = point.y;
		if (x > 10 && x < 216 && y>330 && y < 395 && !isAboutClick)
		{
			CAudio::Instance()->Stop(AUDIO_START);	// 停止 WAVE
			GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
		}
		if (x > 10 && x < 216 && y>400 && y < 450 && !isAboutClick)
		{
			isIntroClick = true;
		}
		else
			isIntroClick = false;
		if (x > 480 && x < 635 && y>10 && y < 58 && !isIntroClick)
		{
			isAboutClick = true;
		}
		else
			isAboutClick = false;

	}

	void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
	{
		long x = point.x;
		long y = point.y;
		if (x > 10 && x < 216 && y>330 && y < 395 && !isAboutClick)
		{
			SetCursor(LoadCursor(NULL, IDC_HAND));
			isStartHover = true;
		}
		else
		{
			isStartHover = false;
		}
		if (x > 10 && x < 216 && y>400 && y < 450 && !isAboutClick)
		{
			SetCursor(LoadCursor(NULL, IDC_HAND));
			isIntroHover = true;
		}
		else
		{
			isIntroHover = false;
		}
		if (x > 480 && x < 635 && y>10 && y < 58 && !isIntroClick && !isAboutClick)
		{
			SetCursor(LoadCursor(NULL, IDC_HAND));
		}
	}

	void CGameStateInit::OnShow()
	{

		if (dadX < 0)
		{
			dadX += 27;
		}
		dad.SetTopLeft(dadX, 0);
		dad.OnShow();
		if (heroX > 300 && dadX == 0)
		{
			heroX -= 10;
		}
		heroBack.SetTopLeft(heroX, 150);
		heroBack.OnShow();
		about.SetTopLeft(480, 10);
		about.OnShow();
		if (!isStartHover)
		{
			start.SetTopLeft(10, 330);
			start.OnShow();
		}
		else
		{
			startHover.OnMove();
			startHover.SetTopLeft(10, 330);
			startHover.OnShow();
		}
		if (!isIntroHover)
		{
			intro.SetTopLeft(10, 400);
			intro.OnShow();
		}
		else
		{
			introHover.OnMove();
			introHover.SetTopLeft(10, 400);
			introHover.OnShow();
		}

		if (isIntroClick)
		{
			if (!introAni.IsFinalBitmap())
			{
				introAni.OnMove();
				introAni.SetTopLeft(0, -55);
				introAni.OnShow();
			}
			else
			{
				introAni.Reset();
				isIntroClick = false;
			}

		}
		if (isAboutClick)
		{
			aboutPic.SetTopLeft(0, 0);
			aboutPic.OnShow();
			back.SetTopLeft(450, 20);
			back.OnShow();
			horse.OnMove();
			horse.SetTopLeft(400, 300);
			horse.OnShow();
		}

		//
		// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
		//
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));

		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	void CGameStateInit::AddBitMaps(char * pic[], int space, CAnimation* ani, int color)
	{
		for (int i = 0; i < space; i++)
		{
			if (color == 0)
				ani->AddBitmap(pic[i], RGB(204, 204, 204));
			else if (color == 1)
				ani->AddBitmap(pic[i], RGB(0, 0, 0));
		}
	}
	void CGameStateInit::LoadBitmap()
	{
		char* dad_back[1] = { "./res/Dad.bmp" };
		char* hero_back[1] = { "./res/hero_back.bmp" };
		char* start_button[1] = { "./res/start/1.bmp" };
		char* start_hover[18] = { "./res/start/2.bmp", "./res/start/3.bmp", "./res/start/4.bmp", "./res/start/5.bmp", "./res/start/6.bmp",
								"./res/start/7.bmp", "./res/start/8.bmp", "./res/start/9.bmp", "./res/start/10.bmp", "./res/start/11.bmp",
								"./res/start/12.bmp", "./res/start/13.bmp", "./res/start/14.bmp","./res/start/17.bmp", "./res/start/18.bmp",
								"./res/start/19.bmp", "./res/start/20.bmp", "./res/start/1.bmp" };
		char* intro_button[1] = { "./res/intro_text/1.bmp" };
		char* intro_hover[14] = { "./res/intro_text/2.bmp", "./res/intro_text/3.bmp", "./res/intro_text/4.bmp", "./res/intro_text/5.bmp", "./res/intro_text/6.bmp",
								"./res/intro_text/7.bmp", "./res/intro_text/8.bmp", "./res/intro_text/9.bmp", "./res/intro_text/10.bmp", "./res/intro_text/11.bmp",
								"./res/intro_text/12.bmp", "./res/intro_text/13.bmp", "./res/intro_text/14.bmp", "./res/intro_text/1.bmp" };
		char* intro_ani[207] = { "./res/intro/1.bmp", "./res/intro/2.bmp", "./res/intro/3.bmp", "./res/intro/4.bmp", "./res/intro/5.bmp",
							"./res/intro/6.bmp", "./res/intro/7.bmp", "./res/intro/8.bmp", "./res/intro/9.bmp", "./res/intro/10.bmp",
							"./res/intro/11.bmp", "./res/intro/12.bmp", "./res/intro/13.bmp", "./res/intro/14.bmp", "./res/intro/15.bmp",
							"./res/intro/16.bmp", "./res/intro/17.bmp", "./res/intro/18.bmp", "./res/intro/19.bmp", "./res/intro/20.bmp",
							"./res/intro/21.bmp", "./res/intro/22.bmp", "./res/intro/23.bmp", "./res/intro/24.bmp", "./res/intro/25.bmp",
							"./res/intro/26.bmp", "./res/intro/27.bmp", "./res/intro/28.bmp", "./res/intro/29.bmp", "./res/intro/30.bmp",
							"./res/intro/31.bmp", "./res/intro/32.bmp", "./res/intro/33.bmp", "./res/intro/34.bmp", "./res/intro/35.bmp",
							"./res/intro/36.bmp", "./res/intro/37.bmp", "./res/intro/38.bmp", "./res/intro/39.bmp", "./res/intro/40.bmp",
							"./res/intro/41.bmp", "./res/intro/42.bmp", "./res/intro/43.bmp", "./res/intro/44.bmp", "./res/intro/45.bmp",
							"./res/intro/46.bmp", "./res/intro/47.bmp", "./res/intro/48.bmp", "./res/intro/49.bmp", "./res/intro/50.bmp",
							"./res/intro/51.bmp", "./res/intro/52.bmp", "./res/intro/53.bmp", "./res/intro/54.bmp", "./res/intro/55.bmp",
							"./res/intro/56.bmp", "./res/intro/57.bmp", "./res/intro/58.bmp", "./res/intro/59.bmp", "./res/intro/60.bmp",
							"./res/intro/61.bmp", "./res/intro/62.bmp", "./res/intro/63.bmp", "./res/intro/64.bmp", "./res/intro/65.bmp",
							"./res/intro/66.bmp", "./res/intro/67.bmp", "./res/intro/68.bmp", "./res/intro/69.bmp", "./res/intro/70.bmp",
							"./res/intro/71.bmp", "./res/intro/72.bmp", "./res/intro/73.bmp", "./res/intro/74.bmp", "./res/intro/75.bmp",
							"./res/intro/76.bmp", "./res/intro/77.bmp", "./res/intro/78.bmp", "./res/intro/79.bmp", "./res/intro/80.bmp",
							"./res/intro/81.bmp", "./res/intro/82.bmp", "./res/intro/83.bmp", "./res/intro/84.bmp", "./res/intro/85.bmp",
							"./res/intro/86.bmp", "./res/intro/87.bmp", "./res/intro/88.bmp", "./res/intro/89.bmp", "./res/intro/90.bmp",
							"./res/intro/91.bmp", "./res/intro/92.bmp", "./res/intro/93.bmp", "./res/intro/94.bmp", "./res/intro/95.bmp",
							"./res/intro/96.bmp", "./res/intro/97.bmp", "./res/intro/98.bmp", "./res/intro/99.bmp", "./res/intro/100.bmp",
							"./res/intro/101.bmp", "./res/intro/102.bmp", "./res/intro/103.bmp", "./res/intro/104.bmp", "./res/intro/105.bmp",
							"./res/intro/106.bmp", "./res/intro/107.bmp", "./res/intro/108.bmp", "./res/intro/109.bmp", "./res/intro/110.bmp",
							"./res/intro/111.bmp", "./res/intro/112.bmp", "./res/intro/113.bmp", "./res/intro/114.bmp", "./res/intro/115.bmp",
							"./res/intro/116.bmp", "./res/intro/117.bmp", "./res/intro/118.bmp", "./res/intro/119.bmp", "./res/intro/120.bmp",
							"./res/intro/121.bmp", "./res/intro/122.bmp", "./res/intro/123.bmp", "./res/intro/124.bmp", "./res/intro/125.bmp",
							"./res/intro/126.bmp", "./res/intro/127.bmp", "./res/intro/128.bmp", "./res/intro/129.bmp", "./res/intro/130.bmp",
							"./res/intro/131.bmp", "./res/intro/132.bmp", "./res/intro/133.bmp", "./res/intro/134.bmp", "./res/intro/135.bmp",
							"./res/intro/136.bmp", "./res/intro/137.bmp", "./res/intro/138.bmp", "./res/intro/139.bmp", "./res/intro/140.bmp",
							"./res/intro/141.bmp", "./res/intro/142.bmp", "./res/intro/143.bmp", "./res/intro/144.bmp", "./res/intro/145.bmp",
							"./res/intro/146.bmp", "./res/intro/147.bmp", "./res/intro/148.bmp", "./res/intro/149.bmp", "./res/intro/150.bmp",
							"./res/intro/151.bmp", "./res/intro/152.bmp", "./res/intro/153.bmp", "./res/intro/154.bmp", "./res/intro/155.bmp",
							"./res/intro/156.bmp", "./res/intro/157.bmp", "./res/intro/158.bmp", "./res/intro/159.bmp", "./res/intro/160.bmp",
							"./res/intro/161.bmp", "./res/intro/162.bmp", "./res/intro/163.bmp", "./res/intro/164.bmp", "./res/intro/165.bmp",
							"./res/intro/166.bmp", "./res/intro/167.bmp", "./res/intro/168.bmp", "./res/intro/169.bmp", "./res/intro/170.bmp",
							"./res/intro/171.bmp", "./res/intro/172.bmp", "./res/intro/173.bmp", "./res/intro/174.bmp", "./res/intro/175.bmp",
							"./res/intro/176.bmp", "./res/intro/177.bmp", "./res/intro/178.bmp", "./res/intro/179.bmp", "./res/intro/180.bmp",
							"./res/intro/181.bmp", "./res/intro/182.bmp", "./res/intro/183.bmp", "./res/intro/184.bmp", "./res/intro/185.bmp",
							"./res/intro/186.bmp", "./res/intro/87.bmp", "./res/intro/188.bmp", "./res/intro/189.bmp", "./res/intro/190.bmp",
							"./res/intro/191.bmp", "./res/intro/192.bmp", "./res/intro/193.bmp", "./res/intro/194.bmp", "./res/intro/195.bmp",
							"./res/intro/196.bmp", "./res/intro/197.bmp", "./res/intro/198.bmp", "./res/intro/199.bmp", "./res/intro/200.bmp",
							"./res/intro/201.bmp", "./res/intro/202.bmp", "./res/intro/203.bmp", "./res/intro/204.bmp", "./res/intro/205.bmp",
							"./res/intro/206.bmp", "./res/intro/207.bmp" };
		char* about_button[1] = { "./res/about.bmp" };
		char* about_pic[1] = { "./res/about_in.bmp" };
		char* about_back[1] = { "./res/back.bmp" };
		char* horses[12] = { "./res/horse/1.bmp", "./res/horse/2.bmp", "./res/horse/3.bmp", "./res/horse/4.bmp", "./res/horse/5.bmp",
							"./res/horse/6.bmp", "./res/horse/7.bmp", "./res/horse/8.bmp", "./res/horse/9.bmp", "./res/horse/10.bmp",
							"./res/horse/11.bmp", "./res/horse/12.bmp" };
		AddBitMaps(dad_back, 1, &dad, 0);
		AddBitMaps(hero_back, 1, &heroBack, 0);
		AddBitMaps(start_button, 1, &start, 0);
		AddBitMaps(start_hover, 17, &startHover, 0);
		AddBitMaps(intro_button, 1, &intro, 0);
		AddBitMaps(intro_hover, 14, &introHover, 0);
		AddBitMaps(intro_ani, 208, &introAni, 0);
		AddBitMaps(about_button, 1, &about, 0);
		AddBitMaps(about_pic, 1, &aboutPic, 0);
		AddBitMaps(about_back, 1, &back, 0);
		AddBitMaps(horses, 12, &horse, 0);
	}

	void CGameStateInit::LoadAudio()
	{
		CAudio::Instance()->Load(AUDIO_START, "Sounds\\start.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_DIED, "Sounds\\died.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_DIED_ANGEL, "Sounds\\died_angel.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_BGM, "Sounds\\gameBGM.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_PASS, "Sounds\\pass.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_ATTACKF1, "Sounds\\attack_F1.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_ATTACKF2, "Sounds\\attack_F2.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_ATTACKF3, "Sounds\\attack_F3.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_ATTACKF4, "Sounds\\attack_F4.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_ATTACKT1, "Sounds\\attack_T1.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_ATTACKT2, "Sounds\\attack_T2.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_ATTACKT3, "Sounds\\attack_T3.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_ATTACKT4, "Sounds\\attack_T4.wav");	// 載入編號0的聲音ding.wav
	}


	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame* g)
		: CGameState(g){}

	void CGameStateOver::OnMove()
	{
		if (!gameOver.IsFinalBitmap())
			gameOver.OnMove();
		else if (!isPlayAgainHover)
		{
			playAgain.OnMove();
		}
		else											 // 有hover
		{
			SetCursor(LoadCursor(NULL, IDC_HAND));
			playAgainHover.OnMove();
		}
		if (isRevived)
		{
			revived.OnMove();
		}

	}

	void CGameStateOver::OnBeginState()
	{
		isRevived = false;
		isPlayAgainHover = false;
		gameOver.Reset();
		CAudio::Instance()->Play(AUDIO_DIED, true);		// 撥放 WAVE

	}

	void CGameStateOver::OnInit()
	{
		ShowInitProgress(50);	// 接個前一個狀態的進度，此處進度視為66%
		LoadBitmap();
		ShowInitProgress(75);	// 接個前一個狀態的進度，此處進度視為66%

	}

	void CGameStateOver::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_Z = 0x5A;
		if (nChar == KEY_Z)
			isRevived = true;
	}
	void CGameStateOver::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
	}
	void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
	{
		long x = point.x;
		long y = point.y;
		if (x > 220 && x < 430 && y>220 && y < 280)
		{
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			isRevived = true;
		}
		if (x > 270 && x < 430 && y>280 && y < 320)
		{
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
		}
	}

	void CGameStateOver::OnMouseMove(UINT nFlags, CPoint point)
	{
		long x = point.x;
		long y = point.y;
		if (221 < x && x < 459 && 222 < y &&y < 270 && !isRevived)
			isPlayAgainHover = true;
		else
			isPlayAgainHover = false;
		if (271 < x && x < 459 && 280 < y &&y < 320 && !isRevived)
		SetCursor(LoadCursor(NULL, IDC_HAND));

	}

	void CGameStateOver::OnShow()
	{
		gameOver.SetTopLeft(-289, -204);
		gameOver.OnShow();
		if (isRevived)
		{
			revived.SetTopLeft(-289, -204);
			revived.OnShow();
			if(revived.GetCurrentBitmapNumber()==13)
				CAudio::Instance()->Play(AUDIO_ATTACKT1);

			if (revived.IsFinalBitmap())
			{
				CAudio::Instance()->Stop(AUDIO_DIED);	// 停止 WAVE
				CAudio::Instance()->Stop(AUDIO_DIED_ANGEL);	// 停止 WAVE
				CAudio::Instance()->Play(AUDIO_START);
				GotoGameState(GAME_STATE_INIT);
			}
		}
		if (gameOver.IsFinalBitmap() && !isRevived &&!isPlayAgainHover)
		{
			playAgain.SetTopLeft(220, 220);
			playAgain.OnShow();
		}
		if (gameOver.IsFinalBitmap() && !isRevived && isPlayAgainHover)
		{
			playAgainHover.SetTopLeft(220, 220);
			playAgainHover.OnShow();
		}
		if (gameOver.IsFinalBitmap() && !isRevived)
		{
			exit.SetTopLeft(270, 280);
			exit.ShowBitmap();
		}
		if(gameOver.GetCurrentBitmapNumber()==54)
			CAudio::Instance()->Play(AUDIO_DIED_ANGEL, false);		// 撥放 WAVE

	}
	void CGameStateOver::AddBitMaps(char * pic[], int space, CAnimation* ani,int color)
	{
		for (int i = 0; i < space; i++)
		{
			if(color==0)
				ani->AddBitmap(pic[i], RGB(204, 204, 204));
			else if(color==1)
				ani->AddBitmap(pic[i],RGB(255,255,255));
		}
	}
	void CGameStateOver::LoadBitmap()
	{
		char* game_over[100] = { "./res/gameover/1.bmp","./res/gameover/2.bmp","./res/gameover/3.bmp","./res/gameover/4.bmp","./res/gameover/5.bmp" ,
							"./res/gameover/6.bmp","./res/gameover/7.bmp","./res/gameover/8.bmp","./res/gameover/9.bmp","./res/gameover/10.bmp",
							"./res/gameover/11.bmp","./res/gameover/12.bmp" ,"./res/gameover/13.bmp","./res/gameover/14.bmp","./res/gameover/15.bmp",
							"./res/gameover/16.bmp","./res/gameover/17.bmp","./res/gameover/18.bmp","./res/gameover/19.bmp","./res/gameover/20.bmp" ,
							"./res/gameover/21.bmp","./res/gameover/22.bmp","./res/gameover/23.bmp","./res/gameover/24.bmp","./res/gameover/25.bmp",
							"./res/gameover/26.bmp","./res/gameover/27.bmp" ,"./res/gameover/28.bmp","./res/gameover/29.bmp","./res/gameover/30.bmp" ,
							"./res/gameover/31.bmp","./res/gameover/32.bmp","./res/gameover/33.bmp","./res/gameover/34.bmp","./res/gameover/35.bmp" ,
							"./res/gameover/36.bmp","./res/gameover/37.bmp","./res/gameover/38.bmp","./res/gameover/39.bmp","./res/gameover/40.bmp",
							"./res/gameover/41.bmp","./res/gameover/42.bmp" ,"./res/gameover/43.bmp","./res/gameover/44.bmp","./res/gameover/45.bmp",
							"./res/gameover/46.bmp","./res/gameover/47.bmp","./res/gameover/48.bmp","./res/gameover/49.bmp","./res/gameover/50.bmp" ,
							"./res/gameover/51.bmp","./res/gameover/52.bmp","./res/gameover/53.bmp","./res/gameover/54.bmp","./res/gameover/55.bmp",
							"./res/gameover/56.bmp","./res/gameover/57.bmp" ,"./res/gameover/58.bmp","./res/gameover/59.bmp","./res/gameover/60.bmp",
							"./res/gameover/61.bmp","./res/gameover/62.bmp","./res/gameover/63.bmp","./res/gameover/64.bmp","./res/gameover/65.bmp" ,
							"./res/gameover/66.bmp","./res/gameover/67.bmp","./res/gameover/68.bmp","./res/gameover/69.bmp","./res/gameover/70.bmp",
							"./res/gameover/71.bmp","./res/gameover/72.bmp" ,"./res/gameover/73.bmp","./res/gameover/74.bmp","./res/gameover/75.bmp",
							"./res/gameover/76.bmp","./res/gameover/77.bmp","./res/gameover/78.bmp","./res/gameover/79.bmp","./res/gameover/80.bmp" ,
							"./res/gameover/81.bmp","./res/gameover/82.bmp","./res/gameover/83.bmp","./res/gameover/84.bmp","./res/gameover/85.bmp",
							"./res/gameover/86.bmp","./res/gameover/87.bmp" ,"./res/gameover/88.bmp","./res/gameover/89.bmp","./res/gameover/90.bmp",
							"./res/gameover/91.bmp","./res/gameover/92.bmp","./res/gameover/93.bmp","./res/gameover/94.bmp","./res/gameover/95.bmp",
							"./res/gameover/96.bmp", "./res/gameover/97.bmp","./res/gameover/98.bmp","./res/gameover/99.bmp","./res/gameover/100.bmp" };

		char* revive[71] = { "./res/gameover/120.bmp","./res/gameover/121.bmp","./res/gameover/122.bmp","./res/gameover/123.bmp","./res/gameover/124.bmp","./res/gameover/125.bmp" ,
							"./res/gameover/126.bmp","./res/gameover/127.bmp","./res/gameover/128.bmp","./res/gameover/129.bmp","./res/gameover/130.bmp",
							"./res/gameover/131.bmp","./res/gameover/132.bmp" ,"./res/gameover/133.bmp","./res/gameover/134.bmp","./res/gameover/135.bmp",
							"./res/gameover/136.bmp","./res/gameover/137.bmp","./res/gameover/138.bmp","./res/gameover/139.bmp","./res/gameover/140.bmp" ,
							"./res/gameover/141.bmp","./res/gameover/142.bmp","./res/gameover/143.bmp","./res/gameover/144.bmp","./res/gameover/145.bmp",
							"./res/gameover/146.bmp","./res/gameover/147.bmp" ,"./res/gameover/148.bmp","./res/gameover/149.bmp","./res/gameover/150.bmp" ,
							"./res/gameover/151.bmp","./res/gameover/152.bmp","./res/gameover/153.bmp","./res/gameover/154.bmp","./res/gameover/155.bmp" ,
							"./res/gameover/156.bmp","./res/gameover/157.bmp","./res/gameover/158.bmp","./res/gameover/159.bmp","./res/gameover/160.bmp",
							"./res/gameover/161.bmp","./res/gameover/162.bmp" ,"./res/gameover/163.bmp","./res/gameover/164.bmp","./res/gameover/165.bmp",
							"./res/gameover/166.bmp","./res/gameover/167.bmp","./res/gameover/168.bmp","./res/gameover/169.bmp","./res/gameover/170.bmp" ,
							"./res/gameover/171.bmp","./res/gameover/172.bmp","./res/gameover/173.bmp","./res/gameover/174.bmp","./res/gameover/175.bmp",
							"./res/gameover/176.bmp","./res/gameover/177.bmp" ,"./res/gameover/178.bmp","./res/gameover/179.bmp","./res/gameover/180.bmp",
							"./res/gameover/181.bmp","./res/gameover/182.bmp","./res/gameover/183.bmp","./res/gameover/184.bmp" ,"./res/gameover/185.bmp",
							"./res/gameover/186.bmp","./res/gameover/187.bmp","./res/gameover/188.bmp","./res/gameover/189.bmp","./res/gameover/190.bmp" };

		char* paly_again[13] = { "./res/PlayAgain/1.bmp","./res/PlayAgain/2.bmp","./res/PlayAgain/3.bmp","./res/PlayAgain/4.bmp","./res/PlayAgain/5.bmp",
							"./res/PlayAgain/6.bmp","./res/PlayAgain/7.bmp","./res/PlayAgain/8.bmp","./res/PlayAgain/9.bmp","./res/PlayAgain/10.bmp",
							"./res/PlayAgain/11.bmp","./res/PlayAgain/12.bmp","./res/PlayAgain/13.bmp" };

		char* paly_again_hover[12] = { "./res/PlayAgainHover/1.bmp","./res/PlayAgainHover/2.bmp","./res/PlayAgain/3.bmp","./res/PlayAgainHover/4.bmp","./res/PlayAgainHover/5.bmp",
							"./res/PlayAgainHover/6.bmp","./res/PlayAgainHover/7.bmp","./res/PlayAgainHover/8.bmp","./res/PlayAgainHover/9.bmp","./res/PlayAgainHover/10.bmp",
							"./res/PlayAgainHover/11.bmp","./res/PlayAgainHover/12.bmp" };
		
		AddBitMaps(game_over, 100, &gameOver, 0);
		AddBitMaps(revive, 71, &revived, 0);
		AddBitMaps(paly_again, 13, &playAgain, 0);
		AddBitMaps(paly_again_hover, 12, &playAgainHover, 0);
		exit.LoadBitmap("./res/exit.bmp", RGB(204, 204, 204));
	}
	
	/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Pass)
/////////////////////////////////////////////////////////////////////////////

	CGameStatePass::CGameStatePass(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStatePass::OnMove()
	{

		if (!isPlayAgainHover)
		{
			playAgain.OnMove();
		}
		else											 // 有hover
		{
			SetCursor(LoadCursor(NULL, IDC_HAND));
			playAgainHover.OnMove();
		}

		if (isExitHover)
			SetCursor(LoadCursor(NULL, IDC_HAND));

	}

	void CGameStatePass::OnBeginState()
	{
		isPlayAgainHover = false;
		isExitHover = false;
		CAudio::Instance()->Play(AUDIO_DIED, true);		// 撥放 WAVE

	}

	void CGameStatePass::OnInit()
	{
		ShowInitProgress(75);	// 接個前一個狀態的進度，此處進度視為66%
		LoadBitmap();
		ShowInitProgress(100);	// 接個前一個狀態的進度，此處進度視為66%

	}

	void CGameStatePass::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{

	}
	void CGameStatePass::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{

	}
	void CGameStatePass::OnLButtonDown(UINT nFlags, CPoint point)
	{
		long x = point.x;
		long y = point.y;
		if (381 < x && x < 620 && 381 < y &&y < 430)
		{
			CAudio::Instance()->Stop(AUDIO_DIED);		// 撥放 WAVE
			GotoGameState(GAME_STATE_INIT);
		}
		if (460 < x && x < 550 && 436 < y && y < 486)
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
	}

	void CGameStatePass::OnMouseMove(UINT nFlags, CPoint point)
	{
		long x = point.x;
		long y = point.y;
		if (381 < x && x < 620 && 381 < y &&y < 430)
			isPlayAgainHover = true;
		else
			isPlayAgainHover = false;
		if (460 < x && x < 550 && 436 < y && y < 486)
			isExitHover = true;
		else
			isExitHover = false;
	}

	void CGameStatePass::OnShow()
	{
		passBack.SetTopLeft(0, 0);
		passBack.OnShow();
		win.SetTopLeft(250, 50);
		win.OnShow();
		if (heroY > 220)
		{
			heroY -= 13;
		}
		else if (carX < 120)
		{
			carX += 20;
			drive.SetTopLeft(carX, 190);
			drive.OnShow();
		}
		else
		{
			car.OnMove();
			car.SetTopLeft(carX, 190);
			car.OnShow();
			Sleep(50);
		}

		passHero.SetTopLeft(5, heroY);
		passHero.OnShow();
		playAgain.SetTopLeft(380, 380);
		playAgain.OnShow();
		exit.SetTopLeft(450, 430);
		exit.OnShow();

		if (isPlayAgainHover)
		{
			playAgainHover.SetTopLeft(380, 380);
			playAgainHover.OnShow();
		}
	}
	void CGameStatePass::AddBitMaps(char * pic[], int space, CAnimation* ani, int color)
	{
		for (int i = 0; i < space; i++)
		{
			if (color == 0)
				ani->AddBitmap(pic[i], RGB(204, 204, 204));
			else if (color == 1)
				ani->AddBitmap(pic[i], RGB(255, 255, 255));
		}
	}
	void CGameStatePass::LoadBitmap()
	{
		char* pass_back[1] = { "./res/PassBack.bmp" };

		char* pass_hero[1] = { "./res/PassHero.bmp" };

		char* pass_drive[1] = { "./res/Drive.bmp" };

		char* pass_car[3] = { "./res/Car/2.bmp", "./res/Car/3.bmp", "./res/Car/4.bmp" };

		char* pass_win[1] = { "./res/win.bmp" };

		char* pass_exit[1] = { "./res/exit.bmp" };

		char* paly_again[13] = { "./res/PlayAgain/1.bmp","./res/PlayAgain/2.bmp","./res/PlayAgain/3.bmp","./res/PlayAgain/4.bmp","./res/PlayAgain/5.bmp",
							"./res/PlayAgain/6.bmp","./res/PlayAgain/7.bmp","./res/PlayAgain/8.bmp","./res/PlayAgain/9.bmp","./res/PlayAgain/10.bmp",
							"./res/PlayAgain/11.bmp","./res/PlayAgain/12.bmp","./res/PlayAgain/13.bmp" };

		char* paly_again_hover[12] = { "./res/PlayAgainHover/1.bmp","./res/PlayAgainHover/2.bmp","./res/PlayAgain/3.bmp","./res/PlayAgainHover/4.bmp","./res/PlayAgainHover/5.bmp",
							"./res/PlayAgainHover/6.bmp","./res/PlayAgainHover/7.bmp","./res/PlayAgainHover/8.bmp","./res/PlayAgainHover/9.bmp","./res/PlayAgainHover/10.bmp",
							"./res/PlayAgainHover/11.bmp","./res/PlayAgainHover/12.bmp" };

		AddBitMaps(pass_back, 1, &passBack, 0);
		AddBitMaps(pass_hero, 1, &passHero, 0);
		AddBitMaps(pass_drive, 1, &drive, 0);
		AddBitMaps(pass_car, 3, &car, 0);
		AddBitMaps(pass_win, 1, &win, 0);
		AddBitMaps(pass_exit, 1, &exit, 0);
		AddBitMaps(paly_again, 13, &playAgain, 0);
		AddBitMaps(paly_again_hover, 12, &playAgainHover, 0);

	}
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame* g)
		: CGameState(g), NUMBALLS(5), BULLETS(10)
	{
		smallPerson = new CSmallPerson [NUMBALLS];
		bulletCount = 0;
		round = 1;
	}

	CGameStateRun::~CGameStateRun()
	{
		delete [] smallPerson;
	}

	void CGameStateRun::OnBeginState()
	{
		hero.Initialize();
		hero.OnInit();
		boss.Initialize();
		boss.OnInit();
		gamemap.Initialize();
		round = 1;
		for (int i = 0; i < BULLETS; i++)
			bullet[i].Initialize();
		for (int i = 0; i < NUMBALLS; i++)
		{		
			if (i < 3)
			{
				smallPerson[i].SetXY(300 + i * 400, 240 + i * 10);
			}
			else
			{
				smallPerson[i].SetXY(2500 + i * 100, 240 + i * 10);
			}

			smallPerson[i].Initialize();
			smallPerson[i].OnInit();
			smallPerson[i].smallChoose = i;
		}
		for (int i = 3; i < NUMBALLS; i++)
		{
			smallPerson[i].SetIsAlive(false);
		}
		boss.SetIsAlive(false);
		CAudio::Instance()->Play(AUDIO_BGM, true);
	}

	void CGameStateRun::Transitions()
	{
		hero.SetHeroState(HERO_STATE_RUN);
		hero.SetMovingRight(true);
		gamemap.SetMovingRight(true);
		hero.SetMovingDown(false);
		hero.SetMovingLeft(false);
		hero.SetMovingUp(false);
		gamemap.SetMovingDown(false);
		gamemap.SetMovingLeft(false);
		gamemap.SetMovingUp(false);
	}


	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		//
		// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
		//
		// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));

		int countFalse = 0;

		//////////////////	hero 抓小人	////////////////////////
		
		for (int i = 0; i < NUMBALLS; i++)
		{
			if (smallPerson[i].IsAlive() && hero.HitSmallPerson(&smallPerson[i]))
			{
				if (!hero.GetIsCatch() && !smallPerson[i].GetIsAttack())
				{
					hero.SetHeroState(HERO_STATE_CATCH);
					smallPerson[i].SetSmallPersonState(S_STATE_BECATCHED);
				}
			}
		}
		for (int i = 0; i < NUMBALLS; i++)
		{
			if (!smallPerson[i].GetIsBeCatched())
				countFalse++;
		}
		TRACE("countFalse = %d \n", countFalse);
		if (countFalse == NUMBALLS)
		{
			hero.SetIsCatch(false);
		}
		else 
			hero.SetIsCatch(true);

		////////////////////////	小人攻擊	////////////////////
		if (smallPerson[0].IsAlive() && !smallPerson[0].GetIsBeCatched())
		{
			if (((smallPerson[0].GetX1() > hero.GetX1()) && !smallPerson[0].GetDirectionStay()) || ((smallPerson[0].GetX2() < hero.GetX1()) && smallPerson[0].GetDirectionStay()))
			{
				smallPerson[0].SetAttack(&hero);
			}
		}
		////////////////////	Boss 攻擊	///////////////////////
		if (boss.IsAlive() && !hero.GetIsCatch())
		{
			if ((boss.GetX1() > hero.GetX1()) && !boss.GetDirectionStay() && hero.GetDirectionStay())   // hero 面右	boss 面左
			{
				boss.SetAttack(&hero);
			}
			else if ((boss.GetX2() < hero.GetX1()) && boss.GetDirectionStay() && !hero.GetDirectionStay())	// boss 面右   hero面左
			{
				boss.SetAttack(&hero);
			}
			if (boss.GetIsAttack())
			{
				//boss.ResetAttack();
				hero.SetIsBeAttackedBoss(true);
				hero.SetHeroState(HERO_STATE_BEATTACKED);
			}
		}
		////////////////////	子彈	//////////////////////////
		if (smallPerson[0].GetIsAttack())
		{
			if (smallPerson[0].GetIsDirectionStay() )
			{
				if (smallPerson[0].GetAni(SATTACKR) == 15)
				{
					bullet[bulletCount].SetIsAlive(true);
					bullet[bulletCount].SetIsDirectionStay(true);
					bullet[bulletCount].SetXY(smallPerson[0].GetX2(), smallPerson[0].GetY1());
					bulletCount++;
				}
			}
			else
			{
				if (smallPerson[0].GetAni(SATTACKL) == 15)
				{
					bullet[bulletCount].SetIsAlive(true);
					bullet[bulletCount].SetIsDirectionStay(false);
					bullet[bulletCount].SetXY(smallPerson[0].GetX1(), smallPerson[0].GetY1());
					bulletCount++;

				}
			}
			for (int i = 0; i < bulletCount; i++)
			{
				if (gamemap.ScreenX(bullet[i].GetX1()) < 50 || gamemap.ScreenX(bullet[i].GetX2()) > 750)
				{
					bullet[i].SetIsAlive(false);
				}
			}
			if (bulletCount == 9)
			{
				bulletCount = 0;
			}
		}
		for (int i = 0; i < BULLETS; i++)
		{
			if (bullet[i].GetIsAlive())
			{
				bullet[i].OnMove(&gamemap, &smallPerson[0]);
				if (bullet[i].GetX1() < hero.GetX2() && bullet[i].GetX1() > hero.GetX1() && bullet[i].GetY1()+20 > hero.GetY1() && bullet[i].GetY2() < hero.GetY2()) {
					hero.SetIsBeAttacked(true);
					hero.SetHeroState(HERO_STATE_BEATTACKED);
					bullet[i].SetIsAlive(false);
				}
				else if (bullet[i].GetX2() < hero.GetX2() && bullet[i].GetX2() > hero.GetX1() && bullet[i].GetY1()+20 > hero.GetY1() && bullet[i].GetY2() < hero.GetY2()) {
					hero.SetIsBeAttacked(true);
					hero.SetHeroState(HERO_STATE_BEATTACKED);
					bullet[i].SetIsAlive(false);
				}
			}
		}
		for (int i = 0; i < BULLETS; i++)
		{
			if (bullet[i].GetIsAlive())
			{
				bullet[i].OnMove(&gamemap, &smallPerson[0]);
			}
		}
		
		
		for (int i = 0; i < NUMBALLS; i++)
		{
			smallPerson[i].OnMove(&gamemap);
		}
		hero.OnMove(&gamemap);
		boss.OnMove(&gamemap);
		///////		Hero死亡	///////////
		if (!hero.GetIsAlive())
		{
			CAudio::Instance()->Stop(AUDIO_BGM);	// 停止 WAVE
			GotoGameState(GAME_STATE_OVER);
		}
		///////		過關		///////////
		if (round == 2 && !boss.GetIsAlive())
		{
			round = 1;
			CAudio::Instance()->Stop(AUDIO_BGM);	// 停止 WAVE
			GotoGameState(GAME_STATE_PASS);
		}
		/////// 移動到下一關   ///////////
		int dead = 0;
		for (int i = 0; i < NUMBALLS; i++)
		{
			if (!smallPerson[i].IsAlive())
				dead++;
		}
		TRACE("dead = %d\n", dead);
		if (dead == NUMBALLS && round<2)
		{
			Transitions();
			gamemap.SetIsPass(true);
			if (hero.GetY2() > 420)
			{
				hero.SetMovingUp(true);
				hero.SetMovingRight(false);
				hero.SetMovingDown(false);
				hero.SetMovingLeft(false);
				gamemap.SetMovingDown(false);
				gamemap.SetMovingLeft(false);
				gamemap.SetMovingRight(false);
				gamemap.SetMovingUp(true);
			}
				
			else if (hero.GetY2() < 400)
			{
				hero.SetMovingUp(false);
				hero.SetMovingRight(false);
				hero.SetMovingDown(true);
				hero.SetMovingLeft(false);
				gamemap.SetMovingDown(true);
				gamemap.SetMovingLeft(false);
				gamemap.SetMovingRight(false);
				gamemap.SetMovingUp(false);
			}
			else if (hero.GetX2() > 2200)
			{
				hero.SetMovingRight(false);
				gamemap.SetMovingRight(false);
				hero.SetHeroState(HERO_STATE_STAY);
				for (int i = 3; i < NUMBALLS; i++)
				{					
					smallPerson[i].SetIsAlive(true);
				}
				boss.SetIsAlive(true);
				round++;
				gamemap.SetRoundMap(round);
				gamemap.SetIsPass(false);
			}
			
		}
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(25);	// 接個前一個狀態的進度，此處進度視為33%
		//
		// 開始載入資料
		//
		hero.LoadBitmap();
		hero.OnInitState();
		hero.OnInit();
		boss.LoadBitmap();
		boss.OnInitState();
		boss.OnInit();
		for (int i = 0; i < NUMBALLS; i++)
		{
			smallPerson[i].LoadBitmap();
			smallPerson[i].OnInitState();
			smallPerson[i].OnInit();
		}
		for (int i = 0; i < BULLETS; i++)
			bullet[i].LoadBitmap();
		gamemap.LoadBitmap();


		//
		// 完成部分Loading動作，提高進度
		//
		ShowInitProgress(50);
		Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep

		// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭

		const char KEY_A = 0x41;											// keyboard A
		const char KEY_S = 0x53;
		const char KEY_Q = 0x51;
		const char KEY_D = 0x68;

		if (nChar == KEY_Q)
		{
			CAudio::Instance()->Stop(AUDIO_BGM);	// 停止 WAVE

			GotoGameState(GAME_STATE_OVER);

		}

		if ((nChar == KEY_LEFT || nChar == KEY_UP || nChar == KEY_RIGHT || nChar == KEY_DOWN))
		{
			hero.SetHeroState(HERO_STATE_RUN);
			hero.OnKeyDown(nChar);
		}
		if (hero.GetIsCatch())
		{
			hero.SetHeroState(HERO_STATE_CATCH);
			hero.OnKeyDown(nChar);
		}
		if (nChar == KEY_A || nChar == KEY_S)
		{
			hero.ResetAttack();
			hero.SetHeroState(HERO_STATE_ATTACK);
			for (int i = 0; i < NUMBALLS; i++)
			{
					hero.AttackSmallPerson(&smallPerson[i]);
					hero.OnKeyDown(nChar);
					smallPerson[i].ResetAttack();
				if (smallPerson[i].GetIsBeCatched() || smallPerson[i].GetIsBeAttacked())
				{
					smallPerson[i].SetSmallPersonState(S_STATE_BEATTACKED);
					smallPerson[i].OnKeyDown(nChar);
				}

			}
			hero.AttackBoss(&boss);
			hero.OnKeyDown(nChar);
			boss.ResetAttack();
			if (boss.GetIsBeAttacked())
			{
				boss.SetBossState(BOSS_STATE_BEATTACKED);
				boss.OnKeyDown(nChar);
			}
		}
		
	if (nChar == KEY_LEFT)
    {
        gamemap.SetMovingLeft(true);
    }

    if (nChar == KEY_RIGHT)
    {
        gamemap.SetMovingRight(true);
	}

    if (nChar == KEY_UP)
    {
        gamemap.SetMovingUp(true);
    }

    if (nChar == KEY_DOWN)
    {
        gamemap.SetMovingDown(true);
    }
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT = 0x25; // keyboard左箭頭
    const char KEY_UP = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN = 0x28; // keyboard下箭頭
	const char KEY_A = 0x41;											// keyboard A
	const char KEY_S = 0x53;											// keyboard s
	if (hero.GetIsCatch() && !hero.GetIsAttack())
	{
		hero.OnKeyUp(nChar);
	}
	if (nChar == KEY_LEFT || nChar == KEY_UP || nChar == KEY_RIGHT || nChar == KEY_DOWN)
	{
		hero.OnKeyUp(nChar);
	}
	for (int i = 0; i < NUMBALLS; i++)
	{
		smallPerson[i].OnKeyUp(nChar);
	}
	boss.OnKeyUp(nChar);
    if (nChar == KEY_LEFT)
    {
        gamemap.SetMovingLeft(false);
    }

    if (nChar == KEY_RIGHT)
    {
        gamemap.SetMovingRight(false);
    }

    if (nChar == KEY_UP)
    {
        gamemap.SetMovingUp(false);
    }

    if (nChar == KEY_DOWN)
    {
        gamemap.SetMovingDown(false); 
    }
}

void CGameStateRun::OnShow()
{	
    gamemap.OnShow();

	for (int i = 0; i < NUMBALLS; i++)
	{
		smallPerson[i].SetSmallPersonAni(SRUNRIGHT);
		if (smallPerson[i].GetY1() < hero.GetY1() && !smallPerson[i].GetIsBeCatched())
		{
			smallPerson[i].OnShow(&gamemap, &hero);
			for (int j = 0; j < BULLETS; j++)
			{
				if (bullet[j].GetIsAlive())
					bullet[j].OnShow(&gamemap);
			}
		}
	}
	if (boss.GetY1() < hero.GetY1())
		boss.OnShow(&gamemap, &hero);
	hero.OnShow(&gamemap);

	if (boss.GetY1() >= hero.GetY1())
		boss.OnShow(&gamemap, &hero);

	for (int i = 0; i < NUMBALLS; i++)
	{
		smallPerson[i].SetSmallPersonAni(SRUNRIGHT);
		if (smallPerson[i].GetY1() >= hero.GetY1() || smallPerson[i].GetIsBeCatched())
		{
			smallPerson[i].OnShow(&gamemap, &hero);
			for (int j = 0; j < BULLETS; j++)
			{
				if (bullet[j].GetIsAlive())
					bullet[j].OnShow(&gamemap);
			}
		}
		
	}
	
	CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
	CFont f, *fp;
	f.CreatePointFont(90, "Times New Roman");	// 產生 font f; 160表示16 point的字
	fp = pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0, 0, 0));
	pDC->SetTextColor(RGB(255, 255, 0));
	char str[200];
	sprintf(str, "x1 = %d, y1 = %d, x2 = %d, y2 = %d, State = %d \n x1 = %d, y1 = %d, x2 = %d, y2 = %d, State = %d", hero.GetX1(), hero.GetY1(), hero.GetX2(), hero.GetY2(), hero.GetHeroState(), boss.GetX1(), boss.GetY1(), boss.GetX2(), boss.GetY2(), gamemap.GetSX());
	pDC->TextOut(5, 440,str );

	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC

}

CGamemap::CGamemap() : sx(130), sy(80), ROW(8), COL(10), MW(795)
{
	int map_init[4] = { 0, 1, 2, 3 };
    isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;

    for (int i = 0; i < 4; i++)
    {
        map[i] = map_init[i];
    }
}
void CGamemap::LoadBitmap()
{
    map0.LoadBitmap(IDB_MAP0);
    map1.LoadBitmap(IDB_MAP1);
	map2.LoadBitmap("./res/map3.bmp");
	map3.LoadBitmap("./res/map4.bmp");

}
void CGamemap::Initialize()
{
	sx = 130;
	sy = 80;
	roundMap = 1;
	isPass = false;
}
void CGamemap::SetSX()
{
	const int moveX_Pass=7;
	const int moveX = 5;
	if (roundMap == 1 && !isPass)				//第一關
	{
		if (isMovingLeft && sx > 5)
			sx -= moveX;
		
		if (isMovingRight && sx<950)
			sx += moveX;
	}
	else if (roundMap == 2 || isPass)			// 第二關 + 過場
	{
		if (isMovingLeft && sx > 1600)
			sx -= moveX;
		else if (isMovingRight && sx < 2500)
		{
			if (!isPass)
				sx += moveX;
			else
				sx += moveX_Pass;				// 過場速度變快
		}
	}
}
void CGamemap::SetSY()
{
    if (isMovingUp && sy > 50)
        sy -= 2;
    else if (isMovingDown && sy < 100)
        sy += 2;
}
bool CGamemap::IsEmpty(int x, int y)
{
    int gx, gy;
    if (x < 800)
    {
		int checkmap[8][10] = { {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 1, 1,1, 1, 1},
								{0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                check[i][j] = checkmap[i][j];
            }
        }

        gx = (x) / 80;
        gy = (y) / 75;
    }
    else if (x >= 800 && x < 1600)
    {
        int checkmap1[8][10] = { {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
								{0, 0, 0, 1, 1, 1, 1, 1, 1, 1} };

        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                check[i][j] = checkmap1[i][j];
            }
        }

        gx = (x - 800) / 80;
        gy = (y) / 75;
    }
	else if (x >= 1600 && x < 2400)
	{
		int checkmap1[8][10] = { {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 1, 1,1, 1, 1},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, };

		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				check[i][j] = checkmap1[i][j];
			}
		}

		gx = (x - 1600) / 80;
		gy = (y) / 75;
	}
	else if (x >= 2400 && x < 3200)
	{
		int checkmap1[8][10] = { {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 1, 1,1, 1, 1},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, };

		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				check[i][j] = checkmap1[i][j];
			}
		}

		gx = (x - 2400) / 80;
		gy = (y) / 75;
	}
	else
        return 1;

    return check[gy][gx];
}
void CGamemap::OnShow()
{
    for (int i = 0; i < 4; i++)
    {
        int x = i * MW - sx;
        int y = i * 0 - sy;

        switch (map[i])
        {
            case 0:
                map0.SetTopLeft(x, y);
                map0.ShowBitmap();
                break;

            case 1:
                map1.SetTopLeft(x, y);
                map1.ShowBitmap();
                break;

			case 2:
				map2.SetTopLeft(x, y);
				map2.ShowBitmap();
				break;
			case 3:
				map3.SetTopLeft(x, y);
				map3.ShowBitmap();
				break;

            default:
                ASSERT(0);
        }
    }
}
void CGamemap::SetMovingDown(bool flag)
{
    isMovingDown = flag;
}
void CGamemap::SetMovingLeft(bool flag)
{
    isMovingLeft = flag;
}
void CGamemap::SetMovingRight(bool flag)
{
    isMovingRight = flag;
}
void CGamemap::SetMovingUp(bool flag)
{
    isMovingUp = flag;
}
void CGamemap::SetRoundMap(int round)
{
	roundMap = round;
}
int CGamemap::ScreenX(int x) // x 為地圖的點座標
{
    return x - sx; // 回傳螢幕的 x 點座標
}
int CGamemap::ScreenY(int y) // y 為地圖的 y 點座標
{
    return y - sy; // 回傳螢幕的點座標
}
int CGamemap::GetSX()
{
	return sx;
}
int CGamemap::GetSY()
{
	return sy;
}
int CGamemap::GetRoundMap()
{
	return roundMap;
}
bool CGamemap::GetIsPass()
{
	return isPass;
}
void CGamemap::SetIsPass(int pass)
{
	isPass = pass;
}
}



