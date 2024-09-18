
#include"../../BaseIncluder/ChBase.h"

#include"ChBaseComponent.h"
#include"ChBaseObject.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChBaseComponentÉÅÉ\ÉbÉh
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
