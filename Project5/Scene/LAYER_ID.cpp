#include <type_traits>
#include "LAYER_ID.h"

LAYER begin(LAYER)
{
	return LAYER::BG;
}

LAYER end(LAYER)
{
	return LAYER::MAX;
}

LAYER operator*(LAYER key)
{
	return key;
}

LAYER operator++(LAYER & key)
{
	// 指定した型の基底の型を返してくれる
	return key = static_cast<LAYER>(std::underlying_type<LAYER>::type(key) + 1);
}