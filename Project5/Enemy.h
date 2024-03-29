#pragma once
#include <tuple>
#include "Obj.h"
#include "EnemyMove.h"



enum class ENEMY_TYPE
{
	A,
	B,
	C,
	MAX
};

enum class ENEMY_STATE
{
	TYPE,			// 敵の種類
	VECTOR,			// 座標
	SIZE,			// 描画ｻｲｽﾞ
	AIM,
	MAX
};

// <敵の種類, 座標, 画像のｻｲｽﾞ, 動きの種類>
using EnemyState = std::tuple<ENEMY_TYPE, vector2Dbl, vector2Dbl, MoveState&>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState&);
	void Update(sharedObj Obj) override;		// 処理
	bool exFlag(void);							// exFlagのget関数
	bool SetExFlag(bool exFlag);				// set関数

	~Enemy();
private:
	bool SetAlive(bool alive) override;

	EnemyMove _moveCtl{ _pos, _rad, _exFlag};	// EnemyMoveへ移行
	void init(void);		// 初期化
	ENEMY_TYPE _type;		// 敵の種類
};

