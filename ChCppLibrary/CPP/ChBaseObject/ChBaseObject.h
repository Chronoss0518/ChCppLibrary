
#ifndef Ch_CPP_BaObj_h
#define Ch_CPP_BaObj_h

#ifdef CRT
#include<memory>
#include<vector>
#include<string>
#endif

#include"../../BasePack/ChPtr.h"

#include"ChBaseComponent.h"

#ifndef CH_OBJECT_FUNCTION
#define CH_OBJECT_FUNCTION(_FunctionNameBase) \
void ChCpp::BasicObject::##_FunctionNameBase##Function()\
{\
	##_FunctionNameBase##();\
	for (auto com : value->comList)\
	{\
		if (!com->useFlg)continue;\
		com->##_FunctionNameBase##();\
		if (value->comList.empty())break;}\
	for (auto&& child : value->childList)\
	{\
		if (child->useFlg)continue;\
		child->##_FunctionNameBase##Function();\
		if (value->childList.empty())break;}\
}
#endif

namespace ChCpp
{
	//オブジェクトを生成する場合、このクラスを継承して作成する。//
	class BasicObject 
#ifdef CRT
		: public std::enable_shared_from_this<BasicObject>
#endif
	{
	protected:

		BasicObject();

		virtual ~BasicObject();

	public:

#ifdef CRT
		template<class T>
		static typename std::enable_if<
			std::is_base_of<BasicObject, T>::value || std::is_same<BasicObject, T>::value,ChPtr::Shared<T>>::type
			CreateObject()
		{
			ChPtr::Shared<BasicObject>res = nullptr;
			res.reset(new T());
			return res;
		}
#endif

	public:

		virtual ~BasicObject() { Release(); }

	public:

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

#ifdef CRT

		//自身が持つ子を削除する//
		virtual void DestroyToChild(const ChPtr::Shared<BasicObject>& _child);

#endif

		//コンポーネントをすべて削除する//
		void DestroyComponent();

		//指定したコンポーネントをすべて削除する//
		void DestroyComponent(const char* _comName);

		//削除される子オブジェクトが存在するかを確認しつつ削除する//
		virtual void DestroyToChildTest();

		//削除されるコンポーネントがあるかどうかを確認しつつ削除する//
		void DestroyComponentTest();

	public:

#ifdef CRT

		//コンポーネントのセット//
		template<class T>
		typename std::enable_if
			<std::is_base_of<BaseComponent, T>::value, const ChPtr::Shared<T>>::type 
			SetComponent()
		{
			ChPtr::Shared<BaseComponent> tmpCom = ChPtr::Make_S<T>();

			if (tmpCom == nullptr)return nullptr;

			value->comList.push_back(tmpCom);

			tmpCom->BaseInit(this);

			return ChPtr::SharedSafeCast<T>(tmpCom);
		}

		void SetComponent(ChPtr::Shared<BaseComponent> _component);

		//子オブジェクトのセット//
		void SetChild(ChPtr::Shared<BasicObject> _childObject);

		void SetParent(ChPtr::Shared<BasicObject> _parentObject);

#endif

		//使用フラグ//
		void SetUseFlg(const bool& _flg) { useFlg = _flg; }

	public://Get Functions//

#ifdef CRT

		//コンポーネントの取得//
		template<class T = BaseComponent>
		typename std::enable_if<
			std::is_base_of<BaseComponent, T>::value,
			ChPtr::Shared<T>>::type
			GetComponent()
		{
			for (auto&& com : value->comList)
			{
				if (com->dFlg)continue;
				auto testCom = ChPtr::SharedSafeCast<T>(com);
				if (testCom != nullptr) { return testCom; }
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
			for (auto&& com : value->comList)
			{
				if (com->dFlg)continue;

				auto test = ChPtr::SharedSafeCast<T>(com);
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

			for (auto&& obj : value->childList)
			{
				auto test = ChPtr::SharedSafeCast<T>(obj);
				if (test == nullptr)continue;
				tmpObjList.push_back(test);
			}

			return tmpObjList;
		}

		std::vector<ChPtr::Shared<BasicObject>> GetAllChildlen();

		//子オブジェクト群の取得//
		template<class T = BasicObject>
		typename std::enable_if<
			std::is_base_of<BasicObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetAllChildlen()
		{
			std::vector<ChPtr::Weak<T>>res;

			for (auto&& obj : value->childList)
			{
				auto test = ChPtr::SharedSafeCast<T>(obj);

				if (test != nullptr) { res.push_back(test); }

				for (auto&& childObj : obj->GetAllChildlen<T>()) { res.push_back(childObj); }
			}
			return res;
		}

		//親の取得//
		ChPtr::Weak<BasicObject>GetParent() { return value->parent; }

#endif

protected://Get Functions//

#ifdef CRT

		std::vector<ChPtr::Shared<BasicObject>>& GetChildlen() { return value->childList; }

#endif

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

		struct BasicObjectCRT
		{
#ifdef CRT
			std::vector<ChPtr::Shared<BasicObject>>childList;
			ChPtr::Weak<BasicObject>parent = ChPtr::Shared<BasicObject>();

			std::vector<ChPtr::Shared<BaseComponent>>comList;
#endif
		};

		BasicObjectCRT* value = nullptr;

	};

	template<typename CharaType>
	class ObjectList;

	template<typename CharaType>
	class BaseObject : public BasicObject
	{
	public:

		friend ObjectList<CharaType>;

	protected:

		BaseObject(){}

	public:

#ifdef CRT

		template<class T = BaseObject<CharaType>>
		static typename std::enable_if<
			std::is_base_of<BaseObject<CharaType>, T>::value || 
			std::is_same<BaseObject<CharaType>, T>::value, ChPtr::Shared<T>>::type
			CreateObject() 
		{
			ChPtr::Shared<BaseObject<CharaType>>res = nullptr;
			res.reset(new T());
			return res;
		}
#endif

	public:

#ifdef CRT

		//自身の名前のセット//
		void SetMyName(const std::basic_string<CharaType>& _newName) { value->myName = _newName; }

#endif

	private://Set Functions//

#ifdef CRT

		void SetObjectList(ObjectList<CharaType>* _objMa) { objMaList = _objMa; }

#endif

	public:

#ifdef CRT

		//子オブジェクト群の取得//
		template<class T = BasicObject>
		typename std::enable_if<
			std::is_base_of<BasicObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetChildlenForName(const std::basic_string<CharaType>& _name)
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (auto&& obj : GetAllChildlen())
			{
				if (obj->GetMyName() != _name)continue;

				auto test = ChPtr::SharedSafeCast<T>(obj);
				if (test == nullptr)continue;
				tmpObjList.push_back(test);
			}

			return tmpObjList;
		}

		//子オブジェクト群の取得//
		template<class T = BaseObject>
		typename std::enable_if<
			std::is_base_of<BaseObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetChildlenConstainsName(const std::basic_string<CharaType>& _name)
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (auto&& obj : GetAllChildlen())
			{
				if (obj->GetMyName().find(_name) == std::basic_string<CharaType>::npos)continue;

				auto test = ChPtr::SharedSafeCast<T>(obj);
				if (test == nullptr)continue;
				tmpObjList.push_back(test);
			}

			return tmpObjList;
		}

		//子オブジェクト群の取得//
		template<class T = BasicObject>
		typename std::enable_if<
			std::is_base_of<BasicObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetAllChildlenForName(const std::basic_string<CharaType>& _name)
		{
			std::vector<ChPtr::Weak<T>>res;

			for (auto&& obj : GetAllChildlen())
			{
				if (obj->GetMyName() == _name)
				{
					auto test = ChPtr::SharedSafeCast<T>(obj);
					if (test != nullptr) { res.push_back(test); }
				}

				for (auto&& childObj : obj->GetAllChildlenForName<T>(_name)) { res.push_back(childObj); }
			}

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

			for (auto&& obj : GetChildlen())
			{
				auto&& baseObj = ChPtr::SharedSafeCast<BaseObject>(obj);

				if (baseObj->GetMyName().find(_name) != std::basic_string<CharaType>::npos)
				{
					auto test = ChPtr::SharedSafeCast<T>(baseObj);
					if (test != nullptr) { res.push_back(test); }
				}

				for (auto&& childObj : baseObj->GetAllChildlenConstainsName<T>(_name)) { res.push_back(childObj); }
			}
			return res;
		}

#endif

	public:

#ifdef CRT

		std::basic_string<CharaType> GetMyName() { return value->myName; }

#endif

	public:

		ObjectList<CharaType>* LookObjectList();

	private:

		void WithdrawObjectList();

	protected:

		//Release時に走る関数//
		void BaseRelease()override final;

	private:

		ObjectList<CharaType>* objMaList = nullptr;

		struct BaseObjectCRT
		{
#ifdef CRT
			std::basic_string<CharaType> myName;
#endif
		};

		BaseObjectCRT* value = nullptr;
	};
}

