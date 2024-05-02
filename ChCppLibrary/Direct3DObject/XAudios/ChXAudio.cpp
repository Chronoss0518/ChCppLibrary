#include<Windows.h>

#include<xaudio2.h>
#include<x3daudio.h>
#include<DirectXMath.h>
#include<mfapi.h>
#include <windows.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <stdio.h>
#include <mferror.h>
#include<mfreadwrite.h>

#pragma comment(lib,"xaudio2.lib")
#pragma comment(lib,"mfplat.lib")
#pragma comment(lib,"mfreadwrite.lib")
#pragma comment(lib,"mfuuid.lib")

#include"../../BaseIncluder/ChBase.h"

#include"ChXAudio.h"

using namespace ChD3D;

#define USE_SUBMIX_VOICE_FLG 1

#define BASE_LENGTH 1000.0f

struct ChXAUDIO2_BUFFER :public XAUDIO2_BUFFER
{
	std::vector<unsigned char> audioDataVector;
};

///////////////////////////////////////////////////////////////////////////////////

void AudioObject::SetVolume(const float _Volume)
{
	if (!*this)return;
	voice->SetVolume(_Volume);
}

///////////////////////////////////////////////////////////////////////////////////

float AudioObject::GetVolume()
{
	float outVol = 0.0f;

	if (!*this)return outVol;

	voice->GetVolume(&outVol);

	return outVol;
}

///////////////////////////////////////////////////////////////////////////////////

void AudioObject::Play()
{
	if (!*this)return;

	voice->Start(0);

}

///////////////////////////////////////////////////////////////////////////////////

void AudioObject::Pause()
{

	if (!*this)return;

	voice->Stop();
	
}

///////////////////////////////////////////////////////////////////////////////////

void AudioObject::Stop()
{
	if (!*this)return;

	voice->Stop();

	voice->FlushSourceBuffers();

	voice->SubmitSourceBuffer(XAudioManager().audioDataMap[fileName][0]);
	voice->SubmitSourceBuffer(XAudioManager().audioDataMap[fileName][1]);

	nowPos = 1;

}

///////////////////////////////////////////////////////////////////////////////////

void AudioObject::Release()
{
	if (!*this)return;

	auto&& audios = XAudioManager().audios;

	auto&& thiss = std::find(audios.begin(), audios.end(), this);

	audios.erase(thiss);

	voice->Stop();

	voice->DestroyVoice();

	voice = nullptr;

	SetInitFlg(false);
}

void X3DAudioObject::Init()
{
	Release();

	emitter = new X3DAUDIO_EMITTER();
	ChStd::MZero(emitter);

	emitter->ChannelCount = 1;
	emitter->CurveDistanceScaler = emitter->DopplerScaler = 1.0f;
	emitter->pCone = nullptr;
}

void X3DAudioObject::Release()
{
	if (ChPtr::NullCheck(emitter))return;

	AudioObject::Release();

	delete emitter;
	emitter = nullptr;
}

X3DAUDIO_EMITTER* X3DAudioObject::GetEmitter()
{
	if (ChPtr::NullCheck(emitter))return emitter;

	auto zDirection = mat.GetZAxisDirection();
	auto yDirection = mat.GetYAxisDirection();

	zDirection.Normalize();
	yDirection.Normalize();

	ChVec3 pos = mat.GetPosition();
	emitter->OrientFront = zDirection;
	emitter->OrientTop = yDirection;
	emitter->Position = pos;

	emitter->Velocity = pos - beforePos;

	return emitter;
}

void XAudio2Manager::Init()
{
	if (*this)return;

	XAudio2Create(&audio, 0, XAUDIO2_DEFAULT_PROCESSOR);

	if (ChPtr::NullCheck(audio))
	{
		Release();
		return;
	}

	audio->CreateMasteringVoice(&audioMV);

	if (ChPtr::NullCheck(audioMV))
	{
		Release();
		return;
	}
	DWORD dwChannelMask;
	audioMV->GetChannelMask(&dwChannelMask);
	//X3DAudioInitialize(dwChannelMask, X3DAUDIO_SPEED_OF_SOUND, X3DInstance);
	X3DAudioInitialize(dwChannelMask, X3DAUDIO_SPEED_OF_SOUND * 0.01f, X3DInstance);

	details = new XAUDIO2_VOICE_DETAILS();

	audioMV->GetVoiceDetails(details);

	matrix.resize(details->InputChannels);

	listener = new X3DAUDIO_LISTENER();

#if USE_SUBMIX_VOICE_FLG

	audio->CreateSubmixVoice(&subMixAudio, 1, 44100, 0, 0, 0, 0);
	sender = new XAUDIO2_SEND_DESCRIPTOR();
	sender->Flags = 0;
	sender->pOutputVoice = subMixAudio;
	sendList = new XAUDIO2_VOICE_SENDS();
	sendList->SendCount = 1;
	sendList->pSends = sender;

#endif
	SetInitFlg(true);

}

