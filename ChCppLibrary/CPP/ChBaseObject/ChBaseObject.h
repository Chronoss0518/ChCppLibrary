
#ifndef Ch_CPP_BaObj_h
#define Ch_CPP_BaObj_h

#include"../ChBitBool/ChBitBool.h"

#include"ChBaseComponent.h"

namespace ChCpp
{
	class ObjectList;

	//�I�u�W�F�N�g�𐶐�����ꍇ�A���̃N���X���p�����č쐬����B//
	class BaseObject :public std::enable_shared_from_this<BaseObject>, public ChCp::Releaser
	{
	public:

		friend BaseComponent;
		friend ObjectList;

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//Set���Ɏ����I�ɑ���֐�//
		virtual void Init() {}

		//���g���̂Ă鎞�Ɏ����I�ɑ���֐�//
		void Release() {}

	public://Destroy Function//

		//���g���̂Ă������ɑ��点��֐�//
		void Destroy();

	public://Destroy Functions//

	//���g�����q���폜����//
		void DestroyToChild();

		//���g�����q���폜����//
		void DestroyToChild(const ChPtr::Shared<BaseObject>& _child);

		//�R���|�[�l���g�����ׂč폜����//
		void DestroyComponent();

		//�w�肵���R���|�[�l���g�����ׂč폜����//
		void DestroyComponent(const std::string& _comName);

		//�폜�����q�I�u�W�F�N�g�����݂��邩���m�F���폜����//
		void DestroyToChildTest();

		//�폜�����R���|�[�l���g�����邩�ǂ������m�F���폜����//
		void DestroyComponentTest();

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		BaseObject() {};

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		std::string GetMyName() { return myName; }

		//�R���|�[�l���g�̎擾//
		template<class T = BaseComponent>
		inline auto GetComponent()->typename std::enable_if<
			std::is_base_of<BaseComponent, T>::value,
			ChPtr::Shared<T>>::type
		{
			for (auto&& com : comList)
			{
				if (com->dFlg)continue;
				if (!com->useFlg)continue;

				auto testCom = ChPtr::SharedSafeCast<T>(com);

				if (testCom != nullptr)
				{
					return testCom;
				}
			}
			return nullptr;
		}

		//�R���|�[�l���g���X�g�̎擾//
		template<typename T = BaseComponent>
		inline auto GetComponents()->typename std::enable_if<
			std::is_base_of<BaseComponent, T>::value,
			std::vector<ChPtr::Shared<T>>>::type
		{
			std::vector<ChPtr::Shared<T>>tmpComList;
			for (auto&& com : comList)
			{
				if (com->dFlg)continue;
				if (!com->useFlg)continue;

				auto test = ChPtr::SharedSafeCast<T>(com);
				if (test == nullptr)continue;
				tmpComList.push_back(test);
			}
			return tmpComList;
		}

		std::vector<ChPtr::Shared<BaseObject>>& GetChildlen();

		//�q�I�u�W�F�N�g�Q�̎擾//
		template<class T = BaseObject>
		inline typename std::enable_if<
			std::is_base_of<BaseObject, T>::value, 
			std::vector<ChPtr::Weak<T>>>::type
			GetChildlen()
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (auto&& obj : childList)
			{
				auto test = ChPtr::SharedSafeCast<T>(obj);
				if (test == nullptr)continue;
				tmpObjList.push_back(test);
			}

			return tmpObjList;
		}

		//�q�I�u�W�F�N�g�Q�̎擾//
		template<class T = BaseObject>
		inline typename std::enable_if<
			std::is_base_of<BaseObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetChildlenForName(const std::string& _name)
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (auto&& obj : childList)
			{
				if (obj->GetMyName() != _name)continue;

				auto test = ChPtr::SharedSafeCast<T>(obj);
				if (test == nullptr)continue;
				tmpObjList.push_back(test);
			}

			return tmpObjList;
		}

		std::vector<ChPtr::Shared<BaseObject>> GetAllChildlen();

		//�q�I�u�W�F�N�g�Q�̎擾//
		template<class T = BaseObject>
		inline typename std::enable_if<
			std::is_base_of<BaseObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetAllChildlen()
		{
			std::vector<ChPtr::Weak<T>>res;

			for (auto&& obj : childList)
			{
				auto test = ChPtr::SharedSafeCast<T>(obj);
				if (test != nullptr)
				{
					res.push_back(test);
				}

				for (auto&& childObj : obj->GetAllChildlen<T>())
				{
					res.push_back(childObj);
				}

			}

			return res;
		}

		//�q�I�u�W�F�N�g�Q�̎擾//
		template<class T = BaseObject>
		inline typename std::enable_if<
			std::is_base_of<BaseObject, T>::value,
			std::vector<ChPtr::Weak<T>>>::type
			GetAllChildlenForName(const std::string& _name)
		{
			std::vector<ChPtr::Weak<T>>res;

			for (auto&& obj : childList)
			{
				if (obj->GetMyName() == _name)
				{
					auto test = ChPtr::SharedSafeCast<T>(obj);
					if (test != nullptr)
					{
						res.push_back(test);
					}
				}

				for (auto&& childObj : obj->GetAllChildlenForName<T>(_name))
				{
					res.push_back(childObj);
				}

			}

			return res;
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

			tmpCom->BaseInit(this);

			return ChPtr::SharedSafeCast<T>(tmpCom);

		}

		void SetComponent(ChPtr::Shared<BaseComponent> _component);

		//�q�I�u�W�F�N�g�̃Z�b�g//
		void SetChild(ChPtr::Shared<BaseObject> _childObject);

		void SetParent(ChPtr::Shared<BaseObject> _parentObject);

		//���g�̖��O�̃Z�b�g//
		inline void SetMyName(const std::string& _newName) { myName = _newName; }

		//�g�p�t���O//
		inline void SetUseFlg(const ChStd::Bool& _flg) { useFlg = _flg; }

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�g�p�ۂ̊m�F//
		inline ChStd::Bool IsUseFlg() { return useFlg; }

		///////////////////////////////////////////////////////////////////////////////////////

		void WithdrawParent();

		void WithdrawObjectList();

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


	private:

		//Release���ɑ���֐�//
		void BaseRelease();

		//Set���ɑ���֐�//
		void BaseInit(
			const std::string& _objectName
			, ObjectList* _objMa);

		///////////////////////////////////////////////////////////////////////////////////

		std::vector<ChPtr::Shared<BaseObject>>childList;
		ChPtr::Weak<BaseObject>parent = ChPtr::Shared<BaseObject>();

		std::vector<ChPtr::Shared<BaseComponent>>comList;

		ObjectList* objMaList = nullptr;
		std::string myName;
		ChStd::Bool dFlg = false;

		ChStd::Bool useFlg = true;

	};

}

#endif