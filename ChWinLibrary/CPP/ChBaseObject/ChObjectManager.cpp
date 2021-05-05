
#include"../../BaseIncluder/ChBase.h"

#include"ChObjectManager.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChObjectManagerÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////


std::vector<ChPtr::Shared<BaseObject>> ObjectManager::GetObjectList()
{
	std::vector<ChPtr::Shared<BaseObject>>tmpObjList;

	for (auto&& objlist : objectList)
	{
		for (auto&& obj : objlist.second)
		{
			tmpObjList.push_back(obj);
		}
	}

	return tmpObjList;

}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<BaseObject>> ObjectManager::GetObjectListForTag(const std::string& _TagName)
{

	std::vector<ChPtr::Shared<BaseObject>>tmpObjList;

	for (auto&& obj : objectList[_TagName])
	{
		tmpObjList.push_back(obj);
	}

	return tmpObjList;

}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<BaseObject>> ObjectManager::GetObjectListForName(const std::string& _Name)
{

	std::vector<ChPtr::Shared<BaseObject>>tmpObjList;

	for (auto&& objlist : objectList)
	{
		for (auto&& obj : objlist.second)
		{
			if (obj->GetMyName() != _Name)continue;
			tmpObjList.push_back(obj);
		}
	}

	return tmpObjList;
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::Update()
{

	ObjectUpdateBegin();

	ObjectUpdate();

	ObjectUpdateEnd();

}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectUpdateBegin()
{

	for (auto&& obj : rootObjects)
	{
		obj->UpdateBeginFunction();
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectUpdate()
{
	for (auto&& objGloap : objectList)
	{
		auto obj = objGloap.second.begin();
		while (obj != objGloap.second.end())
		{
			if ((*obj) != nullptr)
			{

				if (!(*obj)->dFlg)
				{
					(*obj)->IsReleasComponent();
					obj++;
					continue;
				}
			}
			objGloap.second.erase(obj);

		}
	}

	if (rootObjects.empty())return;

	auto obj = rootObjects.begin();

	while (obj != rootObjects.end())
	{

		if ((*obj)->dFlg)
		{
			rootObjects.erase(obj);
			continue;
		}

		(*obj)->UpdateFunction();

		obj++;
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectUpdateEnd()
{
	for (auto&& obj : rootObjects)
	{
		obj->UpdateEndFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::Move()
{
	ObjectMoveBegin();

	ObjectMove();

	ObjectMoveEnd();
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectMoveBegin()
{
	for (auto&& obj : rootObjects)
	{
		obj->MoveBeginFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectMove()
{
	for (auto&& obj : rootObjects)
	{
		obj->MoveFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectMoveEnd()
{
	for (auto&& obj : rootObjects)
	{
		obj->MoveEndFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ClearObject()
{
	for (auto&& obj : rootObjects)
	{
		obj->BaseRelease();
	}

	if (!objectList.empty())objectList.clear();
	if (!rootObjects.empty())rootObjects.clear();
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ClearObjectForTag(const std::string& _Tags)
{
	if (objectList.find(_Tags) == objectList.end())return;

	for (auto&& obj : objectList[_Tags])
	{
		obj->Destroy();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ClearObjectForName(const std::string& _Name)
{
	for (auto&& objList : objectList)
	{
		for (auto&& obj : objList.second)
		{
			if (obj->myName.find(_Name, 0) == std::string::npos)continue;
			obj->Destroy();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ClearObjectForTagAndName(
	const std::string& _Name,
	const std::string& _Tags)
{
	if (objectList.find(_Tags) == objectList.end())return;

	for (auto&& obj : objectList[_Tags])
	{
		if (obj->myName.find(_Name, 0) != std::string::npos)continue;

		obj->Destroy();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::Draw()
{
	ObjectDrawBegin();

	ObjectDraw3D();

	ObjectDraw2D();

	ObjectDrawEnd();
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectDrawBegin()
{
	for (auto&& obj : rootObjects)
	{
		obj->DrawBeginFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectDraw2D()
{
	for (auto&& obj : rootObjects)
	{
		obj->Draw3DFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectDraw3D()
{
	for (auto&& obj : rootObjects)
	{
		obj->Draw2DFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectDrawEnd()
{
	for (auto&& obj : rootObjects)
	{
		obj->DrawEndFunction();
	}
}
