#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CHero.h"
#include "CSmallPerson.h"
#include "CHeroState.h"
#include "mygame.h"

namespace game_framework
{
	CHeroState::CHeroState(CHero *h)
	{
		hero = h;
	}
	void CHeroState::OnMoveState(CGamemap *m)
	{
		OnMove(m);
	}
	void CHeroState::OnShowState(CGamemap *m)
	{
		OnShow(m);
	}
	void CHeroState::SetIsMoving()
	{
		isMovingDown = hero->GetMovingDown();
		isMovingLeft = hero->GetMovingLeft();
		isMovingRight = hero->GetMovingRight();
		isMovingUp = hero->GetMovingUp();
	}
	void CHeroState::GotoHeroState(int state)
	{
		hero->SetHeroState(state);
	}
	CHeroStayState::CHeroStayState(CHero *h) :CHeroState(h)
	{
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isCatch = false;
	}
	CHeroStayState::~CHeroStayState()
	{

	}
	void CHeroStayState::OnBeginState()
	{
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		x = hero->GetX1();
		y = hero->GetY1();
		hero->SetIsCatch(false);
		hero->SetIsAttack(false);
		hero->SetIsBeAttackedBoss(false);

	}
	void CHeroStayState::OnInit()
	{
		hero->SetHeroAni(STAYRIGHT);
		hero->SetDirectionStay(true);
	}
	void CHeroStayState::OnKeyDown(UINT nChar)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_A = 0x41;											// keyboard A
		const char KEY_S = 0x53;											// keyboard s

