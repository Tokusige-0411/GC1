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

INPUT_ID begin(INPUT_ID);				// 1番目のINPUT_ID返す
INPUT_ID end(INPUT_ID);					// 最後のINPUT_ID返す
INPUT_ID operator*(INPUT_ID key);
INPUT_ID operator++(INPUT_ID& key);