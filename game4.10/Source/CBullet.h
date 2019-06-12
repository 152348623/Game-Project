namespace game_framework
{

	class CSmallPerson;

	class CBullet
	{
	public:
		CBullet();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		bool GetIsAlive();
		bool GetIsDirectionStay();
		void SetXY(int, int);
		void SetIsAlive(bool);
		void SetIsDirectionStay(bool);
		void Initialize();				// 設定hero為初始值
		void OnBegin();
		void LoadBitmap();				// 載入圖形
		void OnMove(CGamemap*, CSmallPerson*);					// 移動hero
		void OnShow(CGamemap*);					// 將hero圖形貼到畫面
		bool HitHero(CHero* hero);
	private:
		CMovingBitmap bulletR, bulletL;
		bool isAlive;
		bool isDirectionStay;
		int x, y;

	};
}