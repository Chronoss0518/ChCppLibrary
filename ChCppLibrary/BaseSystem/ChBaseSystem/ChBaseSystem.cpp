
#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"ChBaseSystem.h"

using namespace ChSystem;

///////////////////////////////////////////////////////////////////////////////////////
//ChBaseSystem ÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////


bool BaseSystem::IsPushKey(const int _Key)
{
	if (!useSystemButtonFlg)return 0;
	return buttonList.GetBitFlg(_Key);
}

bool BaseSystem::IsPushKeyNoHold(const int _Key)
{
	return buttonList.GetBitFlg(_Key);
}

bool BaseSystem::IsPause(const int _Key)
{
	return false;
}
