
#include"../../BaseIncluder/ChBase.h"

#include"ChBaseComponent.h"
#include"ChObjectList.h"
#include"ChBaseObject.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChBaseComponent???\?b?h
///////////////////////////////////////////////////////////////////////////////////////

void BaseComponent::BaseInit(ChPtr::Shared<BaseObject> _obj)
{
	obj = _obj;

	Init();
}

void BaseComponent::Destroy()
{
	dFlg = true;
	useFlg = false;
}

void BaseComponent::DestroyObject()
{
	auto tmpObj = obj.lock();
	if (tmpObj == nullptr)return;
	tmpObj->Destroy();
}