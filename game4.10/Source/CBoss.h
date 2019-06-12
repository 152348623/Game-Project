#ifndef CBOSS_H
#define CBOSS_H
#include <vector>

namespace game_framework
{
	enum SBOSSSTATE
	{
		BOSS_STATE_RUN,
		BOSS_STATE_ATTACK,
		BOSS_STATE_BEATTACKED,
		BOSS_STATE_END
	};
	enum BOSSACTION
	{
		B_RUNRIGHT,
		B_RUNLEFT,
		B_BEHITR1,
		B_BEHITR2,
		B_BEHITR3,
		B_BEHITR4,
		B_BEHITL1,
		B_BEHITL2,
		B_BEHITL3,
		B_BEHITL4,
		B_ATTACKR,
		B_ATTACKL,
		B_ACTION_END

	};
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////
	class CHero;
	class CBossState;
	class CBoss
	{
	public:
		CBoss();
		void OnInit();
		void OnInitState();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		bool GetIsBeCatched();
		bool GetIsBeAttacked();
		bool GetIsDirectionStay();
		bool GetMovingDown();
		bool GetMovingLeft();
		bool GetMovingRight();
		bool GetMovingUp();
		bool GetIsAttack();
		int GetAni(int);
		bool GetIsFinalAni();
		int GetCurrentState();
		bool GetIsAlive();
		int GetBlood();
		void Initialize();				// �]�whero����l��
		void OnKeyDown(UINT nChar);
		void OnKeyUp(UINT nChar);
		void LoadBitmap();				// ���J�ϧ�
		void OnMove(CGamemap*);					// ����hero
		void OnShow(CGamemap*, CHero*);					// �Nhero�ϧζK��e��
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetXY(int nx, int ny);		// �]�whero���W���y��
		void SetBlood(int blood);
		bool GetDirectionStay();
		void SetBossState(int);
		void SetBossAni(int);
		void ShowBlood(int percent);
		void SetIsAlive(bool);
		void SetIsBeCatched(bool);
		void SetIsAttack(bool);
		void SetIsBeAttacked(bool);
		void SetDirectionStay(int);
		void SetBloodPercent(int);
		bool IsAlive();
		bool HitHero(CHero* hero);

		void SetAttack(CHero*);
		void StopAttack(UINT);
		void ResetAttack();
		void AddBitMaps(char* pic[], int, int);
		void LoadBitMaps(char* pic[], int, int);
		~CBoss();
	protected:
		int random_num;
		int x, y;					// hero���W���y��   //�D���b�a�ϤW���I���� ���O�ù�����
		bool directionStay;			//�Ȧs��V
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isAttack;				// �O�_���b����
		bool isBeAttacked;			// �O�_�Q����
		bool isAlive;
		bool isBeCatched;
		vector<CAnimation*> bossAction;

		CMovingBitmap blood;
		CBossState* bossState;
		CBossState* bossStateTable[3];
		int countRandomTime = 0;
		int bloodPercent;
		int currentState;
		int currentAni;
		int actionX[B_ACTION_END];
		int actionY[B_ACTION_END];
	private:
		bool HitRectangle(int, int, int, int);
	};
}
#endif // !CBOSS_H

