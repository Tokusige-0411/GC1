#pragma once
#include "Obj.h"
class Bullet :
	public Obj
{
public:
	Bullet();
	Bullet(UNIT_ID unitID, vector2Dbl pos);
	~Bullet();
	void Update(sharedObj Obj);					// 処理
private:
	bool DestroyPrpc(void);						// 描画終わったら消す
	void init(void);							// 初期化
};

