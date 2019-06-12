
/////////////////////////////////////////////////////////////////////////////
// �w�q�C���i�]�w�����һP����
/////////////////////////////////////////////////////////////////////////////

#define SIZE_X				 640		// �]�w�C���e�����ѪR�׬�640x480
#define SIZE_Y				 480		// ���G�Y���ϥμзǪ��ѪR�סA�h�����������ù�
#define OPEN_AS_FULLSCREEN	 false		// �O�_�H���ù��覡�}�ҹC��
#define SHOW_LOAD_PROGRESS   true		// �O�_���loading(OnInit)���i��
#define DEFAULT_BG_COLOR	 RGB(0,0,0)	// �C���e���w�]���I���C��(�¦�)
#define GAME_CYCLE_TIME		 33		    // �C33ms�]�@��Move��Show(�C��30��)
#define SHOW_GAME_CYCLE_TIME true		// �O�_�bdebug mode���cycle time
#define ENABLE_GAME_PAUSE	 true		// �O�_���\�H Ctrl-Q �Ȱ��C��
#define ENABLE_AUDIO		 true		// �Ұʭ��Ĥ���

/////////////////////////////////////////////////////////////////////////////
// �w�qCGame��CGameState�ҨϥΪ��T�Ӫ��A�`��
/////////////////////////////////////////////////////////////////////////////

enum GAME_STATES
{
    GAME_STATE_INIT,
    GAME_STATE_RUN,
    GAME_STATE_OVER,
	GAME_STATE_PASS
};

/////////////////////////////////////////////////////////////////////////////
// Header for STL (Standard Template Library)
/////////////////////////////////////////////////////////////////////////////

#include <list>
#include <vector>
#include <map>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// �^���{�����~�Ϊ�macro
// �Ƶ��G�o�̨ϥ�macro�H�K�O�d�ɮצW�٤Φ渹�A�Q��debug�C
/////////////////////////////////////////////////////////////////////////////

#define GAME_ASSERT(boolexp,str)											\
		if (!(boolexp)) {													\
			int id;															\
			char s[300]="";													\
			sprintf(s,"Game fatal error:\n\n%s\n\nFile: %s\n\nLine: %d"		\
				"\n\n(Press Retry to debug the application, "				\
				"if it is executed in debug mode.)"							\
				"\n(Press Cancel otherwise.)",								\
				 str , __FILE__,__LINE__);									\
			id = AfxMessageBox(s, MB_RETRYCANCEL);							\
			if (id == IDCANCEL)												\
				exit(1);													\
			AfxDebugBreak();												\
		}

