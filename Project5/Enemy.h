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
	TYPE,			// “G‚Ìí—Ş
	VECTOR,			// À•W
	SIZE,			// •`‰æ»²½Ş
	AIM,
	MAX
};

// <“G‚Ìí—Ş, À•W, ‰æ‘œ‚Ì»²½Ş, “®‚«‚Ìí—Ş>
using EnemyState = std::tuple<ENEMY_TYPE, vector2Dbl, vector2Dbl, MoveState&>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState&);
	void Update(sharedObj Obj) override;		// ˆ—
	bool exFlag(void);							// exFlag‚ÌgetŠÖ”
	bool SetExFlag(bool exFlag);				// setŠÖ”

	~Enemy();
private:
	EnemyMove _moveCtl{ _pos, _rad, _exFlag};	// EnemyMove‚ÖˆÚs
	void init(void);		// ‰Šú‰»
	ENEMY_TYPE _type;		// “G‚Ìí—Ş
};

