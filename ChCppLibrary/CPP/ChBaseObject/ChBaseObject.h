
#ifndef Ch_CPP_BaObj_h
#define Ch_CPP_BaObj_h

#include"../ChBitBool/ChBitBool.h"

#include"ChBaseComponent.h"

namespace ChCpp
{
	class ObjectManager;
	class ObjectList;

	//�I�u�W�F�N�g�𐶐�����ꍇ�A���̃N���X���p�����č쐬����B//
	class BaseObject :public std::enable_shared_from_this<BaseObject>
	{
	public:

		friend BaseComponent;
		friend ObjectList;

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//Set���Ɏ����I�ɑ���֐�//
		virtual void Init() {}

		//���g���̂Ă鎞�Ɏ����I�ɑ���֐�//
		virtual void Release() {}

		//���g���̂Ă������ɑ��点��֐�//
		void Destroy();

		//���g�����q���폜����//
		void DestroyToChild(const ChPtr::Shared<BaseObject>& _child);

		//�R���|�[�l���g���w�肵�č폜����//
		void ReleaseComponent(const std::string& _comName);

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		BaseObject() {};

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//���݂̃^�O���擾//
		std::string GetTag() { return tag; }

		std::string GetMyName() { return myName; }

		//�R���|�[�l���g�̎擾//
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

		//�R���|�[�l���g���X�g�̎擾//
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

		//�q�I�u�W�F�N�g�Q�̎擾//
		std::vector<ChPtr::Shared<BaseObject>>& GetChildlen()
		{
			return childList;
		}

		//�e�̎擾//
		ChPtr::Weak<BaseObject>GetParent()
		{
			return parent;
		}


		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�R���|�[�l���g�̃Z�b�g//
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

		//�q�I�u�W�F�N�g�̃Z�b�g//
		inline void SetChild(ChPtr::Shared<BaseObject> _childObject)
		{
			childList.push_back(_childObject);

			auto par = _childObject->parent.lock();
			if (par != nullptr)
			{
				auto&& obj =  std::find(par->childList.begin(), par->childList.end(), _childObject);
				if(obj != par->childList.end())	par->childList.erase(obj);
			}

			_childObject->parent = shared_from_this();

		}

		//���g�̖��O�̃Z�b�g//
		inline void SetMyName(const std::string& _newName) { myName = _newName; }

		//�g�p�t���O//
		inline void SetUseFlg(const ChStd::Bool& _flg) { useFlg = _flg; }

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�g�p�ۂ̊m�F//
		inline ChStd::Bool IsUseFlg() { return useFlg; }

		///////////////////////////////////////////////////////////////////////////////////////

		//Tag�ύX���ɑ��点��֐�//
		void ChengeTag(const std::string& _newTag);

		///////////////////////////////////////////////////////////////////////////////////////

		//�S�̃I�u�W�F�N�g�̊m�F//
		std::vector<ChPtr::Weak<BaseObject>>LookObjectList();

		//�I�������^�O�̃I�u�W�F�N�g�̊m�F//
		std::vector<ChPtr::Weak<BaseObject>>LookObjectListForTag(const std::string& _tag);

		//�I���������O�̃I�u�W�F�N�g�̊m�F//
		std::vector<ChPtr::Weak<BaseObject>>LookObjectListForName(const std::string& _objectName);

		//�I�������^�O���̑I���������O�̂̃I�u�W�F�N�g�̊m�F//
		std::vector<ChPtr::Weak<BaseObject>>LookObjectListForTagAndName(const std::string& _objectName, const std::string& _Tag);

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

		//�I�u�W�F�N�g���g�̋@�\//
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


		ChStd::Bool useFlg = true;

	private:

		//Release���ɑ���֐�//
		void BaseRelease();

		//Set���ɑ���֐�//
		void BaseInit(
			const std::string& _objectName
			, const std::string& _tag
			, ObjectManager* _objMa);

		///////////////////////////////////////////////////////////////////////////////////
		//Component//

		void IsReleasComponent();

		///////////////////////////////////////////////////////////////////////////////////

		std::vector<ChPtr::Shared<BaseObject>>childList;
		ChPtr::Weak<BaseObject>parent;

		std::vector<ChPtr::Shared<BaseComponent>>comList;

		ObjectList* objMaList = nullptr;
		std::string myName;
		std::string tag;
		ChStd::Bool dFlg = false;

	};

}

#endif