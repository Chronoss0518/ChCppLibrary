
#ifndef Ch_CPP_BaObj_h
#define Ch_CPP_BaObj_h

#include<memory>
#include<vector>
#include<string>

#include"../../BasePack/ChPtr.h"

#include"ChBaseComponent.h"


namespace ChCpp
{
	class ObjectList;

	//オブジェクトを生成する場合、このクラスを継承して作成する。//
	class BasicObject :public std::enable_shared_from_this<BasicObject>
	{
	public:

		friend ObjectList;

		friend BaseComponent;

	protected:

		//Release時に走る関数//
		virtual void BaseRelease();

	public://Initialize Deserialize//

		//Set時に自動的に走る関数//
		virtual void Init() {}

		//自身を捨てる時に自動的に走る関数//
		virtual void Release() {}

	public://Destroy Function//

		//自身を捨てたい時に走らせる関数//
		virtual void Destroy();

	public://Destroy Functions//

		//自身が持つ子を削除する//
		virtual void DestroyToChild();

		//自身が持つ子を削除する//
		void DestroyToChild(ChPtr::Shared<BasicObject>& _child)
		{
			auto&& child = std::find(childList.begin(), childList.end(), _child);
			if (child == childList.end())return;
			childList.erase(child);
			_child->BaseRelease();

		}

		//コンポーネントをすべて削除する//
		void DestroyComponent();

		//削除される子オブジェクトが存在するかを確認しつつ削除する//
		virtual void DestroyToChildTest();

		//削除されるコンポーネントがあるかどうかを確認しつつ削除する//
		void DestroyComponentTest();

	public:

		//コンポーネントのセット//
		template<class T>
		typename std::enable_if
			<std::is_base_of<BaseComponent, T>::value, const ChPtr::Shared<T>>::type
			SetComponent()
		{
			ChPtr::Shared<BaseComponent> tmpCom = ChPtr::Make_S<T>();

			if (tmpCom == nullptr)return nullptr;

			comList.push_back(tmpCom);

			tmpCom->BaseInit(this);

			return ChPtr::SharedSafeCast<T>(tmpCom);
		}

		//子オブジェクトのセット//
		void SetComponent(ChPtr::Shared<BaseComponent> _com);

		//子オブジェクトのセット//
		void SetChild(ChPtr::Shared<BasicObject> _childObject);

		//現在調整中//
		inline void SetParent(ChPtr::Shared<BasicObject> _parentObject)
		{
			if (this == _parentObject.get())return;

			WithdrawParent();

			parent = _parentObject;

			_parentObject->SetChild(shared_from_this());
		}

		//使用フラグ//
		void SetUseFlg(const bool& _flg) { useFlg = _flg; }

	private://Set Functions//

		void SetObjectList(ObjectList* _objMa) { objMaList = _objMa; }

	public://Get Functions//

		//コンポーネントの取得//
		template<class T = BaseComponent>
		typename std::enable_if<
			std::is_base_of<BaseComponent, T>::value,
			ChPtr::Shared<T>>::type
			GetComponent()
		{
			for (size_t i = 0; i < comList.size(); i++)
			{
				if (comList[i]->dFlg)continue;
				auto testCom = ChPtr::SharedSafeCast<T>(comList[i]);
				if (testCom != nullptr) return testCom;
			}
			return nullptr;
		}

		//コンポーネントリストの取得//
		template<typename T = BaseComponent>
		typename std::enable_if<
			std::is_base_of<BaseComponent, T>::value,
			std::vector<ChPtr::Shared<T>>>::type
			GetComponents()
		{
			std::vector<ChPtr::Shared<T>>tmpComList;

			for (size_t i = 0; i < comList.size(); i++)
			{
				if (comList[i]->dFlg)continue;
				auto test = ChPtr::SharedSafeCast<T>(comList[i]);
				if (test == nullptr)continue;
				tmpComList.push_back(test);
			}
			return tmpComList;
		}

		//子オブジェクト群の取得//
		template<class T = BasicObject>
		typename std::enable_if<
			std::is_base_of<BasicObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetChildlen()
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (size_t i = 0; i < childList.size(); i++)
			{
				auto test = ChPtr::SharedSafeCast<T>(childList[i]);
				if (test == nullptr)continue;
				tmpObjList.push_back(test);
			}

			return tmpObjList;
		}

		inline std::vector<ChPtr::Shared<BasicObject>> GetAllChildlen()
		{
			std::vector<ChPtr::Shared<BasicObject>>res = childList;

			for (size_t i = 0; i < childList.size(); i++)
			{
				auto&& childObjChildList = childList[i]->GetAllChildlen();
				for (size_t j = 0; j < childObjChildList.size(); j++)
				{
					res.push_back(childObjChildList[j]);
				}
			}

			return res;
		}


		//子オブジェクト群の取得//
		template<class T = BasicObject>
		typename std::enable_if<
			std::is_base_of<BasicObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetAllChildlen()
		{
			std::vector<ChPtr::Weak<T>>res;

			for (size_t i = 0; i < childList.size(); i++)
			{
				auto&& test = ChPtr::SharedSafeCast<T>(childList[i]);
				if (test != nullptr)res.push_back(test);
				auto&& childInchildList = childList[i]->GetAllChildlen<T>();
				for (size_t i = 0; i < childInchildList.size(); i++) { res.push_back(childInchildList[i]); }
			}
			return res;
		}

