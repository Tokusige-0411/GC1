#include <type_traits>
#include "INPUT_ID.h"

INPUT_ID begin(INPUT_ID)
{
	return INPUT_ID::LEFT;
}

INPUT_ID end(INPUT_ID)
{
	return INPUT_ID::MAX;
}

INPUT_ID operator*(INPUT_ID key)
{
	return key;
}

INPUT_ID operator++(INPUT_ID & key)
{
	// 指定した型の基底の型を返してくれる
	return key = static_cast<INPUT_ID>(std::underlying_type<INPUT_ID>::type(key) + 1);
}