		if(!(hero->GetIsCatch()))
			GotoHeroState(HERO_STATE_RUN);
		else
			GotoHeroState(HERO_STATE_CATCH);
		if (nChar == KEY_A || nChar == KEY_S)
			GotoHeroState(HERO_STATE_ATTACK);
	}
	void CHeroStayState::OnKeyUp(UINT nChar)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_A = 0x41;											// keyboard A
		const char KEY_S = 0x53;											// keyboard s

		if (nChar == KEY_LEFT)
		{
			hero->SetMovingLeft(false);
			isMovingLeft = false;
		}

		if (nChar == KEY_RIGHT)
		{
			hero->SetMovingRight(false);
			isMovingRight = false;

		}

		if (nChar == KEY_UP)
		{
			hero->SetMovingUp(false);
			isMovingUp = false;

		}

		if (nChar == KEY_DOWN)
		{
			isMovingDown = false;
			hero->SetMovingDown(false);
		}
		/*if (hero->GetIsCatch())
			GotoHeroState(HERO_STATE_CATCH);*/

	}
	bool CHeroStayState::GetIsDirectionStay()
	{
		return directionStay;
	}
	void CHeroStayState::OnMove(CGamemap *m)
	{

	}
	void CHeroStayState::OnShow(CGamemap *)
	{
		if (hero->GetDirectionStay())
		{
			hero->SetHeroAni(STAYRIGHT);
			hero->SetHeroAniFoot(FOOT_STAY_R);
		}
		else
		{
			hero->SetHeroAni(STAYLEFT);
			hero->SetHeroAniFoot(FOOT_STAY_L);
		}
	}
	CHeroRunState::CHeroRunState(CHero *h) :CHeroState(h)
	{

	}
	CHeroRunState::~CHeroRunState()
	{

	}
	void CHeroRunState::OnBeginState()
	{
		x = hero->GetX1();
		y = hero->GetY1();
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		hero->SetIsAttack(false);
	}

	void CHeroRunState::OnInit()
	{
	}
	
	void CHeroRunState::OnKeyDown(UINT nChar)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		if (nChar == KEY_LEFT)
		{
			hero->SetMovingLeft(true);
			isMovingLeft = true;
		}

		if (nChar == KEY_RIGHT)
		{
			hero->SetMovingRight(true);
			isMovingRight = true;
		}

		if (nChar == KEY_UP)
		{
			hero->SetMovingUp(true);
			isMovingUp = true;
		}

		if (nChar == KEY_DOWN)
		{
			hero->SetMovingDown(true);
			isMovingDown = true;
		}
	}
	void CHeroRunState::OnKeyUp(UINT nChar)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_A = 0x41;											// keyboard A
		const char KEY_S = 0x53;											// keyboard s

		if (nChar == KEY_LEFT)
		{
			hero->SetMovingLeft(false);
			isMovingLeft = false;
		}

		if (nChar == KEY_RIGHT)
		{
			hero->SetMovingRight(false);
			isMovingRight = false;

		}

		if (nChar == KEY_UP)
		{
			hero->SetMovingUp(false);
			isMovingUp = false;

		}

		if (nChar == KEY_DOWN)
		{
			isMovingDown = false;
			hero->SetMovingDown(false);
		}
		if (!hero->GetMovingDown() && !hero->GetMovingUp() && !hero->GetMovingLeft() && !hero->GetMovingRight())
			GotoHeroState(HERO_STATE_STAY);
	}
	
	void CHeroRunState::OnMove(CGamemap *m)
	{
		SetIsMoving();
		const int STEP_SIZE = 7;
		const int STEP_SIZE_CLOSE = 4;
		hero->SetHeroAni(RUNRIGHT);
		TRACE("hero: Map : %d \n", m->GetSX());
		if (isMovingLeft && !isMovingRight)
		{
			hero->SetDirectionStay(false);	// 暫存向左
			if (!(m->IsEmpty(hero->GetX1() - 4, (hero->GetY2() + hero->GetY1()) / 2 + 75)))
			{	
				m->SetSX();
				if (hero->GetX1() > 20)
				{
					if (m->ScreenX(x) < 200)
						x -= STEP_SIZE_CLOSE;
					else
						x -= STEP_SIZE;
				}
			}
		}

		if (isMovingRight || (isMovingLeft && isMovingRight))
		{
			hero->SetDirectionStay(true);	// 暫存向右
			if (!(m->IsEmpty(hero->GetX2() + 4, (hero->GetY2()+ hero->GetY1())/2 + 75 )))
			{	
				m->SetSX();
				if (m->ScreenX(x) < 550 && (hero->GetX2() < 1600 && m->GetRoundMap() == 1) || (hero->GetX2() < 3100 && (m->GetRoundMap() == 2 || m->GetIsPass())))
				{
					if(m->ScreenX(x) > 400)
						x += STEP_SIZE_CLOSE;
					else
						x += STEP_SIZE;
				}
			}
		}

		if (isMovingUp)
		{
			if (!(m->IsEmpty(hero->GetX1(), hero->GetY2() - 4)) && !(m->IsEmpty(hero->GetX2(), hero->GetY2() - 4)))
			{
				y -= STEP_SIZE;
				m->SetSY();
			}
		}

		if (isMovingDown)
		{
			if (hero->GetY2() < 530)
			{
				if (!(m->IsEmpty(hero->GetX2(), hero->GetY2() + 10)) || !(m->IsEmpty(hero->GetX1(), hero->GetY2() + 10)))
				{
					y += STEP_SIZE;
					m->SetSY();
				}
			}
		}

		hero->SetXY(x, y);
		
	}

	void CHeroRunState::OnShow(CGamemap *)
	{
		if (hero->GetDirectionStay())
		{
			hero->SetHeroAni(RUNRIGHT);
		}
		else
		{
			hero->SetHeroAni(RUNLEFT);
		}
	}

	CHeroAttackState::CHeroAttackState(CHero *h) :CHeroState(h)
	{
		hero->SetIsAttack(false);

	}
	CHeroAttackState::~CHeroAttackState()
	{

	}

	void CHeroAttackState::OnBeginState()
	{
		hero->SetIsAttack(true);
		
	}

	void CHeroAttackState::OnInit()
	{

	}
	
	void CHeroAttackState::OnKeyDown(UINT nChar)
	{
		const char KEY_A = 0x41;											// keyboard A
		const char KEY_S = 0x53;											// keyboard s
		int  temp = CSpecialEffect::GetCurrentTimeCount();
		if (nChar == KEY_A || nChar == KEY_S)
			hero->SetIsAttack(true);
		
		if (attackCount.size() >= 2 || (temp - attackTime) > 15)			// 重置
		{
			attackCount.clear();
			attackTime = 0;
		}

		if (nChar == KEY_A)													// 按下 A
		{
			if (attackTime == 0)											// 存前一個time
				attackTime = CSpecialEffect::GetCurrentTimeCount();
			else															// 計算第二次按下的時間
			{
				temp = CSpecialEffect::GetCurrentTimeCount() - attackTime;
				attackTime = 0;
			}
			if (temp <= 15)													// 若 time <= 15 和  size =  1 => 組合鍵  攻擊：AA
			{
				if (attackCount.size() == 1)
					attackCount.push_back(1);
			}
			if (attackCount.size() == 0)									// 攻擊：A
				attackCount.push_back(1);
		}
		else if (nChar == KEY_S)
		{
			if (attackTime == 0)												//存前一個time按下的時間
				attackTime = CSpecialEffect::GetCurrentTimeCount();
			else																// 第二次按下的時間
			{
				temp = CSpecialEffect::GetCurrentTimeCount() - attackTime;
				attackTime = 0;
			}

			if (attackCount.size() == 0)
				attackCount.push_back(2);

			if (temp <= 15 && attackCount.size() == 1)							// 若 time <= 15 和  size =  1 => 組合鍵  攻擊：AS	SS
			{
				attackCount.push_back(2);
			}
		}

	}
	void CHeroAttackState::OnKeyUp(UINT nChar)
	{
		if (hero->GetIsCatch())
			GotoHeroState(HERO_STATE_CATCH);
		else
		{
				GotoHeroState(HERO_STATE_STAY);
		}
	}

	void CHeroAttackState::OnMove(CGamemap *m)
	{
		if (attackCount.size() % 2 == 1)
		{
			if (attackCount[0] == 1)
			{
				CAudio::Instance()->Play(AUDIO_ATTACKF1);
			}
			else if (attackCount[0] == 2)
			{
				CAudio::Instance()->Play(AUDIO_ATTACKF2);
			}
		}
		else if (attackCount.size() % 2 == 0)
		{
			if (attackCount[0] == 1 && attackCount[1] == 1)
			{
				CAudio::Instance()->Play(AUDIO_ATTACKF3);

			}
			else if (attackCount[0] == 1 && attackCount[1] == 2)
			{
				CAudio::Instance()->Play(AUDIO_ATTACKF4);
			}
			else if (attackCount[0] == 2 && attackCount[1] == 2)
			{
				CAudio::Instance()->Play(AUDIO_ATTACKF3);
			}
		}
	}

	void CHeroAttackState::OnShow(CGamemap *)
	{

		if (hero->GetIsCatch())
		{
			if (attackCount.size() > 0)
			{
				if (hero->GetDirectionStay())
				{
					hero->SetHeroAni(CATCHATTACKR1);

				}
				else
				{
					hero->SetHeroAni(CATCHATTACKL1);
				}
			}
		}
		else
		{
			if (hero->GetDirectionStay() && attackCount.size() != 0)						// 攻擊 右
			{
				if (attackCount.size() % 2 == 1)
				{
					if (attackCount[0] == 1)
					{
						hero->SetHeroAni(ATTACKRA);
					}
					else if (attackCount[0] == 2)
					{
						hero->SetHeroAni(ATTACKRS);
					}
				}
				else if (attackCount.size() % 2 == 0)
				{
					if (attackCount[0] == 1 && attackCount[1] == 1)
					{
						hero->SetHeroAni(ATTACKRAA);

					}
					else if (attackCount[0] == 1 && attackCount[1] == 2)
					{
						hero->SetHeroAni(ATTACKRAS);
					}
					else if (attackCount[0] == 2 && attackCount[1] == 2)
					{
						hero->SetHeroAni(ATTACKRSS);
					}
				}
			}
			if (!hero->GetDirectionStay() && attackCount.size() != 0)											// 向左攻擊
			{
				if (attackCount.size() == 1)
				{
					if (attackCount[0] == 1)
					{
						hero->SetHeroAni(ATTACKLA);
					}
					else if (attackCount[0] == 2)
					{
						hero->SetHeroAni(ATTACKLS);
					}
				}
				else if (attackCount.size() == 2)
				{
					if (attackCount[0] == 1 && attackCount[1] == 1)
					{
						hero->SetHeroAni(ATTACKLAA);
					}
					else if (attackCount[0] == 1 && attackCount[1] == 2)
					{
						hero->SetHeroAni(ATTACKLAS);
					}
					else if (attackCount[0] == 2 && attackCount[1] == 2)
					{
						hero->SetHeroAni(ATTACKLSS);
					}
				}
			}
		}
	}

	CHeroCatchState::CHeroCatchState(CHero *h) :CHeroState(h)
	{
		hero->SetIsCatch(false);
	}
	CHeroCatchState::~CHeroCatchState()
	{

	}
	void CHeroCatchState::OnBeginState()
	{
		hero->SetIsCatch(true);
		x = hero->GetX1();
		y = hero->GetY1();
		hero->SetIsAttack(false);

	}
	void CHeroCatchState::OnInit()
	{

	}
	void CHeroCatchState::OnKeyDown(UINT nChar)
	{
		const char KEY_A = 0x41;											// keyboard A
		const char KEY_S = 0x53;
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭

		if (nChar == KEY_A || nChar == KEY_S)
		{
			GotoHeroState(HERO_STATE_ATTACK);
		}
	}		

	void CHeroCatchState::OnKeyUp(UINT nChar)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_A = 0x41;											// keyboard A
		const char KEY_S = 0x53;											// keyboard s

		if (nChar == KEY_LEFT)
		{
			hero->SetMovingLeft(false);
			isMovingLeft = false;
		}

		if (nChar == KEY_RIGHT)
		{
			hero->SetMovingRight(false);
			isMovingRight = false;

		}

		if (nChar == KEY_UP)
		{
			hero->SetMovingUp(false);
			isMovingUp = false;

		}

		if (nChar == KEY_DOWN)
		{
			isMovingDown = false;
			hero->SetMovingDown(false);
		}
		if (!isCatch)
			GotoHeroState(HERO_STATE_STAY);

	}
	

	void CHeroCatchState::OnMove(CGamemap *m)
	{
		SetIsMoving();
		const int STEP_SIZE = 7;
		const int STEP_SIZE_CLOSE = 5;
		hero->SetHeroAni(RUNRIGHT);
		TRACE("hero: Map : %d \n", m->GetSX());
		if (isMovingLeft && !isMovingRight)
		{
			hero->SetDirectionStay(false);	// 暫存向左
			m->SetSX();
			if (hero->GetX1() > 20)
			{
				if (!(m->IsEmpty(hero->GetX1() - 4, (hero->GetY2() + hero->GetY1()) / 2 + 75)))
				{
					if (m->ScreenX(x) < 100)
						x -= STEP_SIZE_CLOSE;
					else
						x -= STEP_SIZE;
				}
			}
		}

		if (isMovingRight || (isMovingLeft && isMovingRight))
		{
			hero->SetDirectionStay(true);	// 暫存向右
			m->SetSX();
			if (!(m->IsEmpty(hero->GetX2() + 4, (hero->GetY2() + hero->GetY1()) / 2 + 75)))
			{
				if (m->ScreenX(x) < 550 && (hero->GetX2() < 1600 && m->GetRoundMap() == 1) || (hero->GetX2() < 3100 && (m->GetRoundMap() == 2 || m->GetIsPass())))
				{
					if (m->ScreenX(x) > 500)
						x += STEP_SIZE_CLOSE;
					else
						x += STEP_SIZE;
				}
			}
		}

		if (isMovingUp)
		{
			if (!(m->IsEmpty(hero->GetX1(), hero->GetY2() - 4)) && !(m->IsEmpty(hero->GetX2(), hero->GetY2() - 4)))
			{
				y -= STEP_SIZE;
				m->SetSY();
			}
		}

		if (isMovingDown)
		{
			if (hero->GetY2() < 530)
			{
				if (!(m->IsEmpty(hero->GetX2(), hero->GetY2() + 10)) || !(m->IsEmpty(hero->GetX1(), hero->GetY2() + 10)))
				{
					y += STEP_SIZE;
					m->SetSY();
				}
			}
		}

		hero->SetXY(x, y);

	}

	void CHeroCatchState::OnShow(CGamemap *m)
	{
		SetIsMoving();
		if (hero->GetDirectionStay())													// 抓到小人 右
		{
			if (isMovingDown || isMovingRight || isMovingUp)
			{
				hero->SetHeroAniFoot(FOOT_CATCH_R);
			}
			else
			{
				hero->SetHeroAniFoot(FOOT_STAY_CATCH_R);
			}
			hero->SetHeroAni(CATCHR);
		}
		else if (!hero->GetDirectionStay())
		{
			if (isMovingDown || isMovingLeft || isMovingUp)							// 移動
			{
				hero->SetHeroAniFoot(FOOT_CATCH_L);
			}
			else																	// 停下
			{
				hero->SetHeroAniFoot(FOOT_STAY_CATCH_L);
			}
			hero->SetHeroAni(CATCHL);
		}
	}
	CHeroBeAttackedState::CHeroBeAttackedState(CHero *h) :CHeroState(h)
	{
		hero->SetIsBeAttacked(false);
	}
	CHeroBeAttackedState::~CHeroBeAttackedState()
	{

	}
	void CHeroBeAttackedState::OnBeginState()
	{
		x = hero->GetX1();
		y = hero->GetY1();
	}
	void CHeroBeAttackedState::OnInit()
	{
	}
	void CHeroBeAttackedState::OnKeyDown(UINT nChar)
	{

	}

	void CHeroBeAttackedState::OnKeyUp(UINT nChar)
	{

	}


	void CHeroBeAttackedState::OnMove(CGamemap *m)
	{

	}

	void CHeroBeAttackedState::OnShow(CGamemap *m)
	{
		if (hero->GetIsBeAttacked())
		{
			if (hero->GetDirectionStay())
			{
				hero->SetHeroAni(BEATTACKR);

			}
			else
			{
				hero->SetHeroAni(BEATTACKL);
			}
			if (hero->GetAni(BEATTACKR) == 7 || hero->GetAni(BEATTACKL) == 7)
			{
				int blood = hero->GetBlood();
				blood -= 5;
				hero->SetBlood(blood);
				GotoHeroState(HERO_STATE_STAY);

			}
		}
		if (hero->GetIsBeAttackedBoss())
		{
			if (!hero->GetDirectionStay())
			{
				hero->SetHeroAni(BEATTACKBOSSR);
				if (!m->IsEmpty(hero->GetX1() + 10, (hero->GetY1() + hero->GetY2()) / 2) || m->ScreenX(hero->GetX1() + 10)<580)
					hero->SetXY(hero->GetX1() + 10,hero->GetY1());
			}
			else
			{
				hero->SetHeroAni(BEATTACKBOSSL);
				if(!m->IsEmpty(hero->GetX1() -10, (hero->GetY1() + hero->GetY2()) / 2) || m->ScreenX(hero->GetX1() - 10)>0)
					hero->SetXY(hero->GetX1() - 10, hero->GetY1());
			}
			if (hero->GetAni(BEATTACKBOSSR) == 4|| hero->GetAni(BEATTACKBOSSL) == 4)
			{

				int blood = hero->GetBlood();
				blood -= 5;
				hero->SetBlood(blood);
				GotoHeroState(HERO_STATE_STAY);

			}
		}
		
	}

}