///////////////////////////////////////////////////////////////////////////////////

void XAudio2Manager::Release()
{

	if (!*this)return;

	LoadEnd();

	for (auto&& aObject : audios)
	{
		aObject->Release();
	}

	for (auto&& waveFormat : mfObjectMap)
	{
		CoTaskMemFree(waveFormat.second->waveFormat);

		waveFormat.second->reader->Release();
	}

	for (auto&& audioDatas : audioDataMap)
	{
		for (auto&& audioData : audioDatas.second)
		{
			delete audioData;
		}
	}

	audioDataMap.clear();

	mfObjectMap.clear();

	audios.clear();

	if (ChPtr::NotNullCheck(listener)) { delete listener; listener = nullptr; }
	if (ChPtr::NotNullCheck(details)) { delete details; details = nullptr; }

#if USE_SUBMIX_VOICE_FLG

	if (ChPtr::NotNullCheck(subMixAudio)) { subMixAudio->DestroyVoice(); subMixAudio = nullptr; }
	if (ChPtr::NotNullCheck(sender)) { delete sender; sender = nullptr; }
	if (ChPtr::NotNullCheck(sendList)) { delete sendList; sendList = nullptr; }

#endif

	if (ChPtr::NotNullCheck(audioMV)) { audioMV->DestroyVoice(); audioMV = nullptr; };
	if (ChPtr::NotNullCheck(audio)) { audio->Release(); audio = nullptr; };

	SetInitFlg(false);

}

void XAudio2Manager::LoadStart()
{
	if (loadFlg)return;

	MFStartup(MF_VERSION);

	(void)CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	loadFlg = true;
}

void XAudio2Manager::LoadEnd()
{
	if (!loadFlg)return;

	MFShutdown();

	loadFlg = false;
}

void XAudio2Manager::LoadSound(AudioObject& _object, const std::string& _fileName)
{
	if (ChPtr::NullCheck(&_object))return;

	if(!CreateMFObject(_fileName))return;
	if(!CreateFileData(_fileName))return;

	_object.Init();

	auto mfObject = mfObjectMap[_fileName];
	auto fileDatas = audioDataMap[_fileName];

#if USE_SUBMIX_VOICE_FLG

	audio->CreateSourceVoice(&_object.voice, mfObject->waveFormat, 0, 2.0f, 0, sendList);

#else

	audio->CreateSourceVoice(&_object.voice, mfObject->waveFormat);

#endif

	_object.voice->SubmitSourceBuffer(fileDatas[0]);
	_object.voice->SubmitSourceBuffer(fileDatas[1]);

	_object.fileName = _fileName;

	_object.SetInitFlg(true);

	audios.push_back(&_object);
}

bool XAudio2Manager::CreateMFObject(const std::string& _fileName)
{

	if (mfObjectMap.find(_fileName) != mfObjectMap.end())return true;

	if (!loadFlg)return false;

	auto mfObject = ChPtr::Make_S<MFObject>();
	MFCreateSourceReaderFromURL(
		ChStr::UTF8ToWString(_fileName).c_str(),
		nullptr,
		&mfObject->reader);

	if (ChPtr::NullCheck(mfObject->reader))
	{
		return false;
	}


	IMFMediaType* mType = nullptr;
	MFCreateMediaType(&mType);

	mType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	mType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);

	mfObject->reader->SetCurrentMediaType((MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, mType);

	mType->Release();

	mfObject->reader->GetCurrentMediaType((MF_SOURCE_READER_FIRST_AUDIO_STREAM), &mType);

	UINT32 size = 0;

	MFCreateWaveFormatExFromMFMediaType(mType, &mfObject->waveFormat, &size);


	mType->Release();
	mfObjectMap[_fileName] = mfObject;

	return true;
}

