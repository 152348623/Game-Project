#ifndef CSMALLPERSONSTATE_H
#define CSMALLPERSONSTATE_H

#include <vector>
#include "CHero.h"
#include "CSmallPerson.h"
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class CSmallPersonState
	{
	public:
		CSmallPersonState(CSmallPerson* s);
		void OnMoveState(CGamemap*);
		void OnShowState(CGamemap*,CHero*);
		void SetIsMoving();
		virtual ~CSmallPersonState() {}        // virtual destructor
		virtual void OnBeginState() {}       // 設定每次進入這個狀態時所需的初值
		virtual void OnInit() {}        // 狀態的初值及圖形設定

		virtual void OnKeyDown(UINT) {}    // 處理鍵盤Down的動作
		virtual void OnKeyUp(UINT) {}    // 處理鍵盤Up的動作
	protected:
		void GotoSmallPersonState(int state);       // 跳躍至指定的state
		virtual void OnMove(CGamemap*) {}        // 移動這個狀態的遊戲元素
		virtual void OnShow(CGamemap*, CHero*) = 0;        // 顯示這個狀態的遊戲畫面
		CSmallPerson* smallPerson;
		bool directionStay;   //暫存方向
		bool isCatch;
		bool isMovingDown;   // 是否正在往下移動
		bool isMovingLeft;   // 是否正在往左移動
		bool isMovingRight;   // 是否正在往右移動
		bool isMovingUp;   // 是否正在往上移動
		int x, y;
	};
	/*class SmallPersonStayState : public SmallPersonState
	{
	public:
		SmallPersonStayState(SmallPerson* s);
		~SmallPersonStayState();
		void OnBeginState();       // 設定每次重玩所需的變數
		void OnInit();          // 遊戲的初值及圖形設定
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
		bool GetIsDirectionStay();

	protected:
		void OnMove(CGamemap*);         // 移動遊戲元素
		void OnShow(CGamemap*);         // 顯示這個狀態的遊戲畫面
	private:
	};*/
	class CSmallPersonRunState : public CSmallPersonState
	{
	public:
		CSmallPersonRunState(CSmallPerson* s);
		~CSmallPersonRunState();
		void OnBeginState();       // 設定每次重玩所需的變數
		void OnInit();          // 遊戲的初值及圖形設定
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
		void RandomDircetion();
		void SetIsMovingFalse();
	protected:
		void OnMove(CGamemap*);
		void OnShow(CGamemap*,CHero*);
	private:
		int countRandomTime = 0;

	};
	class CSmallPersonAttackState : public CSmallPersonState
	{
	public:
		CSmallPersonAttackState(CSmallPerson* s);
		~CSmallPersonAttackState();
		void OnBeginState();       // 設定每次重玩所需的變數
		void OnInit();          // 遊戲的初值及圖形設定
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
	protected:
		void OnMove(CGamemap*);         // 移動遊戲元素
		void OnShow(CGamemap*,CHero *h);         // 顯示這個狀態的遊戲畫面
	private:
		int attackTime;
		vector<int> attackCount;
	};
	class CSmallPersonBeAttackedState :public CSmallPersonState
	{
	public:
		CSmallPersonBeAttackedState(CSmallPerson* s);
		~CSmallPersonBeAttackedState();
		void OnBeginState();
		void OnInit();
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
	protected:
		void OnMove(CGamemap*);
		void OnShow(CGamemap*,CHero*);
	private:
		int attackCount;
	};
	class CSmallPersonBeCatchedState : public CSmallPersonState
	{
	public:
		CSmallPersonBeCatchedState(CSmallPerson* s);
		~CSmallPersonBeCatchedState();
		void OnBeginState();       // 設定每次重玩所需的變數
		void OnInit();          // 遊戲的初值及圖形設定
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
	protected:
		void OnMove(CGamemap*);         // 移動遊戲元素
		void OnShow(CGamemap*,CHero*);         // 顯示這個狀態的遊戲畫面
	private:

	};
}
#endif // !CHEROSTATE_H