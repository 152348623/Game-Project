#ifndef CSMALLPERSON_H
#define CSMALLPERSON_H

namespace game_framework
{
enum SMALLSTATE
{
	S_STATE_RUN,
	S_STATE_ATTACK,
	S_STATE_BEATTACKED,
	S_STATE_BECATCHED,
	S_STATE_END
};
enum SMALLACTION
{
    SRUNRIGHT,
    SRUNLEFT,
    BECATCHEDR,
    BECATCHEDL,
	BEHITR1,
	BEHITR2,
	BEHITR3,
	BEHITR4,
	BEHITL1,
	BEHITL2,
	BEHITL3,
	BEHITL4,
	/*BEATTACKEDR,
    BEATTACKEDL,*/
	DIEDL,
	DIEDR, 
	SATTACKR,
	SATTACKL,
	SACTION_END
    
};
/////////////////////////////////////////////////////////////////////////////
// �o��class���ѥi�H����L�ηƹ�������l
// �����N�i�H��g���ۤv���{���F
/////////////////////////////////////////////////////////////////////////////
class CHero;
class CSmallPersonState;
class CSmallPerson
{
    public:
        CSmallPerson();
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
		void SetSmallPersonState(int);
		void SetSmallPersonAni(int);
		void SetSmallPersonCloth(int);
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
        ~CSmallPerson();
		int smallChoose;
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
        vector<CAnimation*> smallAction;
        vector<CMovingBitmap*> smallClothesR;
        vector<CMovingBitmap*> smallClothesL;
		vector<CMovingBitmap*> blood;
		CSmallPersonState* smallState;
		CSmallPersonState* smallStateTable[4];
		int countRandomTime = 0;
		int bloodPercent;
		int currentState;
		int currentAni,currentCloth;
		int actionX[SACTION_END],clothesX[4];
		int actionY[SACTION_END], clothesY[4];
    private:
        bool HitRectangle(int, int, int, int);
};
}

#endif