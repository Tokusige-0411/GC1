#pragma once
#include <vector>
#include <Vector2.h>

enum class MOVE_TYPE
{
	WAIT,			// 止まる
	SIGMOID,		// ｼｸﾞﾓｯﾄ曲線
	SPIRAL,			// 回転
	PITIN,			// ｹﾞｰﾑ開始位置
	LR,				// 左右移動
	EXRATE,			// 拡大縮小
};

// <動きの種類, 動きの目標地点>
using MoveState = std::vector<std::pair<MOVE_TYPE, vector2Dbl>>;

class EnemyMove
{
public:
	EnemyMove(vector2Dbl& pos, double & rad);								// 座標を入れる
	~EnemyMove();
	void Update(void);										// いろいろ更新
	bool SetMoveState(MoveState& state, bool newFlag);		// 関数ﾎﾟｲﾝﾀに設定する
private:
	void SetMovePrg(void);				// 動きの関数を設定する
	void (EnemyMove::*_move)(void);		// 関数ﾎﾟｲﾝﾀ(動きの設定)
	void MoveSigmoid(void);				// ｼｸﾞﾓｯﾄ関数
	void MoveSpairal(void);				// 回転させる
	void PitIn(void);					// ｹﾞｰﾑ開始位置へ
	void Wait(void);					// 動きを止める
	void MoveLR(void);					// ｹﾞｰﾑ中の左右移動
	void ExRate(void);					// 拡大縮小

	int count;

	MoveState _aimState;				// 動きのｽﾃｰﾀｽ
	int _aimCnt;						// 動きｽﾃｰﾀｽのｶｳﾝﾄ

	vector2Dbl _startPos;		// 各移動関数のｽﾀｰﾄ位置
	vector2Dbl _endPos;			// 各移動関数のｴﾝﾄﾞ位置
	vector2Dbl& _pos;			// EnemyMove上で使う座標
	double& _rad;				// 表示角度
	int _gameCount;
	double _sigCount;			// ｼｸﾞﾓｲﾄﾞ関数のｶｳﾝﾄ
	double _spaiRad;			// 回転で使う中心からの半径
	double _spaiAngl;			// 回転で使う中心の角度
	double _LRSpeed;			// LRでの移動量

	vector2Dbl _oneMoveVec;		// 1ﾌﾚｰﾑ当たりの移動量
};

