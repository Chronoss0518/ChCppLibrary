
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
template<typename CharaType>\
void ChCpp::ObjectList<CharaType>::Object##_FunctionNameBase##()\
{\
	for (auto&& obj : objectList)\
	{\
		if (!obj->IsUseFlg())continue;\
		if (obj->GetParent().expired())continue;\
		obj->##_FunctionNameBase##Function();\
		if (objectList.empty())break;\
	}\
}
#endif

namespace ChCpp
{
	template<typename CharaType>
	class ObjectList
	{
	public:

		friend BaseObject<CharaType>;

	public://Constructor Destructor//

		ObjectList() {}

		virtual ~ObjectList() { Release(); }

	public://Init And Release//

		virtual void Release() { ClearObject(); }

	public://Set Function//

#ifdef CRT

		//オブジェクトを登録する//
		//BaseObjectを継承したオブジェクトのみ登録可能//
		template<class T = BaseObject<CharaType>>
		typename std::enable_if
			<std::is_base_of<BaseObject<CharaType>, T>::value || 
			std::is_same<BaseObject<CharaType>, T>::value, ChPtr::Shared<T>>::type
			SetObject(const std::basic_string<CharaType>& _objectName)
		{
			ChPtr::Shared<BaseObject<CharaType>> tmpObj = ChPtr::Make_S<T>();
			tmpObj->SetObjectList(this);
			tmpObj->SetMyName(_objectName);
			tmpObj->Init();
			objectList.push_back(tmpObj);
			return ChPtr::SharedSafeCast<T>(tmpObj);
		}
		
		void SetObject(ChPtr::Shared<BaseObject<CharaType>> _obj);

#endif

	public://Get Functions//

#ifdef CRT

		template<class T = BaseObject<CharaType>>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject<CharaType>, T>::value, T>::type>>
			GetObjectList()
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (auto&& obj : objectList)
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

		template<class T = BaseObject<CharaType>>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject<CharaType>, T>::value, T>::type>>
			GetObjectListForName(const std::string& _name)
		{
			std::vector<ChPtr::Weak<BaseObject<CharaType>>>tmpObjList;

			for (auto&& obj : objectList)
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

		inline unsigned long GetObjectCount(){ return objectList.size(); }
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
		void ClearObjectForName(const std::basic_string<CharaType>& _name);

#endif

		//削除されるオブジェクトを確認して削除する//
		void DestroyObjectTest();

	protected:

#ifdef CRT

		std::vector<ChPtr::Shared<BaseObject<CharaType>>>objectList;

#endif

	};

}

#ifdef CRT

template<typename CharaType>
void ChCpp::ObjectList<CharaType>::SetObject(ChPtr::Shared<BaseObject<CharaType>> _obj)
{
	if (_obj == nullptr)return;

	if (!objectList.empty())
	{
		if (std::find(objectList.begin(), objectList.end(), _obj) != objectList.end())return;
	}

	_obj->WithdrawObjectList();
	_obj->SetObjList(this);
	objectList.push_back(_obj);

	for (auto&& child : _obj->childList) { SetObject(child); }
}

CH_OBJECT_LIST_FUNCTION(UpdateBegin);

template<typename CharaType>
void ChCpp::ObjectList<CharaType>::ObjectUpdate()
{
	auto&& obj = objectList.begin();

	while (obj != objectList.end())
	{
		if ((*obj)->IsDethFlg())
		{
			(*obj)->BaseRelease();
			obj = objectList.erase(obj);
			if (objectList.empty())break;
			continue;
		}

		if ((*obj)->IsUseFlg())
		{
			if ((*obj)->GetParent().expired())
			{
				(*obj)->UpdateFunction();
				if (objectList.empty())break;
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

template<typename CharaType>
void ChCpp::ObjectList<CharaType>::ClearObject()
{
	for (auto&& obj : objectList)
	{
		if (obj->GetParent().lock())continue;
		obj->BaseRelease();
	}
	if (!objectList.empty())objectList.clear();
}

template<typename CharaType>
void ChCpp::ObjectList<CharaType>::ClearObjectForName(const std::basic_string<CharaType>& _Name)
{
	for (auto&& obj : objectList)
	{
		if (obj->myName.find(_Name, 0) == std::basic_string<CharaType>::npos)continue;
		obj->Destroy();
	}
}

template<typename CharaType>
void ChCpp::ObjectList<CharaType>::DestroyObjectTest()
{
	auto&& obj = objectList.begin();

	while (obj != objectList.end())
	{
		if (!(*obj)->dFlg)
		{
			obj++;
			continue;
		}
		(*obj)->BaseRelease();
		obj = objectList.erase(obj);
	}
}

template<typename CharaType>
ChCpp::ObjectList<CharaType>* ChCpp::BaseObject<CharaType>::LookObjectList() { return objMaList; }

#endif


#endif