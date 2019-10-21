#include <DxLib.h>
#include "KeyState.h"

KeyState::KeyState()
{
	// begin(INPUT_ID());
	// end(INPUT_ID())
	// �����蒼���̂͂߂�ǂ�����
	// �^���̂�INPUT_ID�^�Ȃ̂ŷ��Ă���
	_keyConDef.reserve(static_cast<size_t>(end(INPUT_ID())));
	// ���̒ǉ�
	_keyConDef.emplace_back(KEY_INPUT_LEFT);		// ��
	_keyConDef.emplace_back(KEY_INPUT_RIGHT);		// �E
	_keyConDef.emplace_back(KEY_INPUT_UP);			// ��
	_keyConDef.emplace_back(KEY_INPUT_DOWN);		// ��
	_keyConDef.emplace_back(KEY_INPUT_Z);			// BTN1
	_keyConDef.emplace_back(KEY_INPUT_X);			// BTN2
	_keyConDef.emplace_back(KEY_INPUT_A);			// BTN3
	_keyConDef.emplace_back(KEY_INPUT_S);			// BTN4

	_keyCon = _keyConDef;

	// ���ް�֐����߲���͵̾�ĂɂȂ��Ă���
	// �̾�ĂȂ̂Őe�̱��ڽ���킩��Ȃ�
	// ���O��Ԃ��w�肵�Ă����Ȃ���΂Ȃ�Ȃ�
	func = &KeyState::RefKeyData;
}

KeyState::~KeyState()
{
}

void KeyState::Update(void)
{
	SetOld();					// �����̍X�V
	GetHitKeyStateAll(_buf);	// ���ׂĂ̷����̎擾
	// ���ް�֐��߲��
	(this->*func)();
}

void KeyState::RefKeyData(void)
{
}

void KeyState::SetKeyConfig(void)
{
}
