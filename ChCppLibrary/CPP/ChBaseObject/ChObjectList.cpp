

#include<iterator>

#include"ChBaseObject.h"
#include"ChObjectList.h"

#define CH_OBJECT_LIST_FUNCTION(_FunctionNameBase) \
void ChCpp::ObjectList::Object##_FunctionNameBase()\
{\
	for (size_t i = 0;i < objectList.size();i++){\
		auto&& obj = objectList[i];\
		if (!obj->IsUseFlg())continue;\
		if (obj->GetParent() != nullptr)continue;\
		obj->_FunctionNameBase##Function();\
		if (objectList.empty())return;\
	}\
}

#define EXPLICIT_DECLARATION(_type)\
template void ChCpp::ObjectList::ClearObjectForName<_type>(const std::basic_string<_type>& _Name);


void ChCpp::ObjectList::SetObject(ChPtr::Shared<BasicObject> _obj)
{
	if (_obj == nullptr)return;
	
	auto&& it = std::find(objectList.begin(), objectList.end(), _obj);
	if (it != objectList.end())return;

	_obj->WithdrawObjectList();
	_obj->objMaList = this;
	objectList.push_back(_obj);


	for (size_t i = 0; i < _obj->childList.size(); i++)
		SetObject(_obj->childList[i]);
}

CH_OBJECT_LIST_FUNCTION(UpdateBegin);

void ChCpp::ObjectList::ObjectUpdate()
{
	for (size_t itCount = 0; itCount < objectList.size();itCount)
	{
		
		if (objectList[itCount]->IsDethFlg())
		{
			objectList.erase(objectList.begin() + itCount);
			continue;
		}
		
		if (!objectList[itCount]->parent.expired() ||
			!objectList[itCount]->IsUseFlg())
		{
			itCount++;
			continue;
		}

		objectList[itCount]->UpdateFunction();
		itCount++;
	}

}

CH_OBJECT_LIST_FUNCTION(UpdateEnd);

CH_OBJECT_LIST_FUNCTION(MoveBegin);
CH_OBJECT_LIST_FUNCTION(Move);
CH_OBJECT_LIST_FUNCTION(MoveEnd);

CH_OBJECT_LIST_FUNCTION(DrawBegin);
CH_OBJECT_LIST_FUNCTION(Draw2D);
CH_OBJECT_LIST_FUNCTION(Draw3D);
CH_OBJECT_LIST_FUNCTION(DrawEnd);

void ChCpp::ObjectList::ClearObject()
{
	for (size_t i = 0; i < objectList.size(); i++)
	{
		if (objectList[i]->GetParent() != nullptr)continue;
		objectList[i]->BaseRelease();
	}
	objectList.clear();
}

template<typename CharaType>
void ChCpp::ObjectList::ClearObjectForName(const std::basic_string<CharaType>& _Name)
{
	for (size_t i = 0; i < objectList.size(); i++)
	{
		auto&& baseObj = dynamic_cast<BaseObject<CharaType>*>(objectList[i].get());
		if (ChPtr::NullCheck(baseObj))continue;
		if (baseObj->GetMyName().find(_Name) == std::basic_string<CharaType>::npos)continue;
		baseObj->Destroy();
	}
}

void ChCpp::ObjectList::DestroyObjectTest()
{
	for (auto&& it = objectList.begin();it != objectList.end();it)
	{
		if (!(*it)->dFlg)
		{
			it++;
			continue;
		}
		(*it)->BaseRelease();
		it = objectList.erase(it);
	}
}

EXPLICIT_DECLARATION(char);
EXPLICIT_DECLARATION(wchar_t);
EXPLICIT_DECLARATION(char8_t);
EXPLICIT_DECLARATION(char16_t);
EXPLICIT_DECLARATION(char32_t);