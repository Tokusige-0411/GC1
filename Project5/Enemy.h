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
	TYPE,			// �G�̎��
	VECTOR,			// ���W
	SIZE,			// �`�滲��
	MAX
};

// <�G�̎��, ���W, �摜�̻���>
using EnemyState = std::tuple<ENEMY_TYPE, Vector2, Vector2>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState&);
	void Update(void) override;
	~Enemy();
private:
	void init(void);		// ������
	ENEMY_TYPE _type;		// �G�̎��
};

