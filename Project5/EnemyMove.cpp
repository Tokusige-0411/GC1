#include <cmath>
#include <_DebugConout.h>
#include "EnemyMove.h"

#define MOVE_CNT 60.0

EnemyMove::EnemyMove(vector2Dbl& pos, double & rad) : _pos(pos), _rad(rad)
{
	_move = nullptr;
	_aimCnt = -1;
	// 1�ɂ�����1�񑽂��v�Z���邽��
	_moveCnt = 1;
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
		_move = &EnemyMove::Wait;
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
	// _stratPos��_endPos���g���Ĉړ�������
	vector2Dbl tmpPos = _pos;
	tmpPos.x = (_endPos.x - _startPos.x) / MOVE_CNT;
	tmpPos.y = (_endPos.y - _startPos.y) / MOVE_CNT;

	// �v�Z�������W�����Z
	_pos.x += tmpPos.x;
	_pos.y += tmpPos.y;
	_rad = (std::atan2(tmpPos.y, tmpPos.x)) + (3.14159 / 2);

	// ���Ă��߂�����LR��
	if (_moveCnt >= MOVE_CNT)
	{
		SetMovePrg();
	}
	_moveCnt++;
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
	_rad = 0.0;
}
