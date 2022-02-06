
#ifndef Ch_CPP_ObjList_h
#define Ch_CPP_ObjList_h

#include"../ChBitBool/ChBitBool.h"

#include"ChBaseObject.h"

namespace ChCpp
{



	class ObjectList :public ChCp::Releaser
	{
	public:

		friend BaseObject;

		///////////////////////////////////////////////////////////////////////////////////////
		//CostructerDestructer//

		ObjectList() {}
		~ObjectList() {}

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//オブジェクトを登録する//
		//BaseObjectを継承したオブジェクトのみ登録可能//
		template<class T>
		auto SetObject(const std::string& _objectName, const std::string& _tag) ->typename std::enable_if
			<std::is_base_of<BaseObject, T>::value, ChPtr::Shared<T>>::type
		{

			ChPtr::Shared<BaseObject> tmpObj = ChPtr::Make_S<T>();

			tmpObj->BaseInit(_objectName, _tag, this);

			tmpObj->Init();

			objectList[_tag].push_back(tmpObj);

			return ChPtr::SharedSafeCast<T>(tmpObj);
		}
		
		//BaseObjectを継承したオブジェクトのみ登録可能//
		template<class T>
		auto SetObject(ChPtr::Shared<T> _obj) ->typename std::enable_if
			<std::is_base_of<BaseObject, T>::value, ChPtr::Shared<T>>::type
		{

			ChPtr::Shared<BaseObject> tmpObj = _obj;

			if (objectList.find(tmpObj->GetTag()) != objectList.end())
			{
				if (std::find(objectList[tmpObj->GetTag()].begin(), objectList[tmpObj->GetTag()].end(), tmpObj))return;
			}

			tmpObj->objMa = this;

			objectList[tmpObj->GetTag()].push_back(tmpObj);

			for (auto&& child : tmpObj->childList)
			{
				SetObject(child);
			}

			return ChPtr::SharedSafeCast<T>(tmpObj);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		std::vector<ChPtr::Weak<BaseObject>> GetObjectList();

		std::vector<ChPtr::Weak<BaseObject>> GetObjectListForTag(const std::string& _tagName);

		std::vector<ChPtr::Weak<BaseObject>> GetObjectListForName(const std::string& _name);

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

		//選択されたタグのオブジェクトをすべて消去する//
		void ClearObjectForTag(const std::string& _tags);

		//選択された名前のオブジェクトをすべて消去する//
		void ClearObjectForName(const std::string& _name);

		//選択されたタグと関連する名前のオブジェクトをすべて消去する//
		void ClearObjectForTagAndName(
			const std::string& _name,
			const std::string& _tags);

		///////////////////////////////////////////////////////////////////////////////////////
		
	protected:

		std::map<std::string, std::vector<ChPtr::Shared<BaseObject>>>objectList;


	};

}


#endif