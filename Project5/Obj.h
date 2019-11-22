#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <Vector2.h>

enum class STATE
{
	NORMAL,			// 通常
	EX,				// 特殊
	DETH,			// 爆発
	MAX
};

// 一番上のｸﾗｽで作っているが、種類が多ければ細かく分けたほうがいい
enum class UNIT_ID
{
	NON,
	PLAYER,
	ENEMY,
	PL_BULLET,
	EM_BULLET,
};

// 内側の<>から
class Obj;

using AnimVector = std::vector<std::pair<int, unsigned int>>;
using sharedObj = std::shared_ptr<Obj>;

class Obj
{
public:
	// -----------関数
	Obj();
	virtual void Update(void) = 0;
	void Draw(void);							// ｷｭｰを追加する
	void Draw(int id);							// IDを投げてｷｭｰを追加
	virtual ~Obj();

	bool state(const STATE state);		// set
	const STATE state(void)const;		// get

	bool SetAnim(const STATE state, AnimVector& data);		// ｱﾆﾒｷｰを設定する
	bool SetAlive(bool alive);								// ステータスを変更する
	bool isAlive(void) { return _alive; }					// 生存ﾌﾗｸﾞを返す
	bool isDead(void) { return _dead; }						// 死亡ﾌﾗｸﾞを返す
	bool isAnimEnd(void);

	// 参照させたいpos state sizeのgetをつくる
	const vector2Dbl& pos(void) const;
	const UNIT_ID& unitID(void) const;

private:
	std::map<STATE, AnimVector> _animMap;			// ｱﾆﾒｰｼｮﾝ情報を保存するﾏｯﾌﾟ
	STATE _state;									// 今の状態
	unsigned int _animFrame;						// ｷｰの中のﾌﾚｰﾑ数
	unsigned int _animCount;						// ｷｰの中の出だしから何回ﾙｰﾌﾟしているか

protected:
	bool DestroyPrpc(void);			// 当たり判定などに使う
	UNIT_ID _unitID;
	bool _alive;					// 生存ﾌﾗｸﾞ
	bool _dead;						// 死亡ﾌﾗｸﾞ
	vector2Dbl _pos;				// 描画位置
	vector2Int _size;				// 描画のｻｲｽﾞ
	double _rad;					// 角度
	int _zOrder;					// どの順番で描画するか
};

