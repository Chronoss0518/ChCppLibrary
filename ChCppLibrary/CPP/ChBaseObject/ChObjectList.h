
#ifndef Ch_CPP_ObjList_h
#define Ch_CPP_ObjList_h

#ifdef CRT
#include<memory>
#include<vector>
#include<string>
#endif

#include"../../BasePack/ChPtr.h"

#include"ChBaseObject.h"

#ifndef CH_OBJECT_LIST_FUNCTION
#define CH_OBJECT_LIST_FUNCTION(_FunctionNameBase) \
void ChCpp::ObjectList::Object##_FunctionNameBase##()\
{\
	for (auto&& obj : ValueIns().objectList)\
	{\
		if (!obj->IsUseFlg())continue;\
		if (obj->GetParent().expired())continue;\
		obj->##_FunctionNameBase##Function();\
		if (ValueIns().objectList.empty())break;\
	}\
}
#endif

namespace ChCpp
{

	class ObjectList
	{
	public:

		friend BasicObject;

	public://Constructor Destructor//

		ObjectList();

		virtual ~ObjectList();

	public://Init And Release//

		virtual void Release() { ClearObject(); }

	public://Set Function//

#ifdef CRT

		//オブジェクトを登録する//
		//BaseObjectを継承したオブジェクトのみ登録可能//
		template<class T = BasicObject>
		typename std::enable_if<
			std::is_base_of<BasicObject, T>::value ||
			std::is_same<BasicObject, T>::value,
			ChPtr::Shared<T>>::type
			SetObject();
		
		void SetObject(ChPtr::Shared<BasicObject> _obj);

#endif

	public://Get Functions//

#ifdef CRT

		template<class T = BasicObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BasicObject, T>::value, T>::type>>
			GetObjectList()
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (auto&& obj : ValueIns().objectList)
			{
				if (obj->parent.lock() != nullptr)continue;
				auto&& test = ChPtr::SharedSafeCast<T>(obj);
				if (test == nullptr)continue;
				tmpObjList.push_back(test);
				for (auto&& childObj : obj->GetChildlen<T>())
				{
					tmpObjList.push_back(childObj);
				}
			}
			return tmpObjList;
		}

		template<class T = BasicObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BasicObject, T>::value, T>::type>>
			GetObjectListForName(const std::string& _name)
		{
			std::vector<ChPtr::Weak<BasicObject>>tmpObjList;

			for (auto&& obj : ValueIns().objectList)
			{
				if (obj->parent.lock() != nullptr)continue;
				auto&& test = ChPtr::SharedSafeCast<T>(obj);
				if (test == nullptr)continue;
				if (test->GetMyName() != _name)continue;
				tmpObjList.push_back(test);
				for (auto&& childObj : obj->GetChildlenForName<T>(_name))
				{
					tmpObjList.push_back(childObj);
				}
			}
			return tmpObjList;
		}

		inline size_t GetObjectCount(){ return ValueIns().objectList.size(); }
#endif

	public://Life Cycle Functions//

		//登録されているオブジェクトを更新する//
		void Update()
		{
			ObjectUpdateBegin();

			ObjectUpdate();

			ObjectUpdateEnd();
		}

		//Updateを区分けしたもの//
		void ObjectUpdateBegin();

		void ObjectUpdate();

		void ObjectUpdateEnd();

		//登録されているオブジェクトを移動させる//
		void Move()
		{
			ObjectMoveBegin();

			ObjectMove();

			ObjectMoveEnd();
		}

		//Moveを区分けしたもの//
		void ObjectMoveBegin();

		void ObjectMove();

		void ObjectMoveEnd();

		//登録されているオブジェクトを描画する。
		void Draw()
		{
			ObjectDrawBegin();

			ObjectDraw3D();

			ObjectDraw2D();

			ObjectDrawEnd();
		}


		//Drawをくわけしたもの//
		void ObjectDrawBegin();

		void ObjectDraw2D();

		void ObjectDraw3D();

		void ObjectDrawEnd();



		//保持しているすべてのオブジェクトを削除する。
		void ClearObject();

#ifdef CRT

		//選択された名前のオブジェクトをすべて消去する//
		template<typename CharaType>
		void ClearObjectForName(const std::basic_string<CharaType>& _name);

#endif

		//削除されるオブジェクトを確認して削除する//
		void DestroyObjectTest();

	protected:

		struct ObjectListCRT
		{
#ifdef CRT

			std::vector<ChPtr::Shared<BasicObject>>objectList;

#endif
		};

		ObjectListCRT& ValueIns() { return *value; }

	private:

		ObjectListCRT* value = nullptr;

	};

}

#ifdef CRT

ChCpp::ObjectList::ObjectList()
{
	value = new ObjectListCRT();
}

ChCpp::ObjectList::~ObjectList()
{
	Release();
	delete value;
}

void ChCpp::ObjectList::SetObject(ChPtr::Shared<BasicObject> _obj)
{
	if (_obj == nullptr)return;

	if (!ValueIns().objectList.empty())
	{
		if (std::find(ValueIns().objectList.begin(), ValueIns().objectList.end(), _obj) != ValueIns().objectList.end())return;
	}

	_obj->WithdrawObjectList();
	_obj->SetObjectList(this);
	ValueIns().objectList.push_back(_obj);

	for (auto&& child : _obj->value->childList) { SetObject(child); }
}

CH_OBJECT_LIST_FUNCTION(UpdateBegin);

void ChCpp::ObjectList::ObjectUpdate()
{
	auto&& obj = ValueIns().objectList.begin();

	while (obj != ValueIns().objectList.end())
	{
		if ((*obj)->IsDethFlg())
		{
			(*obj)->BaseRelease();
			obj = ValueIns().objectList.erase(obj);
			if (ValueIns().objectList.empty())break;
			continue;
		}

		if ((*obj)->IsUseFlg())
		{
			if ((*obj)->GetParent().expired())
			{
				(*obj)->UpdateFunction();
				if (ValueIns().objectList.empty())break;
			}
		}
		obj++;
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
	for (auto&& obj : ValueIns().objectList)
	{
		if (obj->GetParent().lock())continue;
		obj->BaseRelease();
	}
	if (!ValueIns().objectList.empty())ValueIns().objectList.clear();
}

template<typename CharaType>
void ChCpp::ObjectList::ClearObjectForName(const std::basic_string<CharaType>& _Name)
{
	for (auto&& obj : ValueIns().objectList)
	{
		auto&& baseObj = ChPtr::SharedSafeCast<BaseObject<CharaType>>(obj);
		if (baseObj == nullptr)continue;
		if (baseObj->myName.find(_Name, 0) == std::basic_string<CharaType>::npos)continue;
		baseObj->Destroy();
	}
}

void ChCpp::ObjectList::DestroyObjectTest()
{
	auto&& obj = ValueIns().objectList.begin();

	while (obj != ValueIns().objectList.end())
	{
		if (!(*obj)->dFlg)
		{
			obj++;
			continue;
		}
		(*obj)->BaseRelease();
		obj = ValueIns().objectList.erase(obj);
	}
}

#endif

#include"SharedFunctions/ChObjectSharedObjectList.h"

#endif