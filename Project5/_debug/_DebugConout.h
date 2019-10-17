#pragma once
#ifdef _DEBUG

#include <windows.h>
#include <memory>

// ���ޯ��ү���ޗp��`
#define AST() {\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %d�s��\0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, "���ĕ\��", MB_OK);\
	}

#define TRACE(fmt, ...)printf(fmt, __VA_ARGS__);

class _DebugConOut
{
public:
	// �ݽ�׸�
	static _DebugConOut& GetInstance(void)
	{
		// imageMng�̎Q�Ƃ�Ԃ�����
		// imageMng��Ԃ�����
		// *�ͽϰ��߲����̒��g��Ԃ�
		return *_sInstance;
	}
private:
	struct _DebugConOutDeleter
	{
		void operator() (_DebugConOut* _debugConOut) const
		{
			delete _debugConOut;
		}
	};
	static std::unique_ptr<_DebugConOut, _DebugConOutDeleter> _sInstance;
	_DebugConOut();
	~_DebugConOut();

	FILE* _debugFp = nullptr;
};
#else	// DEBUG
#define AST()
#define TRACE(fmt, ...)
#endif	// DEBUG

