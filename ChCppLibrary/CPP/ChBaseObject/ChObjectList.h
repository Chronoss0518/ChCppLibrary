
#ifndef Ch_CPP_ObjList_h
#define Ch_CPP_ObjList_h

#include"../ChBitBool/ChBitBool.h"

#include"ChBaseObject.h"

namespace ChCpp
{



	class ObjectList
	{
	public:

		friend BaseObject;

		///////////////////////////////////////////////////////////////////////////////////////
		//CostructerDestructer//

		ObjectList() {}

		virtual ~ObjectList()
		{
			Release();
		}


		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual void Release();

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//オブジェクトを登録する//
		//BaseObjectを継承したオブジェクトのみ登録可能//
		template<class T>
		auto SetObject(const std::string& _objectName) ->typename std::enable_if
			<std::is_base_of<BaseObject, T>::value, ChPtr::Shared<T>>::type
		{

			ChPtr::Shared<BaseObject> tmpObj = ChPtr::Make_S<T>();

			tmpObj->BaseInit(_objectName, this);

			tmpObj->Init();

			objectList.push_back(tmpObj);

			return ChPtr::SharedSafeCast<T>(tmpObj);
		}
		
		void SetObject(ChPtr::Shared<BaseObject> _obj);

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		template<class T = BaseObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject, T>::value, T>::type>>
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

		template<class T = BaseObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject, T>::value, T>::type>>
			GetObjectListForName(const std::string& _name)
		{
			std::vector<ChPtr::Weak<BaseObject>>tmpObjList;

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

		///////////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		//登録されているオブジェクトを更新する//
		void Update();

		//Updateを区分けしたもの//
		void ObjectUpdateBegin();

		void ObjectUpdate();

		void ObjectUpdateEnd();

		///////////////////////////////////////////////////////////////////////////////////////

		//登録されているオブジェクトを移動させる//
		void Move();

		//Moveを区分けしたもの//
		void ObjectMoveBegin();

		void ObjectMove();

		void ObjectMoveEnd();

		///////////////////////////////////////////////////////////////////////////////////////

		//登録されているオブジェクトを描画する。
		void Draw();

		//Drawをくわけしたもの//
		void ObjectDrawBegin();

		void ObjectDraw2D();

		void ObjectDraw3D();

		void ObjectDrawEnd();

		///////////////////////////////////////////////////////////////////////////////////////

		//保持しているすべてのオブジェクトを削除する。
		void ClearObject();

		//選択された名前のオブジェクトをすべて消去する//
		void ClearObjectForName(const std::string& _name);

		//削除されるオブジェクトを確認して削除する//
		void DestroyObjectTest();

		///////////////////////////////////////////////////////////////////////////////////////
		
	protected:

		std::vector<ChPtr::Shared<BaseObject>>objectList;

	};

}


#endif