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
		inline virtual ~SendDataClass(){}
	};
	struct SaveDataClass{
		inline virtual ~SaveDataClass() {}
	};

	class FrameList
	{
	public:

		FrameList();

		virtual ~FrameList();

	public:

#ifdef CRT
		//自作フレームをセット//
		//BaseFrameを継承しているもののみセットできる//
		template<class T>
		typename std::enable_if<std::is_base_of<BaseFrame, T>::value, void>::type SetFrame()
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
		static typename std::enable_if<std::is_base_of<BaseFrame, T>::value, ChPtr::Weak<T>>::type GetNowFrame()
		{
			return ChPtr::SharedSafeCast<T>(GetNowFrame());
		}

		void SetSendData(ChPtr::Shared<SendDataClass> _sendData) { value->sendData = _sendData; }

#endif

		unsigned long GetNowFrameNo() { return nowFrameNo; }

		unsigned long GetRegisterFrameCount();

	public://UpdateFunction//

		void Update();

	public://Release Funciton//

		void Release();

	public://Other Function

#ifdef CRT
		inline void SaveData(ChPtr::Shared<SaveDataClass> _save)
		{
			value->saveData = _save;
		}

		inline ChPtr::Shared<SaveDataClass> GetData()
		{
			return value->saveData;
		}

		template<class T>
		typename std::enable_if<std::is_base_of<SaveDataClass, T>::value, ChPtr::Shared<T>>::type GetData()
		{
			return value->saveData;
		}
#endif

	protected://Other Function

		void ChangeFrame(const unsigned long _frameNo);

		void Changes();

	protected://Static Functions//

#ifdef CRT
		static ChPtr::Shared<BaseFrame>& GetNowFrame()
		{
			static ChPtr::Shared<BaseFrame> ins = nullptr;
			return ins;
		}
#endif

	private:

		struct FrameListCRT
		{
#ifdef CRT
			ChPtr::Shared<SaveDataClass> saveData = nullptr;
			ChPtr::Shared<SendDataClass> sendData = nullptr;

			ChPtr::Shared<BaseFrame>nextFrame = nullptr;

			std::vector<std::function<ChPtr::Shared<BaseFrame>()>>frameList;
#endif

		};

	protected:// Member Value//


		friend BaseFrame;

		unsigned long nextFrameNo = -1;
		unsigned long nowFrameNo = -1;

		FrameListCRT* value = nullptr;

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
			if (value->frameNames.find(_useFrameName) != frameNames.end())
			{
				//ChSystem::ErrerMessage("このフレームはすでに登録されています", "警告");

				return;
			}

			unsigned long no = frameList.size();

			value->frameNames[_useFrameName] = no;

			FrameList::SetFrame<T>();
		}
#endif

	public://Get Function//

#ifdef CRT
		template<class T>
		typename std::enable_if
			<std::is_base_of<BaseFrame, T>::value, ChPtr::Weak<T>>::type GetNowFrame()
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
		inline void SaveData(ChPtr::Shared<SaveDataClass> _save)
		{
			FrameList::SaveData(_save);
		}

		inline ChPtr::Shared<SaveDataClass> GetData()
		{
			return FrameList::GetData();
		}

		void ChangeFrame(const std::basic_string<CharaType>& _frameName);
#endif

	private:// Member Value//

		friend BaseFrame;

		struct FrameManagerCRT
		{
#ifdef CRT
			std::map<std::basic_string<CharaType>, unsigned long>frameNames;
#endif
		};

		FrameManagerCRT* value = nullptr;

	private://ConstructerDestructer//

		FrameManager();

		~FrameManager();

	public://Get Instance//

		inline static FrameManager& GetIns()
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
		inline void SaveData(ChPtr::Shared<SaveDataClass> _save)
		{
			if (ChPtr::NullCheck(mgr))return;
			mgr->SaveData(_save);
		}

		inline ChPtr::Shared<SaveDataClass> GetData()
		{
			if (ChPtr::NullCheck(mgr))return nullptr;
			return mgr->GetData();
		}

		inline void SendData(ChPtr::Shared<SendDataClass> _send)
		{
			if (ChPtr::NullCheck(mgr))return;
			mgr->SetSendData(_send);
		}
#endif
		//登録されているフレームに移動する//
		inline void ChangeFrame(const unsigned long _frameNo)
		{
			mgr->ChangeFrame(_frameNo);
		}

	private://Other Functions//

		inline void SetManager(FrameList* _mgr) { mgr = _mgr; }

	protected://ConstructerDestructer//

		inline BaseFrame() {};

		inline virtual ~BaseFrame() { Release(); };

	private:

		FrameList* mgr;

	};
}
#ifdef CRT


ChCpp::FrameList::FrameList()
{
	value = new FrameListCRT();
};

ChCpp::FrameList::~FrameList()
{
	Release();

	delete value;
}

void ChCpp::FrameList::Release()
{
	value->saveData = nullptr;
	value->sendData = nullptr;

	value->nextFrame = nullptr;
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
	if (value->frameList.size() <= _frameNo)return;

	value->nextFrame = value->frameList[_frameNo]();

	nextFrameNo = _frameNo;

	value->nextFrame->SetManager(this);
}

void ChCpp::FrameList::Changes()
{
	if (value->nextFrame == nullptr)return;

	auto&& nowframe = GetNowFrame();
	if (nowframe != nullptr)
	{
		nowframe->Release();
	}

	nowFrameNo = nextFrameNo;
	nowframe = value->nextFrame;

	nowframe->Init(value->sendData.get());
	value->sendData = nullptr;

	value->nextFrame = nullptr;
	nextFrameNo = -1;
}

unsigned long ChCpp::FrameList::GetRegisterFrameCount() { return value->frameList.size(); }

template<typename CharaType>
void ChCpp::FrameManager<CharaType>::ChangeFrame(const std::basic_string<CharaType>& _frameName)
{
	auto&& frameName = value->frameNames.find(_frameName);

	if (frameName == value->frameNames.end())return;

	FrameList::ChangeFrame(frameName.second);
}

template<typename CharaType>
ChCpp::FrameManager<CharaType>::FrameManager()
{
	value = new FrameManagerCRT();
}

template<typename CharaType>
ChCpp::FrameManager<CharaType>::~FrameManager()
{
	delete value;
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