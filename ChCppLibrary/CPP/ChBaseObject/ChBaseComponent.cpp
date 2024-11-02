
#include"../../BaseIncluder/ChBase.h"

#include"ChBaseComponent.h"
#include"ChBaseObject.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChBaseComponentƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void BaseComponent::BaseInit(BasicObject* _obj)
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
	if (ChPtr::NullCheck(obj))return;
	obj->Destroy();
	obj = nullptr;
}
