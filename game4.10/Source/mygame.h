#include "CHero.h"
#include "CSmallPerson.h"
#include "CBullet.h"
#include "CBoss.h"
namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////

enum AUDIO_ID  				// �w�q�U�ح��Ī��s��
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
// �o��class���C�����C���}�Y�e������
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////


class CGameStateInit : public CGameState
{
public:
	CGameStateInit(CGame* g);
	void OnInit();  								// �C������Ȥιϧγ]�w
	void OnBeginState();							// �]�w�C�������һݪ��ܼ�
	void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
	void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	void AddBitMaps(char* pic[], int, CAnimation*, int);
	void LoadBitmap();
	void LoadAudio();
	void OnMouseMove(UINT nFlags, CPoint point);

protected:
	void OnShow();									// ��ܳo�Ӫ��A���C���e��
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
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

class CGameStateRun : public CGameState
{
    public:
        CGameStateRun(CGame* g);
        ~CGameStateRun();
        void OnBeginState();							// �]�w�C�������һݪ��ܼ�
        void OnInit();  								// �C������Ȥιϧγ]�w
        void OnKeyDown(UINT, UINT, UINT);
        void OnKeyUp(UINT, UINT, UINT);
    protected:
		void Transitions();
        void OnMove();									// ���ʹC������
        void OnShow();									// ��ܳo�Ӫ��A���C���e��
    private:
        CGamemap		gamemap;

        const int		NUMBALLS;	// �y���`��
        CHero			hero;		// ��l
        CSmallPerson*	smallPerson;
		CBoss			boss;
		CBullet			bullet[10];
		const int		BULLETS;
		int				bulletCount;
		int				round;
};

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

class CGameStateOver : public CGameState
{
    public:
        CGameStateOver(CGame* g);
        void OnBeginState();							// �]�w�C�������һݪ��ܼ�
        void OnInit();
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnMouseMove(UINT nFlags, CPoint point);
		void AddBitMaps(char* pic[], int, CAnimation*,int);
		void LoadBitmap();
protected:
        void OnMove();									// ���ʹC������
        void OnShow();									// ��ܳo�Ӫ��A���C���e��
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
	void OnBeginState();							// �]�w�C�������һݪ��ܼ�
	void OnInit();
	void OnKeyDown(UINT, UINT, UINT);
	void OnKeyUp(UINT, UINT, UINT);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void AddBitMaps(char* pic[], int, CAnimation*, int);
	void LoadBitmap();

protected:
	void OnMove();									// ���ʹC������
	void OnShow();									// ��ܳo�Ӫ��A���C���e��
private:
	CAnimation passBack, passHero;
	CAnimation drive, car;
	CAnimation win, exit, playAgain, playAgainHover;
	bool isPlayAgainHover, isExitHover;
	int heroY = 480, carX = -400;
};

}