#pragma once
#include <vector>
#include "InputState.h"

class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();
	void Update(void) override;
private:
	void RefKeyData(void);				// ̧�ق����̨���ް���ǂݍ���
	void SetKeyConfig(void);			// ���т�����̨�ނ�ݒ�
	void (KeyState::*func)(void);

	char _buf[256];						// ����̨�ނ��ް���ۑ�����
	std::vector<int> _keyCon;			// ����̨�ނ��ް�
	std::vector<int> _keyConDef;		// ��̫�Ă̷���̨��
	int modeKeyOld;
	INPUT_ID _confID;
	FILE* filePt;
};

