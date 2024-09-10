#ifdef CRT

#ifdef Ch_CPP_ObjList_h
#ifdef Ch_CPP_BaObj_h

#ifndef Ch_CPP_Shared_BaseObject_ObjectList
#define Ch_CPP_Shared_BaseObject_ObjectList

void ChCpp::BasicObject::WithdrawObjectList()
{
	if (objMaList == nullptr)return;
	if (objMaList->ValueIns().objectList.empty())return;

	auto&& test = std::find(objMaList->ValueIns().objectList.begin(), objMaList->ValueIns().objectList.end(), shared_from_this());

	if (test != objMaList->ValueIns().objectList.end()) { objMaList->ValueIns().objectList.erase(test); }
}

ChCpp::ObjectList* ChCpp::BasicObject::LookObjectList() { return objMaList; }

template<class T>
typename std::enable_if<
	std::is_base_of<ChCpp::BasicObject, T>::value ||
	std::is_same<ChCpp::BasicObject, T>::value,
	ChPtr::Shared<T>>::type
	ChCpp::ObjectList::SetObject()
{
	ChPtr::Shared<ChCpp::BasicObject> res = ChPtr::Make_S<T>();
	res->SetObjectList(this);
	res->Init();
	ValueIns().objectList.push_back(res);
	return ChPtr::SharedSafeCast<T>(res);
}

#endif

#endif
#endif

#endif