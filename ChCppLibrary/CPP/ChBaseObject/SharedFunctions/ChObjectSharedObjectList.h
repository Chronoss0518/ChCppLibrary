#ifdef CRT

#ifdef Ch_CPP_ObjList_h
#ifdef Ch_CPP_BaObj_h

#ifndef Ch_CPP_Shared_BaseObject_ObjectList
#define Ch_CPP_Shared_BaseObject_ObjectList

template<typename CharaType>
ChCpp::ObjectList<CharaType>* ChCpp::BaseObject<CharaType>::LookObjectList() { return objMaList; }

template<typename CharaType>
void ChCpp::BaseObject<CharaType>::WithdrawObjectList()
{
	if (objMaList == nullptr)return;
	if (objMaList->objectList.empty())return;

	auto&& test = std::find(objMaList->objectList.begin(), objMaList->objectList.end(), shared_from_this());

	if (test != objMaList->objectList.end()) { objMaList->objectList.erase(test); }
}

#endif

#endif
#endif

#endif