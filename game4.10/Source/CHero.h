#include <vector>
#ifndef CHERO_H
#define CHERO_H

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	enum HERO_STATE
	{
		HERO_STATE_STAY,
		HERO_STATE_RUN,
		HERO_STATE_ATTACK,
		HERO_STATE_CATCH,
		HERO_STATE_BEATTACKED,
		HERO_STATE_END
	};
	enum ACTION
	{
		STAYRIGHT,
		STAYLEFT,
		RUNRIGHT,
		RUNLEFT,
		CATCHR,
		CATCHL,
		ATTACKRA,
		ATTACKLA,
		ATTACKRAA,
		ATTACKLAA,
		ATTACKRAS,
		ATTACKLAS,
		ATTACKRS,
		ATTACKLS,
		ATTACKRSS,
		ATTACKLSS,
		CATCHATTACKR1,
		CATCHATTACKL1,
		BEATTACKR,
		BEATTACKL,
		BEATTACKBOSSR,
		BEATTACKBOSSL,
		ACTION_END
	};
	enum FOOT
	{
		FOOT_STAY_R,
		FOOT_STAY_L,
		FOOT_CATCH_R,
		FOOT_CATCH_L,
		FOOT_STAY_CATCH_R,
		FOOT_STAY_CATCH_L,
		FOOT_END
	};

	class CSmallPerson;
	class CBoss;
	class CHeroState;
	class CHeroRunState;
	class CHeroAttackState;
	class CHero
	{
	public:
		CHero();
		~CHero();
		void Initialize();				// 設定hero為初始值
		void OnInit();
		void OnInitState();
		void SetHeroState(int);
		void SetHeroAni(int);
		void SetHeroAniFoot(int);
		bool GetIsCatch();
		bool GetIsAttack();
		bool GetIsBeAttacked();
		bool GetIsBeAttackedBoss();
		int GetHeroState();
		bool GetMovingDown();
		bool GetMovingLeft();
		bool GetMovingRight();
		bool GetMovingUp();
		bool GetDirectionStay();
		int GetBlood();
		bool GetIsAlive();
		int GetAni(int);
		int GetCurrentAni();
		bool GetIsFinalAni();
		bool HitSmallPerson(CSmallPerson* person);
		void OnKeyDown(UINT nChar);
		void OnKeyUp(UINT nChar);
		void ShowBlood(int percent);						// 顯示初始化的進度
		void SetMovingDown(bool flag); // 設定是否正在往下移動
		void SetMovingLeft(bool flag); // 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag); // 設定是否正在往上移動
		void SetXY(int, int);
		void SetDirectionStay(bool);
		void SetIsAttack(bool);
		void SetIsBeAttackedBoss(bool);
		void SetIsCatch(bool);
		void SetBlood(int);
		void LoadBitmap();
		void SetIsBeAttacked(bool);
		void AddBitMaps(char* pic[], int, int,int);
		void AttackSmallPerson(CSmallPerson *s);
		void AttackBoss(CBoss *b);
		int  GetX1();     // 擦子左上角 x 座標
		int  GetY1();     // 擦子左上角 y 座標
		int  GetX2();     // 擦子右下角 x 座標
		int  GetY2();     // 擦子右下角 y 座標
		void OnShow(CGamemap*);
		void OnMove(CGamemap*);


		void ResetAttack();
		void ResetAttackBoss();

	protected:
		CMovingBitmap	avatar;
		int blood;
		CHeroState* heroState;				// 指向現在state
		CHeroState* heroStateTable[HERO_STATE_END];
		int currentAni,currentState;
		int currentAniFoot;
		vector<CAnimation*> action;
		vector<CAnimation*> foot;
		int actionX[ACTION_END],actionY[ACTION_END];	//調圖片 (身體)
		int footX[FOOT_END], footY[FOOT_END];			// 調圖片 (腳)
		int x, y;
		bool isMovingDown;   // 是否正在往下移動
		bool isMovingLeft;   // 是否正在往左移動
		bool isMovingRight;   // 是否正在往右移動
		bool isMovingUp;   // 是否正在往上移動
		bool directionStay;
		bool isAttack;
		bool isBeAttackedBoss;
		bool isCatch;
		bool isBeAttacked;
		bool isAlive;
	private:
		bool HitRectangle(int, int, int, int);
	};
}
#endif
