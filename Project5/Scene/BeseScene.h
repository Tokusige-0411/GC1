#pragma once
#include <memory>
#include <Obj.h>

class BaseScene;

enum class ACT_QUE
{
	NON,
	SHOT
};

using unique_Base = std::unique_ptr<BaseScene>;
using ActQueT = std::pair<ACT_QUE, Obj&>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;
	// RunActQue‚Ì‰¼‘zŠÖ”i_actList‚ğ‚»‚Ì‚Ü‚Ü“n‚·j
	virtual void RunActQue(std::vector<ActQueT> actList);
};

