#pragma once

enum class LAYER
{
	BG,
	CHAR,
	UI,
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator*(LAYER key);
LAYER operator++(LAYER & key);
