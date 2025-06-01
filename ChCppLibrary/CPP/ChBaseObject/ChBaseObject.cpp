
#include"../../BaseIncluder/ChBase.h"

#include"ChBaseComponent.h"
#include"ChObjectList.h"
#include"ChBaseObject.h"

#define CH_OBJECT_FUNCTION(_FunctionNameBase) \
void ChCpp::BasicObject::_FunctionNameBase##Function()\
{\
	_FunctionNameBase();\
	for(size_t i = 0; i < comList.size(); i++){\
		if (!comList[i]->useFlg)continue; \
		comList[i]->_FunctionNameBase(); \
		if (comList.empty())break;}\
	for (size_t i = 0; i < childList.size(); i++) {\
		if (!childList[i]->useFlg)continue; \
		childList[i]->_FunctionNameBase##Function(); \
		if (childList.empty())break;}\
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


void ChCpp::BasicObject::DestroyToChild()
{
	if (childList.size() <= 0)return;
	for (size_t i = 0; i < childList.size(); i++)
	{
		childList[i]->BaseRelease();
	}
	childList.clear();
}

void ChCpp::BasicObject::DestroyComponent()
{
	if (comList.size() <= 0)return;
	for (size_t i = 0; i < childList.size(); i++)
	{
		comList[i]->Release();
	}
	comList.clear();
}

void ChCpp::BasicObject::DestroyToChildTest()
{
	if (childList.size())return;
	for (size_t i = 0; i < childList.size(); i)
	{
		if (!childList[i]->IsDethFlg())
		{
			i++;
			continue;
		}
		childList[i]->Release();
		childList.erase(childList.begin() + i);
	}
}

void ChCpp::BasicObject::DestroyComponentTest()
{
	if (comList.size())return;
	for (size_t i = 0; i < comList.size(); i)
	{
		if (!comList[i]->IsDeth())
		{
			i++;
			continue;
		}
		comList[i]->Release();
		comList.erase(comList.begin() + i);
	}
}

void ChCpp::BasicObject::SetComponent(ChPtr::Shared<BaseComponent> _com)
{
	if (_com == nullptr)return;
	if (ChPtr::NotNullCheck(_com->obj))return;

	comList.push_back(_com);

	_com->BaseInit(this);
}

void ChCpp::BasicObject::SetChild(ChPtr::Shared<BasicObject> _childObject)
{
	if (_childObject == nullptr)return;

	_childObject->WithdrawParent();

	childList.push_back(_childObject);

	_childObject->parent = shared_from_this();
}

void ChCpp::BasicObject::WithdrawParent()
{
	if (parent.expired())return;
	auto&& parentObj = parent.lock();
	if (parentObj->childList.empty())return;

	for (size_t i = 0; i < parentObj->childList.size(); i++)
	{
		if (parentObj.get() != parentObj->childList[i].get())continue;
		parentObj->childList.erase(childList.begin() + i);
		break;
	}
}


void ChCpp::BasicObject::WithdrawObjectList()
{
	if (objMaList == nullptr)return;
	if (objMaList->objectList.empty())return;

	for (size_t i = 0; i < objMaList->objectList.size(); i++)
	{
		if (this != objMaList->objectList[i].get())continue;
		objMaList->objectList.erase(objMaList->objectList.begin() + i);
		break;
	}
}

ChCpp::ObjectList* ChCpp::BasicObject::LookObjectList() { return objMaList; }

CH_OBJECT_FUNCTION(UpdateBegin);

void ChCpp::BasicObject::UpdateFunction()
{
	Update();

	if (!comList.empty())
	{
		for (size_t i = 0; i < comList.size(); i)
		{
			if (comList[i]->IsDeth())
			{
				comList[i]->Release();
				comList.erase(comList.begin() + i);
				if (comList.empty())break;
				continue;
			}
			if (comList[i]->IsUseFlg())comList[i]->Update();
			if (comList.empty())break;
			i++;
		}
	}

	if (!childList.empty())
	{
		for (size_t i = 0; i < childList.size(); i++)
		{
			if (childList[i]->dFlg)
			{
				childList[i]->Release();
				childList.erase(childList.begin() + i);
				if (childList.empty())break;
				continue;
			}
			if (childList[i]->useFlg)childList[i]->Update();

			if (childList.empty())break;
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



CH_STRING_TYPE_EXPLICIT_DECLARATION(ChCpp::BaseObject);