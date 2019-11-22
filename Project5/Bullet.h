#pragma once
#include "Obj.h"
class Bullet :
	public Obj
{
public:
	Bullet();
	Bullet(UNIT_ID unitID, vector2Dbl pos);
	~Bullet();
	void Update(void);
private:
	bool DestroyPrpc(void);
	void init(void);
};

