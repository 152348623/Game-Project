#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBoss.h"
#include <time.h>
#include "CBoss.h"
#include "CBossState.h"
namespace game_framework
{

	/////////////////////////////////////////////////////////////////////////////
	// CBoss: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CBoss::CBoss()
	{
		Initialize();
		bossState = NULL;

	}

	void CBoss::OnInit()
	{
		bossState = bossStateTable[BOSS_STATE_RUN];
		bossState->OnBeginState();
		currentState = BOSS_STATE_RUN;
	}

	void CBoss::OnInitState()
	{
		bossStateTable[BOSS_STATE_RUN] = new CBossRunState(this);
		bossStateTable[BOSS_STATE_ATTACK] = new CBossAttackState(this);
		bossStateTable[BOSS_STATE_BEATTACKED] = new CBossBeAttackedState(this);

		for (int i = 0; i < BOSS_STATE_END; i++)
			bossStateTable[i]->OnInit();
	}

	int CBoss::GetX1()
	{
		return x;
	}

	int CBoss::GetY1()
	{
		return y;
	}

	int CBoss::GetX2()
	{
		return x + bossAction[currentAni]->Width();
	}

	int CBoss::GetY2()
	{
		return y + bossAction[currentAni]->Height();
	}
	bool CBoss::GetIsBeCatched()
	{
		return isBeCatched;
	}

	bool CBoss::GetIsBeAttacked()
	{
		return isBeAttacked;
	}

	bool CBoss::GetIsDirectionStay()
	{
		return directionStay;
	}

	bool CBoss::GetMovingDown()
	{
		return isMovingDown;
	}

	bool CBoss::GetMovingLeft()
	{
		return isMovingLeft;
	}

	bool CBoss::GetMovingRight()
	{
		return isMovingRight;
	}

	bool CBoss::GetMovingUp()
	{
		return isMovingUp;
	}

	bool CBoss::GetIsAttack()
	{
		return isAttack;
	}

	int CBoss::GetAni(int Ani)
	{
		return bossAction[Ani]->GetCurrentBitmapNumber();
	}

	bool CBoss::GetIsFinalAni()
	{
		return bossAction[currentAni]->IsFinalBitmap();
	}

	int CBoss::GetCurrentState()
	{
		return currentState;
	}

	bool CBoss::GetIsAlive()
	{
		return isAlive;
	}

	int CBoss::GetBlood()
	{
		return bloodPercent;
	}

	bool CBoss::GetDirectionStay()
	{
		return directionStay;
	}

	bool CBoss::IsAlive()
	{
		return isAlive;
	}

	void CBoss::SetIsAlive(bool Alive)
	{
		isAlive = Alive;
	}

	void CBoss::SetIsBeCatched(bool catched)
	{
		isBeCatched = catched;
	}

	void CBoss::SetIsAttack(bool attack)
	{
		isAttack = attack;
	}

	void CBoss::SetIsBeAttacked(bool attacked)
	{
		isBeAttacked = attacked;
	}

	void CBoss::SetDirectionStay(int stay)
	{
		directionStay = stay;
	}

	void CBoss::SetBloodPercent(int blood)
	{
		bloodPercent = blood;
	}

	bool CBoss::HitHero(CHero* hero)
	{
		return HitRectangle(hero->GetX1(), hero->GetY1(), hero->GetX2(), hero->GetY2());
	}

	bool CBoss::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;
		int y1 = y;
		int x2 = GetX2() + 10;
		int y2 = GetY2();
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	void CBoss::Initialize()
	{
		const int X_POS = 2500;
		const int Y_POS = 360;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isAttack = isBeCatched = false;
		directionStay = true;
		bloodPercent = 100;
		currentAni = B_RUNRIGHT;
		isAlive = true;
		int x_init[B_ACTION_END] = { 0,0,-40,-30,-40,-40,0,  0,  0,0,0,-30 };
		int y_init[B_ACTION_END] = { 0,0,-30,  0,-40,  0,0,-30,-30,0,0,-30 };

		for (int i = 0; i < B_ACTION_END; i++)
		{
			actionX[i] = x_init[i];
			actionY[i] = y_init[i];
		}
	}

	void CBoss::OnKeyDown(UINT nChar)
	{
		bossState->OnKeyDown(nChar);

	}
	void CBoss::OnKeyUp(UINT nChar)
	{
		bossState->OnKeyUp(nChar);
	}

