#ifndef Ch_D3DOBJ_XAudio2_h
#define Ch_D3DOBJ_XAudio2_h


#include<xaudio2.h>

struct IMFSourceReader;

struct X3DAUDIO_EMITTER;

struct IXAudio2;
struct IXAudio2SourceVoice;
struct IXAudio2MasteringVoice;
struct IXAudio2SubmixVoice;

struct XAUDIO2_SEND_DESCRIPTOR;
struct XAUDIO2_VOICE_SENDS;

struct X3DAUDIO_LISTENER;
typedef unsigned char X3DAUDIO_HANDLE[20];
typedef struct tWAVEFORMATEX WAVEFORMATEX;
struct XAUDIO2_VOICE_DETAILS;

namespace ChD3D
{
	class XAudio2Manager;

	class AudioObject :public ChCp::Initializer
	{
	public:

		friend XAudio2Manager;

	public:

		struct AudioObjectCRT
		{
#ifdef CRT
			std::wstring fileName = L"";
#endif
		};

	public:

		AudioObject();

		virtual ~AudioObject();

	public://Init And Release//

		virtual void Release();

	public://Set Functions//

		void SetLoopFlg(const bool _Flg) { loopFlg = _Flg; }

		void SetLoopStartPos(const unsigned long _pos) { loopStartPos = _pos; }

		void SetLoopEndPos(const unsigned long _pos) { loopEndPos = _pos; }

		void SetPlayTime(const unsigned long _Time) { nowPos = _Time; }

		void SetVolume(const float _Volume);

		void SetFileName(const wchar_t* _fileName);

	public://Get Functions//

		unsigned long GetLoopStartPos() { return loopStartPos; }

		unsigned long GetLoopEndPos() { return loopEndPos; }

		unsigned long GetPlayTime() { return nowPos; }

		float GetVolume();

		const wchar_t* GetFileName();

	public:

		virtual void Update();

	public:

		void Play();

		void Pause();

		void Stop();

	protected:

		virtual void Init() { Release(); }

		IXAudio2SourceVoice* voice = nullptr;
		bool loopFlg = false;
		unsigned long nowPos = 1;
		unsigned long loopStartPos = 0;
		unsigned long loopEndPos = -1;

		AudioObjectCRT& ValueIns() { return *value; }

		XAudio2Manager* manager = nullptr;

	private:

		AudioObjectCRT* value = nullptr;

	};

	class X3DAudioObject :public AudioObject
	{
	public:

		friend XAudio2Manager;

	public:

		virtual ~X3DAudioObject()
		{
			Release();
		}

	public :

		void Init()override;

		inline void InitPosition(const ChVec3& _pos)
		{
			mat.Identity();
			mat.SetPosition(_pos);
			beforePos = mat.GetPosition();
		}

		inline void InitMatrix(const ChLMat& _mat)
		{
			mat = _mat;
			beforePos = mat.GetPosition();
		}

		void Release()override;

	public:

		inline void SetPosition(const ChVec3& _pos) 
		{
			beforePos = mat.GetPosition();
			mat.SetPosition(_pos); 
		}

		inline void SetRotation(const ChQua& _rot)
		{
			mat.SetRotation(_rot);
		}

		inline void SetMatrix(const ChLMat& _mat)
		{
			beforePos = mat.GetPosition();
			mat = _mat;
		}

	public:

		X3DAUDIO_EMITTER* GetEmitter();

		inline ChVec3 GetPosition() { return mat.GetPosition(); }

	public:

		void Update()override;

	private:

		X3DAUDIO_EMITTER* emitter = nullptr;
		ChLMat mat;
		ChVec3 beforePos;
	};

	class XAudio2Manager:public ChCp::Initializer
	{
	public:

		friend AudioObject;
		friend X3DAudioObject;

	private:

		struct MFObject
		{
			IMFSourceReader* reader = nullptr;

			WAVEFORMATEX* waveFormat = nullptr;
		};

#ifdef CRT

		struct ChXAUDIO2_BUFFER :public XAUDIO2_BUFFER
		{
			std::vector<unsigned char> audioDataVector;
		};

#endif

	public:

		struct XAudio2ManagerCRT
		{
#ifdef CRT
			std::map<std::wstring, std::vector<XAUDIO2_BUFFER*>>audioDataMap;
			std::map<std::wstring, ChPtr::Shared<MFObject>>mfObjectMap;

