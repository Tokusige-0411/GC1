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
using EnemyState = std::tuple<ENEMY_TYPE, vector2Dbl, vector2Int, MoveState&>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState&);
	void Update(void) override;
	~Enemy();
private:
	EnemyMove _moveCtl{ _pos, _rad };
	void init(void);		// 初期化
	ENEMY_TYPE _type;		// 敵の種類
};

