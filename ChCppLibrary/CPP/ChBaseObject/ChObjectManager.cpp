#include"ChObjectManager.h"

#ifndef CH_OBJECT_MGR_METHOD
#define CH_OBJECT_MGR_METHOD(_FunctionNameBase) \
template<typename CharaType>\
void ChCpp::ObjectManager<CharaType>::_FunctionNameBase()\
{\
	for (auto&& objList : objectList) { objList.second->_FunctionNameBase(); }\
}
#endif

#ifndef CH_OBJECT_MGR_TAG_METHOD
#define CH_OBJECT_MGR_TAG_METHOD(_FunctionNameBase) \
template<typename CharaType>\
void ChCpp::ObjectManager<CharaType>::_FunctionNameBase(const std::basic_string<CharaType>& _tag)\
{\
	auto&& it = objectList.find(_tag);\
	if (it == objectList.end())return;\
	(*it).second->_FunctionNameBase();\
}
#endif

template<typename CharaType>
void ChCpp::ObjectManager<CharaType>::Release() { ClearObject(); }

template<typename CharaType>
void ChCpp::ObjectManager<CharaType>::SetObject(ChPtr::Shared<BaseObject<CharaType>> _obj, const std::basic_string<CharaType>& _tag)
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

template<typename CharaType>
std::vector<std::basic_string<CharaType>> ChCpp::ObjectManager<CharaType>::GetTagList()
{
	std::vector<std::basic_string<CharaType>> res;

	for (auto&& objList : objectList)
	{
		res.push_back(objList.first);
	}

	return res;
}

template<typename CharaType>
unsigned long ChCpp::ObjectManager<CharaType>::GetObjectCount()
{
	unsigned long res = 0;
	for (auto&& objList : objectList)
	{
		res += objList.second->GetObjectCount();
	}
	return res;
}

template<typename CharaType>
unsigned long ChCpp::ObjectManager<CharaType>::GetTagCount() { return objectList.size(); }


CH_OBJECT_MGR_METHOD(Update);
CH_OBJECT_MGR_METHOD(ObjectUpdateBegin);
CH_OBJECT_MGR_METHOD(ObjectUpdate);
CH_OBJECT_MGR_METHOD(ObjectUpdateEnd);

CH_OBJECT_MGR_TAG_METHOD(Update);
CH_OBJECT_MGR_TAG_METHOD(ObjectUpdateBegin);
CH_OBJECT_MGR_TAG_METHOD(ObjectUpdate);
CH_OBJECT_MGR_TAG_METHOD(ObjectUpdateEnd);

CH_OBJECT_MGR_METHOD(Move);
CH_OBJECT_MGR_METHOD(ObjectMoveBegin);
CH_OBJECT_MGR_METHOD(ObjectMove);
CH_OBJECT_MGR_METHOD(ObjectMoveEnd);

CH_OBJECT_MGR_TAG_METHOD(Move);
CH_OBJECT_MGR_TAG_METHOD(ObjectMoveBegin);
CH_OBJECT_MGR_TAG_METHOD(ObjectMove);
CH_OBJECT_MGR_TAG_METHOD(ObjectMoveEnd);

CH_OBJECT_MGR_METHOD(Draw);
CH_OBJECT_MGR_METHOD(ObjectDrawBegin);
CH_OBJECT_MGR_METHOD(ObjectDraw2D);
CH_OBJECT_MGR_METHOD(ObjectDraw3D);
CH_OBJECT_MGR_METHOD(ObjectDrawEnd);

CH_OBJECT_MGR_TAG_METHOD(Draw);
CH_OBJECT_MGR_TAG_METHOD(ObjectDrawBegin);
CH_OBJECT_MGR_TAG_METHOD(ObjectDraw3D);
CH_OBJECT_MGR_TAG_METHOD(ObjectDraw2D);
CH_OBJECT_MGR_TAG_METHOD(ObjectDrawEnd);

template<typename CharaType>
void ChCpp::ObjectManager<CharaType>::ClearObject()
{
	for (auto&& objList : objectList)
	{
		objList.second->ClearObject();
	}
	objectList.clear();
}

template<typename CharaType>
void ChCpp::ObjectManager<CharaType>::ClearObjectForName(const std::basic_string<CharaType>& _name)
{
	for (auto&& objList : objectList)
	{
		objList.second->ClearObjectForName(_name);
	}
}

template<typename CharaType>
void ChCpp::ObjectManager<CharaType>::ClearObjectForTag(const std::basic_string<CharaType>& _tag)
{
	auto&& it = objectList.find(_tag);
	if (it == objectList.end())return;
	(*it).second->ClearObject();
	objectList.erase(it);
}

template<typename CharaType>
void ChCpp::ObjectManager<CharaType>::ClearObjectForNameAndTag(const std::basic_string<CharaType>& _name, const std::basic_string<CharaType>& _tag)
{
	auto&& it = objectList.find(_tag);
	if (it == objectList.end())return;
	(*it).second->ClearObjectForName(_name);
}

CH_STRING_TYPE_EXPLICIT_DECLARATION(ChCpp::ObjectManager);
