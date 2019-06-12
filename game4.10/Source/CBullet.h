namespace game_framework
{

	class CSmallPerson;

	class CBullet
	{
	public:
		CBullet();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		bool GetIsAlive();
		bool GetIsDirectionStay();
		void SetXY(int, int);
		void SetIsAlive(bool);
		void SetIsDirectionStay(bool);
		void Initialize();				// �]�whero����l��
		void OnBegin();
		void LoadBitmap();				// ���J�ϧ�
		void OnMove(CGamemap*, CSmallPerson*);					// ����hero
		void OnShow(CGamemap*);					// �Nhero�ϧζK��e��
		bool HitHero(CHero* hero);
	private:
		CMovingBitmap bulletR, bulletL;
		bool isAlive;
		bool isDirectionStay;
		int x, y;

	};
}