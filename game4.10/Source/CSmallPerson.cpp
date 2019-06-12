#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CSmallPerson.h"
#include <time.h>
#include "CHero.h"
#include "CSmallPersonState.h"
namespace game_framework
{

	/////////////////////////////////////////////////////////////////////////////
	// CSmallPerson: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CSmallPerson::CSmallPerson()
	{
		Initialize();
		smallState = NULL;
		
	}

	void CSmallPerson::OnInit()
	{
		smallState = smallStateTable[S_STATE_RUN];
		smallState->OnBeginState();
		currentState = S_STATE_RUN;
	}

	void CSmallPerson::OnInitState()
	{
		smallStateTable[S_STATE_RUN] = new CSmallPersonRunState(this);
		smallStateTable[S_STATE_ATTACK] = new CSmallPersonAttackState(this);
		smallStateTable[S_STATE_BEATTACKED] = new CSmallPersonBeAttackedState(this);
		smallStateTable[S_STATE_BECATCHED] = new CSmallPersonBeCatchedState(this);

		for (int i = 0; i < S_STATE_END; i++)
			smallStateTable[i]->OnInit();
	}

	int CSmallPerson::GetX1()
	{
		return x;
	}

	int CSmallPerson::GetY1()
	{
		return y;
	}

	int CSmallPerson::GetX2()
	{
		return x + smallAction[currentAni]->Width();
	}

	int CSmallPerson::GetY2()
	{
		return y + smallAction[currentAni]->Height();
	}
	bool CSmallPerson::GetIsBeCatched()
	{
		return isBeCatched;
	}

	bool CSmallPerson::GetIsBeAttacked()
	{
		return isBeAttacked;
	}

	bool CSmallPerson::GetIsDirectionStay()
	{
		return directionStay;
	}

	bool CSmallPerson::GetMovingDown()
	{
		return isMovingDown;
	}

	bool CSmallPerson::GetMovingLeft()
	{
		return isMovingLeft;
	}

	bool CSmallPerson::GetMovingRight()
	{
		return isMovingRight;
	}

	bool CSmallPerson::GetMovingUp()
	{
		return isMovingUp;
	}

	bool CSmallPerson::GetIsAttack()
	{
		return isAttack;
	}

	int CSmallPerson::GetAni(int Ani)
	{
		return smallAction[Ani]->GetCurrentBitmapNumber();
	}

	bool CSmallPerson::GetIsFinalAni()
	{
		return smallAction[currentAni]->IsFinalBitmap();
	}

	int CSmallPerson::GetCurrentState()
	{
		return currentState;
	}

	bool CSmallPerson::GetIsAlive()
	{
		return isAlive;
	}

	bool CSmallPerson::GetDirectionStay()
	{
		return directionStay;
	}

	bool CSmallPerson::IsAlive()
	{
		return isAlive;
	}

	void CSmallPerson::SetIsAlive(bool Alive)
	{
		isAlive = Alive;
	}

	void CSmallPerson::SetIsBeCatched(bool catched)
	{
		isBeCatched = catched;
	}

	void CSmallPerson::SetIsAttack(bool attack)
	{
		isAttack = attack;
	}

	void CSmallPerson::SetIsBeAttacked(bool attacked)
	{
		isBeAttacked = attacked;
	}

	void CSmallPerson::SetDirectionStay(int stay)
	{
		directionStay = stay;
	}

	void CSmallPerson::SetBloodPercent(int blood)
	{
		bloodPercent = blood;
	}

	bool CSmallPerson::HitHero(CHero* hero)
	{
		return HitRectangle(hero->GetX1(), hero->GetY1(), hero->GetX2(), hero->GetY2());
	}

	bool CSmallPerson::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;
		int y1 = y;
		int x2 = GetX2() + 10;
		int y2 = GetY2();
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	void CSmallPerson::Initialize()
	{
		/*const int X_POS = 700;
		const int Y_POS = 360;
		x = X_POS;
		y = Y_POS;*/
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isAttack = isBeCatched = false;
		directionStay = true;
		bloodPercent = 100;
		currentAni = SRUNRIGHT;
		isAlive = true;
		int x_init[SACTION_END] = { 0,0,70,-25,-100,-100,-100,-55,-145,-145,-145,-110,0,0,10,-150 };
		int y_init[SACTION_END] = { 0,0,-10,-15,-110,-110,-110,-115,-120,-120,-120,-125,0,0,0,0 };
		int clothesX_init[4] = {};
		int clothesY_init[4] = {};
		for (int i = 0; i < SACTION_END; i++)
		{
			actionX[i] = x_init[i];
			actionY[i] = y_init[i];
		}
		for (int i = 0; i < 4; i++)
		{
			clothesX[i] = clothesX_init[i];
			clothesY[i] = clothesY_init[i];
		}
	}

