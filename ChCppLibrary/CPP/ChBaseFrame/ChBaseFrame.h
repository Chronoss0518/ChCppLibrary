#ifndef Ch_CPP_BaFr_h
#define Ch_CPP_BaFr_h

#include<memory>
#include<vector>
#include<map>

#include"../../BaseIncluder/ChBase.h"

namespace ChCpp
{

	class BaseFrame;

	struct SendDataClass {
		inline virtual ~SendDataClass() {}
	};
	struct SaveDataClass {
		inline virtual ~SaveDataClass() {}
	};

	class FrameList
	{
	public:


		class FrameCreateMethodBase
		{
		public:
			virtual ChPtr::Shared<BaseFrame> CreateMethod() { return nullptr; };
		};

		template<class Frame>
		class FrameCreateMethod : public FrameCreateMethodBase
		{
		public:
			ChPtr::Shared<BaseFrame> CreateMethod()override
			{
				return ChPtr::Make_S<Frame>();
			}
		};

	public:

		inline virtual ~FrameList()
		{
			Release();
		}


	public:

		//自作フレームをセット//
		//BaseFrameを継承しているもののみセットできる//
		template<class T>
		typename std::enable_if<std::is_base_of<BaseFrame, T>::value, void>::type SetFrame()
		{
			frameList.push_back(ChPtr::Make_S<FrameCreateMethod<T>>());

			if (frameList.size() > 1)return;

			ChangeFrame(0);

			Changes();
		}

		void SetSendData(ChPtr::Shared<SendDataClass> _sendData) { sendData = _sendData; }

	public:

		size_t GetNowFrameNo()const { return nowFrameNo; }

		template<class T>
		static typename std::enable_if<std::is_base_of<BaseFrame, T>::value, ChPtr::Weak<T>>::type GetNowFrame()
		{
			return ChPtr::SharedSafeCast<T>(GetNowFrame());
		}

		inline size_t GetRegisterFrameCount()const { return frameList.size(); }

	public://UpdateFunction//

		void Update();

	public://Release Funciton//

		void Release();

	public://Other Function

		inline void SaveData(ChPtr::Shared<SaveDataClass> _save)
		{
			saveData = _save;
		}

		inline ChPtr::Shared<SaveDataClass> GetData()
		{
			return saveData;
		}

		template<class T>
		inline typename std::enable_if<std::is_base_of<SaveDataClass, T>::value, ChPtr::Shared<T>>::type GetData()
		{
			return ChPtr::SharedSafeCast<T>(saveData);
		}

	protected://Other Function

		void ChangeFrame(const unsigned long _frameNo);

		void Changes();

	protected://Static Functions//

		static ChPtr::Shared<BaseFrame>& GetNowFrame()
		{
			static ChPtr::Shared<BaseFrame> ins = nullptr;
			return ins;
		}

	protected:// Member Value//


		friend BaseFrame;

		size_t nextFrameNo = -1;
		size_t nowFrameNo = -1;

		ChPtr::Shared<SaveDataClass> saveData = nullptr;
		ChPtr::Shared<SendDataClass> sendData = nullptr;

		ChPtr::Shared<BaseFrame>nextFrame = nullptr;

		std::vector<ChPtr::Shared<FrameCreateMethodBase>>frameList;

	};


	//BaseFrame管理用クラス//
	template<typename CharaType>
	class FrameManager :protected FrameList
	{
	public://Set Function//

		//自作フレームをセット//
		//BaseFrameを継承しているもののみセットできる//
		template<class T>
		void SetFrame(typename std::enable_if
			<std::is_base_of<BaseFrame, T>::value, const std::basic_string<CharaType>&>::type _useFrameName)
		{
			auto&& frame = frameNames.find(_useFrameName);
			if (frame != frameNames.end())
			{
				//ChSystem::ErrerMessage("このフレームはすでに登録されています", "警告");
				return;
			}

			unsigned long no = frameList.size();

			frame->second = no;

			FrameList::SetFrame<T>();
		}

	public://Get Function//

		template<class T>
		typename std::enable_if
			<std::is_base_of<BaseFrame, T>::value, ChPtr::Weak<T>>::type GetNowFrame()
		{
			return ChPtr::SharedSafeCast<T, BaseFrame>(FrameList::GetNowFrame());
		}

		inline std::basic_string<CharaType> GetNowFrameName()
		{
			std::map<std::basic_string<CharaType>, unsigned long>tmpFrameNames = frameNames;
			if (tmpFrameNames.empty())return ChStd::GetZeroChara<CharaType>();
			if (tmpFrameNames.size() <= nowFrameNo)return ChStd::GetZeroChara<CharaType>();

			for (auto&& name : tmpFrameNames)
			{
				if (name.second != nowFrameNo)continue;
				return name.first;
			}

			return ChStd::GetZeroChara<CharaType>();
		}

		inline unsigned long GetRegisterFrameCount() { return FrameList::GetRegisterFrameCount(); }

	public://Update Function//

		inline void Update() { FrameList::Update(); }

	public://Other Functions//

		inline void SaveData(ChPtr::Shared<SaveDataClass> _save)
		{
			FrameList::SaveData(_save);
		}

		inline ChPtr::Shared<SaveDataClass> GetData()
		{
			return FrameList::GetData();
		}

		inline void ChangeFrame(const std::basic_string<CharaType>& _frameName)
		{
			auto&& frameName = frameNames.find(_frameName);

			if (frameName == frameNames.end())return;

			FrameList::ChangeFrame(frameName->second);
		}

	private:// Member Value//

		friend BaseFrame;

		std::map<std::basic_string<CharaType>, unsigned long>frameNames;

	private://ConstructerDestructer//

		FrameManager() {}

		~FrameManager() {}

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

		virtual inline void Init(ChPtr::Shared<SendDataClass> _sendData) {};

		virtual inline void Release() {};

	public://Update Function//

		virtual void Update() = 0;

	public:

		friend FrameList;

	protected://Other Functions//

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

		FrameList* mgr = nullptr;

	};
}


#endif