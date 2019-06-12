#include <vector>
#ifndef CHERO_H
#define CHERO_H

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
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
		void Initialize();				// �]�whero����l��
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
		void ShowBlood(int percent);						// ��ܪ�l�ƪ��i��
		void SetMovingDown(bool flag); // �]�w�O�_���b���U����
		void SetMovingLeft(bool flag); // �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag); // �]�w�O�_���b���W����
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
		int  GetX1();     // ���l���W�� x �y��
		int  GetY1();     // ���l���W�� y �y��
		int  GetX2();     // ���l�k�U�� x �y��
		int  GetY2();     // ���l�k�U�� y �y��
		void OnShow(CGamemap*);
		void OnMove(CGamemap*);


		void ResetAttack();
		void ResetAttackBoss();

	protected:
		CMovingBitmap	avatar;
		int blood;
		CHeroState* heroState;				// ���V�{�bstate
		CHeroState* heroStateTable[HERO_STATE_END];
		int currentAni,currentState;
		int currentAniFoot;
		vector<CAnimation*> action;
		vector<CAnimation*> foot;
		int actionX[ACTION_END],actionY[ACTION_END];	//�չϤ� (����)
		int footX[FOOT_END], footY[FOOT_END];			// �չϤ� (�})
		int x, y;
		bool isMovingDown;   // �O�_���b���U����
		bool isMovingLeft;   // �O�_���b��������
		bool isMovingRight;   // �O�_���b���k����
		bool isMovingUp;   // �O�_���b���W����
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
