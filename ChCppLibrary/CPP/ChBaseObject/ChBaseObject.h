
#ifndef Ch_CPP_BaObj_h
#define Ch_CPP_BaObj_h

#include"../../CRTPack/ChSmartPtrPack/ChSmartPtrPack.h"
#include"../../CRTPack/ChVectorPack/ChVectorPack.h"
#include"../../CRTPack/ChStringPack/ChStringPack.h"

#include"../../BasePack/ChPtr.h"

#include"ChBaseComponent.h"


namespace ChCpp
{
	class ObjectList;

	//�I�u�W�F�N�g�𐶐�����ꍇ�A���̃N���X���p�����č쐬����B//
	class BasicObject
	{
	public:

		friend ObjectList;

		friend BaseComponent;

	protected:

		//Release���ɑ���֐�//
		virtual void BaseRelease();

	public://Initialize Deserialize//

		//Set���Ɏ����I�ɑ���֐�//
		virtual void Init() {}

		//���g���̂Ă鎞�Ɏ����I�ɑ���֐�//
		virtual void Release() {}

	public://Destroy Function//

		//���g���̂Ă������ɑ��点��֐�//
		virtual void Destroy();

	public://Destroy Functions//

		//���g�����q���폜����//
		virtual void DestroyToChild();

#ifdef CRT

		//���g�����q���폜����//
		void DestroyToChild(ChPtr::Shared<BasicObject>& _child)
		{
			ChCRT::SharedPtrPack<BasicObject>tmp = _child;
			DestroyToChildBase(tmp);
		}

#endif

		//�R���|�[�l���g�����ׂč폜����//
		void DestroyComponent();

		//�폜�����q�I�u�W�F�N�g�����݂��邩���m�F���폜����//
		virtual void DestroyToChildTest();

		//�폜�����R���|�[�l���g�����邩�ǂ������m�F���폜����//
		void DestroyComponentTest();

	protected:

		virtual void DestroyToChildBase(ChCRT::SharedPtrPack<BasicObject>& _child);

	public:

#ifdef CRT

		//�R���|�[�l���g�̃Z�b�g//
		template<class T>
		typename std::enable_if
			<std::is_base_of<BaseComponent, T>::value, const ChPtr::Shared<T>>::type 
			SetComponent()
		{
			ChPtr::Shared<BaseComponent> tmpCom = ChPtr::Make_S<T>();

			if (tmpCom == nullptr)return nullptr;

			comList.Push(tmpCom);

			tmpCom->BaseInit(this);

			return ChPtr::SharedSafeCast<T>(tmpCom);
		}

		//�q�I�u�W�F�N�g�̃Z�b�g//
		void SetComponent(ChPtr::Shared<BaseComponent> _com)
		{
			SetComponentCRT(_com);
		}

		//�q�I�u�W�F�N�g�̃Z�b�g//
		void SetChild(ChPtr::Shared<BasicObject> _childObject)
		{
			SetChildCRT(_childObject);
		}

#if 0
		//���ݒ�����//
		inline void SetParent(ChPtr::Shared<BasicObject> _parentObject)
		{
			if (this == _parentObject.get())return;

			WithdrawParent();

			parent = _parentObject;

			_parentObject->SetChild(shared_from_this());
		}
#endif

#endif

		//�g�p�t���O//
		void SetUseFlg(const bool& _flg) { useFlg = _flg; }

		void SetComponentCRT(ChCRT::SharedPtrPack<BaseComponent> _com);

		void SetChildCRT(ChCRT::SharedPtrPack<BasicObject> _childObject);

	private://Set Functions//

		void SetObjectList(ObjectList* _objMa) { objMaList = _objMa; }

	public://Get Functions//

#ifdef CRT

		//�R���|�[�l���g�̎擾//
		template<class T = BaseComponent>
		typename std::enable_if<
			std::is_base_of<BaseComponent, T>::value,
			ChPtr::Shared<T>>::type
			GetComponent()
		{
			for (size_t i = 0; i < comList.GetSize(); i++)
			{
				if (comList[i]->dFlg)continue;
				auto testCom = ChPtr::SharedSafeCast<T>(comList[i]);
				if (testCom != nullptr) return testCom;
			}
			return nullptr;
		}

		//�R���|�[�l���g���X�g�̎擾//
		template<typename T = BaseComponent>
		typename std::enable_if<
			std::is_base_of<BaseComponent, T>::value,
			std::vector<ChPtr::Shared<T>>>::type
			GetComponents()
		{
			std::vector<ChPtr::Shared<T>>tmpComList;

			for (size_t i = 0; i < comList.GetSize(); i++)
			{
				if (comList[i]->dFlg)continue;
				auto test = ChPtr::SharedSafeCast<T>(comList[i]);
				if (test == nullptr)continue;
				tmpComList.push_back(test);
			}
			return tmpComList;
		}

		//�q�I�u�W�F�N�g�Q�̎擾//
		template<class T = BasicObject>
		typename std::enable_if<
			std::is_base_of<BasicObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetChildlen()
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (size_t i = 0; i < childList.GetSize(); i++)
			{
				auto test = ChPtr::SharedSafeCast<T>(childList[i]);
				if (test == nullptr)continue;
				tmpObjList.push_back(test);
			}