namespace game_framework
{

/////////////////////////////////////////////////////////////////////////////
// �o��class���Ѯɶ��B���~������
// �@�몺�C���ä��ݪ����ާ@�o�Ӫ���A�]���i�H���޳o��class���ϥΤ�k
/////////////////////////////////////////////////////////////////////////////

class CSpecialEffect
{
    public:
        static void  SetCurrentTime();					// �x�s�ثe���ɶ���ctime
        static DWORD GetEllipseTime();					// Ū���ثe���ɶ� - ctime
        static int   GetCurrentTimeCount();				// Ū���x�sctime������
        static void  Delay(DWORD ms);					// ���� x ms
        static void  DelayFromSetCurrentTime(DWORD ms);	// ��ctime�_��A���� x ms
    private:
        static DWORD ctime;
        static int	 ctimeCount;
};

/////////////////////////////////////////////////////////////////////////////
// �o��class�|�إ�DirectDraw����A�H���Ѩ�Lclass�ϥ�
// �@�몺�C���ä��ݪ����ާ@�o�Ӫ���A�]���i�H���޳o��class���ϥΤ�k
/////////////////////////////////////////////////////////////////////////////

class CDDraw
{
        friend class CMovingBitmap;
    public:
        ~CDDraw();
        static void  BltBackColor(DWORD);		// �NBack plain�����ۤW���w���C��
        static void  BltBackToPrimary();		// �NBack plain�K��Primary plain
        static CDC*  GetBackCDC();				// ���oBack Plain��DC (device context)
        static void  GetClientRect(CRect& r);	// ���o�]�w���ѪR��
        static void  Init(int, int);			// Initialize direct draw
        static void  ReleaseBackCDC();			// ��Back Plain��DC (device context)
        static bool  SetFullScreen(bool);		// �]�w�����ù��Ҧ�/�����Ҧ�
        static bool  IsFullScreen();			// �^���O�_�����ù��Ҧ�/�����Ҧ�
    private:
        CDDraw();								// private constructor
        static void  BltBitmapToBack(unsigned SurfaceID, int x, int y);
        static void  BltBitmapToBack(unsigned SurfaceID, int x, int y, double factor);
        static void  BltBitmapToBitmap(unsigned SourceID, unsigned TargetID, int x, int y);
        static void	 CheckDDFail(char* s);
        static bool  CreateSurface();
        static bool  CreateSurfaceFullScreen();
        static bool  CreateSurfaceWindowed();
        static void  LoadBitmap(int i, int IDB_BITMAP);
        static void  LoadBitmap(int i, char* filename);
        static DWORD MatchColorKey(LPDIRECTDRAWSURFACE lpDDSurface, COLORREF color);
        static int   RegisterBitmap(int IDB_BITMAP, COLORREF ColorKey);
        static int   RegisterBitmap(char* filename, COLORREF ColorKey);
        static void  ReleaseSurface();
        static void  RestoreSurface();
        static void  SetColorKey(unsigned SurfaceID, COLORREF color);
        static HDC					hdc;
        static CDC					cdc;
        static CView*				pCView;
        static LPDIRECTDRAW2		lpDD;
        static LPDIRECTDRAWCLIPPER	lpClipperPrimary;
        static LPDIRECTDRAWCLIPPER	lpClipperBack;
        static LPDIRECTDRAWSURFACE	lpDDSPrimary;
        static LPDIRECTDRAWSURFACE	lpDDSBack;
        static vector<LPDIRECTDRAWSURFACE>	lpDDS;
        static HRESULT				ddrval;
        static vector<int>			BitmapID;
        static vector<string>		BitmapName;
        static vector<CRect>		BitmapRect;
        static vector<COLORREF>		BitmapColorKey;
        static bool					fullscreen;
        static CDDraw				ddraw;
        static int					size_x, size_y;
};

/////////////////////////////////////////////////////////////////////////////
// �o��class���ѰʺA(�i�H����)���ϧ�
// �C��Public Interface���Ϊk���n���AImplementation�i�H����
/////////////////////////////////////////////////////////////////////////////

class CMovingBitmap
{
    public:
        CMovingBitmap();
        int   Height();						// ���o�ϧΪ�����
        int   Left();						// ���o�ϧΪ����W���� x �y��
        void  LoadBitmap(int, COLORREF = CLR_INVALID);		// ���J�ϡA���w�Ϫ��s��(resource)�γz����
        void  LoadBitmap(char*, COLORREF = CLR_INVALID);	// ���J�ϡA���w�Ϫ��ɦW�γz����
        void  SetTopLeft(int, int);			// �N�Ϫ����W���y�в��� (x,y)
        void  ShowBitmap();					// �N�϶K��ù�
        void  ShowBitmap(double factor);	// �N�϶K��ù� factor < 1���Y�p�A>1�ɩ�j�C�`�N�G�ݭnVGA�d�w�骺�䴩�A�_�h�|�ܺC
        void  ShowBitmap(CMovingBitmap&);	// �N�϶K���t�@�i�ϤW (�ȨѯS���γ~)
        int   Top();						// ���o�ϧΪ����W���� y �y��
        int   Width();						// ���o�ϧΪ��e��
    protected:
        CRect    location;			// location of the bitmap
        bool     isBitmapLoaded;	// whether a bitmap has been loaded
        unsigned SurfaceID;			// the surface id of this bitmap
};

/////////////////////////////////////////////////////////////////////////////
// �o��class���ѥi�H���ʪ��ʵe
// �C��Public Interface���Ϊk���n���AImplementation�i�H����
/////////////////////////////////////////////////////////////////////////////

class CAnimation
{
    public:
        CAnimation(int = 1);				// Constructor (�w�]�ʵe�����W�v�C1/3�����@�i��)
        void  AddBitmap(int, COLORREF = CLR_INVALID);
        // �W�[�@�i�ϧΦܰʵe(�Ϫ��s���γz����)
        void  AddBitmap(char*, COLORREF = CLR_INVALID);
        // �W�[�@�i�ϧΦܰʵe(�Ϫ��ɦW�γz����)
        int   GetCurrentBitmapNumber();	// ���o���b����bitmap�O�ĴX��bitma
		bool GetPause();
        int   Height();					// ���o�ʵe������
        bool  IsFinalBitmap();			// �^�ǥ��b����bitmap�O�_���̫�@��bitmap
        int   Left();					// ���o�ʵe�����W���� x �y��
        void  OnMove();					// ���W�v��bitmap
        void  OnShow();					// �N�ʵe�K��ù�
        void  Reset();					// ���]���񶶧Ǧ^��Ĥ@�i�ϧ�
        void  SetDelayCount(int);		// �]�w�ʵe����t�ת��`��(�V�j�V�C)
        void  SetTopLeft(int, int);		// �N�ʵe�����W���y�в��� (x,y)
		void  SetPause(bool);
        int   Top();					// ���o�ʵe�����W���� y �y��
        int   Width();					// ���o�ʵe���e��
        int	  Getttt();
    private:
        list<CMovingBitmap>				bmp;			// list of CMovingBitmap
        list<CMovingBitmap>::iterator	bmp_iter;		// list iterator
        int								bmp_counter;	// �x�sbmp_iter����n��bmp
        int								ttt;
        int								delay_counter;	// ���w�ʵe����t�ת��p�ƾ�
        int								delay_count;	// �ʵe����t�ת��`��
        int								x, y;			// �ʵe���y��
		bool							pause;
		bool							repeat;
		int								times;
};
//////////////////////////////////
class CGamemap
{
    public:
        CGamemap();
        void LoadBitmap();
		void Initialize();
        void OnShow();
        void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
        void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
        void SetMovingRight(bool flag); // �]�w�O�_���b���k����
        void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetRoundMap(int round);
        void SetSX();
        void SetSY();
        bool IsEmpty(int, int);
        int ScreenX(int);
        int ScreenY(int);
		int GetSX();
		int GetSY();
		int GetRoundMap();
		bool GetIsPass();
		void SetIsPass(int pass);
    private:
        int map[4];
        int check[8][10];
        CMovingBitmap map0, map1,map2,map3;
        int sx, sy;    //(sx,sy) ���ù�(�����W��)�b�a�ϤW���I�y��
        const int ROW, COL;
        bool isMovingDown;			// �O�_���b���U����
        bool isMovingLeft;			// �O�_���b��������
        bool isMovingRight;			// �O�_���b���k����
        bool isMovingUp;			// �O�_���b���W����
		int roundMap;
		bool isPass;
        const int MW;
};
/////////////////////////////////////////////////////////////////////////////
// �o��class������ܾ�ƹϧΪ���O
// �C��Public Interface���Ϊk���n���AImplementation�i�H����
/////////////////////////////////////////////////////////////////////////////

class CInteger
{
    public:
        CInteger(int = 5);			// default 5 digits
        void Add(int n);			// �W�[��ƭ�
        int  GetInteger();			// �^�Ǿ�ƭ�
        void LoadBitmap();			// ���J0..9�έt�����ϧ�
        void SetInteger(int);		// �]�w��ƭ�
        void SetTopLeft(int, int);	// �N�ʵe�����W���y�в��� (x,y)
        void ShowBitmap();			// �N�ʵe�K��ù�
    private:
        const int NUMDIGITS;			// �@���NUMDIGITS�Ӧ��
        static CMovingBitmap digit[11]; // �x�s0..9�έt�����ϧ�(bitmap)
        int x, y;						// ��ܪ��y��
        int n;							// ��ƭ�
        bool isBmpLoaded;				// �O�_�w�g���J�ϧ�
};

/////////////////////////////////////////////////////////////////////////////
// �ŧi�|���w�q��class
/////////////////////////////////////////////////////////////////////////////

class CGame;
class CGameStateInit;
class CGameStateRun;
class CGameStateOver;
class CGameStatePass;
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����U�ت��A��Base class(�O�@��abstract class)
// �C��Public Interface���Ϊk���n���AImplementation�i�H����
/////////////////////////////////////////////////////////////////////////////

class CGameState
{
    public:
        CGameState(CGame* g);
        void OnDraw();			// Template Method
        void OnCycle();			// Template Method
        //
        // virtual functions, ���~�Ӫ̴���implementation
        //
        virtual ~CGameState() {}								// virtual destructor
        virtual void OnBeginState() {}							// �]�w�C���i�J�o�Ӫ��A�ɩһݪ����
        virtual void OnInit() {}								// ���A����Ȥιϧγ]�w
        virtual void OnKeyDown(UINT, UINT, UINT) {}				// �B�z��LDown���ʧ@
        virtual void OnKeyUp(UINT, UINT, UINT) {}				// �B�z��LUp���ʧ@
        virtual void OnLButtonDown(UINT nFlags, CPoint point) {}// �B�z�ƹ����ʧ@
        virtual void OnLButtonUp(UINT nFlags, CPoint point) {}	// �B�z�ƹ����ʧ@
        virtual void OnMouseMove(UINT nFlags, CPoint point) {}  // �B�z�ƹ����ʧ@
        virtual void OnRButtonDown(UINT nFlags, CPoint point) {}// �B�z�ƹ����ʧ@
        virtual void OnRButtonUp(UINT nFlags, CPoint point) {}	// �B�z�ƹ����ʧ@
    protected:
        void GotoGameState(int state);							// ���D�ܫ��w��state
        void ShowInitProgress(int percent);						// ��ܪ�l�ƪ��i��
        //
        // virtual functions, ���~�Ӫ̴���implementation
        //
        virtual void OnMove() {}								// ���ʳo�Ӫ��A���C������
        virtual void OnShow() = 0;								// ��ܳo�Ӫ��A���C���e��
        CGame* game;
};

/////////////////////////////////////////////////////////////////////////////
// �o��class�O�C�����֤ߡA����C�����i��
// �@�몺�C���ä��ݪ����ާ@�o�Ӫ���A�]���i�H���޳o��class���ϥΤ�k
/////////////////////////////////////////////////////////////////////////////

class CGame
{
    public:
        CGame();										// Constructor
        ~CGame();										// Destructor
        bool IsRunning();								// Ū���C���O�_���b�i�椤
        void OnDraw();									// ����CGameView��OnDraw()
        void OnFilePause();								// �C���Ȱ�
        void OnInit();									// �C��ø�Ϥέ��Ī���l��
        void OnInitStates();							// �C���U���A����Ȥιϧγ]�w
        bool OnIdle();									// �C�����D�j��
        void OnKeyDown(UINT, UINT, UINT);				// �B�z��LDown���ʧ@
        void OnKeyUp(UINT, UINT, UINT);					// �B�z��LUp���ʧ@
        void OnKillFocus();								// �C���Q���Ȱ�
        void OnLButtonDown(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
        void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
        void OnMouseMove(UINT nFlags, CPoint point);    // �B�z�ƹ����ʧ@
        void OnRButtonDown(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
        void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
        void OnResume();								// �B�z�ۡu�ݩR�v�٭쪺�ʧ@
        void OnSetFocus();								// �B�zFocus
        void OnSuspend();								// �B�z�u�ݩR�v���ʧ@
        void SetGameState(int);
		void SetRunning(bool);
        static CGame* Instance();
    private:
        bool			running;			// �C���O�_���b�i�椤(���QPause)
        bool            suspended;			// �C���O�_�Qsuspended
        const int		NUM_GAME_STATES;	// �C�������A��(3�Ӫ��A)
        CGameState*		gameState;			// pointer���V�ثe���C�����A
        CGameState*		gameStateTable[4];	// �C�����A����pointer
        static CGame	instance;			// �C���ߤ@��instance
};

}