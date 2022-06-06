
#ifndef Ch_CPP_BaObj_h
#define Ch_CPP_BaObj_h

#include"../ChBitBool/ChBitBool.h"

#include"ChBaseComponent.h"

namespace ChCpp
{
	class ObjectManager;
	class ObjectList;

	//オブジェクトを生成する場合、このクラスを継承して作成する。//
	class BaseObject :public std::enable_shared_from_this<BaseObject>,public ChCp::Releaser
	{
	public:

		friend BaseComponent;
		friend ObjectList;

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//Set時に自動的に走る関数//
		virtual void Init() {}

		//自身を捨てる時に自動的に走る関数//
		void Release() {}

	protected:

		//自身を捨てたい時に走らせる関数//
		void Destroy();

		//自身が持つ子を削除する//
		void DestroyToChild();

		//自身が持つ子を削除する//
		void DestroyToChild(const ChPtr::Shared<BaseObject>& _child);

		//削除される子オブジェクトが存在するかを確認しつつ削除する//
		void IsDestroyToChild();

		//コンポーネントをすべて削除する//
		void DestroyComponent();

		//指定したコンポーネントをすべて削除する//
		void DestroyComponent(const std::string& _comName);

		//削除されるコンポーネントがあるかどうかを確認しつつ削除する//
		void IsDestroyComponent();

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		BaseObject() {};

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		std::string GetMyName() { return myName; }

		//コンポーネントの取得//
		template<class T = BaseComponent>
		inline auto GetComponent()->typename std::enable_if
			<std::is_base_of<BaseComponent, T>::value, ChPtr::Shared<T>>::type
		{
			for (auto&& com : comList)
			{
				if (ChPtr::SharedSafeCast<T, BaseComponent>(com) != nullptr)
				{
					if (com->dFlg)continue;
					if (!com->useFlg)continue;
					return ChPtr::SharedSafeCast<T, BaseComponent>(com);
				}
			}
			return nullptr;
		}

		//コンポーネントリストの取得//
		template<typename T = BaseComponent>
		inline auto GetComponents()->typename std::enable_if
			<std::is_base_of<BaseComponent, T>::value, std::vector<ChPtr::Shared<T>>&>::type
		{
			std::vector<ChPtr::Shared<T>>tmpComList;
			for (auto&& com : comList)
			{
				if (ChPtr::SharedSafeCast<T>(com) == nullptr)continue;
				if (com->DFlg)continue;
				if (!com->UseFlg)continue;
				tmpComList.push_back(com);
			}
			return tmpComList;
		}

		//子オブジェクト群の取得//
		template<class T = BaseObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject, T>::value, T>::type>> 
			GetChildlen()
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (auto&& obj : childList)
			{
				auto&& test = ChPtr::SharedSafeCast<T>(obj);
				if (test == nullptr)continue;
				tmpObjList.push_back(test);
			}

			return tmpObjList;
		}

		//子オブジェクト群の取得//
		template<class T = BaseObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject, T>::value, T>::type>>
			GetChildlenForName(const std::string& _name)
		{
			std::vector<ChPtr::Weak<BaseObject>>tmpObjList;

			for (auto&& obj : childList)
			{
				auto&& test = ChPtr::SharedSafeCast<T>(obj);
				if (test == nullptr)continue;
				if (test->GetMyName() != _name)continue;
				tmpObjList.push_back(test);
			}

			return tmpObjList;
		}

		//親の取得//
		ChPtr::Weak<BaseObject>GetParent()
		{
			return parent;
		}


		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//コンポーネントのセット//
		template<class T>
		inline auto SetComponent()->typename std::enable_if
			<std::is_base_of<BaseComponent, T>::value, const ChPtr::Shared<T>>::type
		{

			ChPtr::Shared<BaseComponent> tmpCom = ChPtr::Make_S<T>();

			if (tmpCom == nullptr)return nullptr;

			comList.push_back(tmpCom);

			tmpCom->BaseInit(shared_from_this());

			return ChPtr::SharedSafeCast<T>(tmpCom);

		}

		//子オブジェクトのセット//
		inline void SetChild(ChPtr::Shared<BaseObject> _childObject)
		{
			childList.push_back(_childObject);

			auto&& par = _childObject->parent.lock();

			if (par != nullptr)
			{
				auto&& obj =  std::find(par->childList.begin(), par->childList.end(), _childObject);
				if(obj != par->childList.end())	par->childList.erase(obj);
			}

			_childObject->parent = shared_from_this();

		}

		//自身の名前のセット//
		inline void SetMyName(const std::string& _newName) { myName = _newName; }

		//使用フラグ//
		inline void SetUseFlg(const ChStd::Bool& _flg) { useFlg = _flg; }

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//使用可否の確認//
		inline ChStd::Bool IsUseFlg() { return useFlg; }

		///////////////////////////////////////////////////////////////////////////////////////

		ObjectList* LookObjectList();

		///////////////////////////////////////////////////////////////////////////////////////
		//UsingFunctionToManagers//

		void UpdateBeginFunction();
		void UpdateFunction();
		void UpdateEndFunction();

		void MoveBeginFunction();
		void MoveFunction();
		void MoveEndFunction();

		void DrawBeginFunction();
		void Draw3DFunction();
		void Draw2DFunction();
		void DrawEndFunction();

		//オブジェクト自身の機能//
		virtual void Function() {}

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFuncsions//
		virtual void UpdateBegin() {};
		virtual void Update() {};
		virtual void UpdateEnd() {};

		//MoveFuncsions//
		virtual void MoveBegin() {};
		virtual void Move() {};
		virtual void MoveEnd() {};

		//DrawFuncsions//
		virtual void DrawBegin() {}
		virtual void Draw3D() {}
		virtual void Draw2D() {}
		virtual void DrawEnd() {}


	private:

		//Release時に走る関数//
		void BaseRelease();

		//Set時に走る関数//
		void BaseInit(
			const std::string& _objectName
			, ObjectList* _objMa);

		///////////////////////////////////////////////////////////////////////////////////

		std::vector<ChPtr::Shared<BaseObject>>childList;
		ChPtr::Weak<BaseObject>parent;

		std::vector<ChPtr::Shared<BaseComponent>>comList;

		ObjectList* objMaList = nullptr;
		std::string myName;
		ChStd::Bool dFlg = false;

		ChStd::Bool useFlg = true;

	};

}

#endif