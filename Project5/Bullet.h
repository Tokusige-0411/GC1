#pragma once
#include "Obj.h"
class Bullet :
	public Obj
{
public:
	Bullet();
	Bullet(vector2Dbl pos);
	~Bullet();
	void Update(void);
private:
	void init(void);
};

