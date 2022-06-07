
#include"../../BaseIncluder/ChBase.h"

#include"ChObjectList.h"
#include"ChObjectManager.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChObjectManagerÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////


void ObjectManager::Release()
{
	ClearObject();
}

void ObjectManager::SetObject(ChPtr::Shared<BaseObject> _obj, const std::string& _tag)
{
	if (_obj == nullptr)return;

	auto&& list = objectList.find(_tag);
	if (list == objectList.end())
	{
		objectList[_tag] = ChPtr::Make_S<ObjectList>();
		list = objectList.find(_tag);
	}

	list->second->SetObject(_obj);


}
void ObjectManager::Update()
{

	for (auto&& objList : objectList)
	{
		objList.second->Update();
	}

}

void ObjectManager::ObjectUpdateBegin()
{
	for (auto&& objList : objectList)
	{
		objList.second->ObjectUpdateBegin();
	}

}

void ObjectManager::ObjectUpdate()
{

	for (auto&& objList : objectList)
	{
		objList.second->ObjectUpdate();
	}

}

void ObjectManager::ObjectUpdateEnd()
{
	for (auto&& objList : objectList)
	{
		objList.second->ObjectUpdateEnd();
	}

}

void ObjectManager::Update(const std::string& _tag)
{
	auto&& it = objectList.find(_tag);

	if (it == objectList.end())return;

	(*it).second->Update();
}

void ObjectManager::ObjectUpdateBegin(const std::string& _tag)
{
	auto&& it = objectList.find(_tag);

	if (it == objectList.end())return;

	(*it).second->ObjectUpdateBegin();
}

void ObjectManager::ObjectUpdate(const std::string& _tag)
{
	auto&& it = objectList.find(_tag);

	if (it == objectList.end())return;

	(*it).second->ObjectUpdate();
}

void ObjectManager::ObjectUpdateEnd(const std::string& _tag)
{
	auto&& it = objectList.find(_tag);

	if (it == objectList.end())return;

	(*it).second->ObjectUpdateEnd();
}

void ObjectManager::Move()
{
	for (auto&& objList : objectList)
	{
		objList.second->Move();
	}

}

void ObjectManager::ObjectMoveBegin()
{
	for (auto&& objList : objectList)
	{
		objList.second->ObjectMoveBegin();
	}

}

void ObjectManager::ObjectMove()
{
	for (auto&& objList : objectList)
	{
		objList.second->ObjectMove();
	}
}

void ObjectManager::ObjectMoveEnd()
{
	for (auto&& objList : objectList)
	{
		objList.second->ObjectMoveEnd();
	}
}

void ObjectManager::Move(const std::string& _tag)
{
	auto&& it = objectList.find(_tag);

	if (it == objectList.end())return;

	(*it).second->Move();
}

void ObjectManager::ObjectMoveBegin(const std::string& _tag)
{
	auto&& it = objectList.find(_tag);

	if (it == objectList.end())return;

	(*it).second->ObjectMoveBegin();
}

void ObjectManager::ObjectMove(const std::string& _tag)
{
	auto&& it = objectList.find(_tag);

	if (it == objectList.end())return;

	(*it).second->ObjectMove();
}

void ObjectManager::ObjectMoveEnd(const std::string& _tag)
{
	auto&& it = objectList.find(_tag);

	if (it == objectList.end())return;

	(*it).second->ObjectMoveEnd();
}

void ObjectManager::Draw()
{
	for (auto&& objList : objectList)
	{
		objList.second->Draw();
	}
}

void ObjectManager::ObjectDrawBegin()
{
	for (auto&& objList : objectList)
	{
		objList.second->ObjectDrawBegin();
	}
}

void ObjectManager::ObjectDraw2D()
{
	for (auto&& objList : objectList)
	{
		objList.second->ObjectDraw2D();
	}
}

void ObjectManager::ObjectDraw3D()
{
	for (auto&& objList : objectList)
	{
		objList.second->ObjectDraw3D();
	}
}

void ObjectManager::ObjectDrawEnd()
{
	for (auto&& objList : objectList)
	{
		objList.second->ObjectDrawEnd();
	}
}

void ObjectManager::Draw(const std::string& _tag)
{
	auto&& it = objectList.find(_tag);

	if (it == objectList.end())return;

	(*it).second->Draw();
}

void ObjectManager::ObjectDrawBegin(const std::string& _tag)
{
	auto&& it = objectList.find(_tag);

	if (it == objectList.end())return;

	(*it).second->ObjectDrawBegin();
}

void ObjectManager::ObjectDraw2D(const std::string& _tag)
{
	auto&& it = objectList.find(_tag);

	if (it == objectList.end())return;

	(*it).second->ObjectDraw2D();
}

void ObjectManager::ObjectDraw3D(const std::string& _tag)
{
	auto&& it = objectList.find(_tag);

	if (it == objectList.end())return;

	(*it).second->ObjectDraw3D();
}

void ObjectManager::ObjectDrawEnd(const std::string& _tag)
{
	auto&& it = objectList.find(_tag);

	if (it == objectList.end())return;

	(*it).second->ObjectDrawEnd();
}

void ObjectManager::ClearObject()
{
	for (auto&& objList : objectList)
	{
		objList.second->ClearObject();
	}

	objectList.clear();
}

void ObjectManager::ClearObjectForName(const std::string& _name)
{
	for (auto&& objList : objectList)
	{
		objList.second->ClearObjectForName(_name);
	}

}

void ObjectManager::ClearObjectForTag(const std::string& _tag)
{
	auto&& it = objectList.find(_tag);

	if (it == objectList.end())return;

	(*it).second->ClearObject();

	objectList.erase(it);
}

void ObjectManager::ClearObjectForNameAndTag(const std::string& _name, const std::string& _tag)
{
	auto&& it = objectList.find(_tag);

	if (it == objectList.end())return;

	(*it).second->ClearObjectForName(_name);
}
