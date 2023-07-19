#ifndef Ch_CPP_BaFr_h
#define Ch_CPP_BaFr_h

#include"../../BaseIncluder/ChBase.h"

namespace ChCpp
{
	class BaseFrame;

	class FrameList
	{
	public:

		//����t���[�����Z�b�g//
		//BaseFrame���p�����Ă�����̂̂݃Z�b�g�ł���//
		template<class T>
		auto SetFrame()->
			typename std::enable_if
			<std::is_base_of<BaseFrame, T>::value, const void>::type
		{
			frameList.push_back(
				[]()-> ChPtr::Shared<BaseFrame>
				{
					return ChPtr::Make_S<T>();
				});

			if (frameList.size() > 1)return;

			ChangeFrame(0);

			Changes();
		}

		template<class T>
		static auto GetNowFrame()->
			typename std::enable_if
			<std::is_base_of<BaseFrame, T>::value, ChPtr::Weak<T>>::type
		{
			return ChPtr::SharedSafeCast<T>(GetNowFrame());
		}


		inline unsigned long GetNowFrameNo() { return nowFrameNo; }

		inline unsigned long GetRegisterFrameCount() { return frameList.size(); }

	public://UpdateFunction//

		void Update();

	public://Release Funciton//

		void Release()
		{
			if (ChPtr::NotNullCheck(saveData))
			{
				delete saveData;
				saveData = nullptr;
			}

			nextFrame = nullptr;
			GetNowFrame() = nullptr;

		}
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

	protected://Other Function

		void ChangeFrame(const unsigned long _frameNo);

		void Changes();

	protected:// Member Value//

		friend BaseFrame;

		void* saveData = nullptr;

		unsigned long nextFrameNo = -1;
		unsigned long nowFrameNo = -1;

		ChPtr::Shared<BaseFrame>nextFrame = nullptr;
		
		static ChPtr::Shared<BaseFrame>& GetNowFrame() 
		{
			static ChPtr::Shared<BaseFrame> ins = nullptr;
			return ins;
		}

		std::vector<std::function<ChPtr::Shared<BaseFrame>()>>frameList;
	};


	//BaseFrame�Ǘ��p�N���X//
	class FrameManager :protected FrameList
	{
	public://Set Function//

		//����t���[�����Z�b�g//
		//BaseFrame���p�����Ă�����̂̂݃Z�b�g�ł���//
		template<class T>
		void SetFrame(typename std::enable_if
			<std::is_base_of<BaseFrame, T>::value, const std::string&>::type _useFrameName)
		{
			if (frameNames.find(_useFrameName) != frameNames.end())
			{
				//ChSystem::ErrerMessage("���̃t���[���͂��łɓo�^����Ă��܂�", "�x��");

				return;
			}

			unsigned long no = frameList.size();

			frameNames[_useFrameName] = no;

			FrameList::SetFrame<T>();

		}

	public://Get Function//

		template<class T>
		auto GetNowFrame()->
			typename std::enable_if
			<std::is_base_of<BaseFrame, T>::value, ChPtr::Weak<T>>::type
		{
			return FrameList::GetNowFrame<T>();
		}

		std::string GetNowFrameName();

		inline unsigned long GetRegisterFrameCount() { return FrameList::GetRegisterFrameCount(); }

	public://Update Function//

		inline void Update() { FrameList::Update(); }

	public://Other Functions//

		template<class T>
		void SaveData(const T* _save)
		{
			FrameList::SaveData<T>(_save);
		}

		template<class T>
		T* GetData()
		{
			return FrameList::GetData<T>();
		}

		void ChangeFrame(const std::string& _frameName);

	private:// Member Value//

		friend BaseFrame;

		std::map<std::string, unsigned long>frameNames;

	private://ConstructerDestructer//

		FrameManager() {}

		~FrameManager() { FrameList::Release(); }

	public://Get Instance//

		static FrameManager& GetIns()
		{
			static FrameManager ins;
			return ins;
		}

	};

	inline FrameManager& FrameMgr() { return FrameManager::GetIns(); }

	//�Q�[���V�[�����ȈՓI�������s�����߂̃N���X//
	//�K�v�ɉ����Ĉȉ��̊֐����I�[�o�[���C�h����//
	//void Init(),void Release(),void Update()//
	class BaseFrame
	{

	public://InitAndRelease//
		virtual inline void Init() {};

		virtual inline void Release(){};

	public://Update Function//

		virtual void Update() = 0;

	public:

		friend FrameList;

	protected://Other Functions//

		template<class T>
		void SaveData(const T* _save)
		{
			if (ChPtr::NullCheck(mgr))return nullptr;
			mgr->SaveData(_save);
		}

		template<class T>
		T* GetData()
		{
			if (ChPtr::NullCheck(mgr))return nullptr;
			return mgr->GetData<T>();
		}

		//�o�^����Ă���t���[���Ɉړ�����//
		void ChangeFrame(const unsigned long _frameNo)
		{
			mgr->ChangeFrame(_frameNo);
		}

	private://Other Functions//

		void SetManager(FrameList* _mgr) { mgr = _mgr; }

	protected://ConstructerDestructer//

		BaseFrame() {};

		virtual ~BaseFrame() { Release(); };


	private:

		FrameList* mgr;

	};
}


#endif