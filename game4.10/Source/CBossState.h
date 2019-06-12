#ifndef CBOSSSTATE_H
#define CBOSSSTATE_H

#include <vector>
#include "CHero.h"
#include "CBoss.h"

namespace game_framework
{
	class CBossState
	{
	public:
		CBossState(CBoss* b);
		void OnMoveState(CGamemap*);
		void OnShowState(CGamemap*, CHero*);
		void SetIsMoving();
		virtual ~CBossState() {}        // virtual destructor
		virtual void OnBeginState() {}       // �]�w�C���i�J�o�Ӫ��A�ɩһݪ����
		virtual void OnInit() {}        // ���A����Ȥιϧγ]�w

		virtual void OnKeyDown(UINT) {}    // �B�z��LDown���ʧ@
		virtual void OnKeyUp(UINT) {}    // �B�z��LUp���ʧ@
	protected:
		void GotoBossState(int state);       // ���D�ܫ��w��state
		virtual void OnMove(CGamemap*) {}        // ���ʳo�Ӫ��A���C������
		virtual void OnShow(CGamemap*, CHero*) = 0;        // ��ܳo�Ӫ��A���C���e��
		CBoss* boss;
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
	class CBossRunState : public CBossState
	{
	public:
		CBossRunState(CBoss* b);
		~CBossRunState();
		void OnBeginState();       // �]�w�C�������һݪ��ܼ�
		void OnInit();          // �C������Ȥιϧγ]�w
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
		void RandomDircetion();
		void SetIsMovingFalse();
	protected:
		void OnMove(CGamemap*);
		void OnShow(CGamemap*, CHero*);
	private:
		int countRandomTime = 0;

	};
	class CBossAttackState : public CBossState
	{
	public:
		CBossAttackState(CBoss* b);
		~CBossAttackState();
		void OnBeginState();       // �]�w�C�������һݪ��ܼ�
		void OnInit();          // �C������Ȥιϧγ]�w
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
	protected:
		void OnMove(CGamemap*);         // ���ʹC������
		void OnShow(CGamemap*, CHero *h);         // ��ܳo�Ӫ��A���C���e��
	private:
		int attackTime;
		vector<int> attackCount;
	};
	class CBossBeAttackedState :public CBossState
	{
	public:
		CBossBeAttackedState(CBoss* b);
		~CBossBeAttackedState();
		void OnBeginState();
		void OnInit();
		void OnKeyDown(UINT);
		void OnKeyUp(UINT);
	protected:
		void OnMove(CGamemap*);
		void OnShow(CGamemap*, CHero*);
	private:
		int attackCount;
	};


}
#endif // !CBOSSSTATE_H