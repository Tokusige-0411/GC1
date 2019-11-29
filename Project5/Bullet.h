#pragma once
#include "Obj.h"
class Bullet :
	public Obj
{
public:
	Bullet();
	Bullet(UNIT_ID unitID, vector2Dbl pos);
	~Bullet();
	void Update(sharedObj Obj);					// ˆ—
private:
	bool DestroyPrpc(void);						// •`‰æI‚í‚Á‚½‚çÁ‚·
	void init(void);							// ‰Šú‰»
};

