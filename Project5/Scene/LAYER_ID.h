#pragma once

// add���Y��
enum class LAYER
{
	BG,
	CHAR,
	UI,
	EX,
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator*(LAYER key);
LAYER operator++(LAYER & key);
