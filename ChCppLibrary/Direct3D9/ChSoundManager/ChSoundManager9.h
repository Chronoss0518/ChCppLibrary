
#ifndef Ch_D3D9_SoMa_h
#define Ch_D3D9_SoMa_h

namespace ChSound
{
	typedef class BackGroundMusic8 BGM8;
	typedef class SoundEffect8 SE8;

	class SoundManager8:public ChCp::Initializer
	{
	public:

		void Init(const HWND _hWin);

		inline virtual void Release()
		{
			if (ChPtr::NotNullCheck(soundDevice))
			{
				soundDevice->Release();
				soundDevice = nullptr;
			}
			SetInitFlg(false);
		}

	protected:

		WAVEFORMATEX SetWaveFormat();

		SoundManager8(){}

		virtual ~SoundManager8()
		{
			Release();
		}


		LPDIRECTSOUND8 soundDevice = nullptr;
		LPDIRECTSOUNDBUFFER8 mainBuffer = nullptr;
		LPDIRECTSOUND3DLISTENER8 lpSListener = nullptr;//リスナー(聞く人)//

		std::map<std::string, ChPtr::Shared<BGM8>>musicList;

		std::map<std::string, ChPtr::Shared<SE8>>seList;

	};

}

#endif
