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
	// 新しく設定されたら中身を空にする
	if (newFlag)
	{
		_aimState.clear();
	}

	// 所有権を渡す
	_aimState = std::move(state);
	
	// 新しく設定されたら関数を設定する
	if (newFlag)
	{
		SetMovePrg();
	}

	return true;
}

void EnemyMove::SetMovePrg(void)
{
	_aimCnt++;

	// ｶｳﾝﾄが回ってたら何もせず終わる
	if (_aimCnt >= _aimState.size())
	{
		return;
	}

	_startPos = _pos;
	_endPos = _aimState[_aimCnt].second;
	switch (_aimState[_aimCnt].first)
	{
	case MOVE_TYPE::WAIT:
		_move = &EnemyMove::Wait;
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