#ifdef CRT

void ChCpp::BaseComponent::DestroyObject()
{
	if (ChPtr::NullCheck(obj))return;
	obj->Destroy();
	obj = nullptr;
}

ChCpp::BasicObject::BasicObject()
{
	value = new BasicObject();
}

ChCpp::BasicObject::~BasicObject()
{
	delete value;
}

void ChCpp::BasicObject::BaseRelease()
{
	DestroyComponent();

	DestroyToChild();

	WithdrawParent();

	Release();

	dFlg = true;
	useFlg = false;
}

void ChCpp::BasicObject::Destroy() { BaseRelease(); }

void ChCpp::BasicObject::DestroyToChild(const ChPtr::Shared<BasicObject>& _child)
{
	auto it = std::find(value->childList.begin(), value->childList.end(), _child);
	if (it == value->childList.end())return;
	(*it)->BaseRelease();
}

//自身が持つ子を削除する//
void ChCpp::BasicObject::DestroyToChild()
{
	if (value->childList.empty())return;
	for (auto&& childs : value->childList) { childs->BaseRelease(); }
	value->childList.clear();
}

void ChCpp::BasicObject::DestroyComponent()
{
	if (value->comList.empty())return;
	for (auto com : value->comList) { com->Release(); }
	value->comList.clear();
}

