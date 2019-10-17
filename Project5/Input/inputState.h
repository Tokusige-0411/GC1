#pragma once
#include <map>

enum class INPUT_ID
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	BTN_1,
	BTN_2,
	BTN_3,
	BTN_4,
	MAX
};

// <���̷��̏��, 1�ڰёO�̷��̏��>
using KeyPair = std::pair<int, int>;
// <����ID, <���̷��̏��, 1�ڰёO�̷��̏��>>
using KeyMap = std::map<INPUT_ID, KeyPair>;

class InputState
{
public:
	InputState();
	virtual ~InputState();
	const KeyMap& state(void)const;				// ���̏������̂܂ܕԂ�
	const KeyPair& state(INPUT_ID id)const;		// ���̏��̒��g��Ԃ�
	bool state(INPUT_ID id, int data);			// ���̏�����������
private:
	KeyMap _state;
};

