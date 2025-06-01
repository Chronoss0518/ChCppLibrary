
#ifndef Ch_CPP_ObjMa_h
#define Ch_CPP_ObjMa_h

#include<string>
#include<map>

#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChPtr.h"

#include"ChObjectList.h"

namespace ChCpp
{
	template<typename CharaType>
	class ObjectManager
	{
	public:

		virtual void Release();

	public://Set Functions//

		//オブジェクトを登録する//
		//BaseObjectを継承したオブジェクトのみ登録可能//
		template<class T = BaseObject<CharaType>>
		typename std::enable_if<std::is_base_of<BaseObject<CharaType>, T>::value ||
			std::is_same<BaseObject<CharaType>, T>::value, ChPtr::Shared<T>>::type
			SetObject(const std::basic_string<CharaType>& _tag = ChStd::GetZeroChara<CharaType>())
		{

			auto&& list = objectList.find(_tag);
			if (list == objectList.end())
			{
				objectList[_tag] = ChPtr::Make_S<ObjectList>();
				list = objectList.find(_tag);
			}

			return (*list).second->template SetObject<T>();
		}

		void SetObject(ChPtr::Shared<BaseObject<CharaType>> _obj, const std::basic_string<CharaType>& _tag = ChStd::GetZeroChara<CharaType>());

	public://Get Functions//

		template<class T = BaseObject<CharaType>>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject<CharaType>, T>::value, T>::type>>
			GetObjectList()
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (auto&& objlist : objectList)
			{
				for (auto&& outObj : objlist.second->template GetObjectList<T>())
				{
					tmpObjList.push_back(outObj);
				}
			}

			return tmpObjList;
		}

		template<class T = BaseObject<CharaType>>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject<CharaType>, T>::value, T>::type>>
			GetObjectListForName(const std::basic_string<CharaType>& _name)
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (auto&& objlist : objectList)
			{
				for (auto&& outObj : objlist.second->template GetObjectListForName<T>(_name))
				{
					tmpObjList.push_back(outObj);
				}
			}

			return tmpObjList;
		}

		template<class T = BaseObject<CharaType>>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject<CharaType>, T>::value, T>::type>>
			GetObjectListForTag(const std::basic_string<CharaType>& _tag = ChStd::GetZeroChara<CharaType>())
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			auto&& it = objectList.find(_tag);

			if (it == objectList.end())return tmpObjList;

			for (auto&& outObj : (*it).second->template GetObjectList<T>())
			{
				tmpObjList.push_back(outObj);
			}

			return tmpObjList;
		}

		template<class T = BaseObject<CharaType>>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject<CharaType>, T>::value, T>::type>>
			GetObjectListForNameAndTag(const std::basic_string<CharaType>& _name, const std::basic_string<CharaType>& _tag = "")
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			auto&& it = objectList.find(_tag);

			if (it == objectList.end())return tmpObjList;

			for (auto&& outObj : (*it).second->template GetObjectListForName<T>(_name))
			{
				tmpObjList.push_back(outObj);
			}

			return tmpObjList;
		}

		std::vector<std::basic_string<CharaType>> GetTagList();

		unsigned long GetObjectCount();

		unsigned long GetTagCount();

	public://Life Cycle Functions//

		//登録されているオブジェクトを更新する//
		void Update();

		//Updateを区分けしたもの//
		void ObjectUpdateBegin();

		void ObjectUpdate();

		void ObjectUpdateEnd();

		void Update(const std::basic_string<CharaType>& _tag);

		void ObjectUpdateBegin(const std::basic_string<CharaType>& _tag);

		void ObjectUpdate(const std::basic_string<CharaType>& _tag);

		void ObjectUpdateEnd(const std::basic_string<CharaType>& _tag);

		//登録されているオブジェクトを移動させる//
		void Move();

		//Moveを区分けしたもの//
		void ObjectMoveBegin();

		void ObjectMove();

		void ObjectMoveEnd();

		void Move(const std::basic_string<CharaType>& _tag);

		void ObjectMoveBegin(const std::basic_string<CharaType>& _tag);

		void ObjectMove(const std::basic_string<CharaType>& _tag);

		void ObjectMoveEnd(const std::basic_string<CharaType>& _tag);

		//登録されているオブジェクトを描画する。
		void Draw();

		//Drawをくわけしたもの//
		void ObjectDrawBegin();

		void ObjectDraw2D();

		void ObjectDraw3D();

		void ObjectDrawEnd();

		void Draw(const std::basic_string<CharaType>& _tag);

		void ObjectDrawBegin(const std::basic_string<CharaType>& _tag);

		void ObjectDraw2D(const std::basic_string<CharaType>& _tag);

		void ObjectDraw3D(const std::basic_string<CharaType>& _tag);

		void ObjectDrawEnd(const std::basic_string<CharaType>& _tag);

	public:
	
		//保持しているすべてのオブジェクトを削除する。
		void ClearObject();

		//選択された名前のオブジェクトをすべて消去する//
		void ClearObjectForName(const std::basic_string<CharaType>& _name);

		//選択された名前のオブジェクトをすべて消去する//
		void ClearObjectForTag(const std::basic_string<CharaType>& _tag);

		//選択された名前のオブジェクトをすべて消去する//
		void ClearObjectForNameAndTag(const std::basic_string<CharaType>& _name, const std::basic_string<CharaType>& _tag);

	private://Member Value//

		std::map<std::basic_string<CharaType>, ChPtr::Shared<ObjectList>>objectList;

	private:

		ObjectManager() {}
		virtual ~ObjectManager() { Release(); }

	public:

		static ObjectManager<CharaType>& GetIns()
		{
			static ObjectManager<CharaType> Ins;
			return Ins;
		}

	};

	template<typename CharaType>
	static ObjectManager<CharaType>& ObjManager() { return ObjectManager<CharaType>::GetIns(); };

}

#endif