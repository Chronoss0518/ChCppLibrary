
#ifndef Ch_Game_BaseSystem_h
#define Ch_Game_BaseSystem_h

namespace ChSystem
{
	class SystemManager;

	class BaseSystem : public ChCp::Initializer
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetSystemManager(const SystemManager* _own)
		{
			system = const_cast<SystemManager*>(_own);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Windの横幅サイズ取得//
		const inline unsigned int GetWindWidth()const { return windSize.w; }

		//Windの立幅サイズ取得//
		const inline unsigned int GetWindHeight()const { return windSize.h; }

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		virtual bool IsPushKey(const int _key);

		virtual bool IsPushKeyNoHold(const int _key);

		virtual bool IsPause(const int _key);

		virtual bool IsUpdate() { return false; };

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		virtual inline void MouseUpdate() {}

		virtual inline unsigned long GetNowTime() { return 0; }

		///////////////////////////////////////////////////////////////////////////////////

		inline virtual void ErrerMessage(
			const std::string& _mainStr
			, const std::string& _subStr)
		{
			std::cerr << _mainStr;
		};

	protected:

		SystemManager* system = nullptr;

		ChMath::Vector2Base<unsigned long> windSize;

		ChCpp::BitBool buttonList;
		ChCpp::BitBool isNowPush;

		//Pause用変数//
		bool nowKey = false;
		bool pauseFlg = false;

	};

	class SystemManager :public ChCp::Initializer
	{
	public:

		friend BaseSystem;

		///////////////////////////////////////////////////////////////////////////////////s
		//InitiarizeAndRelease//

		//初期化を行う(戻り値は、マネージャーが扱うシステムのPointer)//
		template<class C>
		auto Init()
			->typename std::enable_if
			<std::is_base_of<BaseSystem,C>::value
			&& !std::is_same<BaseSystem,C>::value, C* const>::type
		{
			if (*this)return nullptr;

			if (ChPtr::NotNullCheck(baseSystems))delete baseSystems;
			baseSystems = nullptr;

			baseSystems = new C();
			baseSystems->SetSystemManager(this);

			SetInitFlg(true);

			return ChPtr::SafeCast<C>(baseSystems);
		}

		inline virtual void Release()
		{
			if (!*this)return;

			if (ChPtr::NotNullCheck(baseSystems))delete baseSystems;
			baseSystems = nullptr;

			SetInitFlg(false);
		}

		///////////////////////////////////////////////////////////////////////////////////s
		//SetFunction//

		//全体で利用するFPSを管理//
		inline void SetFPS(const unsigned long _FPS) { FPS = _FPS; }

		inline void SetNowTime(const unsigned long _time) { lastFPSPoint = _time; }

		inline void SetUseSystemButtons(const bool _button) { useSystemButton = _button; }

		///////////////////////////////////////////////////////////////////////////////////s
		//GetFunction//

		//FPSカウントの取得//
		const inline unsigned long GetFPS() const { return FPS; }

		const inline long double GetNowFPSPoint()const { return lastFPSPoint; }

		//ウィンドシステム(BaseSystem継承)を取得する//
		template<class T>
		auto GetSystem()->
			typename std::enable_if
			<std::is_base_of<BaseSystem, T>::value, T* const>::type
		{
			return ChPtr::SafeCast<T>(baseSystems);
		}

		///////////////////////////////////////////////////////////////////////////////////s
		//IsFunction//

		//BaseSystemより間接的に確認する//
		inline bool IsPushKey(const int _key)
		{
			if (!*this)return false;
			if (baseSystems == nullptr)return false;
			return baseSystems->IsPushKey(_key);
		}

		//BaseSystemより間接的に確認する//
		inline bool IsPushKeyNoHold(const int _key)
		{
			if (!*this)return false;
			if (baseSystems == nullptr)return false;
			return baseSystems->IsPushKeyNoHold(_key);

		}

		//BaseSystemより間接的に確認する//
		inline bool IsPause(const int _key)
		{
			if (!*this)return false;
			if (baseSystems == nullptr)return false;
			return baseSystems->IsPause(_key);

		}

		//システムを継続するか//
		bool IsUpdate()
		{
			if (baseSystems == nullptr)return false;

			return baseSystems->IsUpdate();
		}

		//システムで提供されているボタンを利用するか//
		bool IsUseSystemButtons() { return useSystemButton; }

		///////////////////////////////////////////////////////////////////////////////////s

		//FPS処理
		inline bool FPSProcess()
		{
			if (!*this)return false;
			if (baseSystems == nullptr)return false;

			unsigned long nowTime = baseSystems->GetNowTime();
			unsigned long tmp = nowTime - lastFPSTime;

			if (tmp < 1000 / FPS)return false;

			lastFPSPoint = 1000 / tmp;
			lastFPSTime = nowTime;

			return true;
		}

	private:

		BaseSystem* baseSystems = nullptr;

		SystemManager() {}

		virtual ~SystemManager()
		{
			Release();
		}

		unsigned long FPS = 60;
		long double lastFPSPoint = 0;
		unsigned long lastFPSTime = 0;

		bool useSystemButton = true;

	public:

		static SystemManager& GetIns()
		{

			static SystemManager ins;

			return ins;
		}


	};

	static const std::function<SystemManager & ()>SysManager = SystemManager::GetIns;

}

#endif