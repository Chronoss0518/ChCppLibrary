
#ifndef Ch_CPP_ObjList_h
#define Ch_CPP_ObjList_h

#include<vector>
#include<string>

#include"../../BasePack/ChPtr.h"

#include"ChBaseObject.h"

namespace ChCpp
{
	class BasicObject;

	class ObjectList
	{
	public:

		friend BasicObject;

	public://Init And Release//

		virtual void Release() { ClearObject(); }

	public://Set Function//

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
			objectList.push_back(res);
			return ChPtr::SharedSafeCast<T>(res);
		}

		void SetObject(ChPtr::Shared<BasicObject> _obj);

	public://Get Functions//

		template<class T = BasicObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BasicObject, T>::value, T>::type>>
			GetObjectList()
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (size_t i = 0; i < objectList.size(); i++)
			{
				if (objectList[i]->GetParent() != nullptr)continue;
				auto&& test = ChPtr::SharedSafeCast<T>(objectList[i]);
				if (test == nullptr)continue;
				tmpObjList.push_back(test);
				for (auto&& childObj : objectList[i]->GetChildlen<T>())
				{
					tmpObjList.push_back(childObj);
				}
			}

			return tmpObjList;
		}

		inline size_t GetObjectCount() { return objectList.size(); }

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

		//選択された名前のオブジェクトをすべて消去する//
		template<typename CharaType>
		void ClearObjectForName(const std::basic_string<CharaType>& _name);

		//削除されるオブジェクトを確認して削除する//
		void DestroyObjectTest();

	protected:

		std::vector<ChPtr::Shared<BasicObject>>objectList;

	};

}

#endif