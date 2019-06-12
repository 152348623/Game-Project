#ifndef CHEROSTATE_H
#define CHEROSTATE_H

#include <vector>
#include "CHero.h"
#include "CSmallPerson.h"
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
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
		virtual void OnBeginState() {}       // �]�w�C���i�J�o�Ӫ��A�ɩһݪ����
		virtual void OnInit() {}        // ���A����Ȥιϧγ]�w

		virtual void OnKeyDown(UINT) {}    // �B�z��LDown���ʧ@
		virtual void OnKeyUp(UINT) {}    // �B�z��LUp���ʧ@
	protected:
		void GotoHeroState(int state);       // ���D�ܫ��w��state
		virtual void OnMove(CGamemap*) {}        // ���ʳo�Ӫ��A���C������
		virtual void OnShow(CGamemap*) = 0;        // ��ܳo�Ӫ��A���C���e��

		CHero* hero;
		bool directionStay;   //�Ȧs��V
		bool isCatch;
		bool isMovingDown;   // �O�_���b���U����
		bool isMovingLeft;   // �O�_���b��������
		bool isMovingRight;   // �O�_���b���k����
		bool isMovingUp;   // �O�_���b���W����
		int x, y;
	};
	class CHeroStayState : public CHeroState
	{
	public:
		CHeroStayState(CHero* h);
		~CHeroStayState();
		void OnBeginState();       // �]�w�C�������һݪ��ܼ�
		void OnInit();          // �C������Ȥιϧγ]�w
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
		bool GetIsDirectionStay();

	protected:
		void OnMove(CGamemap*);         // ���ʹC������
		void OnShow(CGamemap*);         // ��ܳo�Ӫ��A���C���e��
	private:
	};
	class CHeroRunState : public CHeroState
	{
	public:
		CHeroRunState(CHero* h);
		~CHeroRunState();
		void OnBeginState();       // �]�w�C�������һݪ��ܼ�
		void OnInit();          // �C������Ȥιϧγ]�w
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
		void OnBeginState();       // �]�w�C�������һݪ��ܼ�
		void OnInit();          // �C������Ȥιϧγ]�w
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
	protected:
		void OnMove(CGamemap*);         // ���ʹC������
		void OnShow(CGamemap*);         // ��ܳo�Ӫ��A���C���e��
	private:
		int attackTime;
		vector<int> attackCount;
	};

	class CHeroCatchState : public CHeroState
	{
	public:
		CHeroCatchState(CHero* h);
		~CHeroCatchState();
		void OnBeginState();       // �]�w�C�������һݪ��ܼ�
		void OnInit();          // �C������Ȥιϧγ]�w
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
	protected:
		void OnMove(CGamemap*);         // ���ʹC������
		void OnShow(CGamemap*);         // ��ܳo�Ӫ��A���C���e��
	private:

	};
	class CHeroBeAttackedState : public CHeroState
	{
	public:
		CHeroBeAttackedState(CHero* h);
		~CHeroBeAttackedState();
		void OnBeginState();       // �]�w�C�������һݪ��ܼ�
		void OnInit();          // �C������Ȥιϧγ]�w
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
	protected:
		void OnMove(CGamemap*);         // ���ʹC������
		void OnShow(CGamemap*);         // ��ܳo�Ӫ��A���C���e��
	private:
		//int blood;
	};
}
#endif // !CHEROSTATE_H