		//親の取得//
		ChPtr::Shared<BasicObject> GetParent() { return parent.lock(); }

	protected://Get Functions//

		std::vector<ChPtr::Shared<BasicObject>>& GetChildlen() { return childList; }

	protected:

		ObjectList* LookObjectList();

	private:

		void WithdrawObjectList();

	public://Is Functions//

		//使用可否の確認//
		bool IsUseFlg() { return useFlg; }

		bool IsDethFlg() { return dFlg; }

	public://Life Cycle Base//

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

	protected://Life Cycle Base//

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

	public:

		void WithdrawParent();

	private:

		bool dFlg = false;

		bool useFlg = true;

		ObjectList* objMaList = nullptr;

		std::vector<ChPtr::Shared<BasicObject>>childList;
		ChPtr::Weak<BasicObject> parent;
		std::vector<ChPtr::Shared<BaseComponent>>comList;
	};

	template<typename CharaType>
	class BaseObject : public BasicObject
	{
	public:

		//自身の名前のセット//
		void SetMyName(const std::basic_string<CharaType>& _newName) { myName = _newName; }

	public:

		//子オブジェクト群の取得//
		template<class T = BaseObject>
		typename std::enable_if<
			std::is_base_of<BaseObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetChildlenForName(const std::basic_string<CharaType>& _name)
		{
			std::vector<ChPtr::Weak<T>>res;
			GetChildlenForName(res, _name);
			return res;
		}

		//子オブジェクト群の取得//
		template<class T = BaseObject>
		typename std::enable_if<
			std::is_base_of<BaseObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetChildlenConstainsName(const std::basic_string<CharaType>& _name)
		{
			std::vector<ChPtr::Weak<T>>res;
			GetChildlenConstainsName(res, _name);
			return res;
		}

		//子オブジェクト群の取得//
		template<class T = BaseObject>
		typename std::enable_if<
			std::is_base_of<BaseObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetAllChildlenForName(const std::basic_string<CharaType>& _name)
		{
			std::vector<ChPtr::Weak<T>>res;
			GetAllChildlenForName(res, _name);
			return res;
		}

		//子オブジェクト群の取得//
		template<class T = BaseObject>
		typename std::enable_if<
			std::is_base_of<BaseObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetAllChildlenConstainsName(const std::basic_string<CharaType>& _name)
		{
			std::vector<ChPtr::Weak<T>>res;
			GetAllChildlenConstainsName(res, _name);
			return res;
		}

	private:

		//子オブジェクト群の取得//
		template<class T = BaseObject>
		void GetChildlenForName(std::vector<ChPtr::Weak<T>>& _result ,const std::basic_string<CharaType>& _name)
		{
			for (auto&& obj : GetChildlen())
			{
				auto&& baseObj = ChPtr::SharedSafeCast<BaseObject>(obj);
				if (baseObj == nullptr)continue;
				if (baseObj->GetMyName() != _name)continue;

				auto test = ChPtr::SharedSafeCast<T>(baseObj);
				if (test == nullptr)continue;
				_result.push_back(test);
			}
		}

		//子オブジェクト群の取得//
		template<class T = BaseObject>
		void GetChildlenConstainsName(std::vector<ChPtr::Weak<T>>& _result,const std::basic_string<CharaType>& _name)
		{
			for (auto&& obj : GetAllChildlen())
			{
				auto&& baseObj = ChPtr::SharedSafeCast<BaseObject>(obj);
				if (baseObj == nullptr)continue;
				if (baseObj->GetMyName().find(_name) == std::basic_string<CharaType>::npos)continue;

				auto test = ChPtr::SharedSafeCast<T>(baseObj);
				if (test == nullptr)continue;
				_result.push_back(test);
			}
		}

		//子オブジェクト群の取得//
		template<class T = BaseObject>
		void GetAllChildlenForName(std::vector<ChPtr::Weak<T>>& _result,const std::basic_string<CharaType>& _name)
		{
			for (auto&& obj : GetAllChildlen())
			{
				auto&& baseObj = ChPtr::SharedSafeCast<BaseObject>(obj);
				if (baseObj == nullptr)continue;
				if (baseObj->GetMyName() != _name)continue;
				auto test = ChPtr::SharedSafeCast<T>(baseObj);
				if (test != nullptr) { _result.push_back(test); }
				baseObj->GetAllChildlenForName(_result, _name);
			}
		}

		//子オブジェクト群の取得//
		template<class T = BaseObject>

		void GetAllChildlenConstainsName(std::vector<ChPtr::Weak<T>>& _result,const std::basic_string<CharaType>& _name)
		{
			for (auto&& obj : GetChildlen())
			{
				auto&& baseObj = ChPtr::SharedSafeCast<BaseObject>(obj);
				if (baseObj == nullptr)continue;
				if (baseObj->GetMyName().find(_name) != std::basic_string<CharaType>::npos)
				{
					auto test = ChPtr::SharedSafeCast<T>(baseObj);
					if (test != nullptr) { _result.push_back(test); }
				}
				baseObj->GetAllChildlenConstainsName(_result, _name);
			}
		}


	public:

		std::basic_string<CharaType> GetMyName() { return myName; }

	private:

		std::basic_string<CharaType> myName;
	};
}

#endif