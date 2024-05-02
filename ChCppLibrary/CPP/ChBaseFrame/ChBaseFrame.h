#ifndef Ch_CPP_BaFr_h
#define Ch_CPP_BaFr_h

#include"../../BaseIncluder/ChBase.h"

namespace ChCpp
{

	class BaseFrame;

	struct SendDataClass{
		virtual ~SendDataClass(){}
	};
	struct SaveDataClass{
		virtual ~SaveDataClass() {}
	};

	class FrameList
	{
	public:

		//自作フレームをセット//
		//BaseFrameを継承しているもののみセットできる//
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

		inline void SetSendData(ChPtr::Shared<SendDataClass> _sendData) { sendData = _sendData; }

		inline unsigned long GetNowFrameNo() { return nowFrameNo; }

		inline unsigned long GetRegisterFrameCount() { return frameList.size(); }

	public://UpdateFunction//

		void Update();

	public://Release Funciton//

		void Release()
		{
			saveData = nullptr;
			sendData = nullptr;

			nextFrame = nullptr;
			GetNowFrame() = nullptr;

		}
	public://Other Function

		void SaveData(ChPtr::Shared<SaveDataClass> _save)
		{
			saveData = _save;
		}

		ChPtr::Shared<SaveDataClass> GetData()
		{
			return saveData;
		}

		template<class T>
		auto GetData()->typename std::enable_if<std::is_base_of<SaveDataClass,T>::value,ChPtr::Shared<T>>::type
		{
			return saveData;
		}

	protected://Other Function

		void ChangeFrame(const unsigned long _frameNo);

		void Changes();

	protected:// Member Value//

		friend BaseFrame;

		ChPtr::Shared<SaveDataClass> saveData = nullptr;
		ChPtr::Shared<SendDataClass> sendData = nullptr;

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


	//BaseFrame管理用クラス//
	class FrameManager :protected FrameList
	{
	public://Set Function//

		//自作フレームをセット//
		//BaseFrameを継承しているもののみセットできる//
		template<class T>
		void SetFrame(typename std::enable_if
			<std::is_base_of<BaseFrame, T>::value, const std::string&>::type _useFrameName)
		{
			if (frameNames.find(_useFrameName) != frameNames.end())
			{
				//ChSystem::ErrerMessage("このフレームはすでに登録されています", "警告");

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

		void SaveData(ChPtr::Shared<SaveDataClass> _save)
		{
			FrameList::SaveData(_save);
		}

		ChPtr::Shared<SaveDataClass> GetData()
		{
			return FrameList::GetData();
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

	//ゲームシーンを簡易的生成を行うためのクラス//
	//必要に応じて以下の関数をオーバーライドする//
	//void Init(),void Release(),void Update()//
	class BaseFrame
	{

	public://InitAndRelease//
		virtual inline void Init(ChPtr::Shared<SendDataClass> _sendData) {};

		virtual inline void Release(){};

	public://Update Function//

		virtual void Update() = 0;

	public:

		friend FrameList;

	protected://Other Functions//

		void SaveData(ChPtr::Shared<SaveDataClass> _save)
		{
			if (ChPtr::NullCheck(mgr))return;
			mgr->SaveData(_save);
		}

		ChPtr::Shared<SaveDataClass> GetData()
		{
			if (ChPtr::NullCheck(mgr))return nullptr;
			return mgr->GetData();
		}

		void SendData(ChPtr::Shared<SendDataClass> _send)
		{
			if (ChPtr::NullCheck(mgr))return;
			mgr->SetSendData(_send);
		}

		//登録されているフレームに移動する//
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