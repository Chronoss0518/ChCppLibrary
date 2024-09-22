
#include"ChBaseObject.h"
#include"ChObjectList.h"

#define CH_OBJECT_LIST_FUNCTION(_FunctionNameBase) \
void ChCpp::ObjectList::Object##_FunctionNameBase##()\
{\
	for (size_t i = 0;i < objectList.GetSize();i++){\
		auto&& obj = objectList[i];\
		if (!obj->IsUseFlg())continue;\
		if (ChPtr::NotNullCheck(obj->GetParent()))continue;\
		obj->##_FunctionNameBase##Function();\
		if (objectList.IsEmpty())break;\
	}\
}

#define EXPLICIT_DECLARATION(_type)\
template void ChCpp::ObjectList::ClearObjectForNameBase<##_type##>(const ChCRT::StringPack<##_type##>& _Name);


void ChCpp::ObjectList::SetObjectCRT(ChCRT::SharedPtrPack<BasicObject> _obj)
{
	if (_obj == ChCRT::NullPtr())return;

	if (objectList.IsFind(_obj))return;

	_obj->WithdrawObjectList();
	_obj->objMaList = this;
	objectList.Push(_obj);


	for (size_t i = 0; i < _obj->childList.GetSize(); i++)
		SetObjectCRT(_obj->childList[i]);
}

CH_OBJECT_LIST_FUNCTION(UpdateBegin);

void ChCpp::ObjectList::ObjectUpdate()
{
	for (size_t i = 0; i < objectList.GetSize(); i)
	{
		if (objectList[i]->IsDethFlg())
		{
			objectList[i]->BaseRelease();
			objectList.Remove(i);
			if (objectList.IsEmpty())break;
			continue;
		}

		if (objectList[i]->IsUseFlg())
		{
			if (ChPtr::NullCheck(objectList[i]->GetParent()))
			{
				objectList[i]->UpdateFunction();
				if (objectList.IsEmpty())break;
			}
		}
		i++;
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
	for (size_t i = 0; i < objectList.GetSize(); i++)
	{
		if (ChPtr::NotNullCheck(objectList[i]->GetParent()))continue;
		objectList[i]->BaseRelease();
	}
	objectList.Clear();
}

template<typename CharaType>
void ChCpp::ObjectList::ClearObjectForNameBase(const ChCRT::StringPack<CharaType>& _Name)
{
	for (size_t i = 0; i < objectList.GetSize(); i++)
	{
		auto&& baseObj = dynamic_cast<BaseObject<CharaType>*>(objectList[i].Get());
		if (ChPtr::NullCheck(baseObj))continue;
		if (baseObj->myName.GetFindPosition(_Name) == ChCRT::StringPack<CharaType>::NPos)continue;
		baseObj->Destroy();
	}
}

void ChCpp::ObjectList::DestroyObjectTest()
{
	for (size_t i = 0; i < objectList.GetSize(); i++)
	{
		if (!objectList[i]->dFlg)
		{
			i++;
			continue;
		}
		objectList[i]->BaseRelease();
		objectList.Remove(i);
	}
}

EXPLICIT_DECLARATION(char);
EXPLICIT_DECLARATION(wchar_t);
EXPLICIT_DECLARATION(char8_t);
EXPLICIT_DECLARATION(char16_t);
EXPLICIT_DECLARATION(char32_t);