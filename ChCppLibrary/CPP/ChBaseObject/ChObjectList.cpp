
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

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Weak<BaseObject>> ObjectList::GetObjectList()
{
	std::vector<ChPtr::Weak<BaseObject>>tmpObjList;

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

std::vector<ChPtr::Weak<BaseObject>> ObjectList::GetObjectListForTag(const std::string& _TagName)
{

	std::vector<ChPtr::Weak<BaseObject>>tmpObjList;

	for (auto&& obj : objectList[_TagName])
	{
		tmpObjList.push_back(obj);
	}

	return tmpObjList;

}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Weak<BaseObject>> ObjectList::GetObjectListForName(const std::string& _Name)
{

	std::vector<ChPtr::Weak<BaseObject>>tmpObjList;

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

void ObjectList::Update()
{

	ObjectUpdateBegin();

	ObjectUpdate();

	ObjectUpdateEnd();

}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectUpdateBegin()
{
	for (auto&& gObj : objectList)
	{
		for (auto&& obj : gObj.second)
		{
			if (obj->parent.lock() != nullptr)continue;
			obj->UpdateBeginFunction();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectUpdate()
{
	for (auto&& gObj : objectList)
	{
		auto obj = gObj.second.begin();

		while (obj != gObj.second.end())
		{

			if ((*obj)->dFlg)
			{
				gObj.second.erase(obj);
				continue;
			}

			if ((*obj)->parent.lock() != nullptr)continue;

			(*obj)->UpdateFunction();

			obj++;
		}
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectUpdateEnd()
{
	for (auto&& gObj : objectList)
	{
		for (auto&& obj : gObj.second)
		{
			if (obj->parent.lock() != nullptr)continue;
			obj->UpdateEndFunction();
		}
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
	for (auto&& gObj : objectList)
	{
		for (auto&& obj : gObj.second)
		{
			if (obj->parent.lock() != nullptr)continue;
			obj->MoveBeginFunction();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectMove()
{
	for (auto&& gObj : objectList)
	{
		for (auto&& obj : gObj.second)
		{
			if (obj->parent.lock() != nullptr)continue;
			obj->MoveFunction();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectMoveEnd()
{
	for (auto&& gObj : objectList)
	{
		for (auto&& obj : gObj.second)
		{
			if (obj->parent.lock() != nullptr)continue;
			obj->MoveEndFunction();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ClearObject()
{
	for (auto&& gObj : objectList)
	{
		for (auto&& obj : gObj.second)
		{
			if (obj->parent.lock() != nullptr)continue;
			obj->BaseRelease();
		}
	}

	if (!objectList.empty())objectList.clear();
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ClearObjectForTag(const std::string& _Tags)
{
	if (objectList.find(_Tags) == objectList.end())return;

	for (auto&& obj : objectList[_Tags])
	{
		obj->Destroy();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ClearObjectForName(const std::string& _Name)
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

void ObjectList::ClearObjectForTagAndName(
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
	for (auto&& gObj : objectList)
	{
		for (auto&& obj : gObj.second)
		{
			if (obj->parent.lock() != nullptr)continue;
			obj->DrawBeginFunction();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectDraw2D()
{
	for (auto&& gObj : objectList)
	{
		for (auto&& obj : gObj.second)
		{
			if (obj->parent.lock() != nullptr)continue;
			obj->Draw3DFunction();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectDraw3D()
{
	for (auto&& gObj : objectList)
	{
		for (auto&& obj : gObj.second)
		{
			if (obj->parent.lock() != nullptr)continue;
			obj->UpdateEndFunction();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectList::ObjectDrawEnd()
{
	for (auto&& gObj : objectList)
	{
		for (auto&& obj : gObj.second)
		{
			if (obj->parent.lock() != nullptr)continue;
			obj->DrawEndFunction();
		}
	}
}