	void CBoss::OnMove(CGamemap* m)
	{
		const int STEP_SIZE = 5;
		int space = bossAction.size();
		if (bloodPercent <= 0)
		{
			isAlive = false;
			isBeAttacked = isBeCatched = isMovingDown = isMovingLeft = isMovingRight = isMovingUp = false;

		}
		for (int i = 0; i < space; i++)
		{
			bossAction[i]->OnMove();
		}
		bossState->OnMoveState(m);

		if (currentState == BOSS_STATE_ATTACK)
		{
			for (int i = 10; i < 12; i++)
			{
				if (bossAction[i]->IsFinalBitmap() == true)
				{
					SetBossState(BOSS_STATE_RUN);
				}

			}
		}
	}

	void CBoss::SetAttack(CHero *h)
	{
		currentAni = B_RUNRIGHT;

		int bossDisX = (GetX2() + GetX1()) / 2;
		int heroDisX = (h->GetX2() + h->GetX1()) / 2;
		int bossDisY = (GetY2() + GetY1()) / 2;
		int heroDisY = (h->GetY2() + h->GetY1()) / 2;
		if (abs(bossDisX - heroDisX) < 200 && abs(bossDisY - heroDisY) < 20)
		{
			SetBossState(BOSS_STATE_ATTACK);
			//h->ResetAttackBoss();
		}
		
		/*else if (currentState != BOSS_STATE_RUN)
			SetBossState(BOSS_STATE_RUN);*/
	}
	void CBoss::StopAttack(UINT nChar)
	{

	}

	void CBoss::ResetAttack()
	{
		for (int i = 10; i < 12; i++)
			bossAction[i]->Reset();
	}