			std::vector<AudioObject*>audios;
			std::vector<float>matrix;
#endif
		};

	private:

		XAudio2Manager();

		virtual ~XAudio2Manager();

	public://Init And Release//

		void Init();

		inline void InitPosition(const ChVec3& _pos)
		{
			mat.Identity();
			mat.SetPosition(_pos);
			beforePos = mat.GetPosition();
		}

		inline void InitMatrix(const ChLMat& _mat)
		{
			mat = _mat;
			beforePos = mat.GetPosition();
		}

		virtual void Release();

	private:

		bool MFObjectInit(const wchar_t* _key, MFObject& _target);

		void CRTRelease();

		void MFObjectRelease(MFObject& _target);

	public://Set Functions//

		inline void SetMatrix(const ChLMat& _mat)
		{
			beforePos = mat.GetPosition();
			mat = _mat;
		}

		inline void SetPosition(const ChVec3& _pos)
		{
			beforePos = mat.GetPosition();
			mat.SetPosition(_pos);
		}

		inline void SetRotation(const ChQua& _dir)
		{
			mat.SetRotation(_dir);
		}

	public://Get Functions//

		inline ChVec3 GetPosition() { return mat.GetPosition(); }

	public://Load Functions//

		void LoadStart();

		void LoadEnd();

#ifdef CRT
		void LoadSound(AudioObject& _object, const std::wstring& _str)
		{
			LoadSoundBase(_object, _str.c_str());
		}
#endif

	private:

		void LoadSoundBase(AudioObject& _object, const wchar_t* _str);

	public://Update Function//

		void Update();

	private:

		bool CreateMFObject(const wchar_t* _fileName);

		bool CreateFileData(const wchar_t* _fileName);

	private:

		XAUDIO2_BUFFER* LoadBuffers(MFObject* _MFObj);

		XAUDIO2_BUFFER* SetBuffer(BYTE* _data, unsigned long _maxStreamLen);

		bool ContainAudioData(const wchar_t* _key);

		ChStd::SizeType GetAudioDataCount(const wchar_t* _key);

		MFObject* CreateMFObjectPtr(const wchar_t* _key);

		bool ContainMFObject(const wchar_t* _key);

		MFObject* GetMFObject(const wchar_t* _key);

		void SubmitSourceBuffer(IXAudio2SourceVoice* _voice,const wchar_t* _filename, ChStd::SizeType _num);

		void AddAudios(AudioObject* _obj);

		void RemoveAudios(AudioObject* _obj);

		void UpdateAudios();

		float* GetMatrix();

		void ResizeMatrix(ChStd::SizeType _num);

	private:

		bool loadFlg = false;

		IXAudio2* audio = nullptr;
		IXAudio2MasteringVoice* audioMV = nullptr;
		IXAudio2SubmixVoice* subMixAudio = nullptr;
		XAUDIO2_SEND_DESCRIPTOR* sender = nullptr;
		XAUDIO2_VOICE_SENDS* sendList = nullptr;

		//3DAudioŠÖ˜A//
		X3DAUDIO_LISTENER* listener = nullptr;
		X3DAUDIO_HANDLE X3DInstance;
		XAUDIO2_VOICE_DETAILS* details = nullptr;

		ChLMat mat;
		ChVec3 beforePos;

		XAudio2ManagerCRT* value = nullptr;

	public:

		static XAudio2Manager& GetIns()
		{
			static XAudio2Manager ins;
			return ins;
		}

	};

	inline XAudio2Manager& XAudioManager() { return XAudio2Manager::GetIns(); }
}

#ifdef CRT

ChD3D::AudioObject::AudioObject()
{
	value = new AudioObjectCRT();
}

ChD3D::AudioObject::~AudioObject()
{
	Release();
	delete value;
}

void ChD3D::AudioObject::SetFileName(const wchar_t* _fileName)
{
	value->fileName = _fileName;
}

const wchar_t* ChD3D::AudioObject::GetFileName()
{
	return value->fileName.c_str();
}

ChD3D::XAudio2Manager::XAudio2Manager()
{
	value = new XAudio2ManagerCRT();
}

ChD3D::XAudio2Manager::~XAudio2Manager()
{
	Release();
	delete value;
}

ChStd::SizeType ChD3D::XAudio2Manager::GetAudioDataCount(const wchar_t* _key)
{
	auto&& data = value->audioDataMap.find(_key);
	if (data == value->audioDataMap.end())return 0;
	return data->second.size();
}