	void CSmallPerson::OnKeyDown(UINT nChar)
	{
		smallState->OnKeyDown(nChar);

	}
	void CSmallPerson::OnKeyUp(UINT nChar)
	{
		smallState->OnKeyUp(nChar);
		/*if (bloodPercent < 0)
		{
			isAlive = false;
			isBeAttacked = isBeCatched = isMovingDown = isMovingLeft = isMovingRight = isMovingUp = false;
		}*/

	}

	void CSmallPerson::OnMove(CGamemap* m)
	{
		const int STEP_SIZE = 5;
		int space = smallAction.size();
		if (bloodPercent <= 0)
		{
			isAlive = false;
			isBeAttacked = isBeCatched = isMovingDown = isMovingLeft = isMovingRight = isMovingUp = false;

		}
		for (int i = 0; i < space; i++)
		{
			smallAction[i]->OnMove();
		}
		smallState->OnMoveState(m);

		if (currentState == S_STATE_BEATTACKED)
		{
			for (int i = 4; i < 12; i++)
			{
				if (smallAction[i]->IsFinalBitmap() == true && !isBeCatched)
				{
					SetSmallPersonState(S_STATE_RUN);
				}
				else if (smallAction[i]->IsFinalBitmap() == true && !isBeCatched)
					SetSmallPersonState(S_STATE_BECATCHED);
			}
		}
	}

	void CSmallPerson::SetAttack(CHero *h)
	{
		currentAni = SRUNRIGHT;
		
		int smallDisX = (GetX2() + GetX1()) / 2;
		int heroDisX = (h->GetX2() + h->GetX1()) / 2;
		int smallDisY = (GetY2() + GetY1()) / 2;
		int heroDisY = (h->GetY2() + h->GetY1()) / 2;
		if (abs(smallDisX - heroDisX) < 400 && abs(smallDisY - heroDisY) < 10)
		{
			SetSmallPersonState(S_STATE_ATTACK);
		}
		else if(currentState!=S_STATE_RUN)
			SetSmallPersonState(S_STATE_RUN);		
	}
	void CSmallPerson::StopAttack(UINT nChar)
	{

	}

	void CSmallPerson::ResetAttack()
	{
		for (int i = 4; i < 12; i++)
			smallAction[i]->Reset();
	}

