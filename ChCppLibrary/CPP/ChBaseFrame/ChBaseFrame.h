#ifndef Ch_CPP_BaFr_h
#define Ch_CPP_BaFr_h

#ifdef CRT

#include<vector>
#include<map>
#include<functional>

#endif

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

		FrameList() {};

		virtual ~FrameList() { Release(); }

	public:

#ifdef CRT
		//自作フレームをセット//
		//BaseFrameを継承しているもののみセットできる//
		template<class T>
		auto SetFrame()->
			typename std::enable_if<std::is_base_of<BaseFrame, T>::value, void>::type
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
			typename std::enable_if<std::is_base_of<BaseFrame, T>::value, ChPtr::Weak<T>>::type
		{
			return ChPtr::SharedSafeCast<T>(GetNowFrame());
		}

		void SetSendData(ChPtr::Shared<SendDataClass> _sendData) { sendData = _sendData; }

#endif

		unsigned long GetNowFrameNo() { return nowFrameNo; }

		unsigned long GetRegisterFrameCount();

	public://UpdateFunction//

		void Update();

	public://Release Funciton//

		void Release();

	public://Other Function

#ifdef CRT
		void SaveData(ChPtr::Shared<SaveDataClass> _save)
		{
			saveData = _save;
		}

		ChPtr::Shared<SaveDataClass> GetData()
		{
			return saveData;
		}

		template<class T>
		auto GetData()->
			typename std::enable_if<std::is_base_of<SaveDataClass,T>::value,ChPtr::Shared<T>>::type
		{
			return saveData;
		}
#endif

	protected://Other Function

		void ChangeFrame(const unsigned long _frameNo);

		void Changes();

	protected:// Member Value//

		friend BaseFrame;

		unsigned long nextFrameNo = -1;
		unsigned long nowFrameNo = -1;

#ifdef CRT
		ChPtr::Shared<SaveDataClass> saveData = nullptr;
		ChPtr::Shared<SendDataClass> sendData = nullptr;

		ChPtr::Shared<BaseFrame>nextFrame = nullptr;
		
		static ChPtr::Shared<BaseFrame>& GetNowFrame() 
		{
			static ChPtr::Shared<BaseFrame> ins = nullptr;
			return ins;
		}

		std::vector<std::function<ChPtr::Shared<BaseFrame>()>>frameList;
#endif
	};


	//BaseFrame管理用クラス//
	template<typename CharaType>
	class FrameManager :protected FrameList
	{
	public://Set Function//

#ifdef CRT
		//自作フレームをセット//
		//BaseFrameを継承しているもののみセットできる//
		template<class T>
		void SetFrame(typename std::enable_if
			<std::is_base_of<BaseFrame, T>::value, const std::basic_string<CharaType>&>::type _useFrameName)
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
#endif

	public://Get Function//

#ifdef CRT
		template<class T>
		auto GetNowFrame()->
			typename std::enable_if
			<std::is_base_of<BaseFrame, T>::value, ChPtr::Weak<T>>::type
		{
			return FrameList::GetNowFrame<T>();
		}

		std::basic_string<CharaType> GetNowFrameName();
#endif

		inline unsigned long GetRegisterFrameCount() { return FrameList::GetRegisterFrameCount(); }

	public://Update Function//

		inline void Update() { FrameList::Update(); }

	public://Other Functions//

#ifdef CRT
		void SaveData(ChPtr::Shared<SaveDataClass> _save)
		{
			FrameList::SaveData(_save);
		}

		ChPtr::Shared<SaveDataClass> GetData()
		{
			return FrameList::GetData();
		}

		void ChangeFrame(const std::basic_string<CharaType>& _frameName);
#endif

	private:// Member Value//

		friend BaseFrame;

#ifdef CRT

		std::map<std::basic_string<CharaType>, unsigned long>frameNames;

#endif

	private://ConstructerDestructer//

		FrameManager() {}

		~FrameManager() {}

	public://Get Instance//

		static FrameManager& GetIns()
		{
			static FrameManager ins;
			return ins;
		}

	};

	template<typename CharaType>
	static inline FrameManager<CharaType>& FrameMgr() { return FrameManager<CharaType>::GetIns(); }

	//ゲームシーンを簡易的生成を行うためのクラス//
	//必要に応じて以下の関数をオーバーライドする//
	//void Init(),void Release(),void Update()//
	class BaseFrame
	{

	public://InitAndRelease//

		virtual inline void Init(SendDataClass* _sendData) {};

		virtual inline void Release(){};

	public://Update Function//

		virtual void Update() = 0;

	public:

		friend FrameList;

	protected://Other Functions//

#ifdef CRT
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
#endif
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
#ifdef CRT

void ChCpp::FrameList::Release()
{
	saveData = nullptr;
	sendData = nullptr;

	nextFrame = nullptr;
	GetNowFrame() = nullptr;
}

void ChCpp::FrameList::Update()
{

	auto&& nowframe = GetNowFrame();
	if (nowframe == nullptr)return;
	nowframe->Update();

	Changes();
}

void ChCpp::FrameList::ChangeFrame(const unsigned long _frameNo)
{
	if (frameList.size() <= _frameNo)return;

	nextFrame = frameList[_frameNo]();

	nextFrameNo = _frameNo;

	nextFrame->SetManager(this);
}

void ChCpp::FrameList::Changes()
{
	if (nextFrame == nullptr)return;

	auto&& nowframe = GetNowFrame();
	if (nowframe != nullptr)
	{
		nowframe->Release();
	}

	nowFrameNo = nextFrameNo;
	nowframe = nextFrame;

	nowframe->Init(sendData.get());
	sendData = nullptr;

	nextFrame = nullptr;
	nextFrameNo = -1;
}

unsigned long ChCpp::FrameList::GetRegisterFrameCount() { return frameList.size(); }

template<typename CharaType>
void ChCpp::FrameManager<CharaType>::ChangeFrame(const std::basic_string<CharaType>& _frameName)
{
	if (frameNames.find(_frameName) == frameNames.end())return;

	FrameList::ChangeFrame(frameNames[_frameName]);
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::FrameManager<CharaType>::GetNowFrameName()
{
	if (frameNames.empty())return ChStd::GetZeroChara<CharaType>();

	if (frameNames.size() <= nowFrameNo)return ChStd::GetZeroChara<CharaType>();

	for (auto&& name : frameNames)
	{
		if (name.second != nowFrameNo)continue;

		return name.first;
	}

	return ChStd::GetZeroChara<CharaType>();
}

#endif

#endif