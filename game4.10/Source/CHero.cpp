#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CHero.h"
#include "CSmallPerson.h"
#include "CHeroState.h"
#include "CBoss.h"
namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// CHero: Eraser class
/////////////////////////////////////////////////////////////////////////////

CHero::CHero()
{
    Initialize();
	
	heroState = NULL;

}
CHero::~CHero()
{
    for (int i = 0; i < HERO_STATE_END; i++)
        delete heroStateTable[i];
	int space = action.size();
	for (int i = 0; i < space; i++)
		delete action[i];
	space = foot.size();
	for (int i = 0; i < space; i++)
		delete foot[i];
}
void CHero::OnInit()
{
    heroState = heroStateTable[HERO_STATE_STAY];
    heroState->OnBeginState();
	currentState = HERO_STATE_STAY;
}

void CHero::OnInitState()
{    
	heroStateTable[HERO_STATE_STAY] = new CHeroStayState(this);
    heroStateTable[HERO_STATE_RUN] = new CHeroRunState(this);
    heroStateTable[HERO_STATE_ATTACK] = new CHeroAttackState(this);
    heroStateTable[HERO_STATE_CATCH] = new CHeroCatchState(this);
	heroStateTable[HERO_STATE_BEATTACKED] = new CHeroBeAttackedState(this);
    for (int i = 0; i < HERO_STATE_END; i++)
        heroStateTable[i]->OnInit();
}
void CHero::Initialize()
{
	currentAni = RUNRIGHT;
	isMovingDown = isMovingLeft = isMovingRight = isMovingUp = false;
	x = 300;
	y = 400;
    blood = 100;
	isAlive = true;
	int x_init[ACTION_END] = { 0,0,0,0,0,0,-8,-45,-23,-45,-130,-60,0,-38,-34,-100,-25,-3,-18,4,20,-20};
	int y_init[ACTION_END] = { 0,0,0,0,0,0,-2, -2,  0, 1, -30,-30,0,  0,-12,	-12, 10,10,17,18,-150,-150};
	int x_foot_init[FOOT_END] = { 0,16,12,20,10,20};
	int y_foot_init[FOOT_END] = { 93,94,108,108,108,108 };
	for (int i = 0; i < ACTION_END; i++)
	{
		actionX[i] = x_init[i];
		actionY[i] = y_init[i];
	}
	for (int i = 0; i < FOOT_END; i++)
	{
		footX[i] = x_foot_init[i];
		footY[i] = y_foot_init[i];
	}
}
void CHero::OnShow(CGamemap* m)
{
	avatar.SetTopLeft(0, -15);
	avatar.ShowBitmap();
	ShowBlood(blood);

	heroState->OnShowState(m);
	if (currentState == HERO_STATE_STAY || currentState == HERO_STATE_CATCH)
	{
		foot[currentAniFoot]->SetTopLeft(m->ScreenX(x + footX[currentAniFoot]), m->ScreenY(y + footY[currentAniFoot]));
		foot[currentAniFoot]->OnShow();
	}
	action[currentAni]->SetTopLeft(m->ScreenX(x + actionX[currentAni]), m->ScreenY(y + actionY[currentAni]));
	action[currentAni]->OnShow();
}
class CGamemap;

bool CHero::HitRectangle(int tx1, int ty1, int tx2, int ty2)
{
    int x1 = x;
    int y1 = y;
    int x2 = GetX2();
    int y2 = GetY2();
    return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
}
bool CHero::HitSmallPerson(CSmallPerson* s)
{
	s->SetSmallPersonAni(SRUNRIGHT);
	int heroDisX = (GetX2() + GetX1()) / 2;
	int smallDisX = (s->GetX2() + s->GetX1()) / 2;
	int heroDisY = (GetY2() + GetY1()) / 2;
	int smallDisY = (s->GetY2() + s->GetY1()) / 2;

	if (abs(smallDisX - heroDisX) < 70 && abs(smallDisY - heroDisY) < 30 && currentState!=HERO_STATE_ATTACK)
	{
		return true;
	}

		return false;

}
void CHero::SetHeroState(int state)
{
    heroState = heroStateTable[state];
    heroState->OnBeginState();
	currentState = state;
}

