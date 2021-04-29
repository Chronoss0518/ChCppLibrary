
#include"../../BaseIncluder/ChBase.h"

#include"ChBaseComponent.h"
#include"ChObjectManager.h"
#include"ChBaseObject.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChBaseComponent���\�b�h
///////////////////////////////////////////////////////////////////////////////////////

void BaseComponent::BaseInit(ChPtr::Shared<BaseObject> _Obj)
{
	Obj = _Obj;
}

void BaseComponent::Destroy()
{
	DFlg = true;
}

void BaseComponent::ObjectDestroy()
{
	Obj->Destroy();
}