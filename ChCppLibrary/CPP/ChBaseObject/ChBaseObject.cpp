
#include"../../BaseIncluder/ChBase.h"

#include"ChBaseComponent.h"
#include"ChObjectList.h"
#include"ChBaseObject.h"

#define CH_OBJECT_FUNCTION(_FunctionNameBase) \
void ChCpp::BasicObject::##_FunctionNameBase##Function()\
{\
	##_FunctionNameBase##();\
	for(size_t i = 0; i < comList.GetSize(); i++){\
		if (!comList[i]->useFlg)continue; \
		comList[i]->##_FunctionNameBase##(); \
		if (comList.IsEmpty())break;}\
	for (size_t i = 0; i < childList.GetSize(); i++) {\
		if (!childList[i]->useFlg)continue; \
		childList[i]->##_FunctionNameBase##Function(); \
		if (childList.IsEmpty())break;}\
}

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//BaseObjectÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::BasicObject::BaseRelease()
{
	DestroyComponent();

	DestroyToChild();

	WithdrawParent();

	Release();

	dFlg = true;
	useFlg = false;

	if (ChPtr::NullCheck(objMaList))return;

	WithdrawObjectList();
}

void ChCpp::BasicObject::Destroy() { BaseRelease(); }


void ChCpp::BasicObject::DestroyToChildBase(ChCRT::SharedPtrPack<BasicObject>& _child)
{
	if (!childList.RemoveObj(_child))return;
	_child->BaseRelease();
}

void ChCpp::BasicObject::DestroyToChild()
{
	if (childList.GetSize() <= 0)return;
	for (size_t i = 0; i < childList.GetSize(); i++)
	{
		childList[i]->BaseRelease();
	}
	childList.Clear();
}

void ChCpp::BasicObject::DestroyComponent()
{
	if (comList.GetSize() <= 0)return;
	for (size_t i = 0; i < childList.GetSize(); i++)
	{
		comList[i]->Release();
	}
	comList.Clear();
}

void ChCpp::BasicObject::DestroyToChildTest()
{
	if (childList.GetSize())return;
	for (size_t i = 0; i < childList.GetSize(); i)
	{
		if (!childList[i]->IsDethFlg())
		{
			i++;
			continue;
		}
		childList[i]->Release();
		childList.Remove(i);
	}
}

void ChCpp::BasicObject::DestroyComponentTest()
{
	if (comList.GetSize())return;
	for (size_t i = 0; i < comList.GetSize(); i)
	{
		if (!comList[i]->IsDeth())
		{
			i++;
			continue;
		}
		comList[i]->Release();
		comList.Remove(i);
	}
}

void ChCpp::BasicObject::SetComponentCRT(ChCRT::SharedPtrPack<BaseComponent> _com)
{
	if (_com == ChCRT::NullPtr())return;
	if (ChPtr::NotNullCheck(_com->obj))return;

	comList.Push(_com);

	_com->BaseInit(this);
}

void ChCpp::BasicObject::SetChildCRT(ChCRT::SharedPtrPack<BasicObject> _childObject)
{
	if (_childObject == ChCRT::NullPtr())return;
	if (this == _childObject.Get())return;

	_childObject->WithdrawParent();

	childList.Push(_childObject);

	_childObject->parent = this;
}

void ChCpp::BasicObject::WithdrawParent()
{
	if (ChPtr::NullCheck(parent))return;
	if (parent->childList.IsEmpty())return;

	for (size_t i = 0; i < parent->childList.GetSize(); i++)
	{
		if (parent != parent->childList[i].Get())continue;
		parent->childList.Remove(i);
		break;
	}
}


void ChCpp::BasicObject::WithdrawObjectList()
{
	if (objMaList == nullptr)return;
	if (objMaList->objectList.IsEmpty())return;

	for (size_t i = 0; i < objMaList->objectList.GetSize(); i++)
	{
		if (this != objMaList->objectList[i].Get())continue;
		objMaList->objectList.Remove(i);
		break;
	}
}

ChCpp::ObjectList* ChCpp::BasicObject::LookObjectList() { return objMaList; }

CH_OBJECT_FUNCTION(UpdateBegin);

void ChCpp::BasicObject::UpdateFunction()
{
	Update();

	if (!comList.IsEmpty())
	{
		for (size_t i = 0; i < comList.GetSize(); i)
		{
			if (comList[i]->IsDeth())
			{
				comList[i]->Release();
				comList.Remove(i);
				if (comList.IsEmpty())break;
				continue;
			}
			if (comList[i]->IsUseFlg())comList[i]->Update();
			if (comList.IsEmpty())break;
			i++;
		}
	}

	if (!childList.IsEmpty())
	{
		for (size_t i = 0; i < childList.GetSize(); i++)
		{
			if (childList[i]->dFlg)
			{
				childList[i]->Release();
				childList.Remove(i);
				if (childList.IsEmpty())break;
				continue;
			}
			if (childList[i]->useFlg)childList[i]->Update();

			if (childList.IsEmpty())break;
			i++;
		}
	}
}

CH_OBJECT_FUNCTION(UpdateEnd);

CH_OBJECT_FUNCTION(MoveBegin);
CH_OBJECT_FUNCTION(Move);
CH_OBJECT_FUNCTION(MoveEnd);

CH_OBJECT_FUNCTION(DrawBegin);
CH_OBJECT_FUNCTION(Draw2D);
CH_OBJECT_FUNCTION(Draw3D);
CH_OBJECT_FUNCTION(DrawEnd);
