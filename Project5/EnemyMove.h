#pragma once
#include <vector>
#include <Vector2.h>

enum class MOVE_TYPE
{
	WAIT,			// �~�܂�
	SIGMOID,		// ���ӯċȐ�
	SPIRAL,			// ��]
	PITIN,			// �ްъJ�n�ʒu
	LR				// ���E�ړ�
};

// <�����̎��, �����̖ڕW�n�_>
using MoveState = std::vector<std::pair<MOVE_TYPE, vector2Dbl>>;

class EnemyMove
{
public:
	EnemyMove(vector2Dbl& pos);								// ���W������
	~EnemyMove();
	void Update(void);										// ���낢��X�V
	bool SetMoveState(MoveState& state, bool newFlag);		// �֐��߲���ɐݒ肷��
private:
	void SetMovePrg(void);				// �����̊֐���ݒ肷��
	void (EnemyMove::*_move)(void);		// �֐��߲��(�����̐ݒ�)
	void MoveSigmoid(void);				// ���ӯĊ֐�
	void MoveSpairal(void);				// ��]������
	void PitIn(void);					// �ްъJ�n�ʒu��
	void Wait(void);					// �������~�߂�
	void MoveLR(void);					// �ްђ��̍��E�ړ�

	MoveState _aimState;				// �����̽ð��
	int _aimCnt;						// �����ð���̶���

	vector2Dbl _startPos;		// �e�ړ��֐��̽��Ĉʒu
	vector2Dbl _endPos;			// �e�ړ��֐��̴��ވʒu
	vector2Dbl & _pos;			// EnemyMove��Ŏg�����W
};

