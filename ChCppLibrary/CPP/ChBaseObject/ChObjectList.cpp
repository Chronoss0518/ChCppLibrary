
#include"../../BaseIncluder/ChBase.h"

#include"ChObjectList.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChObjectListÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::Release()
{
	ClearObject();
}

void ObjectList::SetObject(ChPtr::Shared<BaseObject> _obj)
{

	if (_obj == nullptr)return;

	if (!objectList.empty())
	{
		if (std::find(objectList.begin(), objectList.end(), _obj) != objectList.end())return;
	}

	_obj->WithdrawObjectList();

	_obj->objMaList = this;

	objectList.push_back(_obj);

	for (auto&& child : _obj->childList)
	{
		SetObject(child);
	}
}
///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::Update()
{

	ObjectUpdateBegin();

	ObjectUpdate();

	ObjectUpdateEnd();

}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectUpdateBegin()
{
	for (auto&& obj : objectList)
	{
		if (!obj->IsUseFlg())continue;
		if (obj->parent.lock())continue;
		obj->UpdateBeginFunction();
		if (objectList.empty())break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectUpdate()
{
	auto&& obj = objectList.begin();

	while (obj != objectList.end())
	{

		if ((*obj)->dFlg)
		{
			(*obj)->BaseRelease();
			obj = objectList.erase(obj);
			if (objectList.empty())break;
			continue;
		}

		if ((*obj)->IsUseFlg())
		{
			if (!(*obj)->parent.lock())
			{
				(*obj)->UpdateFunction();
				if (objectList.empty())break;
			}
		}
		
		obj++;
	}


}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectUpdateEnd()
{
	for (auto&& obj : objectList)
	{
		if (!obj->IsUseFlg())continue;
		if (!obj->parent.lock())continue;
		obj->UpdateEndFunction();
		if (objectList.empty())break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::Move()
{
	ObjectMoveBegin();

	ObjectMove();

	ObjectMoveEnd();
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectMoveBegin()
{
	for (auto&& obj : objectList)
	{
		if (!obj->IsUseFlg())continue;
		if (obj->parent.lock())continue;
		obj->MoveBeginFunction();
		if (objectList.empty())break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectMove()
{
	for (auto&& obj : objectList)
	{
		if (!obj->IsUseFlg())continue;
		if (obj->parent.lock())continue;
		obj->MoveFunction();
		if (objectList.empty())break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectMoveEnd()
{
	for (auto&& obj : objectList)
	{
		if (!obj->IsUseFlg())continue;
		if (obj->parent.lock())continue;
		obj->MoveEndFunction();
		if (objectList.empty())break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ClearObject()
{
	for (auto&& obj : objectList)
	{
		if (obj->parent.lock())continue;
		obj->BaseRelease();
	}

	if (!objectList.empty())objectList.clear();
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ClearObjectForName(const std::string& _Name)
{
	for (auto&& obj : objectList)
	{
		if (obj->myName.find(_Name, 0) == std::string::npos)continue;
		obj->Destroy();
	}
}

void ObjectList::DestroyObjectTest()
{

	auto&& obj = objectList.begin();

	while (obj != objectList.end())
	{

		if (!(*obj)->dFlg)
		{
			obj++;
			continue;
		}

		(*obj)->BaseRelease();
		obj = objectList.erase(obj);
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::Draw()
{
	ObjectDrawBegin();

	ObjectDraw3D();

	ObjectDraw2D();

	ObjectDrawEnd();
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectDrawBegin()
{
	for (auto&& obj : objectList)
	{
		if (!obj->IsUseFlg())continue;
		if (obj->parent.lock())continue;
		obj->DrawBeginFunction();
		if (objectList.empty())break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectDraw2D()
{
	for (auto&& obj : objectList)
	{
		if (!obj->IsUseFlg())continue;
		if (obj->parent.lock())continue;
		obj->Draw2DFunction();
		if (objectList.empty())break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectDraw3D()
{
	for (auto&& obj : objectList)
	{
		if (!obj->IsUseFlg())continue;
		if (obj->parent.lock())continue;
		obj->Draw3DFunction();
		if (objectList.empty())break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectDrawEnd()
{
	for (auto&& obj : objectList)
	{
		if (!obj->IsUseFlg())continue;
		if (obj->parent.lock())continue;
		obj->DrawEndFunction();
		if (objectList.empty())break;
	}
}


ObjectList* BaseObject::LookObjectList()
{
	return objMaList;
}
