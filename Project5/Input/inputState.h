#pragma once
#include <map>
#include "INPUT_ID.h"

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
	void SetOld(void);							// 1�ڰёO�̏�����������
private:
	KeyMap _state;			// �e���̽ð��
};
