
#include"../../BaseIncluder/ChBase.h"

#include"ChObjectList.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChObjectListƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::Release()
{
	ClearObject();
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
		if (obj->parent.lock() != nullptr)continue;
		obj->UpdateBeginFunction();
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
			objectList.erase(obj);
			continue;
		}

		if ((*obj)->parent.lock() != nullptr)continue;

		(*obj)->UpdateFunction();

		obj++;
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectUpdateEnd()
{
	for (auto&& obj : objectList)
	{
		if (obj->parent.lock() != nullptr)continue;
		obj->UpdateEndFunction();
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
		if (obj->parent.lock() != nullptr)continue;
		obj->MoveBeginFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectMove()
{
	for (auto&& obj : objectList)
	{
		if (obj->parent.lock() != nullptr)continue;
		obj->MoveFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectMoveEnd()
{
	for (auto&& obj : objectList)
	{
		if (obj->parent.lock() != nullptr)continue;
		obj->MoveEndFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ClearObject()
{
	for (auto&& obj : objectList)
	{
		if (obj->parent.lock() != nullptr)continue;
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
		if (obj->parent.lock() != nullptr)continue;
		obj->DrawBeginFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectDraw2D()
{
	for (auto&& obj : objectList)
	{
		if (obj->parent.lock() != nullptr)continue;
		obj->Draw3DFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectDraw3D()
{
	for (auto&& obj : objectList)
	{
		if (obj->parent.lock() != nullptr)continue;
		obj->UpdateEndFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectDrawEnd()
{
	for (auto&& obj : objectList)
	{
		if (obj->parent.lock() != nullptr)continue;
		obj->DrawEndFunction();
	}
}


ObjectList* BaseObject::LookObjectList()
{
	return objMaList;
}
