#include "CHero.h"
#include "CSmallPerson.h"
#include "CBullet.h"
#include "CBoss.h"
namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////

enum AUDIO_ID  				// 定義各種音效的編號
{
    AUDIO_BGM,				// 0
    AUDIO_START,				// 1
	AUDIO_PASS,
	AUDIO_DIED,
	AUDIO_DIED_ANGEL,
	AUDIO_ATTACKF1,
	AUDIO_ATTACKF2,
	AUDIO_ATTACKF3,
	AUDIO_ATTACKF4,
	AUDIO_ATTACKT1,
	AUDIO_ATTACKT2,
	AUDIO_ATTACKT3,
	AUDIO_ATTACKT4,
	AUDIO_END
};

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////


class CGameStateInit : public CGameState
{
public:
	CGameStateInit(CGame* g);
	void OnInit();  								// 遊戲的初值及圖形設定
	void OnBeginState();							// 設定每次重玩所需的變數
	void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
	void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	void AddBitMaps(char* pic[], int, CAnimation*, int);
	void LoadBitmap();
	void LoadAudio();
	void OnMouseMove(UINT nFlags, CPoint point);

protected:
	void OnShow();									// 顯示這個狀態的遊戲畫面
private:
	CAnimation dad;
	CAnimation heroBack;
	CAnimation horse;
	CAnimation start, startHover, about, aboutPic, back;
	CAnimation intro, introHover, introAni;
	bool isStartHover, isIntroHover;
	bool isIntroClick, isAboutClick;
	int dadX = -648, heroX = 633;
};

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateRun : public CGameState
{
    public:
        CGameStateRun(CGame* g);
        ~CGameStateRun();
        void OnBeginState();							// 設定每次重玩所需的變數
        void OnInit();  								// 遊戲的初值及圖形設定
        void OnKeyDown(UINT, UINT, UINT);
        void OnKeyUp(UINT, UINT, UINT);
    protected:
		void Transitions();
        void OnMove();									// 移動遊戲元素
        void OnShow();									// 顯示這個狀態的遊戲畫面
    private:
        CGamemap		gamemap;

        const int		NUMBALLS;	// 球的總數
        CHero			hero;		// 拍子
        CSmallPerson*	smallPerson;
		CBoss			boss;
		CBullet			bullet[10];
		const int		BULLETS;
		int				bulletCount;
		int				round;
};

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateOver : public CGameState
{
    public:
        CGameStateOver(CGame* g);
        void OnBeginState();							// 設定每次重玩所需的變數
        void OnInit();
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnMouseMove(UINT nFlags, CPoint point);
		void AddBitMaps(char* pic[], int, CAnimation*,int);
		void LoadBitmap();
protected:
        void OnMove();									// 移動遊戲元素
        void OnShow();									// 顯示這個狀態的遊戲畫面
    private:
		CAnimation gameOver;
		CAnimation revived;
		CAnimation playAgain, playAgainHover;
		CMovingBitmap exit;
		bool isRevived;
		bool isPlayAgainHover;
		
};
class CGameStatePass : public CGameState
{
public:
	CGameStatePass(CGame* g);
	void OnBeginState();							// 設定每次重玩所需的變數
	void OnInit();
	void OnKeyDown(UINT, UINT, UINT);
	void OnKeyUp(UINT, UINT, UINT);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void AddBitMaps(char* pic[], int, CAnimation*, int);
	void LoadBitmap();

protected:
	void OnMove();									// 移動遊戲元素
	void OnShow();									// 顯示這個狀態的遊戲畫面
private:
	CAnimation passBack, passHero;
	CAnimation drive, car;
	CAnimation win, exit, playAgain, playAgainHover;
	bool isPlayAgainHover, isExitHover;
	int heroY = 480, carX = -400;
};

}