bool ChD3D::XAudio2Manager::ContainAudioData(const wchar_t* _key)
{
	return  value->audioDataMap.find(_key) != value->audioDataMap.end();
}

ChD3D::XAudio2Manager::MFObject* ChD3D::XAudio2Manager::CreateMFObjectPtr(const wchar_t* _key)
{
	auto&& mfObject = ChPtr::Make_S<MFObject>();

	if (!MFObjectInit(_key, *mfObject))
		return nullptr;

	value->mfObjectMap[_key] = mfObject;

	return mfObject.get();
}

bool ChD3D::XAudio2Manager::CreateFileData(const wchar_t* _fileName)
{
	if (ContainAudioData(_fileName))return true;

	if (!loadFlg)return false;


	std::vector<XAUDIO2_BUFFER*> fileDatas;

	auto&& mfObject = GetMFObject(_fileName);

	ChXAUDIO2_BUFFER* fileData = static_cast<ChXAUDIO2_BUFFER*>(LoadBuffers(mfObject));

	while (ChPtr::NotNullCheck(fileData))
	{
		fileDatas.push_back(fileData);

		fileData = static_cast<ChXAUDIO2_BUFFER*>(LoadBuffers(mfObject));
	}

	value->audioDataMap[_fileName] = fileDatas;
	return true;
}

XAUDIO2_BUFFER* ChD3D::XAudio2Manager::SetBuffer(BYTE* _data, unsigned long _maxStreamLen)
{
	auto fileData = new ChXAUDIO2_BUFFER();

	for (DWORD i = 0; i < _maxStreamLen; i++)
	{
		unsigned char data = _data[i];
		fileData->audioDataVector.push_back(data);
	}

	fileData->AudioBytes = _maxStreamLen;
	fileData->pAudioData = &fileData->audioDataVector[0];
	fileData->Flags = XAUDIO2_END_OF_STREAM;

	return fileData;
}

ChD3D::XAudio2Manager::MFObject* ChD3D::XAudio2Manager::GetMFObject(const wchar_t* _key)
{
	auto&& obj = value->mfObjectMap.find(_key);

	if (obj == value->mfObjectMap.end())return nullptr;
	return obj->second.get();
}

bool ChD3D::XAudio2Manager::ContainMFObject(const wchar_t* _key)
{
	return value->mfObjectMap.find(_key) != value->mfObjectMap.end();
}

void ChD3D::XAudio2Manager::SubmitSourceBuffer(IXAudio2SourceVoice* _voice, const wchar_t* _filename, ChStd::SizeType _num)
{
	if (ChPtr::NullCheck(_voice))return;
	if (ChPtr::NullCheck(_filename))return;
	auto&& audioData = value->audioDataMap.find(_filename);
	if (audioData == value->audioDataMap.end())return;
	if (audioData->second.size() <= _num)return;

	_voice->SubmitSourceBuffer(audioData->second[_num]);
}

void ChD3D::XAudio2Manager::AddAudios(AudioObject* _obj)
{
	value->audios.push_back(_obj);
}

void ChD3D::XAudio2Manager::RemoveAudios(AudioObject* _obj)
{
	auto&& audios = value->audios;

	auto&& thiss = std::find(audios.begin(), audios.end(), _obj);

	audios.erase(thiss);
}

void ChD3D::XAudio2Manager::UpdateAudios()
{
	for (auto&& audio = value->audios.begin(); audio != value->audios.end(); audio)
	{
		if (ChPtr::NullCheck(*audio))
		{
			audio = value->audios.erase(audio);
			continue;
		}
		(*audio)->Update();

		audio++;
	}
}

float* ChD3D::XAudio2Manager::GetMatrix()
{
	return &value->matrix[0];
}

void ChD3D::XAudio2Manager::ResizeMatrix(ChStd::SizeType _num)
{
	value->matrix.resize(_num);
}

void ChD3D::XAudio2Manager::CRTRelease()
{
	for (auto&& aObject : value->audios)
	{
		aObject->Release();
	}

	for (auto&& waveFormat : value->mfObjectMap)
	{
		MFObjectRelease(*waveFormat.second);
	}

	for (auto&& audioDatas : value->audioDataMap)
	{
		for (auto&& audioData : audioDatas.second)
		{
			delete audioData;
		}
	}

	value->audioDataMap.clear();

	value->mfObjectMap.clear();

	value->audios.clear();

}

#endif

#endif