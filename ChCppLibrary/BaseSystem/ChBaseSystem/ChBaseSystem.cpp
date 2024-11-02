
#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"ChBaseSystem.h"

using namespace ChSystem;

///////////////////////////////////////////////////////////////////////////////////////
//ChBaseSystem ÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

bool ChSystem::BaseSystem::IsPushKey(const int _Key)
{
	SetKeyCode();

	if (buttonList.GetBitFlg(_Key))
	{
		isNowPush.SetBitTrue(_Key);
		return true;
	}
	isNowPush.SetBitFalse(_Key);
	return false;
}

bool ChSystem::BaseSystem::IsPushKeyNoHold(const int _Key)
{
	SetKeyCode();

	if (buttonList.GetBitFlg(_Key))
	{
		if (!isNowPush.GetBitFlg(_Key))
		{
			isNowPush.SetBitTrue(_Key);
			return true;
		}
		return false;
	}
	isNowPush.SetBitFalse(_Key);
	return false;
}

bool ChSystem::BaseSystem::IsPause(const int _Key)
{
	SetKeyCode();

	bool tmpFlg;
	tmpFlg = IsPushKey(_Key);

	if (tmpFlg && nowKey)return pauseFlg;
	nowKey = false;

	if (!tmpFlg)return pauseFlg;

	pauseFlg = !pauseFlg;
	nowKey = true;

	return pauseFlg;
}

void ChSystem::SystemManager::Release()
{
	if (!*this)return;

	baseSystems = nullptr;

	SetInitFlg(false);
}