	void CBoss::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CBoss::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CBoss::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CBoss::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CBoss::SetXY(int nx, int ny)
	{
		x = nx;
		y = ny;
	}
	void CBoss::SetBlood(int blood)
	{
		bloodPercent -= blood;
	}
	void CBoss::SetBossState(int state)
	{
		currentState = state;
		bossState = bossStateTable[state];
		bossState->OnBeginState();

	}
	void CBoss::SetBossAni(int ani)
	{
		currentAni = ani;

	}
	void CBoss::OnShow(CGamemap* m, CHero* h)
	{
		if (isAlive)
		{
			bossState->OnShowState(m, h);
			bossAction[currentAni]->SetTopLeft(m->ScreenX(x + actionX[currentAni]), m->ScreenY(y + actionY[currentAni]));
			bossAction[currentAni]->OnShow();
			
			if ((isBeCatched || isBeAttacked) && bloodPercent >= 0)
			{
				blood.SetTopLeft(545, -10);
				blood.ShowBitmap();
				ShowBlood(bloodPercent);
			}

		}


	}
	void CBoss::AddBitMaps(char* pic[], const int space, int number)
	{
		bossAction.push_back(new CAnimation);

		for (int i = 0; i < number; i++)
		{
			bossAction[bossAction.size() - 1]->AddBitmap(pic[i]/*, RGB(204, 204, 204)*/);
		}
	}
	void CBoss::LoadBitMaps(char* pic[], int number, int choose)
	{
		

	}
	void CBoss::ShowBlood(int percent)
	{
		if (!SHOW_LOAD_PROGRESS)
			return;

		const int bar_width = blood.Width() - 28;
		const int bar_height = 16;
		const int x1 = 560;
		const int x2 = x1 + bar_width;
		const int y1 = bar_height + 85;
		const int y2 = y1 + bar_height;
		const int pen_width = bar_height / 8;
		const int progress_x1 = x1 + pen_width;
		const int progress_x2 = progress_x1 + percent * (bar_width - 2 * pen_width) / 100;
		const int progress_x2_end = x2 - pen_width;
		const int progress_y1 = y1 + pen_width;
		const int progress_y2 = y2 - pen_width;
		//
		// 以下為CDC的用法
		//
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CPen* pp, p(PS_NULL, 0, RGB(0, 0, 0));		// 清除pen
		pp = pDC->SelectObject(&p);
		CBrush* pb, b(RGB(0, 0, 0));				// 畫黑色 progress框
		pb = pDC->SelectObject(&b);
		pDC->Rectangle(x1, y1, x2, y2);
		CBrush b1(RGB(0, 0, 0));				// 畫黑色 progrss中心
		pDC->SelectObject(&b1);
		pDC->Rectangle(progress_x1, progress_y1, progress_x2_end, progress_y2);
		CBrush b2(RGB(255, 255, 0));					// 畫黃色 progrss進度
		pDC->SelectObject(&b2);
		pDC->Rectangle(progress_x1, progress_y1, progress_x2, progress_y2);
		pDC->SelectObject(pp);						// 釋放 pen
		pDC->SelectObject(pb);						// 釋放 brush
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	void CBoss::LoadBitmap()
	{
		///////////////////////////////////////////////////////////////////////

		char* right_run[8] = { "./res/BossRunR/1.bmp", "./res/BossRunR/2.bmp", "./res/BossRunR/3.bmp", "./res/BossRunR/4.bmp", "./res/BossRunR/5.bmp", "./res/BossRunR/6.bmp", "./res/BossRunR/7.bmp", "./res/BossRunR/8.bmp" };
		char* left_run[8] = { "./res/BossRunL/1.bmp", "./res/BossRunL/2.bmp", "./res/BossRunL/3.bmp", "./res/BossRunL/4.bmp", "./res/BossRunL/5.bmp", "./res/BossRunL/6.bmp", "./res/BossRunL/7.bmp", "./res/BossRunL/8.bmp" };
		char* left_beHit1[13] = { "./res/BossBeHitL/1.bmp","./res/BossBeHitL/2.bmp","./res/BossBeHitL/3.bmp", "./res/BossBeHitL/4.bmp", "./res/BossBeHitL/5.bmp", "./res/BossBeHitL/6.bmp", "./res/BossBeHitL/7.bmp",
								"./res/BossBeHitL/8.bmp", "./res/BossBeHitL/9.bmp", "./res/BossBeHitL/10.bmp", "./res/BossBeHitL/11.bmp","./res/BossBeHitL/12.bmp","./res/BossBeHitL/13.bmp" };
		char* left_beHit2[14] = { "./res/BossBeHitL/15.bmp", "./res/BossBeHitL/16.bmp", "./res/BossBeHitL/17.bmp","./res/BossBeHitL/18.bmp", "./res/BossBeHitL/19.bmp", "./res/BossBeHitL/20.bmp",
									"./res/BossBeHitL/21.bmp", "./res/BossBeHitL/22.bmp", "./res/BossBeHitL/23.bmp",  "./res/BossBeHitL/24.bmp", "./res/BossBeHitL/25.bmp",
									 "./res/BossBeHitL/26.bmp",  "./res/BossBeHitL/27.bmp",  "./res/BossBeHitL/28.bmp", };
		char* left_beHit3[16] = { "./res/BossBeHitL/29.bmp", "./res/BossBeHitL/30.bmp", "./res/BossBeHitL/31.bmp", "./res/BossBeHitL/32.bmp", "./res/BossBeHitL/33.bmp", "./res/BossBeHitL/34.bmp",
								"./res/BossBeHitL/35.bmp", "./res/BossBeHitL/36.bmp", "./res/BossBeHitL/37.bmp","./res/BossBeHitL/38.bmp", "./res/BossBeHitL/39.bmp", "./res/BossBeHitL/40.bmp",
								"./res/BossBeHitL/41.bmp", "./res/BossBeHitL/42.bmp", "./res/BossBeHitL/43.bmp", "./res/BossBeHitL/44.bmp" };
		char* left_beHit4[10] = { "./res/BossBeHitL/45.bmp", "./res/BossBeHitL/46.bmp", "./res/BossBeHitL/47.bmp", "./res/BossBeHitL/48.bmp", "./res/BossBeHitL/49.bmp", "./res/BossBeHitL/50.bmp",
									"./res/BossBeHitL/51.bmp", "./res/BossBeHitL/52.bmp", "./res/BossBeHitL/53.bmp", "./res/BossBeHitL/54.bmp" };
		char* right_beHit1[13] = { "./res/BossBeHitR/1.bmp","./res/BossBeHitR/2.bmp","./res/BossBeHitR/3.bmp", "./res/BossBeHitR/4.bmp", "./res/BossBeHitR/5.bmp", "./res/BossBeHitR/6.bmp", "./res/BossBeHitR/7.bmp", "./res/BossBeHitR/8.bmp",
								"./res/BossBeHitR/9.bmp", "./res/BossBeHitR/10.bmp", "./res/BossBeHitR/11.bmp","./res/BossBeHitR/12.bmp","./res/BossBeHitR/13.bmp" };
		char* right_beHit2[14] = { "./res/BossBeHitR/15.bmp", "./res/BossBeHitR/16.bmp", "./res/BossBeHitR/17.bmp","./res/BossBeHitR/18.bmp", "./res/BossBeHitR/19.bmp", "./res/BossBeHitR/20.bmp",
									"./res/BossBeHitR/21.bmp", "./res/BossBeHitR/22.bmp", "./res/BossBeHitR/23.bmp",  "./res/BossBeHitR/24.bmp", "./res/BossBeHitR/25.bmp",
									 "./res/BossBeHitR/26.bmp",  "./res/BossBeHitR/27.bmp",  "./res/BossBeHitR/28.bmp", };
		char* right_beHit3[16] = { "./res/BossBeHitR/29.bmp", "./res/BossBeHitR/30.bmp", "./res/BossBeHitR/31.bmp", "./res/BossBeHitR/32.bmp", "./res/BossBeHitR/33.bmp", "./res/BossBeHitR/34.bmp",
								"./res/BossBeHitR/35.bmp", "./res/BossBeHitR/36.bmp", "./res/BossBeHitR/37.bmp","./res/BossBeHitR/38.bmp", "./res/BossBeHitR/39.bmp", "./res/BossBeHitR/40.bmp",
								"./res/BossBeHitR/41.bmp", "./res/BossBeHitR/42.bmp", "./res/BossBeHitR/43.bmp", "./res/BossBeHitR/44.bmp" };
		char* right_beHit4[10] = { "./res/BossBeHitR/45.bmp", "./res/BossBeHitR/46.bmp", "./res/BossBeHitR/47.bmp", "./res/BossBeHitR/48.bmp", "./res/BossBeHitR/49.bmp", "./res/BossBeHitR/50.bmp",
									"./res/BossBeHitR/51.bmp", "./res/BossBeHitR/52.bmp", "./res/BossBeHitR/53.bmp", "./res/BossBeHitR/54.bmp" };
		char* right_attack[16] = { "./res/BossAttackR/1.bmp", "./res/BossAttackR/2.bmp",  "./res/BossAttackR/3.bmp",  "./res/BossAttackR/4.bmp",  "./res/BossAttackR/5.bmp",
									 "./res/BossAttackR/6.bmp",  "./res/BossAttackR/7.bmp",  "./res/BossAttackR/8.bmp",  "./res/BossAttackR/9.bmp",  "./res/BossAttackR/10.bmp",
									 "./res/BossAttackR/11.bmp",  "./res/BossAttackR/12.bmp",  "./res/BossAttackR/13.bmp",  "./res/BossAttackR/14.bmp",  "./res/BossAttackR/15.bmp",
									 "./res/BossAttackR/16.bmp" };
		char* left_attack[16] = { "./res/BossAttackL/1.bmp", "./res/BossAttackL/2.bmp",  "./res/BossAttackL/3.bmp",  "./res/BossAttackL/4.bmp",  "./res/BossAttackL/5.bmp",
								 "./res/BossAttackL/6.bmp",  "./res/BossAttackL/7.bmp",  "./res/BossAttackL/8.bmp",  "./res/BossAttackL/9.bmp",  "./res/BossAttackL/10.bmp",
								 "./res/BossAttackL/11.bmp",  "./res/BossAttackL/12.bmp",  "./res/BossAttackL/13.bmp",  "./res/BossAttackL/14.bmp",  "./res/BossAttackL/15.bmp",
								 "./res/BossAttackL/16.bmp",};

		AddBitMaps(right_run, B_RUNRIGHT, 8);
		AddBitMaps(left_run, B_RUNLEFT, 8);
		AddBitMaps(right_beHit1, B_BEHITR1, 13);
		AddBitMaps(right_beHit2, B_BEHITR2, 14);
		AddBitMaps(right_beHit3, B_BEHITR3, 16);
		AddBitMaps(right_beHit4, B_BEHITR4, 10);
		AddBitMaps(left_beHit1, B_BEHITL1, 13);
		AddBitMaps(left_beHit2, B_BEHITL2, 14);
		AddBitMaps(left_beHit3, B_BEHITL3, 16);
		AddBitMaps(left_beHit4, B_BEHITL4, 10);
		AddBitMaps(right_attack, B_ATTACKR, 16);
		AddBitMaps(left_attack, B_ATTACKL, 16);

		blood.LoadBitmap("./res/SmallBlood/1.bmp", RGB(204, 204, 204));
		
	}
	CBoss::~CBoss()
	{
		int space = bossAction.size();

		for (int i = 0; i < space; i++)
			delete bossAction[i];

		for (int i = 0; i < BOSS_STATE_END; i++)
			delete bossStateTable[i];
	}
}
