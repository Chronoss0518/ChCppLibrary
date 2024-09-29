
#ifndef Ch_CPP_BaseSystem_h
#define Ch_CPP_BaseSystem_h

#include"../../BasePack/ChPtr.h"
#include"../../BasePack/ChMath3D.h"

#include"../../CPP/ChBitBool/ChBitBool.h"
#include"../../ClassParts/ChCPInitializer.h"

namespace ChSystem
{
	class SystemManager;

	class BaseSystem : public ChCp::Initializer
	{
	public:

		friend SystemManager;

	protected:

		BaseSystem() {}

		virtual ~BaseSystem()
		{
			Release();
		}

	public:

		virtual void Release() {};

	public://Set Functions//

		inline void SetUseSystemButtons(const bool _button) { useSystemButtonFlg = _button; }

		//�S�̂ŗ��p����FPS���Ǘ�//
		inline void SetFPS(const unsigned long _FPS) { FPS = _FPS; }

		inline void SetNowTime(const unsigned long _time) { lastFPSPoint = _time; }
	
	protected://Set Functions//

		virtual void SetKeyCode() = 0;

	public://Get Functions//

		//Wind�̉����T�C�Y�擾//
		const inline unsigned int GetWindWidth()const { return windSize.w; }

		//Wind�̗����T�C�Y�擾//
		const inline unsigned int GetWindHeight()const { return windSize.h; }

		//FPS�J�E���g�̎擾//
		const inline unsigned long GetFPS() const { return FPS; }

		const inline long double GetNowFPSPoint()const { return lastFPSPoint; }

	public://Is Functions//

		//�L�[���������ۂ̃`�F�b�N���s���֐�//
		bool IsPushKey(const int _key);

		//�L�[���������ۂɒ��������܂񂾂̃`�F�b�N���s���֐�//
		bool IsPushKeyNoHold(const int _key);

		//�|�[�Y�����ǂ����𔻒f����֐��B//
		//�������̓|�[�Y�ֈڍs����{�^��//
		//�߂�l��True�������ꍇ�̓|�[�Y��//
		bool IsPause(const int _key);

		virtual bool IsUpdate() { return false; };

		//�V�X�e���Œ񋟂���Ă���{�^���𗘗p���邩//
		bool IsUseSystemButtons() { return useSystemButtonFlg; }

	public://Update Functions//

		virtual inline void MouseUpdate() {}

		virtual inline unsigned long GetNowTime() { return 0; }
	
	public://Other Functions//

		//FPS����
		inline bool FPSProcess()
		{
			if (!*this)return false;

			unsigned long nowTime = GetNowTime();
			unsigned long tmp = nowTime - lastFPSTime;

			if (tmp < 1000 / FPS)return false;

			lastFPSPoint = 1000 / tmp;
			lastFPSTime = nowTime;

			return true;
		}

	protected:

		ChMath::Vector2Base<unsigned long> windSize;

		bool useSystemButtonFlg = true;

		//Pause�p�ϐ�//
		bool nowKey = false;
		bool pauseFlg = false;

		unsigned long FPS = 60;
		long double lastFPSPoint = 0;
		unsigned long lastFPSTime = 0;

		ChCpp::BitBool buttonList;
		ChCpp::BitBool isNowPush;

	};

	class SystemManager :public ChCp::Initializer
	{
	public:

		friend BaseSystem;
	
	public://Init And Release//

		//���������s��(�߂�l�́A�}�l�[�W���[�������V�X�e����Pointer)//
		template<class C>
		typename std::enable_if
			<std::is_base_of<BaseSystem, C>::value
			&& !std::is_same<BaseSystem, C>::value, C* const>::type Init()
		{
			if (*this)return nullptr;

			baseSystems = nullptr;

			baseSystems = ChPtr::Make_S<C>();
			SetInitFlg(true);

			return ChPtr::SafeCast<C>(baseSystems.get());
		}

		virtual void Release();
	
	public://SetFunction//

		//�S�̂ŗ��p����FPS���Ǘ�//
		inline void SetFPS(const unsigned long _FPS) { if (baseSystems != nullptr)baseSystems->SetFPS(_FPS); }

		inline void SetNowTime(const unsigned long _time) { if (baseSystems != nullptr)baseSystems->SetNowTime(_time); }

		inline void SetUseSystemButtons(const bool _button) { if(baseSystems != nullptr) baseSystems->SetUseSystemButtons(_button); }

	public://GetFunction//

		//FPS�J�E���g�̎擾//
		const inline unsigned long GetFPS() const { return baseSystems != nullptr ? baseSystems->GetFPS() : 0; }

		const inline long double GetNowFPSPoint()const { return baseSystems != nullptr ? baseSystems->GetNowFPSPoint() : 0; }

		//�E�B���h�V�X�e��(BaseSystem�p��)���擾����//
		template<class T>
		auto GetSystem() ->
			typename std::enable_if
			<std::is_base_of<BaseSystem, T>::value, T* const>::type
		{
			return ChPtr::SafeCast<T>(baseSystems);
		}

	public://Is Functions//

		//BaseSystem���ԐړI�Ɋm�F����//
		inline bool IsPushKey(const int _key)
		{
			if (!*this)return false;
			if (baseSystems == nullptr)return false;
			return baseSystems->IsPushKey(_key);
		}

		//BaseSystem���ԐړI�Ɋm�F����//
		inline bool IsPushKeyNoHold(const int _key)
		{
			if (!*this)return false;
			if (baseSystems == nullptr)return false;
			return baseSystems->IsPushKeyNoHold(_key);
		}

		//BaseSystem���ԐړI�Ɋm�F����//
		inline bool IsPause(const int _key)
		{
			if (!*this)return false;
			if (baseSystems == nullptr)return false;
			return baseSystems->IsPause(_key);

		}

		//�V�X�e�����p�����邩//
		inline bool IsUpdate()
		{
			if (baseSystems == nullptr)return false;
			return baseSystems->IsUpdate();
		}

		//�V�X�e���Œ񋟂���Ă���{�^���𗘗p���邩//
		bool IsUseSystemButtons() { return baseSystems != nullptr ? baseSystems->IsUseSystemButtons() : false; }

	public://Other Functions//

		//FPS����
		inline bool FPSProcess()
		{
			if (!*this)return false;
			if (baseSystems == nullptr)return false;

			return baseSystems->FPSProcess();
		}

	private:

		ChPtr::Shared<BaseSystem> baseSystems = nullptr;

		SystemManager() {}

		~SystemManager()
		{
			Release();
		}
	public:

		static SystemManager& GetIns()
		{
			static SystemManager ins;

			return ins;
		}

	};
	inline SystemManager& SysManager() { return SystemManager::GetIns(); };
}

#endif