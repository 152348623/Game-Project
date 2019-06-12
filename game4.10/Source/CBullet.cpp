#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CSmallPerson.h"
#include <time.h>
#include "CHero.h"
#include "CBullet.h"
namespace game_framework
{
	void CBullet::Initialize()
	{
		isAlive = false;
		x = 300;
		y = 300;
		isDirectionStay = true;
	}
	void CBullet::OnBegin()
	{

	}
	void CBullet::LoadBitmap()
	{
		bulletR.LoadBitmap("./res/bulletR.bmp", RGB(204, 204, 204));
		bulletL.LoadBitmap("./res/bulletL.bmp", RGB(204, 204, 204));
	}

	void CBullet::OnMove(CGamemap *m, CSmallPerson *s)
	{
		if (isDirectionStay)
		{
			x += 7;
		}
		else
		{
			x -= 7;
		}
	}

	void CBullet::OnShow(CGamemap *m)
	{
		if (isDirectionStay)
		{
			bulletR.SetTopLeft(m->ScreenX(x), m->ScreenY(y + 30));
			bulletR.ShowBitmap();
		}
		else
		{
			bulletL.SetTopLeft(m->ScreenX(x - 60), m->ScreenY(y + 30));
			bulletL.ShowBitmap();
		}
	}

	CBullet::CBullet()
	{

	}

	int CBullet::GetX1()
	{
		return x;
	}

	int CBullet::GetY1()
	{
		return y;
	}

	int CBullet::GetX2()
	{
		return x + bulletR.Width();
	}

	int CBullet::GetY2()
	{
		return y + bulletL.Height();
	}

	bool CBullet::GetIsAlive()
	{
		return isAlive;
	}

	bool CBullet::GetIsDirectionStay()
	{
		return isDirectionStay;
	}

	void CBullet::SetXY(int nx, int ny)
	{
		x = nx;
		y = ny;
	}

	void CBullet::SetIsAlive(bool alive)
	{
		isAlive = alive;
	}

	void CBullet::SetIsDirectionStay(bool isDir)
	{
		isDirectionStay = isDir;
	}

}