#include <cmath>
#include <_DebugConout.h>
#include "EnemyMove.h"
#include <Vector2.h>

#define MOVE_CNT 60.0

EnemyMove::EnemyMove(vector2Dbl& pos, double & rad) : _pos(pos), _rad(rad)
{
	_move = nullptr;
	_aimCnt = -1;
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{
	// 優先度の問題
	if (_move != nullptr)
	{
		(this->*_move)();
	}
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
	if (_aimCnt >= static_cast<int>(_aimState.size()))
	{
		return;
	}

	_startPos = _pos;								// 現在の座標を入れる
	_endPos = _aimState[_aimCnt].second;			// 関数終了位置を入れる

	// 現在のｶｳﾝﾄに応じて処理を決める
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
		_oneMoveVec = ((_endPos - _startPos) / 120.0);
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
	// _stratPosと_endPosを使って移動させる
	vector2Dbl _lenght;


	if (abs(_endPos.x - _pos.x) >= abs(_oneMoveVec.x))
	{
		// 移動
		_pos += _oneMoveVec;

		// 角度の処理
		_lenght = _endPos - _pos;
		_rad = (atan2(_lenght.y, _lenght.x) + 3.14159 / 2);
	}
	else
	{
		_pos = _endPos;
		_rad = 0.0;
		SetMovePrg();
	}
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
