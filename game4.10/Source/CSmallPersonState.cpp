#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CHero.h"
#include "CSmallPerson.h"
#include "CHeroState.h"
#include "CSmallPersonState.h"
#include "mygame.h"
namespace game_framework
{
	CSmallPersonState::CSmallPersonState(CSmallPerson *s)
	{
		smallPerson = s;
	}
	void CSmallPersonState::OnMoveState(CGamemap *m)
	{
		OnMove(m);
	}
	void CSmallPersonState::OnShowState(CGamemap *m,CHero *h)
	{
		OnShow(m,h);
	}
	void CSmallPersonState::SetIsMoving()
	{
		isMovingDown = smallPerson->GetMovingDown();
		isMovingLeft = smallPerson->GetMovingLeft();
		isMovingRight = smallPerson->GetMovingRight();
		isMovingUp = smallPerson->GetMovingUp();
	}
	void CSmallPersonState::GotoSmallPersonState(int state)
	{
		smallPerson->SetSmallPersonState(state);
	}
	/*SmallPersonStayState::SmallPersonStayState(SmallPerson *s) :CSmallPersonState(s)
	{
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isCatch = false;
	}
	SmallPersonStayState::~SmallPersonStayState()
	{

	}
	void SmallPersonStayState::OnBeginState()
	{
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		x = smallPerson->GetX1();
		y = smallPerson->GetY1();
	}
	void SmallPersonStayState::OnInit()
	{
		smallPerson->SetSmallPersonAni(STAYRIGHT);
		smallPerson->SetDirectionStay(true);
	}
	void SmallPersonStayState::OnKeyDown(UINT nChar)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		if (!(smallPerson->GetIsCatch()))
			GotoHeroState(HERO_STATE_RUN);
		else
			GotoHeroState(HERO_STATE_CATCH);
	}
	void SmallPersonStayState::OnKeyUp(UINT nChar)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_A = 0x41;											// keyboard A
		const char KEY_S = 0x53;											// keyboard s

		if (nChar == KEY_LEFT)
		{
			smallPerson->SetMovingLeft(false);
			isMovingLeft = false;
		}

		if (nChar == KEY_RIGHT)
		{
			smallPerson->SetMovingRight(false);
			isMovingRight = false;

		}

		if (nChar == KEY_UP)
		{
			smallPerson->SetMovingUp(false);
			isMovingUp = false;

		}

		if (nChar == KEY_DOWN)
		{
			isMovingDown = false;
			smallPerson->SetMovingDown(false);
		}
		if (smallPerson->GetIsCatch())
			GotoHeroState(HERO_STATE_CATCH);
		//smallPerson.OnKeyUp(nChar);
		//TRACE("STAY : x1 = %d y1 = %d x2 = %d y2 = %d\n", smallPerson->GetX1(), smallPerson->GetY1(), smallPerson->GetX2(), smallPerson->GetY2());

	}
	bool SmallPersonStayState::GetIsDirectionStay()
	{
		return directionStay;
	}
	void SmallPersonStayState::OnMove(CGamemap *m)
	{

	}
	void SmallPersonStayState::OnShow(CGamemap *)
	{
		if (smallPerson->GetDirectionStay())
		{
			smallPerson->SetHeroAni(STAYRIGHT);
			smallPerson->SetHeroAniFoot(FOOT_STAY_R);
		}
		else
		{
			smallPerson->SetHeroAni(STAYLEFT);
			smallPerson->SetHeroAniFoot(FOOT_STAY_L);
		}
	}*/
	CSmallPersonRunState::CSmallPersonRunState(CSmallPerson *s) :CSmallPersonState(s)
	{

	}
	CSmallPersonRunState::~CSmallPersonRunState()
	{

	}
	void CSmallPersonRunState::OnBeginState()
	{
		x = smallPerson->GetX1();
		y = smallPerson->GetY1();
		smallPerson->SetIsAttack(false);
		smallPerson->SetIsBeAttacked(false);
		smallPerson->SetIsBeCatched(false);
		
		//isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CSmallPersonRunState::OnInit()
	{
		//smallPerson->SetHeroAni(RUNRIGHT);
		//isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;

	}

	void CSmallPersonRunState::OnKeyDown(UINT nChar)
	{
	}
	void CSmallPersonRunState::OnKeyUp(UINT nChar)
	{

	}

	void CSmallPersonRunState::RandomDircetion()
	{
			const int MAX_RAND_NUM = 8;
			bool isBeCatched = smallPerson->GetIsBeCatched();
			int random_num = (rand() % MAX_RAND_NUM) + 1;
			int temp = 0;

			if (countRandomTime == 0)
				countRandomTime = CSpecialEffect::GetCurrentTimeCount();

			temp = CSpecialEffect::GetCurrentTimeCount() - countRandomTime;

			if (temp > 25)
			{
				countRandomTime = 0;

				switch (random_num)
				{
				case 1:							// 上
					if (isBeCatched || smallPerson->GetIsAttack())
					{
						SetIsMovingFalse();
						break;
					}

					isMovingUp = true;
					isMovingDown = false;
					isMovingLeft = false;
					isMovingRight = false;
					break;

				case 2:							// 下
					if (isBeCatched || smallPerson->GetIsAttack())
					{
						SetIsMovingFalse();
						break;
					}

					isMovingUp = false;
					isMovingDown = true;
					isMovingLeft = false;
					isMovingRight = false;
					break;

				case 3:							// 左
					if (isBeCatched || smallPerson->GetIsAttack())
					{
						isMovingUp = false;
						isMovingDown = false;
						isMovingLeft = false;
						isMovingRight = false;
						break;
					}

					isMovingUp = false;
					isMovingDown = false;
					isMovingLeft = true;
					isMovingRight = false;
					break;

				case 4:							// 右
					if (isBeCatched || smallPerson->GetIsAttack())
					{
						SetIsMovingFalse();
						break;
					}

					isMovingUp = false;
					isMovingDown = false;
					isMovingLeft = false;
					isMovingRight = true;
					break;

				case 5:							// 上左
					if (isBeCatched || smallPerson->GetIsAttack())
					{
						SetIsMovingFalse();
						break;
					}

					isMovingUp = true;
					isMovingDown = false;
					isMovingLeft = true;
					isMovingRight = false;
					break;

				case 6:							// 上右
					if (isBeCatched || smallPerson->GetIsAttack())
					{
						SetIsMovingFalse();
						break;
					}

					isMovingUp = true;
					isMovingDown = false;
					isMovingLeft = false;
					isMovingRight = false;
					break;

				case 7:							// 下左
					if (isBeCatched || smallPerson->GetIsAttack())
					{
						SetIsMovingFalse();
						break;
					}

					isMovingUp = false;
					isMovingDown = true;
					isMovingLeft = true;
					isMovingRight = false;
					break;

				case 8:							// 下右
					if (isBeCatched || smallPerson->GetIsAttack())
					{
						SetIsMovingFalse();
						break;
					}

					isMovingUp = false;
					isMovingDown = true;
					isMovingLeft = false;
					isMovingRight = true;
					break;

				default:
					break;
				}
			}
			smallPerson->SetMovingDown(isMovingDown);
			smallPerson->SetMovingLeft(isMovingLeft);
			smallPerson->SetMovingRight(isMovingRight);
			smallPerson->SetMovingUp(isMovingUp);
	}

	void CSmallPersonRunState::SetIsMovingFalse()
	{
		isMovingUp = false;
		isMovingDown = false;
		isMovingLeft = false;
		isMovingRight = false;
	}

	void CSmallPersonRunState::OnMove(CGamemap *m)
	{
		if(smallPerson->GetIsAlive())
			RandomDircetion();
		SetIsMoving();
		const int STEP_SIZE = 5;
		if (isMovingLeft && !isMovingRight)
		{
			smallPerson->SetDirectionStay(false);	// 暫存向左
			if (m->ScreenX(x) > 50)
			{
				if (!(m->IsEmpty(smallPerson->GetX1() - 10, smallPerson->GetY2())))
				{
					x -= STEP_SIZE;
				}
			}
		}

		if (isMovingRight || (isMovingLeft && isMovingRight))
		{
			smallPerson->SetDirectionStay(true);	// 暫存向右
			if (!(m->IsEmpty(smallPerson->GetX2() + 10, smallPerson->GetY2())))
			{
				if (m->ScreenX(x) < 550)
					x += STEP_SIZE;

			}
		}

		if (isMovingUp)
		{
			if (!(m->IsEmpty(smallPerson->GetX1(), smallPerson->GetY2() - 10)) && !(m->IsEmpty(smallPerson->GetX2(), smallPerson->GetY2() - 10)))
			{
				y -= STEP_SIZE;
			}
		}

		if (isMovingDown)
		{
			if (smallPerson->GetY2() < 550)
			{
				if (!(m->IsEmpty(smallPerson->GetX2(), smallPerson->GetY2() + 10)) || !(m->IsEmpty(smallPerson->GetX1(), smallPerson->GetY2() + 10)))
				{
					y += STEP_SIZE;
				}
			}
		}

		smallPerson->SetXY(x, y);
		
	}

	void CSmallPersonRunState::OnShow(CGamemap *m,CHero *h)
	{
		if (smallPerson->GetDirectionStay())
		{
			smallPerson->SetSmallPersonAni(SRUNRIGHT);
		}
		else
		{
			smallPerson->SetSmallPersonAni(SRUNLEFT);
		}
	}

	CSmallPersonAttackState::CSmallPersonAttackState(CSmallPerson *s) :CSmallPersonState(s)
	{
		smallPerson->SetIsAttack(false);
	}
	CSmallPersonAttackState::~CSmallPersonAttackState()
	{
	}

	void CSmallPersonAttackState::OnBeginState()
	{
		smallPerson->SetIsAttack(true);
	}

	void CSmallPersonAttackState::OnInit()
	{

	}

	void CSmallPersonAttackState::OnKeyDown(UINT nChar)
	{
		
	}
	void CSmallPersonAttackState::OnKeyUp(UINT nChar)
	{
	
	}

	void CSmallPersonAttackState::OnMove(CGamemap *m)
	{
		

	}

	void CSmallPersonAttackState::OnShow(CGamemap *m,CHero *h)
	{
			if (smallPerson->GetDirectionStay())
				smallPerson->SetSmallPersonAni(SATTACKR);
			else
				smallPerson->SetSmallPersonAni(SATTACKL);
	}
	CSmallPersonBeAttackedState::CSmallPersonBeAttackedState(CSmallPerson *s):CSmallPersonState(s)
	{
		smallPerson->SetIsBeAttacked(false);
		attackCount = 0;

	}

	CSmallPersonBeAttackedState::~CSmallPersonBeAttackedState()
	{
	}

	void CSmallPersonBeAttackedState::OnBeginState()
	{
		smallPerson->SetIsBeAttacked(true);
	}

	void CSmallPersonBeAttackedState::OnInit()
	{
	}

	void CSmallPersonBeAttackedState::OnKeyDown(UINT)
	{
		smallPerson->SetBlood(10);
		attackCount++;
		if(!smallPerson->GetIsBeCatched())
		{
			if (attackCount >= 5)
				attackCount = 1;
		}
	}

	void CSmallPersonBeAttackedState::OnKeyUp(UINT)
	{
		if (smallPerson->GetIsBeCatched())
			GotoSmallPersonState(S_STATE_BECATCHED);


	}

	void CSmallPersonBeAttackedState::OnMove(CGamemap *m)
	{

	}

	void CSmallPersonBeAttackedState::OnShow(CGamemap *m,CHero *h)
	{
		if (h->GetIsCatch())
		{
			if (h->GetDirectionStay())
			{
				smallPerson->SetSmallPersonAni(BEHITR1);
				CAudio::Instance()->Play(AUDIO_ATTACKT1);

			}
			else
			{
				smallPerson->SetSmallPersonAni(BEHITL1);
				CAudio::Instance()->Play(AUDIO_ATTACKT1);
			}
		}
		else if (h->GetIsAttack())
		{
			if (h->GetDirectionStay())
			{
				if (attackCount == 1)
					smallPerson->SetSmallPersonAni(BEHITR1);
				else if (attackCount == 2)
					smallPerson->SetSmallPersonAni(BEHITR2);
				else if (attackCount == 3)
					smallPerson->SetSmallPersonAni(BEHITR3);
				else if (attackCount == 4)
				{
					smallPerson->SetSmallPersonAni(BEHITR4);
					if (!m->IsEmpty(smallPerson->GetX1() + 20, (smallPerson->GetY1()+smallPerson->GetY2())/2))
						smallPerson->SetXY(smallPerson->GetX1() + 20, smallPerson->GetY1());
					else if (!m->IsEmpty(smallPerson->GetX1() + 10, (smallPerson->GetY1() + smallPerson->GetY2()) / 2))
						smallPerson->SetXY(smallPerson->GetX1() + 10, smallPerson->GetY1());

				}
			}
			else
			{
				if (attackCount == 1)
					smallPerson->SetSmallPersonAni(BEHITL1);
				else if (attackCount == 2)
					smallPerson->SetSmallPersonAni(BEHITL2);
				else if (attackCount == 3)
					smallPerson->SetSmallPersonAni(BEHITL3);
				else if (attackCount == 4)
				{
					smallPerson->SetSmallPersonAni(BEHITL4);
					if(!m->IsEmpty(smallPerson->GetX1() - 20, (smallPerson->GetY1() + smallPerson->GetY2()) / 2))
						smallPerson->SetXY(smallPerson->GetX1() - 20, smallPerson->GetY1());
					else if (!m->IsEmpty(smallPerson->GetX1() - 10, (smallPerson->GetY1() + smallPerson->GetY2()) / 2))
						smallPerson->SetXY(smallPerson->GetX1() - 10, smallPerson->GetY1());

				}
			}
			if (attackCount == 1 )
				CAudio::Instance()->Play(AUDIO_ATTACKT1);
			else if (attackCount == 2)
				CAudio::Instance()->Play(AUDIO_ATTACKT2);
			else if (attackCount == 3)
				CAudio::Instance()->Play(AUDIO_ATTACKT3);			
			else if (attackCount == 4)
				CAudio::Instance()->Play(AUDIO_ATTACKT4);
		}

	}
	CSmallPersonBeCatchedState::CSmallPersonBeCatchedState(CSmallPerson *s) :CSmallPersonState(s)
	{
		smallPerson->SetIsBeCatched(false);
	}
	CSmallPersonBeCatchedState::~CSmallPersonBeCatchedState()
	{

	}
	void CSmallPersonBeCatchedState::OnBeginState()
	{
		smallPerson->SetIsBeCatched(true);
		smallPerson->SetIsAttack(false);
		x = smallPerson->GetX1();
		y = smallPerson->GetY1();
	}
	void CSmallPersonBeCatchedState::OnInit()
	{

	}
	void CSmallPersonBeCatchedState::OnKeyDown(UINT nChar)
	{

		const char KEY_A = 0x41;						// keyboard A
		const char KEY_S = 0x53;
		if (nChar == KEY_A || nChar == KEY_S)
		{
			GotoSmallPersonState(S_STATE_BEATTACKED);
		}
	}

	void CSmallPersonBeCatchedState::OnKeyUp(UINT nChar)
	{

	}

	void CSmallPersonBeCatchedState::OnMove(CGamemap *m)
	{
		SetIsMoving();
		const int STEP_SIZE = 5;
		if (isMovingLeft && !isMovingRight)
		{
			smallPerson->SetDirectionStay(false);	// 暫存向左
			if (m->ScreenX(x) > 50)
			{
				if (!(m->IsEmpty(smallPerson->GetX1() - 4, smallPerson->GetY2())))
				{
					x -= STEP_SIZE;
				}
			}
		}

		if (isMovingRight || (isMovingLeft && isMovingRight))
		{
			smallPerson->SetDirectionStay(true);	// 暫存向右
			if (!(m->IsEmpty(smallPerson->GetX2() + 4, smallPerson->GetY2())))
			{
				if (m->ScreenX(x) < 550)
					x += STEP_SIZE;
			}
		}

		if (isMovingUp)
		{
			if (!(m->IsEmpty(smallPerson->GetX1(), smallPerson->GetY2() - 4)) && !(m->IsEmpty(smallPerson->GetX2(), smallPerson->GetY2() - 4)))
			{
				y -= STEP_SIZE;
			}
		}

		if (isMovingDown)
		{
			if (smallPerson->GetY2() < 550)
			{
				if (!(m->IsEmpty(smallPerson->GetX2(), smallPerson->GetY2() + 4)) || !(m->IsEmpty(smallPerson->GetX1(), smallPerson->GetY2() + 4)))
				{
					y += STEP_SIZE;
				}
			}
		}
		smallPerson->SetXY(x, y);
	}

	void CSmallPersonBeCatchedState::OnShow(CGamemap *m,CHero *h)
	{
		smallPerson->SetXY(h->GetX1(), h->GetY1());

		if (h->GetDirectionStay())
		{
			smallPerson->SetDirectionStay(true);
			smallPerson->SetSmallPersonAni(BECATCHEDR);			
		}
		else
		{
			smallPerson->SetDirectionStay(false);
			smallPerson->SetSmallPersonAni(BECATCHEDL);

		}
	}
}