#include <_DebugConout.h>
#include "EnemyMove.h"

EnemyMove::EnemyMove(vector2Dbl& pos) : _pos(pos)
{
	_move = nullptr;
	_aimCnt = -1;
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{
	// �D��x�̖��
	if (_move != nullptr)
	{
		(this->*_move)();
	}
}

bool EnemyMove::SetMoveState(MoveState & state, bool newFlag)
{
	// �V�����ݒ肳�ꂽ�璆�g����ɂ���
	if (newFlag)
	{
		_aimState.clear();
	}

	// ���L����n��
	_aimState = std::move(state);
	
	// �V�����ݒ肳�ꂽ��֐���ݒ肷��
	if (newFlag)
	{
		SetMovePrg();
	}

	return true;
}

void EnemyMove::SetMovePrg(void)
{
	_aimCnt++;

	// ���Ă�����Ă��牽�������I���
	if (_aimCnt >= static_cast<int>(_aimState.size()))
	{
		return;
	}

	_startPos = _pos;								// ���݂̍��W������
	_endPos = _aimState[_aimCnt].second;			// �֐��I���ʒu������

	// ���̶݂��Ăɉ����ď��������߂�
	switch (_aimState[_aimCnt].first)
	{
	case MOVE_TYPE::WAIT:
		_move = &EnemyMove::Wait;
		count = 0;
		break;
	case MOVE_TYPE::SIGMOID:
		_move = &EnemyMove::MoveSigmoid;
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpairal;
		break;
	case MOVE_TYPE::PITIN:
		_move = &EnemyMove::PitIn;
		break;
	case MOVE_TYPE::LR:
		_move = &EnemyMove::MoveLR;
		break;
	default:
		AST();
		_move = nullptr;
		break;
	}
}

void EnemyMove::MoveSigmoid(void)
{
}

void EnemyMove::MoveSpairal(void)
{
}

void EnemyMove::PitIn(void)
{
}

void EnemyMove::Wait(void)
{
	if (count > _aimState[_aimCnt].second.x)
	{
		SetMovePrg();
	}
	count++;
}

void EnemyMove::MoveLR(void)
{
}