bool XAudio2Manager::CreateFileData(const std::string& _fileName)
{
	if (audioDataMap.find(_fileName) != audioDataMap.end())return true;

	if (!loadFlg)return false;

	DWORD streamFlg = 0;
	LONGLONG streamLen = 0;

	auto mfObject = mfObjectMap[_fileName];
	std::vector<XAUDIO2_BUFFER*> fileDatas;

	while (true)
	{
		IMFSample* sample;

		mfObject->reader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &streamFlg, &streamLen, &sample);


		if (ChPtr::NullCheck(sample))break;

		IMFMediaBuffer* mediaBuffer;

		sample->ConvertToContiguousBuffer(&mediaBuffer);

		BYTE* Data;

		DWORD maxStreamLen;
		DWORD currentLen;

		mediaBuffer->GetMaxLength(&maxStreamLen);
		mediaBuffer->GetCurrentLength(&currentLen);

		mediaBuffer->Lock(&Data, &maxStreamLen, &currentLen);

		auto fileData = new ChXAUDIO2_BUFFER();

		for (DWORD i = 0; i < maxStreamLen; i++)
		{
			fileData->audioDataVector.push_back(Data[i]);
		}

		fileData->AudioBytes = maxStreamLen;
		fileData->pAudioData = &fileData->audioDataVector[0];
		fileData->Flags = XAUDIO2_END_OF_STREAM;

		fileDatas.push_back(fileData);

		mediaBuffer->Unlock();

		mediaBuffer->Release();

		sample->Release();
	}

	audioDataMap[_fileName] = fileDatas;
	return true;
}

void XAudio2Manager::Update()
{
	
	auto zDirection = mat.GetZAxisDirection();
	auto yDirection = mat.GetYAxisDirection();

	zDirection.Normalize();
	yDirection.Normalize();

	ChVec3 pos = mat.GetPosition();

	listener->OrientFront = zDirection;
	listener->OrientTop = yDirection;
	listener->Position = pos;
	listener->Velocity = pos - beforePos;

	for (auto&& audio = audios.begin() ; audio != audios.end();audio)
	{

		if (ChPtr::NullCheck(*audio))
		{
			audio = audios.erase(audio);
			continue;
		}
		Update3DAudios(*audio);
		UpdateBGMAudios(*audio);
		audio++;
	}

}

void XAudio2Manager::Update3DAudios(AudioObject* _audio)
{
	auto audio = ChPtr::SafeCast<X3DAudioObject>(_audio);
	if (ChPtr::NullCheck(audio))return;

	X3DAUDIO_DSP_SETTINGS dspSettings;

	dspSettings.SrcChannelCount = 1;
	dspSettings.DstChannelCount = details->InputChannels;
	dspSettings.pMatrixCoefficients = &matrix[0];

	auto&& emitter = audio->GetEmitter();

	auto ePos = emitter->Position;
	emitter->Position.x *= BASE_LENGTH;
	emitter->Position.y *= BASE_LENGTH;
	emitter->Position.z *= BASE_LENGTH;
	auto lPos = listener->Position;
	listener->Position.x *= BASE_LENGTH;
	listener->Position.y *= BASE_LENGTH;
	listener->Position.z *= BASE_LENGTH;

	X3DAudioCalculate(X3DInstance, listener, emitter,
		X3DAUDIO_CALCULATE_MATRIX | 
		X3DAUDIO_CALCULATE_DOPPLER | 
		X3DAUDIO_CALCULATE_LPF_DIRECT | 
		X3DAUDIO_CALCULATE_REVERB | 
		X3DAUDIO_CALCULATE_EMITTER_ANGLE |
		X3DAUDIO_CALCULATE_DOPPLER,
		&dspSettings);

	emitter->Position = ePos;
	listener->Position = lPos;

	audio->voice->SetOutputMatrix(audioMV, 1, details->InputChannels, dspSettings.pMatrixCoefficients);
	audio->voice->SetFrequencyRatio(dspSettings.DopplerFactor);

#if USE_SUBMIX_VOICE_FLG

	audio->voice->SetOutputMatrix(audioMV, 1, 1, &dspSettings.ReverbLevel);

#endif

	XAUDIO2_FILTER_PARAMETERS FilterParameters = { LowPassFilter, 2.0f * sinf(X3DAUDIO_PI / 6.0f * dspSettings.LPFDirectCoefficient), 1.0f };
	audio->voice->SetFilterParameters(&FilterParameters);

}

void XAudio2Manager::UpdateBGMAudios(AudioObject* _audio)
{
	auto audio = _audio;

	audio->loopEndPos = audio->loopEndPos >= audioDataMap[audio->fileName].size() ? audioDataMap[audio->fileName].size() : audio->loopEndPos;

	audio->loopStartPos = audio->loopStartPos >= audio->loopEndPos ? 0 : audio->loopStartPos;

	XAUDIO2_VOICE_STATE state;
	audio->voice->GetState(&state);

	if (state.BuffersQueued >= 2)return;
	bool loopFlg = false;
	unsigned long nowPos = 0;
	nowPos = audio->nowPos + 1 >= audio->loopEndPos ? audio->loopStartPos : audio->nowPos + 1;

	if (nowPos <= 0)loopFlg = true;

	if (!audio->loopFlg && loopFlg)return;

	audio->nowPos = nowPos;

	audio->voice->SubmitSourceBuffer(audioDataMap[audio->fileName][nowPos]);

}
