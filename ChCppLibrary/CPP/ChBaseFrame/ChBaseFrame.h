#ifndef Ch_CPP_BaFr_h
#define Ch_CPP_BaFr_h

#include"../../BaseIncluder/ChBase.h"

namespace ChCpp
{
	class BaseFrame;

	//BaseFrame�Ǘ��p�N���X//
	class BaseFrameManager:public ChCp::Initializer
	{
	public://Set Function//

		//����t���[�����Z�b�g//
		//BaseFrame���p�����Ă�����̂̂݃Z�b�g�ł���//
		template<class T>
		void SetFrame(typename std::enable_if
			<std::is_base_of<BaseFrame, T>::value, const std::string&>::type _useFrameName)
		{
			if (frameList.find(_useFrameName) != frameList.end())
			{
				//ChSystem::ErrerMessage("���̃t���[���͂��łɓo�^����Ă��܂�", "�x��");

				return;
			}

			frameList[_useFrameName]
				= []()-> ChPtr::Shared<BaseFrame>
			{
				return ChPtr::Make_S<T>(); 
			};

			if (nowFrame != nullptr)return;

			ChengeFrame(_useFrameName);

			Chenges();
		}

		template<class T>
		auto GetNowFrame()->
			typename std::enable_if
			<std::is_base_of<BaseFrame,T>::value,ChPtr::Weak<T>>::type
		{
			return ChPtr::SharedSafeCast<T>(nowFrame);
		}

	public://UpdateFunction//

		void Update();

	private://Release Funciton//

		void Release()
		{
			if (ChPtr::NotNullCheck(saveData))
			{
				delete saveData;
				saveData = nullptr;
			}

			SetInitFlg(false);

		}

	public://Get Function//

		inline std::string GetNowFrameName() { return nowFrameName; }

	public://Other Function

		template<class T>
		void SaveData(const T* _save)
		{
			if (ChPtr::NullCheck(saveData))
			{
				saveData = new T();
			}

			auto tmp = static_cast<T*>(saveData);


			*tmp = *_save;
		}

		template<class T>
		T* GetData()
		{
			if (ChPtr::NullCheck(saveData))return nullptr;

			auto tmp = static_cast<T*>(saveData);


			return tmp;
		}

	private://Other Function

		void ChengeFrame(const std::string& _frameName);

		void Chenges();

	private:// Member Value//

		friend BaseFrame;

		void* saveData = nullptr;

		std::string nextFrameName = "";
		std::string nowFrameName = "";

		std::map<std::string, std::function<ChPtr::Shared<BaseFrame>()>>frameList;

		ChPtr::Shared<BaseFrame>nextFrame = nullptr;

		ChPtr::Shared<BaseFrame>nowFrame;

	private://ConstructerDestructer//

		BaseFrameManager() { SetInitFlg(true); }

		~BaseFrameManager() { Release(); }

	public://Get Instance//

		static BaseFrameManager& GetIns()
		{
			static BaseFrameManager ins;
			return ins;
		}

	};

	static const std::function<BaseFrameManager&()>FrameManager = BaseFrameManager::GetIns;

	//�Q�[���V�[�����ȈՓI�������s�����߂̃N���X//
	//�K�v�ɉ����Ĉȉ��̊֐����I�[�o�[���C�h����//
	//void Init(),void Release(),void Update()//
	class BaseFrame:public ChCp::Releaser
	{
	public://InitAndRelease//
		virtual inline void Init() {};

		virtual inline void Release()override {};

	public://Update Function//

		virtual void Update() = 0;

	public:

		friend BaseFrameManager;

	protected://ConstructerDestructer//

		template<class T>
		void SaveData(const T* _save)
		{
			FrameManager().SaveData(_save);
		}

		template<class T>
		T* GetData()
		{
			return FrameManager().GetData<T>();
		}

		BaseFrame() {};

		virtual ~BaseFrame() { Release(); };

		//�o�^����Ă���t���[���Ɉړ�����//
		void ChangeFrame(const std::string& _frameName)
		{
			FrameManager().ChengeFrame(_frameName);
		}

	private:

	};
}


#endif