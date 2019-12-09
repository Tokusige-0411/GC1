#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <Vector2.h>

enum class STATE
{
	NORMAL,			// ’Êí
	EX,				// “Áê
	DETH,			// ”š”­
	MAX
};

// ˆê”Ôã‚Ì¸×½‚Åì‚Á‚Ä‚¢‚é‚ªAí—Ş‚ª‘½‚¯‚ê‚Î×‚©‚­•ª‚¯‚½‚Ù‚¤‚ª‚¢‚¢
enum class UNIT_ID
{
	NON,
	PLAYER,
	ENEMY,
	PL_BULLET,
	EM_BULLET,
};

// “à‘¤‚Ì<>‚©‚ç
class Obj;

using AnimVector = std::vector<std::pair<int, unsigned int>>;
using sharedObj = std::shared_ptr<Obj>;

class Obj
{
public:
	// -----------ŠÖ”
	Obj();
	virtual void Update(sharedObj Obj) = 0;
	void Draw(void);							// ·­°‚ğ’Ç‰Á‚·‚é
	void Draw(int id);							// ID‚ğ“Š‚°‚Ä·­°‚ğ’Ç‰Á
	virtual ~Obj();

	bool state(const STATE state);		// set
	const STATE state(void)const;		// get

	bool SetAnim(const STATE state, AnimVector& data);		// ±ÆÒ·°‚ğİ’è‚·‚é
	virtual bool SetAlive(bool alive);						// ½Ã°À½‚ğ•ÏX‚·‚é
	virtual bool exFlag(void);								// exFlag‚ğŒ©‚é
	virtual bool SetExFlag(bool exFlag);					// exFlag‚ğİ’è‚·‚é

	bool isAlive(void) { return _alive; }					// ¶‘¶Ì×¸Ş‚ğ•Ô‚·
	bool isDead(void) { return _dead; }						// €–SÌ×¸Ş‚ğ•Ô‚·
	bool isAnimEnd(void);									// ±ÆÒ°¼®İ‚ªI‚í‚Á‚½‚©‚Ç‚¤‚©

	// QÆ‚³‚¹‚½‚¢pos state size‚Ìget‚ğ‚Â‚­‚é
	const vector2Dbl& pos(void) const;						// pos‚ÌgetŠÖ”
	const vector2Dbl& size(void) const;						// size‚ÌgetŠÖ”
	const UNIT_ID& unitID(void) const;						// unitID‚ÌgetŠÖ”

private:
	std::map<STATE, AnimVector> _animMap;			// ±ÆÒ°¼®İî•ñ‚ğ•Û‘¶‚·‚éÏ¯Ìß
	STATE _state;									// ¡‚Ìó‘Ô
	unsigned int _animFrame;						// ·°‚Ì’†‚ÌÌÚ°Ñ”
	unsigned int _animCount;						// ·°‚Ì’†‚Ìo‚¾‚µ‚©‚ç‰½‰ñÙ°Ìß‚µ‚Ä‚¢‚é‚©

protected:
	bool DestroyPrpc(void);			// “–‚½‚è”»’è‚È‚Ç‚Ég‚¤
	UNIT_ID _unitID;				// ÕÆ¯ÄŠÇ—
	bool _alive;					// ¶‘¶Ì×¸Ş
	bool _dead;						// €–SÌ×¸Ş
	vector2Dbl _pos;				// •`‰æˆÊ’u
	vector2Dbl _size;				// •`‰æ‚Ì»²½Ş
	double _rad;					// Šp“x
	int _zOrder;					// ‚Ç‚Ì‡”Ô‚Å•`‰æ‚·‚é‚©
	bool _exFlag;					// EXÓ°ÄŞ(“G‚ªŠg‘åk¬‚©Œ©‚ÄAttack‚ÉˆÚ‚é‚©‚Ç‚¤‚©)
};