	void CSmallPerson::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CSmallPerson::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CSmallPerson::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CSmallPerson::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}


	void CSmallPerson::SetXY(int nx, int ny)
	{
		x = nx;
		y = ny;
	}
	void CSmallPerson::SetBlood(int blood)
	{
		bloodPercent -= blood;
	}
	void CSmallPerson::SetSmallPersonState(int state)
	{
		currentState = state;
		smallState = smallStateTable[state];
		smallState->OnBeginState();

	}
	void CSmallPerson::SetSmallPersonAni(int ani)
	{
		currentAni = ani;
		
	}

	void CSmallPerson::SetSmallPersonCloth(int)
	{

	}

	void CSmallPerson::OnShow(CGamemap* m, CHero* h)
	{
		if (isAlive)
		{
			smallState->OnShowState(m, h);
			smallAction[currentAni]->SetTopLeft(m->ScreenX(x + actionX[currentAni]), m->ScreenY(y + actionY[currentAni]));
			smallAction[currentAni]->OnShow();
			if (directionStay  &&!isAttack && !isBeCatched && !isBeAttacked)
			{
				if (smallAction[currentAni]->GetCurrentBitmapNumber()<5)
				{
					smallClothesR[smallChoose]->SetTopLeft(m->ScreenX(x+10), m->ScreenY(y+37));
					smallClothesR[smallChoose]->ShowBitmap();
				}
				else 
				{
					smallClothesR[smallChoose]->SetTopLeft(m->ScreenX(x + 10), m->ScreenY(y + 43));
					smallClothesR[smallChoose]->ShowBitmap();
				}
				
			}
			else if(!isAttack && !directionStay && !isBeCatched && !isBeAttacked)
			{
				if (smallAction[currentAni]->GetCurrentBitmapNumber() < 5)
				{
				smallClothesL[smallChoose]->SetTopLeft(m->ScreenX(x+3), m->ScreenY(y+35));
				smallClothesL[smallChoose]->ShowBitmap();
				}
				else
				{
				smallClothesL[smallChoose]->SetTopLeft(m->ScreenX(x + 3), m->ScreenY(y + 41));
				smallClothesL[smallChoose]->ShowBitmap();
				}
			}
			else if (isBeCatched && !isBeAttacked)
			{
				if (h->GetDirectionStay())
				{
					if (smallAction[currentAni]->GetCurrentBitmapNumber() > 3)
					{
						smallClothesL[smallChoose]->SetTopLeft(m->ScreenX(x + 71), m->ScreenY(y + 25));
						smallClothesL[smallChoose]->ShowBitmap();
					}
					else
					{
						smallClothesL[smallChoose]->SetTopLeft(m->ScreenX(x + 70), m->ScreenY(y + 25));
						smallClothesL[smallChoose]->ShowBitmap();
					}
				}
				else
				{
					if (smallAction[currentAni]->GetCurrentBitmapNumber() < 4)
					{
					smallClothesR[smallChoose]->SetTopLeft(m->ScreenX(x -28), m->ScreenY(y + 16));
					smallClothesR[smallChoose]->ShowBitmap();
					}
					else
					{
						smallClothesR[smallChoose]->SetTopLeft(m->ScreenX(x - 29), m->ScreenY(y + 16));
						smallClothesR[smallChoose]->ShowBitmap();
					}
				}
			}
			if ((isBeCatched || isBeAttacked ) && bloodPercent >= 0)
			{
				blood[smallChoose]->SetTopLeft(545, -10);
				blood[smallChoose]->ShowBitmap();
				ShowBlood(bloodPercent);
			}

		}


	}
	void CSmallPerson::AddBitMaps(char* pic[], const int space, int number)
	{
		smallAction.push_back(new CAnimation);

		for (int i = 0; i < number; i++)
		{
			smallAction[smallAction.size() - 1]->AddBitmap(pic[i], RGB(204, 204, 204));
		}
	}
	void CSmallPerson::LoadBitMaps(char* pic[], int number, int choose)
	{
		if (choose == 0)
		{
			for (int i = 0; i < number; i++)
			{
				smallClothesR.push_back(new CMovingBitmap);
				smallClothesR[smallClothesR.size() - 1]->LoadBitmap(pic[i], RGB(204, 204, 204));
			}
		}
		else if (choose == 1)
		{
			for (int i = 0; i < number; i++)
			{
				smallClothesL.push_back(new CMovingBitmap);
				smallClothesL[smallClothesL.size() - 1]->LoadBitmap(pic[i], RGB(204, 204, 204));
			}
		}
		else if (choose == 2)
		{
			for (int i = 0; i < number; i++)
			{
				blood.push_back(new CMovingBitmap);
				blood[blood.size() - 1]->LoadBitmap(pic[i], RGB(204, 204, 204));
			}
		}

	}
	void CSmallPerson::ShowBlood(int percent)
	{
		if (!SHOW_LOAD_PROGRESS)
			return;

		const int bar_width = blood[smallChoose]->Width() - 28;
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

	void CSmallPerson::LoadBitmap()
	{
		///////////////////////////////////////////////////////////////////////
		char* right_run[8] = { "./res/smallRunR/1.bmp", "./res/smallRunR/2.bmp", "./res/smallRunR/3.bmp", "./res/smallRunR/4.bmp", "./res/smallRunR/5.bmp", "./res/smallRunR/6.bmp", "./res/smallRunR/7.bmp", "./res/smallRunR/8.bmp" };
		char* left_run[8] = { "./res/smallRunL/1.bmp", "./res/smallRunL/2.bmp", "./res/smallRunL/3.bmp", "./res/smallRunL/4.bmp", "./res/smallRunL/5.bmp", "./res/smallRunL/6.bmp", "./res/smallRunL/7.bmp", "./res/smallRunL/8.bmp" };
		char* right_clothes[10] = { "./res/smallClothesR/2.bmp", "./res/smallClothesR/3.bmp","./res/smallClothesR/4.bmp","./res/smallClothesR/5.bmp",
									"./res/smallClothesR/6.bmp","./res/smallClothesR/7.bmp","./res/smallClothesR/8.bmp","./res/smallClothesR/9.bmp","./res/smallClothesR/10.bmp",
									"./res/smallClothesR/11.bmp" };
		char* left_clothes[10] = { "./res/smallClothesL/2.bmp", "./res/smallClothesL/3.bmp","./res/smallClothesL/4.bmp","./res/smallClothesL/5.bmp",
									"./res/smallClothesL/6.bmp","./res/smallClothesL/7.bmp","./res/smallClothesL/8.bmp","./res/smallClothesL/9.bmp","./res/smallClothesL/10.bmp",
									"./res/smallClothesL/11.bmp" };
		char* right_beCatched[14] = { "./res/beCatchedR/1.bmp", "./res/beCatchedR/2.bmp", "./res/beCatchedR/3.bmp", "./res/beCatchedR/4.bmp", "./res/beCatchedR/5.bmp",
									  "./res/beCatchedR/6.bmp", "./res/beCatchedR/7.bmp", "./res/beCatchedR/8.bmp", "./res/beCatchedR/9.bmp", "./res/beCatchedR/10.bmp",
									  "./res/beCatchedR/11.bmp", "./res/beCatchedR/12.bmp", "./res/beCatchedR/13.bmp", "./res/beCatchedR/14.bmp" };
		char* left_beCatched[14] = { "./res/beCatchedL/1.bmp", "./res/beCatchedL/2.bmp", "./res/beCatchedL/3.bmp", "./res/beCatchedL/4.bmp", "./res/beCatchedL/5.bmp",
									 "./res/beCatchedL/6.bmp", "./res/beCatchedL/7.bmp", "./res/beCatchedL/8.bmp", "./res/beCatchedL/9.bmp", "./res/beCatchedL/10.bmp",
									 "./res/beCatchedL/11.bmp", "./res/beCatchedL/12.bmp", "./res/beCatchedL/13.bmp", "./res/beCatchedL/14.bmp" };
		char* left_beHit1[9] = { "./res/beHitL/3.bmp", "./res/beHitL/4.bmp", "./res/beHitL/5.bmp", "./res/beHitL/6.bmp", "./res/beHitL/7.bmp",
								"./res/beHitL/8.bmp", "./res/beHitL/9.bmp", "./res/beHitL/10.bmp", "./res/beHitL/11.bmp" };
		char* left_beHit2[9] = { "./res/beHitL/12.bmp", "./res/beHitL/13.bmp", "./res/beHitL/14.bmp", "./res/beHitL/15.bmp", "./res/beHitL/16.bmp", "./res/beHitL/17.bmp",
								"./res/beHitL/18.bmp", "./res/beHitL/19.bmp", "./res/beHitL/20.bmp" };
		char* left_beHit3[9] = { "./res/beHitL/21.bmp", "./res/beHitL/22.bmp", "./res/beHitL/23.bmp", "./res/beHitL/24.bmp", "./res/beHitL/25.bmp", "./res/beHitL/26.bmp",
								"./res/beHitL/27.bmp", "./res/beHitL/28.bmp", "./res/beHitL/29.bmp" };
		char* left_beHit4[18] = { "./res/beHitL/73.bmp", "./res/beHitL/74.bmp", "./res/beHitL/75.bmp", "./res/beHitL/76.bmp", "./res/beHitL/77.bmp", "./res/beHitL/78.bmp",
									"./res/beHitL/79.bmp", "./res/beHitL/80.bmp", "./res/beHitL/81.bmp", "./res/beHitL/82.bmp", "./res/beHitL/83.bmp", "./res/beHitL/84.bmp", 
									"./res/beHitL/85.bmp","./res/beHitL/86.bmp", "./res/beHitL/87.bmp", "./res/beHitL/88.bmp", "./res/beHitL/89.bmp", "./res/beHitL/90.bmp" };
		char* right_beHit1[9] = { "./res/beHitR/3.bmp", "./res/beHitR/4.bmp", "./res/beHitR/5.bmp", "./res/beHitR/6.bmp", "./res/beHitR/7.bmp", "./res/beHitR/8.bmp",
								"./res/beHitR/9.bmp", "./res/beHitR/10.bmp", "./res/beHitR/11.bmp" };
		char* right_beHit2[9] = { "./res/beHitR/12.bmp", "./res/beHitR/13.bmp", "./res/beHitR/14.bmp", "./res/beHitR/15.bmp", "./res/beHitR/16.bmp", "./res/beHitR/17.bmp",
									"./res/beHitR/18.bmp", "./res/beHitR/19.bmp", "./res/beHitR/20.bmp" };
		char* right_beHit3[9] = { "./res/beHitR/21.bmp", "./res/beHitR/22.bmp", "./res/beHitR/23.bmp", "./res/beHitR/24.bmp", "./res/beHitR/25.bmp", "./res/beHitR/26.bmp",
						"./res/beHitR/27.bmp", "./res/beHitR/28.bmp", "./res/beHitR/29.bmp" };
		char* right_beHit4[18] = { "./res/beHitR/73.bmp", "./res/beHitR/74.bmp", "./res/beHitR/75.bmp", "./res/beHitR/76.bmp", "./res/beHitR/77.bmp", "./res/beHitR/78.bmp",
							"./res/beHitR/79.bmp", "./res/beHitR/80.bmp", "./res/beHitR/81.bmp", "./res/beHitR/82.bmp", "./res/beHitR/83.bmp", "./res/beHitR/84.bmp",
							"./res/beHitR/85.bmp","./res/beHitR/86.bmp", "./res/beHitR/87.bmp", "./res/beHitR/88.bmp", "./res/beHitR/89.bmp", "./res/beHitR/90.bmp" };
		char* blood_pic[27] = { "./res/SmallBlood/0.bmp","./res/SmallBlood/1.bmp","./res/SmallBlood/2.bmp","./res/SmallBlood/3.bmp","./res/SmallBlood/4.bmp","./res/SmallBlood/5.bmp",
								"./res/SmallBlood/6.bmp","./res/SmallBlood/7.bmp","./res/SmallBlood/8.bmp","./res/SmallBlood/9.bmp","./res/SmallBlood/10.bmp",
								"./res/SmallBlood/11.bmp", "./res/SmallBlood/12.bmp","./res/SmallBlood/13.bmp", "./res/SmallBlood/14.bmp","./res/SmallBlood/15.bmp",
								"./res/SmallBlood/16.bmp", "./res/SmallBlood/17.bmp","./res/SmallBlood/18.bmp", "./res/SmallBlood/19.bmp", "./res/SmallBlood/20.bmp",
								"./res/SmallBlood/21.bmp","./res/SmallBlood/22.bmp","./res/SmallBlood/23.bmp", "./res/SmallBlood/24.bmp", "./res/SmallBlood/25.bmp",
								"./res/26.bmp" };
		char* left_died[26] = { "./res/beHitL/73.bmp", "./res/beHitL/74.bmp", "./res/beHitL/75.bmp", "./res/beHitL/76.bmp", "./res/beHitL/77.bmp",
								"./res/beHitL/78.bmp", "./res/beHitL/79.bmp", "./res/beHitL/80.bmp", "./res/beHitL/81.bmp", "./res/beHitL/82.bmp",
								"./res/beHitL/83.bmp", "./res/beHitL/84.bmp", "./res/beHitL/85.bmp", "./res/beHitL/86.bmp", "./res/beHitL/87.bmp",
								"./res/beHitL/88.bmp", "./res/beHitL/89.bmp", "./res/beHitL/90.bmp", "./res/beHitL/91.bmp", "./res/beHitL/92.bmp",
								"./res/beHitL/93.bmp", "./res/beHitL/94.bmp", "./res/beHitL/95.bmp", "./res/beHitL/96.bmp", "./res/beHitL/97.bmp",
								"./res/beHitL/98.bmp" };
		char* right_died[26] = { "./res/beHitR/73.bmp", "./res/beHitR/74.bmp", "./res/beHitR/75.bmp", "./res/beHitR/76.bmp", "./res/beHitR/77.bmp",
								"./res/beHitR/78.bmp", "./res/beHitR/79.bmp", "./res/beHitR/80.bmp", "./res/beHitR/81.bmp", "./res/beHitR/82.bmp",
								"./res/beHitR/83.bmp", "./res/beHitR/84.bmp", "./res/beHitR/85.bmp", "./res/beHitR/86.bmp", "./res/beHitR/87.bmp",
								"./res/beHitR/88.bmp", "./res/beHitR/89.bmp", "./res/beHitR/90.bmp", "./res/beHitR/91.bmp", "./res/beHitR/92.bmp",
								"./res/beHitR/93.bmp", "./res/beHitR/94.bmp", "./res/beHitR/95.bmp", "./res/beHitR/96.bmp", "./res/beHitR/97.bmp",
								"./res/beHitR/98.bmp" };
		char* right_attack[23] = { "./res/SmallAttackR/1.bmp", "./res/SmallAttackR/2.bmp",  "./res/SmallAttackR/3.bmp",  "./res/SmallAttackR/4.bmp",  "./res/SmallAttackR/5.bmp",
									 "./res/SmallAttackR/6.bmp",  "./res/SmallAttackR/7.bmp",  "./res/SmallAttackR/8.bmp",  "./res/SmallAttackR/9.bmp",  "./res/SmallAttackR/10.bmp",
									 "./res/SmallAttackR/11.bmp",  "./res/SmallAttackR/12.bmp",  "./res/SmallAttackR/13.bmp",  "./res/SmallAttackR/14.bmp",  "./res/SmallAttackR/15.bmp",
									 "./res/SmallAttackR/16.bmp",  "./res/SmallAttackR/17.bmp",  "./res/SmallAttackR/18.bmp",  "./res/SmallAttackR/19.bmp",  "./res/SmallAttackR/20.bmp",
									 "./res/SmallAttackR/21.bmp",  "./res/SmallAttackR/22.bmp",  "./res/SmallAttackR/23.bmp" };
		char* left_attack[23] = { "./res/SmallAttackL/1.bmp", "./res/SmallAttackL/2.bmp",  "./res/SmallAttackL/3.bmp",  "./res/SmallAttackL/4.bmp",  "./res/SmallAttackL/5.bmp",
								 "./res/SmallAttackL/6.bmp",  "./res/SmallAttackL/7.bmp",  "./res/SmallAttackL/8.bmp",  "./res/SmallAttackL/9.bmp",  "./res/SmallAttackL/10.bmp",
								 "./res/SmallAttackL/11.bmp",  "./res/SmallAttackL/12.bmp",  "./res/SmallAttackL/13.bmp",  "./res/SmallAttackL/14.bmp",  "./res/SmallAttackL/15.bmp",
								 "./res/SmallAttackL/16.bmp",  "./res/SmallAttackL/17.bmp",  "./res/SmallAttackL/18.bmp",  "./res/SmallAttackL/19.bmp",  "./res/SmallAttackL/20.bmp",
								 "./res/SmallAttackL/21.bmp",  "./res/SmallAttackL/22.bmp",  "./res/SmallAttackL/23.bmp" };

		AddBitMaps(right_run, SRUNRIGHT, 8);
		AddBitMaps(left_run, SRUNLEFT, 8);
		AddBitMaps(right_beCatched, BECATCHEDR, 14);
		AddBitMaps(left_beCatched, BECATCHEDL, 14);
		AddBitMaps(right_beHit1, BEHITR1, 9);
		AddBitMaps(right_beHit2, BEHITR2, 9);
		AddBitMaps(right_beHit3, BEHITR3, 9);
		AddBitMaps(right_beHit4, BEHITR4, 18);
		AddBitMaps(left_beHit1, BEHITL1, 9);
		AddBitMaps(left_beHit2, BEHITL2, 9);
		AddBitMaps(left_beHit3, BEHITL3, 9);
		AddBitMaps(left_beHit4, BEHITL4, 18);
		AddBitMaps(left_died, DIEDL, 26);
		AddBitMaps(right_died, DIEDR, 26);
		AddBitMaps(right_attack, SATTACKR, 23);
		AddBitMaps(left_attack, SATTACKL, 23);

		LoadBitMaps(right_clothes, 10, 0);
		LoadBitMaps(left_clothes, 10, 1);
		LoadBitMaps(blood_pic, 27, 2);

	}
	CSmallPerson::~CSmallPerson()
	{
		int space = smallAction.size();

		for (int i = 0; i < space; i++)
			delete smallAction[i];

		space = smallClothesL.size();

		for (int i = 0; i < space; i++)
		{
			delete smallClothesL[i];
		}
		space = smallClothesR.size();
		for (int i = 0; i < space; i++)
			delete smallClothesR[i];

		space = blood.size();

		for (int i = 0; i < space; i++)
		{
			delete blood[i];
		}

		for (int i = 0; i < S_STATE_END; i++)
			delete smallStateTable[i];
	}
}
