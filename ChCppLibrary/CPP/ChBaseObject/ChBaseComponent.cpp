
#include"../../BaseIncluder/ChBase.h"

#include"ChBaseComponent.h"
#include"ChObjectList.h"
#include"ChBaseObject.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChBaseComponent���\�b�h
///////////////////////////////////////////////////////////////////////////////////////

void BaseComponent::BaseInit(BaseObject* _obj)
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