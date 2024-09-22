
#ifndef Ch_CPP_ObjList_h
#define Ch_CPP_ObjList_h

#include"../../CRTPack/ChSmartPtrPack/ChSmartPtrPack.h"
#include"../../CRTPack/ChVectorPack/ChVectorPack.h"
#include"../../CRTPack/ChStringPack/ChStringPack.h"

#include"../../BasePack/ChPtr.h"

#include"ChBaseObject.h"

namespace ChCpp
{
	class BasicObject;

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
			SetObject()
		{
			ChPtr::Shared<ChCpp::BasicObject> res = ChPtr::Make_S<T>();
			res->SetObjectList(this);
			res->Init();
			objectList.Push(res);
			return ChPtr::SharedSafeCast<T>(res);
		}

		void SetObject(ChPtr::Shared<BasicObject> _obj)
		{
			SetObjectCRT(_obj);
		}

#endif

		void SetObjectCRT(ChCRT::SharedPtrPack<BasicObject> _obj);

	public://Get Functions//

#ifdef CRT

		template<class T = BasicObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BasicObject, T>::value, T>::type>>
			GetObjectList()
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (size_t i = 0; i < objectList.GetSize(); i++)
			{
				if (ChPtr::NotNullCheck(objectList[i]->GetParent()))continue;
				auto&& test = ChPtr::SharedSafeCast<T>(objectList[i]);
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

			for (size_t i = 0; i < objectList.GetSize(); i++)
			{
				if (ChPtr::NotNullCheck(objectList[i]->GetParent()))continue;
				auto&& test = ChPtr::SharedSafeCast<T>(objectList[i]);
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

#endif

		inline size_t GetObjectCount() { return objectList.GetSize(); }

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


	private:

		template<typename CharaType>
		void ClearObjectForNameBase(const ChCRT::StringPack<CharaType>& _name);

	protected:

		ChCRT::VectorPack<ChCRT::SharedPtrPack<BasicObject>>objectList;

	};

}

#ifdef CRT

#endif

#include"SharedFunctions/ChObjectSharedObjectList.h"

#endif