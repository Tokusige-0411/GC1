#pragma once
#include <functional>
#include <map>
#include "BeseScene.h"
#include "Obj.h"

// 中身いじる場合はﾍｯﾀﾞｰをｲﾝｸﾙｰﾄﾞしないといけないが、そうじゃない場合は仮宣言でいい
struct FuncCheckHit;
struct FuncBullet;
struct FuncShake;

using funcAct = std::function<bool(ActQueT&, void*)>;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;		// 描画情報のｱｯﾌﾟﾃﾞｰﾄ
private:
	// ﾌﾚﾝﾄﾞ登録
	friend FuncCheckHit;
	friend FuncBullet;
	friend FuncShake;

	void initFunc(void);
	std::vector<sharedObj> _objList;					// ｵﾌﾞｼﾞｪｸﾄの配列
	// RunActQueで描画と同じようなことを
	void RunActQue(std::vector<ActQueT> actList);		// 発射、当たり判定をする
	std::map<ACT_QUE, funcAct> funcQue;					// Actを管理する
	int _shakeCount;									// 
};

