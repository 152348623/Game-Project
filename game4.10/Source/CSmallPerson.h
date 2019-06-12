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
// 這個class提供可以用鍵盤或滑鼠控制的擦子
// 看懂就可以改寫成自己的程式了
/////////////////////////////////////////////////////////////////////////////
class CHero;
class CSmallPersonState;
class CSmallPerson
{
    public:
        CSmallPerson();
		void OnInit();
		void OnInitState();
        int  GetX1();					// 擦子左上角 x 座標
        int  GetY1();					// 擦子左上角 y 座標
        int  GetX2();					// 擦子右下角 x 座標
        int  GetY2();					// 擦子右下角 y 座標
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
		
        void Initialize();				// 設定hero為初始值
		void OnKeyDown(UINT nChar);
		void OnKeyUp(UINT nChar);
        void LoadBitmap();				// 載入圖形
        void OnMove(CGamemap*);					// 移動hero
        void OnShow(CGamemap*, CHero*);					// 將hero圖形貼到畫面
        void SetMovingDown(bool flag);	// 設定是否正在往下移動
        void SetMovingLeft(bool flag);	// 設定是否正在往左移動
        void SetMovingRight(bool flag); // 設定是否正在往右移動
        void SetMovingUp(bool flag);	// 設定是否正在往上移動
        void SetXY(int nx, int ny);		// 設定hero左上角座標
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
        int x, y;					// hero左上角座標   //主角在地圖上的點坐標 不是螢幕坐標
        bool directionStay;			//暫存方向
        bool isMovingDown;			// 是否正在往下移動
        bool isMovingLeft;			// 是否正在往左移動
        bool isMovingRight;			// 是否正在往右移動
        bool isMovingUp;			// 是否正在往上移動
        bool isAttack;				// 是否正在攻擊
		bool isBeAttacked;			// 是否被攻擊
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