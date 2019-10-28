#include <DxLib.h>
#include <_DebugConout.h>
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

	modeKeyOld = 1;					// ����̨�ނ��ضް����
	_confID = INPUT_ID::LEFT;		// ����̨�ޗp�̕ϐ�

	// ̧�ق��緰���̓ǂݍ���
	if ((fopen_s(&filePt, "data/key.dat", "r")) == NULL)
	{
		_keyCon.resize(static_cast<size_t>(end(INPUT_ID())));
		fread(_keyCon.data(), sizeof(_keyCon[0]), static_cast<size_t>(end(INPUT_ID())), filePt);
		fclose(filePt);
	}
	else
	{
		_keyCon = _keyConDef;			// ���������ꍇ��̫�Ă̷���̨�ނ��i�[
	}

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
	modeKeyOld = _buf[KEY_INPUT_F1];
	GetHitKeyStateAll(_buf);	// ���ׂĂ̷����̎擾
	// ���ް�֐��߲��
	(this->*func)();
}

void KeyState::RefKeyData(void)
{
	// _buf��INPUT_ID�̏���_state�ɏ�������
	for (auto id : INPUT_ID())
	{
		state(id, _buf[_keyCon[static_cast<int>(id)]]);
	}
	// F1����SetKeyConfig�ɐ؂�ւ�
	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		func = &KeyState::SetKeyConfig;
		// �ڰ��ŕ\��
		TRACE("����̨�ނ̊J�n\n")
	}

}

void KeyState::SetKeyConfig(void)
{

	 // F1����RefKeyData�ɐ؂�ւ�
	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		_confID = INPUT_ID::MAX;
		func = &KeyState::RefKeyData;
		// �ڰ��ŕ\��
		TRACE("����̨�ނ̏I��\n")
	}

	// ���݂��������炻�̷��ɐݒ�
	// ���肵���玟�̷��ɕύX
	// �Ō�܂ōs�����玩���I�ɏI��
	// ���������

	// ������
	for (auto key : INPUT_ID())
	{
		state(key, 0);
	}

	// ���ނ��g���Đݒ肵�����̔���
	auto checkKey = [&](int id) {
		for (INPUT_ID findKey = INPUT_ID::LEFT; findKey < _confID; ++findKey)
		{
			if (_keyCon[static_cast<int>(findKey)] == id)
			{
				return false;
			}
		}
		return true;
	};

	// ������Ă��鷰��������
	for (int id = 0; id < sizeof(_buf); id++)
	{
		if (!checkKey(id))
		{
			continue;
		}
		if (_buf[id] && (!_buf[KEY_INPUT_F1]))
		{
			// ���̐ݒ�
			_keyCon[static_cast<int>(_confID)] = id;
			++_confID;
			TRACE("%d�Ԗڂ̷��ݒ�\n", _confID)

			// �Ō�̷���̨�ނ��I�����
			if (_confID >= end(_confID))
			{
				if ((fopen_s(&filePt, "data/key.dat", "w")) == NULL)
				{
					fwrite(_keyCon.data(), sizeof(_keyCon[0]), static_cast<size_t>(end(INPUT_ID())), filePt);
					fclose(filePt);
				}
				else
				{
					AST();
				}
				func = &KeyState::RefKeyData;
				TRACE("����̨�ނ̏I��\n")
				break;
			}
		}
	}
}
