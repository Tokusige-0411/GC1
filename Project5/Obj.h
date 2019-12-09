#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <Vector2.h>

enum class STATE
{
	NORMAL,			// �ʏ�
	EX,				// ����
	DETH,			// ����
	MAX
};

// ��ԏ�̸׽�ō���Ă��邪�A��ނ�������΍ׂ����������ق�������
enum class UNIT_ID
{
	NON,
	PLAYER,
	ENEMY,
	PL_BULLET,
	EM_BULLET,
};

// ������<>����
class Obj;

using AnimVector = std::vector<std::pair<int, unsigned int>>;
using sharedObj = std::shared_ptr<Obj>;

class Obj
{
public:
	// -----------�֐�
	Obj();
	virtual void Update(sharedObj Obj) = 0;
	void Draw(void);							// �����ǉ�����
	void Draw(int id);							// ID�𓊂��ķ����ǉ�
	virtual ~Obj();

	bool state(const STATE state);		// set
	const STATE state(void)const;		// get

	bool SetAnim(const STATE state, AnimVector& data);		// ��ҷ���ݒ肷��
	virtual bool SetAlive(bool alive);						// �ð����ύX����
	virtual bool exFlag(void);								// exFlag������
	virtual bool SetExFlag(bool exFlag);					// exFlag��ݒ肷��

	bool isAlive(void) { return _alive; }					// �����׸ނ�Ԃ�
	bool isDead(void) { return _dead; }						// ���S�׸ނ�Ԃ�
	bool isAnimEnd(void);									// ��Ұ��݂��I��������ǂ���

	// �Q�Ƃ�������pos state size��get������
	const vector2Dbl& pos(void) const;						// pos��get�֐�
	const vector2Dbl& size(void) const;						// size��get�֐�
	const UNIT_ID& unitID(void) const;						// unitID��get�֐�

private:
	std::map<STATE, AnimVector> _animMap;			// ��Ұ��ݏ���ۑ�����ϯ��
	STATE _state;									// ���̏��
	unsigned int _animFrame;						// ���̒����ڰѐ�
	unsigned int _animCount;						// ���̒��̏o�������牽��ٰ�߂��Ă��邩

protected:
	bool DestroyPrpc(void);			// �����蔻��ȂǂɎg��
	UNIT_ID _unitID;				// �ƯĊǗ�
	bool _alive;					// �����׸�
	bool _dead;						// ���S�׸�
	vector2Dbl _pos;				// �`��ʒu
	vector2Dbl _size;				// �`��̻���
	double _rad;					// �p�x
	int _zOrder;					// �ǂ̏��Ԃŕ`�悷�邩
	bool _exFlag;					// EXӰ��(�G���g��k��������Attack�Ɉڂ邩�ǂ���)
};

