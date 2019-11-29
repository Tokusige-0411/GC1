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
	TYPE,			// �G�̎��
	VECTOR,			// ���W
	SIZE,			// �`�滲��
	AIM,
	MAX
};

// <�G�̎��, ���W, �摜�̻���, �����̎��>
using EnemyState = std::tuple<ENEMY_TYPE, vector2Dbl, vector2Dbl, MoveState&>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState&);
	void Update(sharedObj Obj) override;		// ����
	bool exFlag(void);							// exFlag��get�֐�
	bool SetExFlag(bool exFlag);				// set�֐�

	~Enemy();
private:
	EnemyMove _moveCtl{ _pos, _rad, _exFlag};	// EnemyMove�ֈڍs
	void init(void);		// ������
	ENEMY_TYPE _type;		// �G�̎��
};

