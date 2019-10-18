#pragma once

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

INPUT_ID begin(INPUT_ID);				// 1�Ԗڂ�INPUT_ID�Ԃ�
INPUT_ID end(INPUT_ID);					// �Ō��INPUT_ID�Ԃ�
INPUT_ID operator*(INPUT_ID key);
INPUT_ID operator++(INPUT_ID& key);