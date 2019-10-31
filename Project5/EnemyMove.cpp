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
	_pos.x++;
}

bool EnemyMove::SetMoveState(MoveState & state, bool newFlag)
{
	if (newFlag)
	{
		_aimState.clear();
	}
	_aimState = std::move(state);
	
	if (newFlag)
	{
		SetMovePrg();
	}

	return true;
}

void EnemyMove::SetMovePrg(void)
{
	_aimCnt++;
	if (_aimCnt >= _aimState.size())
	{
		return;
	}

	_startPos = _pos;
	_endPos = _aimState[_aimCnt].second;
	switch (_aimState[_aimCnt].first)
	{
	case(MOVE_TYPE::WAIT):
		_move = Wait;
		break;
	case(MOVE_TYPE::SIGMOID):
		_move = MoveSigmoid;
		break;
	case(MOVE_TYPE::SPIRAL):
		_move = MoveSpairal;
		break;
	case(MOVE_TYPE::PITIN):
		_move = PitIn;
		break;
	case(MOVE_TYPE::LR):
		_move = MoveLR;
		break;
	default:
		AST();
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
}

void EnemyMove::MoveLR(void)
{
}
