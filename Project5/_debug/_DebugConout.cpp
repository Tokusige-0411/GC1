#ifdef _DEBUG
#include <Windows.h>
#include "_DebugConout.h"

std::unique_ptr<_DebugConOut, _DebugConOut::_DebugConOutDeleter> _DebugConOut::_sInstance(new _DebugConOut());

_DebugConOut::_DebugConOut()
{
	AllocConsole();
	freopen_s(&_debugFp, "CONOUT$", "w", stdout);
	freopen_s(&_debugFp, "CONOUT$", "r", stdin);
}

_DebugConOut::~_DebugConOut()
{
	FreeConsole();
}

#endif // DEBUG