			return tmpObjList;
		}

		inline std::vector<ChPtr::Shared<BasicObject>> GetAllChildlen()
		{
			std::vector<ChPtr::Shared<BasicObject>>res;

			for (size_t i = 0;i < childList.GetSize();i++)
			{
				auto&& childObj = childList[i];
				res.push_back(childObj);

				auto&& childObjChildList = childObj->GetAllChildlen();
				for (size_t j = 0;j< childObjChildList.size();j++)
				{
					res.push_back(childObjChildList[j]);
				}
			}

			return res;
		}


		//�q�I�u�W�F�N�g�Q�̎擾//
		template<class T = BasicObject>
		typename std::enable_if<
			std::is_base_of<BasicObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetAllChildlen()
		{
			std::vector<ChPtr::Weak<T>>res;

			for (size_t i = 0; i < childList.GetSize(); i++)
			{
				auto&& test = ChPtr::SharedSafeCast<T>(childList[i]);
				if (test != nullptr)res.push_back(test);
				auto&& childInchildList = childList[i]->GetAllChildlen<T>();
				for (size_t i = 0; i < childInchildList.GetSize();i++) { res.push_back(childInchildList[i]); }
			}
			return res;
		}

#endif

		//�e�̎擾//
		BasicObject* GetParent() { return parent; }

	protected://Get Functions//

#ifdef CRT

		std::vector<ChPtr::Shared<BasicObject>> GetChildlen() 
		{
			std::vector<ChPtr::Shared<BasicObject>> res;
			for (size_t i = 0; i < childList.GetSize(); i++)
			{
				res.push_back(childList[i]);
			}
			return res;
		}

#endif

		ChCRT::VectorPack<ChCRT::SharedPtrPack<BasicObject>>& GetChildlenCRT() { return childList; }

	protected:

		ObjectList* LookObjectList();

	private:

		void WithdrawObjectList();

	public://Is Functions//

		//�g�p�ۂ̊m�F//
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

		//�I�u�W�F�N�g���g�̋@�\//
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

		ChCRT::VectorPack<ChCRT::SharedPtrPack<BasicObject>>childList;
		BasicObject* parent;
		ChCRT::VectorPack<ChCRT::SharedPtrPack<BaseComponent>>comList;
	};

	template<typename CharaType>
	class BaseObject : public BasicObject
	{
	public:

		BaseObject();

		virtual ~BaseObject();

	public:

#ifdef CRT

		//���g�̖��O�̃Z�b�g//
		void SetMyName(const std::basic_string<CharaType>& _newName) { SetMyNameCRT(_newName); }

#endif

		//���g�̖��O�̃Z�b�g//
		void SetMyNameCRT(const ChCRT::StringPack<CharaType>& _newName) { myName = _newName; }

	public:

#ifdef CRT

		//�q�I�u�W�F�N�g�Q�̎擾//
		template<class T = BaseObject>
		typename std::enable_if<
			std::is_base_of<BaseObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetChildlenForName(const std::basic_string<CharaType>& _name)
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (auto&& obj : GetChildlen())
			{
				auto&& baseObj = ChPtr::SharedSafeCast<BaseObject>(obj);
				if (baseObj->GetMyName() != _name)continue;

				auto test = ChPtr::SharedSafeCast<T>(baseObj);
				if (test == nullptr)continue;
				tmpObjList.push_back(test);
			}

			return tmpObjList;
		}

		//�q�I�u�W�F�N�g�Q�̎擾//
		template<class T = BaseObject>
		typename std::enable_if<
			std::is_base_of<BaseObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetChildlenConstainsName(const std::basic_string<CharaType>& _name)
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (auto&& obj : GetAllChildlen())
			{
				auto&& baseObj = ChPtr::SharedSafeCast<BaseObject>(obj);
				if (baseObj->GetMyName().find(_name) == std::basic_string<CharaType>::npos)continue;

				auto test = ChPtr::SharedSafeCast<T>(baseObj);
				if (test == nullptr)continue;
				tmpObjList.push_back(test);
			}

			return tmpObjList;
		}

		//�q�I�u�W�F�N�g�Q�̎擾//
		template<class T = BaseObject>
		typename std::enable_if<
			std::is_base_of<BaseObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetAllChildlenForName(const std::basic_string<CharaType>& _name)
		{
			std::vector<ChPtr::Weak<T>>res;

			for (auto&& obj : GetAllChildlen())
			{
				auto&& baseObj = ChPtr::SharedSafeCast<BaseObject>(obj);

				if (baseObj->GetMyName() == _name)
				{
					auto test = ChPtr::SharedSafeCast<T>(baseObj);
					if (test != nullptr) { res.push_back(test); }
				}

				for (auto&& childObj : baseObj->GetAllChildlenForName<T>(_name)) { res.push_back(childObj); }
			}

			return res;
		}

		//�q�I�u�W�F�N�g�Q�̎擾//
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

		std::basic_string<CharaType> GetMyName() { return GetMyNameCRT(); }

#endif

		ChCRT::StringPack<CharaType> GetMyNameCRT() { return myName; }

	private:

		ChCRT::StringPack<CharaType> myName;
	};
}

#endif