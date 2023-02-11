#ifndef Ch_CPP_D3DOBJ_XAudio2_h
#define Ch_CPP_D3DOBJ_XAudio2_h

struct IMFSourceReader;

struct X3DAUDIO_EMITTER;

struct IXAudio2;
struct IXAudio2SourceVoice;
struct IXAudio2MasteringVoice;
struct IXAudio2SubmixVoice;

struct XAUDIO2_SEND_DESCRIPTOR;
struct XAUDIO2_VOICE_SENDS;

struct X3DAUDIO_LISTENER;
struct X3DAUDIO_DSP_SETTINGS;
typedef unsigned char X3DAUDIO_HANDLE[20];
typedef struct tWAVEFORMATEX WAVEFORMATEX;
struct XAUDIO2_VOICE_DETAILS;

namespace ChD3D
{
	class XAudio2Manager;


	class AudioObject :public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetLoopFlg(const ChStd::Bool _Flg) { loopFlg = _Flg; }

		void SetLoopStartPos(const unsigned long _pos) { loopStartPos = _pos; }

		void SetLoopEndPos(const unsigned long _pos) { loopEndPos = _pos; }

		void SetPlayTime(const unsigned long _Time) { nowPos = _Time; }

		void SetVolume(const float _Volume);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		unsigned long GetLoopStartPos() { return loopStartPos; }

		unsigned long GetLoopEndPos() { return loopEndPos; }

		unsigned long GetPlayTime() { return nowPos; }

		float GetVolume();

		///////////////////////////////////////////////////////////////////////////////////

		void Play();

		///////////////////////////////////////////////////////////////////////////////////

		void Pause();

		///////////////////////////////////////////////////////////////////////////////////

		void Stop();

		///////////////////////////////////////////////////////////////////////////////////

		friend XAudio2Manager;


	protected:

		virtual void Init() { Release(); }

		IXAudio2SourceVoice* voice = nullptr;
		std::string fileName = "";
		ChStd::Bool loopFlg = false;
		unsigned long nowPos = 1;
		unsigned long loopStartPos = 0;
		unsigned long loopEndPos = -1;

	};


	class X3DAudioObject :public AudioObject
	{

	public :

		friend XAudio2Manager;

		void Init()override;

		void Release()override;

		inline void SetPosition(const ChVec3& _pos) { mat.SetPosition(_pos); }

		inline void SetRotation(const ChVec3& _rot) { mat.SetRotation(_rot); }

		X3DAUDIO_EMITTER* GetEmitter();


	private:

		X3DAUDIO_EMITTER* emitter = nullptr;
		ChLMat mat;

	};

	struct ChXAUDIO2_BUFFER :public XAUDIO2_BUFFER
	{
		std::vector<unsigned char> audioDataVector;
	};

	class XAudio2Manager:public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		friend AudioObject;
		friend X3DAudioObject;

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init();

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPosition(const ChVec3& _pos)
		{
			mat.SetPosition(_pos);
		}

		inline void SetRotation(const ChVec3& _dir)
		{
			mat.SetRotation(_dir);
		}

	public://Load Functions//

		void LoadStart();

		void LoadEnd();

		void LoadSound(AudioObject& _object,const std::string& _str);

	public://Update Function//

		void Update();

	private:

		void Update3DAudios(AudioObject* _audio);

		void UpdateBGMAudios(AudioObject* _audio);

		struct MFObject
		{
			IMFSourceReader* reader = nullptr;
			
			WAVEFORMATEX* waveFormat = nullptr;
		};

		ChStd::Bool CreateMFObject(const std::string& _fileName);

		ChStd::Bool CreateFileData(const std::string& _fileName);

		XAudio2Manager(){}
		
		std::map<std::string, std::vector<ChPtr::Shared<XAUDIO2_BUFFER>>>audioDataMap;
		std::map<std::string, ChPtr::Shared<MFObject>>mfObjectMap;

		ChStd::Bool loadFlg = false;

		std::vector<AudioObject*>audios;
		IXAudio2* audio = nullptr;
		IXAudio2SubmixVoice* subMixAudio = nullptr;
		IXAudio2MasteringVoice* audioMV = nullptr;
		XAUDIO2_SEND_DESCRIPTOR* sender = nullptr;
		XAUDIO2_VOICE_SENDS* sendList = nullptr;

		//3DAudioŠÖ˜A//
		X3DAUDIO_LISTENER* listener = nullptr;
		X3DAUDIO_DSP_SETTINGS* dspSettings = nullptr;
		X3DAUDIO_HANDLE X3DInstance;
		XAUDIO2_VOICE_DETAILS* details;
		std::vector<float>matrix;

		ChLMat mat;

	public:

		static XAudio2Manager& GetIns()
		{
			static XAudio2Manager ins;
			return ins;
		}

	};

	static std::function<XAudio2Manager& ()>XAudioManager = XAudio2Manager::GetIns;


}

#endif