void CHero::SetHeroAni(int ani)
{
    currentAni = ani;
	int space = action.size();
	for (int i = 0; i < space; i++)
	{
		if (i == currentAni)
		{
			action[i]->SetPause(false);
		}
		else
			action[i]->SetPause(true);
	}
}

void CHero::SetHeroAniFoot(int footAni)
{
    currentAniFoot = footAni;
}

bool CHero::GetIsCatch()
{
	return isCatch;
}

bool CHero::GetIsAttack()
{
	return isAttack;
}

bool CHero::GetIsBeAttacked()
{
	return isBeAttacked;
}

bool CHero::GetIsBeAttackedBoss()
{
	return isBeAttackedBoss;
;
}

int CHero::GetHeroState()
{
	return currentState;
}

bool CHero::GetMovingDown()
{
	return isMovingDown;
}

bool CHero::GetMovingLeft()
{
	return isMovingLeft;
}

bool CHero::GetMovingRight()
{
	return isMovingRight;
}

bool CHero::GetMovingUp()
{
	return isMovingUp;
}

bool CHero::GetDirectionStay()
{
	return directionStay;
}

int CHero::GetBlood()
{
	return blood;
}

bool CHero::GetIsAlive()
{
	return isAlive;
}

int CHero::GetAni(int Ani)
{
	return action[Ani]->GetCurrentBitmapNumber();

}

int CHero::GetCurrentAni()
{
	return currentAni;
}

bool CHero::GetIsFinalAni()
{
	return action[currentAni]->IsFinalBitmap();
}

void CHero::OnKeyDown(UINT nChar)
{
        heroState->OnKeyDown(nChar);
}
void CHero::OnKeyUp(UINT nChar)
{
    heroState->OnKeyUp(nChar);
}

