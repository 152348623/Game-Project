#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CHero.h"
#include "CBoss.h"
#include "CHeroState.h"
#include "CBossState.h"

namespace game_framework
{
	CBossState::CBossState(CBoss *b)
	{
		boss = b;
	}
	void CBossState::OnMoveState(CGamemap *m)
	{
		OnMove(m);
	}
	void CBossState::OnShowState(CGamemap *m, CHero *h)
	{
		OnShow(m, h);
	}
	void CBossState::SetIsMoving()
	{
		isMovingDown = boss->GetMovingDown();
		isMovingLeft = boss->GetMovingLeft();
		isMovingRight = boss->GetMovingRight();
		isMovingUp = boss->GetMovingUp();
	}
	void CBossState::GotoBossState(int state)
	{
		boss->SetBossState(state);
	}
	/*SmallPersonStayState::SmallPersonStayState(SmallPerson *s) :CBossState(s)
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
		x = boss->GetX1();
		y = boss->GetY1();
	}
	void SmallPersonStayState::OnInit()
	{
		boss->SetBossAni(STAYRIGHT);
		boss->SetDirectionStay(true);
	}
	void SmallPersonStayState::OnKeyDown(UINT nChar)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		if (!(boss->GetIsCatch()))
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
			boss->SetMovingLeft(false);
			isMovingLeft = false;
		}

		if (nChar == KEY_RIGHT)
		{
			boss->SetMovingRight(false);
			isMovingRight = false;

		}

		if (nChar == KEY_UP)
		{
			boss->SetMovingUp(false);
			isMovingUp = false;

		}

		if (nChar == KEY_DOWN)
		{
			isMovingDown = false;
			boss->SetMovingDown(false);
		}
		if (boss->GetIsCatch())
			GotoHeroState(HERO_STATE_CATCH);
		//boss.OnKeyUp(nChar);
		//TRACE("STAY : x1 = %d y1 = %d x2 = %d y2 = %d\n", boss->GetX1(), boss->GetY1(), boss->GetX2(), boss->GetY2());

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
		if (boss->GetDirectionStay())
		{
			boss->SetHeroAni(STAYRIGHT);
			boss->SetHeroAniFoot(FOOT_STAY_R);
		}
		else
		{
			boss->SetHeroAni(STAYLEFT);
			boss->SetHeroAniFoot(FOOT_STAY_L);
		}
	}*/
	CBossRunState::CBossRunState(CBoss *b) :CBossState(b)
	{

	}
	CBossRunState::~CBossRunState()
	{

	}
	void CBossRunState::OnBeginState()
	{
		x = boss->GetX1();
		y = boss->GetY1();
		boss->SetIsAttack(false);
		boss->SetIsBeAttacked(false);
		boss->SetIsBeCatched(false);
		
		//isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CBossRunState::OnInit()
	{
		//boss->SetHeroAni(RUNRIGHT);
		//isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;

	}

	void CBossRunState::OnKeyDown(UINT nChar)
	{
	}
	void CBossRunState::OnKeyUp(UINT nChar)
	{

	}

	void CBossRunState::RandomDircetion()
	{
		const int MAX_RAND_NUM = 8;
		bool isBeCatched = boss->GetIsBeCatched();
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
				if (isBeCatched || boss->GetIsAttack())
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
				if (isBeCatched || boss->GetIsAttack())
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
				if (isBeCatched || boss->GetIsAttack())
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
				if (isBeCatched || boss->GetIsAttack())
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
				if (isBeCatched || boss->GetIsAttack())
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
				if (isBeCatched || boss->GetIsAttack())
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
				if (isBeCatched || boss->GetIsAttack())
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
				if (isBeCatched || boss->GetIsAttack())
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
		boss->SetMovingDown(isMovingDown);
		boss->SetMovingLeft(isMovingLeft);
		boss->SetMovingRight(isMovingRight);
		boss->SetMovingUp(isMovingUp);
	}

	void CBossRunState::SetIsMovingFalse()
	{
		isMovingUp = false;
		isMovingDown = false;
		isMovingLeft = false;
		isMovingRight = false;
	}

	void CBossRunState::OnMove(CGamemap *m)
	{
		if (boss->GetIsAlive())
			RandomDircetion();
		SetIsMoving();
		const int STEP_SIZE = 5;
		if (isMovingLeft && !isMovingRight)
		{
			boss->SetDirectionStay(false);	// 暫存向左
			if (m->ScreenX(x) > 50)
			{
				if (!(m->IsEmpty(boss->GetX1() - 4, boss->GetY2())))
				{
					x -= STEP_SIZE;
				}
			}
		}

		if (isMovingRight || (isMovingLeft && isMovingRight))
		{
			boss->SetDirectionStay(true);	// 暫存向右
			if (!(m->IsEmpty(boss->GetX2() + 4, boss->GetY2())))
			{
				if (m->ScreenX(x) < 550)
					x += STEP_SIZE;

			}
		}

		if (isMovingUp)
		{
			if (!(m->IsEmpty(boss->GetX1(), boss->GetY2() - 4)) && !(m->IsEmpty(boss->GetX2(), boss->GetY2() - 4)))
			{
				y -= STEP_SIZE;
			}
		}

		if (isMovingDown)
		{
			if (boss->GetY2() < 550)
			{
				if (!(m->IsEmpty(boss->GetX2(), boss->GetY2() + 4)) || !(m->IsEmpty(boss->GetX1(), boss->GetY2() + 4)))
				{
					y += STEP_SIZE;
				}
			}
		}

		boss->SetXY(x, y);

	}

	void CBossRunState::OnShow(CGamemap *m, CHero *h)
	{
		if (boss->GetDirectionStay())
		{
			boss->SetBossAni(B_RUNRIGHT);
		}
		else
		{
			boss->SetBossAni(B_RUNLEFT);
		}
	}

	CBossAttackState::CBossAttackState(CBoss *s) :CBossState(s)
	{
		boss->SetIsAttack(false);
	}
	CBossAttackState::~CBossAttackState()
	{
	}

	void CBossAttackState::OnBeginState()
	{
		boss->SetIsAttack(true);
	}

	void CBossAttackState::OnInit()
	{

	}

	void CBossAttackState::OnKeyDown(UINT nChar)
	{

	}
	void CBossAttackState::OnKeyUp(UINT nChar)
	{
	}

	void CBossAttackState::OnMove(CGamemap *m)
	{


	}

	void CBossAttackState::OnShow(CGamemap *m, CHero *h)
	{
		if (boss->GetDirectionStay())
		{	
			if (h->GetAni(BEATTACKBOSSR) == 2)
				boss->SetXY(h->GetX1()-100, h->GetY1()-60);
			boss->SetBossAni(B_ATTACKR);
		}
		else
		{
			if (h->GetAni(BEATTACKBOSSL) == 2)
				boss->SetXY(h->GetX2()-50, h->GetY1()-20);
			boss->SetBossAni(B_ATTACKL);
		}
	}
	CBossBeAttackedState::CBossBeAttackedState(CBoss *s) :CBossState(s)
	{
		boss->SetIsBeAttacked(false);
		attackCount = 0;

	}

	CBossBeAttackedState::~CBossBeAttackedState()
	{
	}

	void CBossBeAttackedState::OnBeginState()
	{
		boss->SetIsBeAttacked(true);
	}

	void CBossBeAttackedState::OnInit()
	{
	}

	void CBossBeAttackedState::OnKeyDown(UINT)
	{
		boss->SetBlood(1);
		attackCount++;
		if (!boss->GetIsBeCatched())
		{
			if (attackCount >= 5)
				attackCount = 1;
		}
	}

	void CBossBeAttackedState::OnKeyUp(UINT nChar)
	{
		GotoBossState(BOSS_STATE_RUN);

	}

	void CBossBeAttackedState::OnMove(CGamemap *m)
	{

	}

	void CBossBeAttackedState::OnShow(CGamemap *m, CHero *h)
	{

		if (h->GetIsAttack())
		{
			TRACE("attackCount = %d \n", attackCount);
			if (!h->GetDirectionStay())
			{
				if (attackCount == 1)
					boss->SetBossAni(B_BEHITR1);
				else if (attackCount == 2)
					boss->SetBossAni(B_BEHITR2);
				else if (attackCount == 3)
					boss->SetBossAni(B_BEHITR3);
				else if (attackCount == 4)
				{
					boss->SetBossAni(B_BEHITR4);
					if (!m->IsEmpty(boss->GetX1() - 20, (boss->GetY1() + boss->GetY2()) / 2))
						boss->SetXY(boss->GetX1() - 20, boss->GetY1());
					else if (!m->IsEmpty(boss->GetX1() - 10, (boss->GetY1() + boss->GetY2()) / 2))
						boss->SetXY(boss->GetX1() - 10, boss->GetY1());

				}
			}
			else
			{
				if (attackCount == 1)
					boss->SetBossAni(B_BEHITL1);
				else if (attackCount == 2)
					boss->SetBossAni(B_BEHITL2);
				else if (attackCount == 3)
					boss->SetBossAni(B_BEHITL3);
				else if (attackCount == 4)
				{
					boss->SetBossAni(B_BEHITL4);
					if (!m->IsEmpty(boss->GetX1() + 20, (boss->GetY1() + boss->GetY2()) / 2))
						boss->SetXY(boss->GetX1() + 20, boss->GetY1());
					else if (!m->IsEmpty(boss->GetX1() - 10, (boss->GetY1() + boss->GetY2()) / 2))
						boss->SetXY(boss->GetX1() + 10, boss->GetY1());

				}
			}

		}

	}

}