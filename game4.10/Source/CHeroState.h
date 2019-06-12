#ifndef CHEROSTATE_H
#define CHEROSTATE_H

#include <vector>
#include "CHero.h"
#include "CSmallPerson.h"
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class CHero;
	class CHeroState
	{
	public:
		CHeroState(CHero* h);
		void OnMoveState(CGamemap*);
		void OnShowState(CGamemap*);
		void SetIsMoving();
		virtual ~CHeroState() {}        // virtual destructor
		virtual void OnBeginState() {}       // 設定每次進入這個狀態時所需的初值
		virtual void OnInit() {}        // 狀態的初值及圖形設定

		virtual void OnKeyDown(UINT) {}    // 處理鍵盤Down的動作
		virtual void OnKeyUp(UINT) {}    // 處理鍵盤Up的動作
	protected:
		void GotoHeroState(int state);       // 跳躍至指定的state
		virtual void OnMove(CGamemap*) {}        // 移動這個狀態的遊戲元素
		virtual void OnShow(CGamemap*) = 0;        // 顯示這個狀態的遊戲畫面

		CHero* hero;
		bool directionStay;   //暫存方向
		bool isCatch;
		bool isMovingDown;   // 是否正在往下移動
		bool isMovingLeft;   // 是否正在往左移動
		bool isMovingRight;   // 是否正在往右移動
		bool isMovingUp;   // 是否正在往上移動
		int x, y;
	};
	class CHeroStayState : public CHeroState
	{
	public:
		CHeroStayState(CHero* h);
		~CHeroStayState();
		void OnBeginState();       // 設定每次重玩所需的變數
		void OnInit();          // 遊戲的初值及圖形設定
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
		bool GetIsDirectionStay();

	protected:
		void OnMove(CGamemap*);         // 移動遊戲元素
		void OnShow(CGamemap*);         // 顯示這個狀態的遊戲畫面
	private:
	};
	class CHeroRunState : public CHeroState
	{
	public:
		CHeroRunState(CHero* h);
		~CHeroRunState();
		void OnBeginState();       // 設定每次重玩所需的變數
		void OnInit();          // 遊戲的初值及圖形設定
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
		protected:
			void OnMove(CGamemap*);
			void OnShow(CGamemap*);
	private:
	};
	class CHeroAttackState : public CHeroState
	{
	public:
		CHeroAttackState(CHero* h);
		~CHeroAttackState();
		void OnBeginState();       // 設定每次重玩所需的變數
		void OnInit();          // 遊戲的初值及圖形設定
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
	protected:
		void OnMove(CGamemap*);         // 移動遊戲元素
		void OnShow(CGamemap*);         // 顯示這個狀態的遊戲畫面
	private:
		int attackTime;
		vector<int> attackCount;
	};

	class CHeroCatchState : public CHeroState
	{
	public:
		CHeroCatchState(CHero* h);
		~CHeroCatchState();
		void OnBeginState();       // 設定每次重玩所需的變數
		void OnInit();          // 遊戲的初值及圖形設定
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
	protected:
		void OnMove(CGamemap*);         // 移動遊戲元素
		void OnShow(CGamemap*);         // 顯示這個狀態的遊戲畫面
	private:

	};
	class CHeroBeAttackedState : public CHeroState
	{
	public:
		CHeroBeAttackedState(CHero* h);
		~CHeroBeAttackedState();
		void OnBeginState();       // 設定每次重玩所需的變數
		void OnInit();          // 遊戲的初值及圖形設定
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
	protected:
		void OnMove(CGamemap*);         // 移動遊戲元素
		void OnShow(CGamemap*);         // 顯示這個狀態的遊戲畫面
	private:
		//int blood;
	};
}
#endif // !CHEROSTATE_H