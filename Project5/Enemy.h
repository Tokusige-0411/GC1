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
	MAX
};

// <“G‚Ìí—Ş, À•W, ‰æ‘œ‚Ì»²½Ş>
using EnemyState = std::tuple<ENEMY_TYPE, vector2Dbl, vector2Int>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState&);
	void Update(void) override;
	~Enemy();
private:
	EnemyMove moveCtl{ _pos };
	void init(void);		// ‰Šú‰»
	ENEMY_TYPE _type;		// “G‚Ìí—Ş
};

