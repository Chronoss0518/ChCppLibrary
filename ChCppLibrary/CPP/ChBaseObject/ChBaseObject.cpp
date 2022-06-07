
#include"../../BaseIncluder/ChBase.h"

#include"ChBaseComponent.h"
#include"ChObjectList.h"
#include"ChBaseObject.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//BaseObjectメソッド
///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::Destroy()
{
	if (ChPtr::NullCheck(objMaList))
	{
		BaseRelease();
		return;
	}

	dFlg = true;
	useFlg = false;

	DestroyToChild();

	WithdrawParent();
}

void BaseObject::DestroyToChild(const ChPtr::Shared<BaseObject>& _child)
{
	auto it = std::find(childList.begin(), childList.end(), _child);

	if (it == childList.end())return;

	if (ChPtr::NullCheck((*it)->objMaList))
	{
		(*it)->BaseRelease();
		return;
	}

	(*it)->dFlg = true;

}

//自身が持つ子を削除する//
void BaseObject::DestroyToChild()
{
	if (childList.empty())return;

	for (auto&& childs : childList)
	{
		childs->dFlg = true;
	}

	childList.clear();

	objMaList->IsDestroyObject();
	
}

void BaseObject::DestroyComponent()
{
	if (comList.empty())return;

	for (auto com : comList)
	{
		com->Release();
	}

	comList.clear();

}

void BaseObject::DestroyComponent(const std::string& _comName)
{

	for (auto&& com : comList)
	{
		std::string tmpName = typeid((*com)).name();

		if (tmpName.find(_comName) == tmpName.npos) {
			continue;
		}

		auto tmp = std::find(comList.begin(), comList.end(), com);
		com->Release();
		comList.erase(tmp);

		if (comList.empty())break;

	}
}

void BaseObject::DestroyToChildTest()
{
	if (childList.empty())return;
	auto child = childList.begin();
	while (child != childList.end())
	{
		if (!(*child)->dFlg)
		{
			child++;
			continue;
		}
		(*child)->Release();
		childList.erase(child);

		if (childList.empty())break;
	}
}

void BaseObject::DestroyComponentTest()
{
	if (comList.empty())return;
	auto com = comList.begin();
	while (com != comList.end())
	{
		if (!(*com)->dFlg)
		{
			com++;
			continue;
		}
		(*com)->Release();
		comList.erase(com);
		if (comList.empty())break;

	}
}

void BaseObject::SetChild(ChPtr::Shared<BaseObject> _childObject)
{

	if (_childObject == nullptr)return;
	if (this == _childObject.get())return;

	_childObject->WithdrawParent();

	childList.push_back(_childObject);

	_childObject->parent = shared_from_this();

}

void BaseObject::SetParent(ChPtr::Shared<BaseObject>& _parentObject)
{
	if (this == _parentObject.get())return;

	WithdrawParent();

	parent = _parentObject;

	_parentObject->SetChild(shared_from_this());

}

void BaseObject::WithdrawParent()
{

	auto parentObj = parent.lock();

	if (parentObj == nullptr)return;
	if (parentObj->childList.empty())return;

	auto test = std::find(parentObj->childList.begin(), parentObj->childList.end(), shared_from_this());

	if (test != parentObj->childList.end())
	{
		parentObj->childList.erase(test);
	}
}

void BaseObject::WithdrawObjectList()
{
	if (objMaList == nullptr)return;
	if (objMaList->objectList.empty())return;

	auto test = std::find(objMaList->objectList.begin(), objMaList->objectList.end(), shared_from_this());

	if (test != objMaList->objectList.end())
	{
		objMaList->objectList.erase(test);
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::UpdateBeginFunction()
{
	UpdateBegin();

	for (auto com : comList)
	{
		if(!com->IsUseFlg())continue;
		com->UpdateBegin();
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->UpdateBeginFunction();
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::UpdateFunction()
{
	Update();

	auto com = comList.begin();
	while (com != comList.end())
	{
		if ((*com)->IsDeth())
		{
			(*com)->Release();
			comList.erase(com);
			if (comList.empty())break;
			continue;
		}
		if (!(*com)->IsUseFlg())continue;
		(*com)->Update();
		com++;
	}

	auto child = childList.begin();
	while (child != childList.end())
	{
		if ((*child)->dFlg)
		{
			(*child)->Release();
			childList.erase(child);
			if (childList.empty())break;
			continue;
		}
		if (!(*child)->IsUseFlg())continue;
		(*child)->Update();
		child++;
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::UpdateEndFunction()
{

	UpdateEnd();

	for (auto com : comList)
	{
		if (!com->IsUseFlg())continue;
		com->UpdateEnd();
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->UpdateEnd();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::MoveBeginFunction()
{

	MoveBegin();

	for (auto com : comList)
	{
		if (!com->IsUseFlg())continue;
		com->MoveBegin();
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->MoveBeginFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::MoveFunction()
{

	Move();

	for (auto com : comList)
	{
		if (!com->IsUseFlg())continue;
		com->Move();
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->MoveFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::MoveEndFunction()
{

	MoveEnd();

	for (auto com : comList)
	{
		if (!com->IsUseFlg())continue;
		com->MoveEnd();
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->MoveEndFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::DrawBeginFunction()
{

	DrawBegin();

	for (auto com : comList)
	{
		if (!com->IsUseFlg())continue;
		com->DrawBegin();
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->DrawBeginFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::Draw3DFunction()
{

	Draw3D();

	for (auto com : comList)
	{
		if (!com->IsUseFlg())continue;
		com->Draw3D();
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->Draw3DFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::Draw2DFunction()
{

	Draw2D();

	for (auto com : comList)
	{
		if (!com->IsUseFlg())continue;
		com->Draw2D();
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->Draw2DFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::DrawEndFunction()
{

	DrawEnd();

	for (auto com : comList)
	{
		if (!com->IsUseFlg())continue;
		com->DrawEnd();
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->DrawEndFunction();
	}
}

void BaseObject::BaseRelease()
{
	DestroyComponent();
	
	DestroyToChild();

	WithdrawParent();

	Release();
}

void BaseObject::BaseInit(
	const std::string& _ObjectName
	, ObjectList* _objMaList)
{
	myName = _ObjectName;

	Init();
}
