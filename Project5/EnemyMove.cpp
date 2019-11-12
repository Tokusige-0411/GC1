#include <cmath>
#include <_DebugConout.h>
#include "EnemyMove.h"
#include <Vector2.h>
#include "Scene\SceneMng.h"

#define MOVE_CNT 60.0
#define pi 3.14159

EnemyMove::EnemyMove(vector2Dbl& pos, double & rad) : _pos(pos), _rad(rad)
{
	_move = nullptr;
	_aimCnt = -1;
	_sigCount = -5.0;
	_spaiAngl = 90.0;
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
		count = 0;
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpairal;
		_spaiRad = abs(_endPos.y - _startPos.y);			// _endPosを基準に半径を決定
		break;
	case MOVE_TYPE::PITIN:
		_move = &EnemyMove::PitIn;
		_oneMoveVec = ((_endPos - _startPos) / 120.0);			// 移動時間が120ﾌﾚｰﾑになるように
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
	// ｼｸﾞﾓｲﾄﾞ曲線を描く
	vector2Dbl tmpPos = _pos;			// 座標を求める用
	vector2Dbl oldPos = _pos;			// 角度を求める用
	
	tmpPos.x = ((_endPos.x - _startPos.x) / 150.0);
	tmpPos.y = ((1.0 / (1.0 + exp(-_sigCount))) * (_endPos.y - _startPos.y));
	_sigCount += 0.1;

	// 求めた移動量を座標に反映
	_pos.x += tmpPos.x;
	_pos.y = _startPos.y + tmpPos.y;

	// 描画方向を決定
	_rad = (atan2(_pos.y - oldPos.y, _pos.x - oldPos.x) + pi / 2);

	// 秒数まで行ったらMoveSpairalに変換
	if (count >= 150)
	{
		SetMovePrg();
	}
	count++;
}

void EnemyMove::MoveSpairal(void)
{
	vector2Dbl tmpPos;
	vector2Dbl oldPos = _pos;

	tmpPos.x = _spaiRad * cos(_spaiAngl * (pi / 180.0));
	tmpPos.y = _spaiRad * sin(_spaiAngl * (pi / 180.0));

	_pos.x = _endPos.x + tmpPos.x;
	_pos.y = _endPos.y + tmpPos.y;

	// 描画方向を決定
	_rad = (atan2(_pos.y - oldPos.y, _pos.x - oldPos.x) + pi / 2);;

	if (_startPos.x < lpSceneMng.ScreenSize.x/2)
	{
		_spaiAngl += 2;
	}
	else
	{
		_spaiAngl -= 2;
	}

	// 半径を小さくしていく
	_spaiRad -= 0.1;

	if (abs(_spaiAngl - 90) > 720)
	{
		SetMovePrg();
	}
}

void EnemyMove::PitIn(void)
{
	// _stratPosと_endPosを使って移動させる
	vector2Dbl _lenght;

	// ｴﾝﾄﾞの位置に来たらLRに移るようにする
	if (abs(_endPos.x - _pos.x) >= abs(_oneMoveVec.x))
	{
		// 移動
		_pos += _oneMoveVec;

		// 角度の処理
		_lenght = _endPos - _pos;
		_rad = (atan2(_lenght.y, _lenght.x) + pi / 2);
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
