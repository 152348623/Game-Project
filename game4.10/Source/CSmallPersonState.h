#ifndef CSMALLPERSONSTATE_H
#define CSMALLPERSONSTATE_H

#include <vector>
#include "CHero.h"
#include "CSmallPerson.h"
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////
	class CSmallPersonState
	{
	public:
		CSmallPersonState(CSmallPerson* s);
		void OnMoveState(CGamemap*);
		void OnShowState(CGamemap*,CHero*);
		void SetIsMoving();
		virtual ~CSmallPersonState() {}        // virtual destructor
		virtual void OnBeginState() {}       // �]�w�C���i�J�o�Ӫ��A�ɩһݪ����
		virtual void OnInit() {}        // ���A����Ȥιϧγ]�w

		virtual void OnKeyDown(UINT) {}    // �B�z��LDown���ʧ@
		virtual void OnKeyUp(UINT) {}    // �B�z��LUp���ʧ@
	protected:
		void GotoSmallPersonState(int state);       // ���D�ܫ��w��state
		virtual void OnMove(CGamemap*) {}        // ���ʳo�Ӫ��A���C������
		virtual void OnShow(CGamemap*, CHero*) = 0;        // ��ܳo�Ӫ��A���C���e��
		CSmallPerson* smallPerson;
		bool directionStay;   //�Ȧs��V
		bool isCatch;
		bool isMovingDown;   // �O�_���b���U����
		bool isMovingLeft;   // �O�_���b��������
		bool isMovingRight;   // �O�_���b���k����
		bool isMovingUp;   // �O�_���b���W����
		int x, y;
	};
	/*class SmallPersonStayState : public SmallPersonState
	{
	public:
		SmallPersonStayState(SmallPerson* s);
		~SmallPersonStayState();
		void OnBeginState();       // �]�w�C�������һݪ��ܼ�
		void OnInit();          // �C������Ȥιϧγ]�w
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
		bool GetIsDirectionStay();

	protected:
		void OnMove(CGamemap*);         // ���ʹC������
		void OnShow(CGamemap*);         // ��ܳo�Ӫ��A���C���e��
	private:
	};*/
	class CSmallPersonRunState : public CSmallPersonState
	{
	public:
		CSmallPersonRunState(CSmallPerson* s);
		~CSmallPersonRunState();
		void OnBeginState();       // �]�w�C�������һݪ��ܼ�
		void OnInit();          // �C������Ȥιϧγ]�w
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
		void OnBeginState();       // �]�w�C�������һݪ��ܼ�
		void OnInit();          // �C������Ȥιϧγ]�w
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
	protected:
		void OnMove(CGamemap*);         // ���ʹC������
		void OnShow(CGamemap*,CHero *h);         // ��ܳo�Ӫ��A���C���e��
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
		void OnBeginState();       // �]�w�C�������һݪ��ܼ�
		void OnInit();          // �C������Ȥιϧγ]�w
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
	protected:
		void OnMove(CGamemap*);         // ���ʹC������
		void OnShow(CGamemap*,CHero*);         // ��ܳo�Ӫ��A���C���e��
	private:

	};
}
#endif // !CHEROSTATE_H