void ChCpp::BasicObject::DestroyComponent(const char* _comName)
{
	std::string comName = _comName;
	if (comName == "")return;
	auto&& com = value->comList.begin();

	while (com != value->comList.end())
	{
		std::string tmpName = typeid((*com)).name();

		if (tmpName.find(comName) == tmpName.npos) {
			com++;
			continue;
		}
		(*com)->Release();
		com = value->comList.erase(com);

		if (value->comList.empty())break;
	}
}

void ChCpp::BasicObject::DestroyToChildTest()
{
	if (value->childList.empty())return;
	auto child = value->childList.begin();
	while (child != value->childList.end())
	{
		if (!(*child)->IsDethFlg())
		{
			child++;
			continue;
		}
		(*child)->Release();
		child = value->childList.erase(child);

		if (value->childList.empty())break;
	}
}

void ChCpp::BasicObject::DestroyComponentTest()
{
	if (value->comList.empty())return;
	auto com = value->comList.begin();
	while (com != value->comList.end())
	{
		if (!(*com)->IsDeth())
		{
			com++;
			continue;
		}
		(*com)->Release();
		com = value->comList.erase(com);
		if (value->comList.empty())break;
	}
}

std::vector<ChPtr::Shared<ChCpp::BasicObject>> ChCpp::BasicObject::GetAllChildlen()
{
	std::vector<ChPtr::Shared<BasicObject>>res = value->childList;

	for (auto&& childObj : value->childList)
	{
		for (auto&& childChild : childObj->GetAllChildlen())
		{
			res.push_back(childChild);
		}
	}

	return res;
}

void ChCpp::BasicObject::SetComponent(ChPtr::Shared<BaseComponent> _component)
{
	if (_component == nullptr)return;
	if (ChPtr::NotNullCheck(_component->obj))return;

	_component->BaseInit(this);

	value->comList.push_back(_component);
}

void ChCpp::BasicObject::SetChild(ChPtr::Shared<BasicObject> _childObject)
{

	if (_childObject == nullptr)return;
	if (this == _childObject.get())return;

	_childObject->WithdrawParent();

	value->childList.push_back(_childObject);

	_childObject->value->parent = shared_from_this();
}

void ChCpp::BasicObject::SetParent(ChPtr::Shared<BasicObject> _parentObject)
{
	if (this == _parentObject.get())return;

	WithdrawParent();

	value->parent = _parentObject;

	_parentObject->SetChild(shared_from_this());
}

void ChCpp::BasicObject::WithdrawParent()
{
	auto parentObj = value->parent.lock();

	if (parentObj == nullptr)return;
	if (parentObj->value->childList.empty())return;

	value->parent.reset();

	auto test = std::find(parentObj->value->childList.begin(), parentObj->value->childList.end(), shared_from_this());

	if (test != parentObj->value->childList.end()) { parentObj->value->childList.erase(test); }
}

CH_OBJECT_FUNCTION(UpdateBegin);

void ChCpp::BasicObject::UpdateFunction()
{
	Update();

	if (!value->comList.empty())
	{
		auto com = value->comList.begin();
		while (com != value->comList.end())
		{
			if ((*com)->IsDeth())
			{
				(*com)->Release();
				com = value->comList.erase(com);
				if (value->comList.empty())break;
				continue;
			}
			if ((*com)->IsUseFlg())(*com)->Update();

			if (value->comList.empty())break;
			com++;
		}
	}

	if (!value->childList.empty())
	{
		auto child = value->childList.begin();
		while (child != value->childList.end())
		{
			if ((*child)->dFlg)
			{
				(*child)->Release();
				child = value->childList.erase(child);
				if (value->childList.empty())break;
				continue;
			}
			if ((*child)->useFlg)(*child)->Update();

			if (value->childList.empty())break;
			child++;
		}
	}
}

CH_OBJECT_FUNCTION(UpdateEnd);

CH_OBJECT_FUNCTION(MoveBegin);
CH_OBJECT_FUNCTION(Move);
CH_OBJECT_FUNCTION(MoveEnd);

CH_OBJECT_FUNCTION(DrawBegin);
CH_OBJECT_FUNCTION(Draw2D);
CH_OBJECT_FUNCTION(Draw3D);
CH_OBJECT_FUNCTION(DrawEnd);

template<typename CharaType>
void ChCpp::BaseObject<CharaType>::BaseRelease()
{
	BasicObject::BaseRelease();
	if (ChPtr::NullCheck(objMaList))return;
	WithdrawObjectList();
}

#endif

#include"SharedFunctions/ChObjectSharedObjectList.h"

#include"ChObjectList.h"

#endif