void CHero::ShowBlood(int percent)
{
    if (!SHOW_LOAD_PROGRESS)
        return;

    const int bar_width = 70;
    const int bar_height = 13;
    const int x1 = 20;
    const int x2 = x1 + bar_width;
    const int y1 = bar_height + 87;
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

void CHero::SetMovingDown(bool flag)
{
	isMovingDown = flag;
}

void CHero::SetMovingLeft(bool flag)
{
	isMovingLeft = flag;
}
void CHero::SetMovingRight(bool flag)
{
	isMovingRight = flag;
}
void CHero::SetMovingUp(bool flag)
{
	isMovingUp = flag;
}

int CHero::GetX1()
{
    return x;
}
int CHero::GetX2()
{
    return x + action[currentAni]->Height();
}
int CHero::GetY1()
{
    return y;
}
int CHero::GetY2()
{
    return y + action[currentAni]->Width();
}

void CHero::OnMove(CGamemap* m)
{
	if (blood <= 0)
		isAlive = false;
	action[currentAni]->OnMove();
	int space = foot.size();
	for (int i = 0; i < space; i++)
		foot[i]->OnMove();
	heroState->OnMoveState(m);


	if (currentState == HERO_STATE_ATTACK)
	{
		for (int i = 6; i < 18; i++)
		{
			if (action[i]->IsFinalBitmap() == true)
			{
				SetHeroState(HERO_STATE_STAY);
			}
		}
	}

	/*if (currentState == HERO_STATE_BEATTACKED)
	{
		for (int i = 19; i < 22; i++)
		{
			if (action[i]->IsFinalBitmap() == true)
			{
				SetHeroState(HERO_STATE_STAY);
			}
		}
	}*/

}
void CHero::ResetAttack()
{
	for(int i=6;i<18;i++)
		action[i]->Reset();

}
void CHero::ResetAttackBoss()
{
	for (int i = 19; i < 21; i++)
		action[i]->Reset();

}
void CHero::SetXY(int nx, int ny)
{
	x = nx;
	y = ny;
}
void CHero::SetDirectionStay(bool isDir)
{
	directionStay = isDir;
}
void CHero::SetIsAttack(bool attack)
{
	isAttack = attack;
}
void CHero::SetIsBeAttackedBoss(bool bossAttack)
{
	isBeAttackedBoss = bossAttack;
}
void CHero::SetIsCatch(bool ncatch)
{
	isCatch = ncatch;
}
void CHero::SetBlood(int b)
{
	blood = b;
}
void CHero::AddBitMaps(char* pic[], const int space, int number, int choose)
{
    if (choose == 1)						//action
    {
        int action_size = action.size();

        if (action_size == space)
            action.push_back(new CAnimation);

        for (int i = 0; i < number; i++)
            action[action.size() - 1]->AddBitmap(pic[i],RGB(204,204,204));
    }

    if (choose == 2)						//foot
    {
        int foot_size = foot.size();

        if (foot_size == space)
            foot.push_back(new CAnimation);

        for (int i = 0; i < number; i++)
            foot[foot.size() - 1]->AddBitmap(pic[i], RGB(204, 204, 204));
    }
}
void CHero::AttackBoss(CBoss *b)
{
	if (directionStay)
	{
		b->SetBossAni(B_RUNRIGHT);
		int disHeroX = (GetX1() + GetX2()) / 2;
		int disHeroY = (GetY1() + GetY2()) / 2;
		int sX1 = b->GetX1();
		int sX2 = b->GetX2();
		int sY1 = b->GetY1();
		int sY2 = b->GetY2();
		int disSmallX = (b->GetX1() + b->GetX2()) / 2;
		int disSmallY = (b->GetY1() + b->GetY2()) / 2;

		if (GetX1()-100 < sX1 && sX1-100 < GetX2() && sY1-50 < disHeroY && disHeroY < sY2+50 &&GetY1()-50 < sY1 && GetY2() + 100 > sY2)
		{
			b->ResetAttack();
			b->SetBossState(BOSS_STATE_BEATTACKED);
		}
		else
			b->SetBossState(BOSS_STATE_RUN);


	}
	else	/////////////	左邊攻擊	///////////
	{
		b->SetBossAni(B_RUNRIGHT);
		int disHeroX = (GetX1() + GetX2()) / 2;
		int disHeroY = (GetY1() + GetY2()) / 2;
		int sX1 = b->GetX1();
		int sX2 = b->GetX2();
		int sY1 = b->GetY1();
		int sY2 = b->GetY2();
		int disSmallX = (b->GetX1() + b->GetX2()) / 2;
		int disSmallY = (b->GetY1() + b->GetY2()) / 2;

		if (GetX1() < sX2 + 40 && sX2 < GetX2() && sY1-50 < disHeroY && disHeroY < sY2+50 &&GetY1() - 40 < sY1 && GetY2() + 100 > sY2)
		{
			b->ResetAttack();
			b->SetBossState(BOSS_STATE_BEATTACKED);
		}
		else
			b->SetBossState(BOSS_STATE_RUN);

	}
}
void CHero::AttackSmallPerson(CSmallPerson *s)
{
	if (directionStay)
	{
		s->SetSmallPersonAni(SRUNRIGHT);
		int disHeroX = (GetX1() + GetX2()) / 2;
		int disHeroY= (GetY1() + GetY2()) / 2 ;
		int sX1 = s->GetX1();
		int sX2 = s->GetX2();
		int sY1 = s->GetY1();
		int sY2 = s->GetY2();
		int disSmallX = (s->GetX1() + s->GetX2()) / 2;
		int disSmallY = (s->GetY1() + s->GetY2()) / 2;
		if (s->GetIsBeCatched())
		{
			s->SetSmallPersonState(S_STATE_BEATTACKED);
		}
		else if (GetX1()<sX1 && sX1 < GetX2() && sY1 < disHeroY && disHeroY < sY2 &&GetY1()<sY1 && GetY2()+100>sY2)
		{
			s->SetSmallPersonState(S_STATE_BEATTACKED);
		}
		else
			s->SetSmallPersonState(S_STATE_RUN);


	}
	else	/////////////	左邊攻擊	///////////
	{
		s->SetSmallPersonAni(SRUNRIGHT);
		int disHeroX = (GetX1() + GetX2()) / 2;
		int disHeroY = (GetY1() + GetY2()) / 2 ;
		int sX1 = s->GetX1();
		int sX2 = s->GetX2();
		int sY1 = s->GetY1();
		int sY2 = s->GetY2();
		int disSmallX = (s->GetX1() + s->GetX2()) / 2;
		int disSmallY = (s->GetY1() + s->GetY2()) / 2;
		if (s->GetIsBeCatched())
		{
			s->SetSmallPersonState(S_STATE_BEATTACKED);
		}
		else if (GetX1() < sX2+40 && sX2 < GetX2() && sY1 < disHeroY && disHeroY < sY2 &&GetY1()-20 < sY1 && GetY2() + 50 > sY2)
		{
			s->SetSmallPersonState(S_STATE_BEATTACKED);
		}
		else
			s->SetSmallPersonState(S_STATE_RUN);
	}
	/////////////////////////	Boss	///////////////////////
	
}
void CHero::LoadBitmap()
{
    avatar.LoadBitmap("./res/avatar.bmp", RGB(204, 204, 204));
    char* right_stay[19] = { "./res/RStay/RStay1.bmp", "./res/RStay/RStay2.bmp", "./res/RStay/RStay3.bmp", "./res/RStay/RStay4.bmp", "./res/RStay/RStay5.bmp",
                             "./res/RStay/RStay6.bmp", "./res/RStay/RStay7.bmp", "./res/RStay/RStay8.bmp", "./res/RStay/RStay9.bmp", "./res/RStay/RStay10.bmp",
                             "./res/RStay/RStay11.bmp", "./res/RStay/RStay12.bmp", "./res/RStay/RStay13.bmp", "./res/RStay/RStay14.bmp", "./res/RStay/RStay15.bmp",
                             "./res/RStay/RStay16.bmp", "./res/RStay/RStay17.bmp", "./res/RStay/RStay18.bmp", "./res/RStay/RStay19.bmp"};
    
	char* left_stay[19] = { "./res/LStay/LStay1.bmp", "./res/LStay/LStay2.bmp", "./res/LStay/LStay3.bmp", "./res/LStay/LStay4.bmp", "./res/LStay/LStay5.bmp",
                            "./res/LStay/LStay6.bmp", "./res/LStay/LStay7.bmp", "./res/LStay/LStay8.bmp", "./res/LStay/LStay9.bmp", "./res/LStay/LStay10.bmp",
                            "./res/LStay/LStay11.bmp", "./res/LStay/LStay12.bmp", "./res/LStay/LStay13.bmp", "./res/LStay/LStay14.bmp", "./res/LStay/LStay15.bmp",
                            "./res/LStay/LStay16.bmp", "./res/LStay/LStay17.bmp", "./res/LStay/LStay18.bmp", "./res/LStay/LStay19.bmp"};
    
	char* right_run[11] = { "./res/RRun/HeroRun1.bmp", "./res/RRun/HeroRun2.bmp", "./res/RRun/HeroRun3.bmp", "./res/RRun/HeroRun4.bmp", "./res/RRun/HeroRun5.bmp",
                            "./res/RRun/HeroRun6.bmp", "./res/RRun/HeroRun7.bmp"	, "./res/RRun/HeroRun8.bmp", "./res/RRun/HeroRun9.bmp", "./res/RRun/HeroRun10.bmp",
                            "./res/RRun/HeroRun11.bmp"};
    
	char* left_run[11] = { "./res/LRun/HeroRun1.bmp", "./res/LRun/HeroRun2.bmp", "./res/LRun/HeroRun3.bmp", "./res/LRun/HeroRun4.bmp", "./res/LRun/HeroRun5.bmp",
                           "./res/LRun/HeroRun6.bmp", "./res/LRun/HeroRun7.bmp"	, "./res/LRun/HeroRun8.bmp", "./res/LRun/HeroRun9.bmp", "./res/LRun/HeroRun10.bmp",
                           "./res/LRun/HeroRun11.bmp"};
   
	char* right_catch[6] = { "./res/catchSmallR/1.bmp", "./res/catchSmallR/2.bmp", "./res/catchSmallR/3.bmp", "./res/catchSmallR/4.bmp", "./res/catchSmallR/5.bmp",
                             "./res/catchSmallR/6.bmp"};
   
	char* left_catch[6] = { "./res/catchSmallL/1.bmp", "./res/catchSmallL/2.bmp", "./res/catchSmallL/3.bmp", "./res/catchSmallL/4.bmp", "./res/catchSmallL/5.bmp",
                            "./res/catchSmallL/6.bmp"};
    
	char* right_attack_A[9] = { "./res/RAttackA/1.bmp", "./res/RAttackA/2.bmp", "./res/RAttackA/3.bmp", "./res/RAttackA/4.bmp", "./res/RAttackA/5.bmp",
                                "./res/RAttackA/6.bmp", "./res/RAttackA/7.bmp", "./res/RAttackA/8.bmp", "./res/RAttackA/9.bmp"};
   
	char* left_attack_A[9] = { "./res/LAttackA/1.bmp", "./res/LAttackA/2.bmp", "./res/LAttackA/3.bmp", "./res/LAttackA/4.bmp", "./res/LAttackA/5.bmp",
                               "./res/LAttackA/6.bmp", "./res/LAttackA/7.bmp", "./res/LAttackA/8.bmp", "./res/LAttackA/9.bmp"};
    
	char* right_attack_AA[7] = { "./res/RAttackAA/1.bmp", "./res/RAttackAA/2.bmp", "./res/RAttackAA/3.bmp", "./res/RAttackAA/4.bmp", "./res/RAttackAA/5.bmp",
                                 "./res/RAttackAA/6.bmp", "./res/RAttackAA/7.bmp"};
    
	char* left_attack_AA[7] = { "./res/LAttackAA/1.bmp", "./res/LAttackAA/2.bmp", "./res/LAttackAA/3.bmp", "./res/LAttackAA/4.bmp", "./res/LAttackAA/5.bmp",
                                "./res/LAttackAA/6.bmp", "./res/LAttackAA/7.bmp"};
   
	char* right_attackAS[11] = { "./res/RAttackAS/1.bmp", "./res/RAttackAS/2.bmp", "./res/RAttackAS/3.bmp", "./res/RAttackAS/4.bmp", "./res/RAttackAS/5.bmp",
                                 "./res/RAttackAS/6.bmp", "./res/RAttackAS/7.bmp", "./res/RAttackAS/8.bmp", "./res/RAttackAS/9.bmp", "./res/RAttackAS/10.bmp",
                                 "./res/RAttackAS/11.bmp"};
    
	char* left_attackAS[11] = { "./res/LAttackAS/1.bmp", "./res/LAttackAS/2.bmp", "./res/LAttackAS/3.bmp", "./res/LAttackAS/4.bmp", "./res/LAttackAS/5.bmp",
                                "./res/LAttackAS/6.bmp", "./res/LAttackAS/7.bmp", "./res/LAttackAS/8.bmp", "./res/LAttackAS/9.bmp", "./res/LAttackAS/10.bmp",
                                "./res/LAttackAS/11.bmp"};
   
	char* right_attackS[10] = { "./res/RattackS/1.bmp", "./res/RattackS/2.bmp", "./res/RattackS/3.bmp", "./res/RattackS/4.bmp", "./res/RattackS/5.bmp",
                                "./res/RattackS/6.bmp", "./res/RattackS/7.bmp", "./res/RattackS/8.bmp", "./res/RattackS/9.bmp", "./res/RattackS/10.bmp",};
    
	char* left_attackS[10] = { "./res/LattackS/1.bmp", "./res/LattackS/2.bmp", "./res/LattackS/3.bmp", "./res/LattackS/4.bmp", "./res/LattackS/5.bmp",
                               "./res/LattackS/6.bmp", "./res/LattackS/7.bmp", "./res/LattackS/8.bmp", "./res/LattackS/9.bmp", "./res/LattackS/10.bmp",};
    
	char* right_attackSS[11] = { "./res/RattackSS/1.bmp", "./res/RattackSS/2.bmp", "./res/RattackSS/3.bmp", "./res/RattackSS/4.bmp", "./res/RattackSS/5.bmp",
                                 "./res/RattackSS/6.bmp", "./res/RattackSS/7.bmp", "./res/RattackSS/8.bmp", "./res/RattackSS/9.bmp", "./res/RattackSS/10.bmp",
                                 "./res/RattackSS/11.bmp"};
    
	char* left_attackSS[11] = { "./res/LattackSS/1.bmp", "./res/LattackSS/2.bmp", "./res/LattackSS/3.bmp", "./res/LattackSS/4.bmp", "./res/LattackSS/5.bmp",
                                "./res/LattackSS/6.bmp", "./res/LattackSS/7.bmp", "./res/LattackSS/8.bmp", "./res/LattackSS/9.bmp", "./res/LattackSS/10.bmp",
                                "./res/LattackSS/11.bmp"};
   
	char* right_catch_attack1[15] = { "./res/RCatchAttack1/1.bmp", "./res/RCatchAttack1/2.bmp", "./res/RCatchAttack1/3.bmp",  "./res/RCatchAttack1/4.bmp",  "./res/RCatchAttack1/5.bmp",
                                      "./res/RCatchAttack1/6.bmp", "./res/RCatchAttack1/7.bmp", "./res/RCatchAttack1/8.bmp", "./res/RCatchAttack1/9.bmp", "./res/RCatchAttack1/10.bmp",
                                      "./res/RCatchAttack1/11.bmp",  "./res/RCatchAttack1/12.bmp",  "./res/RCatchAttack1/13.bmp",  "./res/RCatchAttack1/14.bmp",  "./res/RCatchAttack1/15.bmp"  };
	
	char* left_catch_attack1[15] = { "./res/LCatchAttack1/1.bmp", "./res/LCatchAttack1/2.bmp", "./res/LCatchAttack1/3.bmp",  "./res/LCatchAttack1/4.bmp",  "./res/LCatchAttack1/5.bmp",
									  "./res/LCatchAttack1/6.bmp", "./res/LCatchAttack1/7.bmp", "./res/LCatchAttack1/8.bmp", "./res/LCatchAttack1/9.bmp", "./res/LCatchAttack1/10.bmp",
									  "./res/LCatchAttack1/11.bmp",  "./res/LCatchAttack1/12.bmp",  "./res/LCatchAttack1/13.bmp",  "./res/LCatchAttack1/14.bmp",  "./res/LCatchAttack1/15.bmp"};
	
	char* right_beAttack[9] = { "./res/heroBeHitR/1.bmp","./res/heroBeHitR/2.bmp", "./res/heroBeHitR/3.bmp","./res/heroBeHitR/4.bmp", "./res/heroBeHitR/5.bmp",
								"./res/heroBeHitR/6.bmp","./res/heroBeHitR/7.bmp","./res/heroBeHitR/8.bmp","./res/heroBeHitR/9.bmp"};
	
	char* left_beAttack[9] = { "./res/heroBeHitL/1.bmp","./res/heroBeHitL/2.bmp", "./res/heroBeHitL/3.bmp","./res/heroBeHitL/4.bmp", "./res/heroBeHitL/5.bmp",
							"./res/heroBeHitL/6.bmp","./res/heroBeHitL/7.bmp","./res/heroBeHitL/8.bmp","./res/heroBeHitL/9.bmp" };
	char* right_beAttack_boss[5] = { "./res/BeHitBossR/1.bmp","./res/BeHitBossR/2.bmp", "./res/BeHitBossR/3.bmp","./res/BeHitBossR/4.bmp", "./res/BeHitBossR/5.bmp" };
	char* left_beAttack_boss[5] = { "./res/BeHitBossL/1.bmp","./res/BeHitBossL/2.bmp", "./res/BeHitBossL/3.bmp","./res/BeHitBossL/4.bmp", "./res/BeHitBossL/5.bmp" };

	//////////////////////////	Foot	////////////////////////////
    char* right_stay_foot[1] = { "./res/RStay/RFoot.bmp" };
    char* left_stay_foot[1] = { "./res/LStay/LFoot.bmp" };
    char* right_catch_foot[11] = { "./res/CatchFootR/1.bmp", "./res/CatchFootR/2.bmp", "./res/CatchFootR/3.bmp", "./res/CatchFootR/4.bmp", "./res/CatchFootR/5.bmp"
                                   , "./res/CatchFootR/6.bmp", "./res/CatchFootR/7.bmp", "./res/CatchFootR/8.bmp", "./res/CatchFootR/9.bmp", "./res/CatchFootR/10.bmp",
                                   "./res/CatchFootR/11.bmp"  };
    char* left_catch_foot[11] = { "./res/CatchFootL/1.bmp", "./res/CatchFootL/2.bmp", "./res/CatchFootL/3.bmp", "./res/CatchFootL/4.bmp", "./res/CatchFootL/5.bmp"
                                  , "./res/CatchFootL/6.bmp", "./res/CatchFootL/7.bmp", "./res/CatchFootL/8.bmp", "./res/CatchFootL/9.bmp", "./res/CatchFootL/10.bmp",
                                  "./res/CatchFootL/11.bmp"  };

    AddBitMaps(right_stay, STAYRIGHT, 19, 1);
    AddBitMaps(left_stay, STAYLEFT, 19, 1);
    AddBitMaps(right_run, RUNRIGHT, 11, 1);
    AddBitMaps(left_run, RUNLEFT, 11, 1);
    AddBitMaps(right_catch, CATCHR, 6, 1);
    AddBitMaps(left_catch, CATCHL, 6, 1);
    AddBitMaps(right_attack_A, ATTACKRA, 9, 1);
    AddBitMaps(left_attack_A, ATTACKLA, 9, 1);
    AddBitMaps(right_attack_AA, ATTACKRAA, 7, 1);
    AddBitMaps(left_attack_AA, ATTACKLAA, 7, 1);
    AddBitMaps(right_attackAS, ATTACKRAS, 11, 1);
    AddBitMaps(left_attackAS, ATTACKLAS, 11, 1);
    AddBitMaps(right_attackS, ATTACKRS, 10, 1);
    AddBitMaps(left_attackS, ATTACKLS, 10, 1);
    AddBitMaps(right_attackSS, ATTACKRSS, 11, 1);
    AddBitMaps(left_attackSS, ATTACKLSS, 11, 1);
    AddBitMaps(right_catch_attack1, CATCHATTACKR1, 15, 1);
	AddBitMaps(left_catch_attack1, CATCHATTACKL1, 15, 1);
	AddBitMaps(right_beAttack, BEATTACKR, 9,1);
	AddBitMaps(left_beAttack, BEATTACKL, 9,1);
	AddBitMaps(right_beAttack_boss, BEATTACKBOSSR, 5, 1);
	AddBitMaps(left_beAttack_boss, BEATTACKBOSSL, 5, 1);

    AddBitMaps(right_stay_foot, FOOT_STAY_R, 1, 2);
    AddBitMaps(left_stay_foot, FOOT_STAY_L, 1, 2);
    AddBitMaps(right_catch_foot, FOOT_CATCH_R, 11, 2);
    AddBitMaps(left_catch_foot, FOOT_CATCH_L, 11, 2);
	AddBitMaps(right_stay_foot, FOOT_STAY_CATCH_R, 1, 2);
	AddBitMaps(left_stay_foot, FOOT_STAY_CATCH_L, 1, 2);
}

void CHero::SetIsBeAttacked(bool attack)
{
	isBeAttacked = attack;
}

}
