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

// ������<>����
class Obj;

using AnimVector = std::vector<std::pair<int, unsigned int>>;
using sharedObj = std::shared_ptr<Obj>;

class Obj
{
public:
	// -----------�֐�
	Obj();
	virtual void Update(void) = 0;
	void Draw(void);							// �����ǉ�����
	void Draw(int id);							// ID�𓊂��ķ����ǉ�
	virtual ~Obj();

	bool state(const STATE state);		// set
	const STATE state(void)const;		// get

	bool SetAnim(const STATE state, AnimVector& data);		// ��ҷ���ݒ肷��
	bool SetAlive(bool alive);								// �X�e�[�^�X��ύX����
	bool isAlive(void) { return _alive; }					// �����׸ނ�Ԃ�
	bool isDead(void) { return _dead; }						// ���S�׸ނ�Ԃ�
	bool isAnimEnd(void);

private:
	std::map<STATE, AnimVector> _animMap;			// ��Ұ��ݏ���ۑ�����ϯ��
	STATE _state;									// ���̏��
	unsigned int _animFrame;						// ���̒����ڰѐ�
	unsigned int _animCount;						// ���̒��̏o�������牽��ٰ�߂��Ă��邩

protected:
	bool DestroyPrpc(void);			// �����蔻��ȂǂɎg��
	bool _alive;					// �����׸�
	bool _dead;						// ���S�׸�
	vector2Dbl _pos;				// �`��ʒu
	vector2Int _size;				// �`��̻���
};

