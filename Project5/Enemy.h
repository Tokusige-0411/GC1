#pragma once
#include <tuple>
#include "Obj.h"

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
	MAX
};

using EnemyState = std::tuple<ENEMY_TYPE, Vector2, Vector2>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState&);
	~Enemy();
private:
	void init(void);		// 初期化
	ENEMY_TYPE _type;		// 敵の種類
};

