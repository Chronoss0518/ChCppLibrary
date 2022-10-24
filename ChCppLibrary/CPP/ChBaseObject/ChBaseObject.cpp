
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
		(*it)->WithdrawParent();
		childList.erase(it);
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

		if (ChPtr::NotNullCheck(objMaList))continue;

		childs->BaseRelease();
	}

	childList.clear();
	
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

	auto&& com = comList.begin();

	while (com != comList.end())
	{
		std::string tmpName = typeid((*com)).name();

		if (tmpName.find(_comName) == tmpName.npos) {
			com++;
			continue;
		}
		(*com)->Release();
		com = comList.erase(com);

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
		child = childList.erase(child);

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
		com = comList.erase(com);
		if (comList.empty())break;

	}
}

std::vector<ChPtr::Shared<BaseObject>>& BaseObject::GetChildlen()
{
	return childList;
}

std::vector<ChPtr::Shared<BaseObject>> BaseObject::GetAllChildlen()
{
	std::vector<ChPtr::Shared<BaseObject>>res = childList;

	for (auto&& childObj : childList)
	{
		for (auto&& childChild : childObj->GetAllChildlen())
		{
			res.push_back(childChild);
		}
	}

	return res;
}

void BaseObject::SetComponent(ChPtr::Shared<BaseComponent> _component)
{
	if (_component == nullptr)return;
	if (ChPtr::NotNullCheck(_component->obj))return;

	_component->BaseInit(this);

	comList.push_back(_component);
}

void BaseObject::SetChild(ChPtr::Shared<BaseObject> _childObject)
{

	if (_childObject == nullptr)return;
	if (this == _childObject.get())return;

	_childObject->WithdrawParent();

	childList.push_back(_childObject);

	_childObject->parent = shared_from_this();

}

void BaseObject::SetParent(ChPtr::Shared<BaseObject> _parentObject)
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

	parent.reset();

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
		if (comList.empty())break;
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->UpdateBeginFunction();
		if (childList.empty())break;
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::UpdateFunction()
{
	Update();

	if (!comList.empty())
	{
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
			if ((*com)->IsUseFlg())(*com)->Update();

			if (comList.empty())break;
			com++;
		}
	}

	if (!childList.empty())
	{
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
			if ((*child)->IsUseFlg())(*child)->Update();

			if (childList.empty())break;
			child++;
		}
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
		if (comList.empty())break;
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->UpdateEnd();
		if (childList.empty())break;
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
		if (comList.empty())break;
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->MoveBeginFunction();
		if (childList.empty())break;
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
		if (comList.empty())break;
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->MoveFunction();
		if (childList.empty())break;
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
		if (comList.empty())break;
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->MoveEndFunction();
		if (childList.empty())break;
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
		if (comList.empty())break;
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->DrawBeginFunction();
		if (childList.empty())break;
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
		if (comList.empty())break;
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->Draw3DFunction();
		if (childList.empty())break;
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
		if (comList.empty())break;
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->Draw2DFunction();
		if (childList.empty())break;
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
		if (comList.empty())break;
	}

	for (auto&& childs : childList)
	{
		if (!childs->IsUseFlg())continue;
		childs->DrawEndFunction();
		if (childList.empty())break;
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

	objMaList = _objMaList;

}
