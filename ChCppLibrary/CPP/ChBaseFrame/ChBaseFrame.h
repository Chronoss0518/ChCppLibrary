#ifndef Ch_CPP_BaFr_h
#define Ch_CPP_BaFr_h

#include"../../CRTPack/ChMapPack/ChMapPack.h"
#include"../../CRTPack/ChVectorPack/ChVectorPack.h"
#include"../../CRTPack/ChSmartPtrPack/ChSmartPtrPack.h"

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
			virtual ChCRT::SharedPtrPack<BaseFrame> CreateMethod() { return ChCRT::NullPtr(); };
		};

#ifdef CRT
		template<class Frame>
		class FrameCreateMethod : public FrameCreateMethodBase
		{
		public:
			ChCRT::SharedPtrPack<BaseFrame> CreateMethod()override
			{
				return ChPtr::Make_S<Frame>();
			}
		};

#endif


	public:

		inline virtual ~FrameList()
		{
			Release();
		}


	public:

#ifdef CRT
		//自作フレームをセット//
		//BaseFrameを継承しているもののみセットできる//
		template<class T>
		typename std::enable_if<std::is_base_of<BaseFrame, T>::value, void>::type SetFrame()
		{
			frameList.Push(ChPtr::Make_S<FrameCreateMethod<T>>());

			if (frameList.GetSize() > 1)return;

			ChangeFrame(0);

			Changes();
		}

		void SetSendData(ChPtr::Shared<SendDataClass> _sendData) { sendData = _sendData; }

#endif

	public:

		size_t GetNowFrameNo()const { return nowFrameNo; }

#ifdef CRT
		template<class T>
		static typename std::enable_if<std::is_base_of<BaseFrame, T>::value, ChPtr::Weak<T>>::type GetNowFrame()
		{
			return ChPtr::SharedSafeCast<T>(GetNowFrame());
		}
#endif
		inline size_t GetRegisterFrameCount()const { return frameList.GetSize(); }

	public://UpdateFunction//

		void Update();

	public://Release Funciton//

		void Release();

	public://Other Function
#ifdef CRT
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
#endif

	protected://Other Function

		void ChangeFrame(const unsigned long _frameNo);

		void Changes();

	protected://Static Functions//

		static ChCRT::SharedPtrPack<BaseFrame>& GetNowFrame()
		{
			static ChCRT::SharedPtrPack<BaseFrame> ins = ChCRT::NullPtr();
			return ins;
		}

	protected:// Member Value//


		friend BaseFrame;

		size_t nextFrameNo = -1;
		size_t nowFrameNo = -1;

		ChCRT::SharedPtrPack<SaveDataClass> saveData = ChCRT::NullPtr();
		ChCRT::SharedPtrPack<SendDataClass> sendData = ChCRT::NullPtr();

		ChCRT::SharedPtrPack<BaseFrame>nextFrame = ChCRT::NullPtr();

		ChCRT::VectorPack<ChCRT::SharedPtrPack<FrameCreateMethodBase>>frameList;

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
			std::map<ChCRT::StringPack<CharaType>>tmpFrameNames = frameNames;
			if (tmpFrameNames.find(_useFrameName) != tmpFrameNames.end())
			{
				//ChSystem::ErrerMessage("このフレームはすでに登録されています", "警告");
				return;
			}

			unsigned long no = frameList.GetSize();

			tmpFrameNames[_useFrameName] = no;

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

		inline unsigned long GetRegisterFrameCount() { return FrameList::GetRegisterFrameCount(); }
#endif

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

		template<typename CharaType>
		inline void ChangeFrame(const std::basic_string<CharaType>& _frameName)
		{
			auto&& frameName = frameNames.Find(_frameName);

			if (ChPtr::NullCheck(frameName))return;

			FrameList::ChangeFrame(*frameName);
		}

		template<typename CharaType>
		inline std::basic_string<CharaType> GetNowFrameName()
		{
			std::map<ChCRT::StringPack<CharaType>, unsigned long>tmpFrameNames = frameNames;
			if (tmpFrameNames.empty())return ChStd::GetZeroChara<CharaType>();
			if (tmpFrameNames.size() <= nowFrameNo)return ChStd::GetZeroChara<CharaType>();

			for (auto&& name : tmpFrameNames)
			{
				if (name.second != nowFrameNo)continue;
				return name.first;
			}

			return ChStd::GetZeroChara<CharaType>();
		}

#endif

	private:// Member Value//

		friend BaseFrame;

		ChCRT::MapPack<ChCRT::StringPack<CharaType>, unsigned long>frameNames;

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

		virtual inline void Init(SendDataClass* _sendData) {};

		virtual inline void Release() {};

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

		FrameList* mgr = nullptr;

	};
}


#endif