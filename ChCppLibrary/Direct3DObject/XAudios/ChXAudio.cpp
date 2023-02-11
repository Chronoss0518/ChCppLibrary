#include<Windows.h>

#include<xaudio2.h>
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

	voice->SubmitSourceBuffer(XAudioManager().audioDataMap[fileName][0].get());
	voice->SubmitSourceBuffer(XAudioManager().audioDataMap[fileName][1].get());

	nowPos = 1;

}

///////////////////////////////////////////////////////////////////////////////////

void AudioObject::Release()
{
	if (!*this)return;

	voice->Stop();

	voice->DestroyVoice();

	voice = nullptr;

	auto& audios = XAudioManager().audios;

	auto thiss = std::find(audios.begin(), audios.end(), this);

	audios.erase(thiss);

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void XAudio2Manager::Init()
{
	if (*this)return;

	XAudio2Create(&audio, 0, XAUDIO2_DEFAULT_PROCESSOR);


	if (audio == nullptr)return;

	audio->CreateMasteringVoice(&audioMV);

	SetInitFlg(true);

}

///////////////////////////////////////////////////////////////////////////////////

void XAudio2Manager::Release()
{

	if (!*this)return;

	LoadEnd();

	audioDataMap.clear();

	for (auto&& aObject : audios)
	{
		aObject->Release();
	}

	for (auto&& waveFormat : mfObjectMap)
	{
		CoTaskMemFree(waveFormat.second->waveFormat);

		waveFormat.second->reader->Release();
	}

	mfObjectMap.clear();

	audios.clear();

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

void XAudio2Manager::LoadSound(AudioObject* _object, const std::string& _fileName)
{
	if (ChPtr::NullCheck(_object))return;
	if (!loadFlg)return;

	if(!CreateMFObject(_fileName))return;
	if(!CreateFileData(_fileName))return;

	auto mfObject = mfObjectMap[_fileName];
	auto fileDatas = audioDataMap[_fileName];

	audio->CreateSourceVoice(&_object->voice, mfObject->waveFormat);

	_object->voice->SubmitSourceBuffer(fileDatas[0].get());
	_object->voice->SubmitSourceBuffer(fileDatas[1].get());

	_object->fileName = _fileName;

	_object->SetInitFlg(true);

	audios.push_back(_object);
}

ChStd::Bool XAudio2Manager::CreateMFObject(const std::string& _fileName)
{

	if (mfObjectMap.find(_fileName) != mfObjectMap.end())return true;

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

ChStd::Bool XAudio2Manager::CreateFileData(const std::string& _fileName)
{
	if (audioDataMap.find(_fileName) != audioDataMap.end())return true;

	DWORD streamFlg = 0;
	LONGLONG streamLen = 0;

	auto mfObject = mfObjectMap[_fileName];
	std::vector<ChPtr::Shared<XAUDIO2_BUFFER>> fileDatas;

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

		auto fileData = ChPtr::Make_S<ChXAUDIO2_BUFFER>();

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

	for (auto&& audio : audios)
	{

		audio->loopEndPos = audio->loopEndPos >= audioDataMap[audio->fileName].size() ? audioDataMap[audio->fileName].size() : audio->loopEndPos;

		audio->loopStartPos = audio->loopStartPos >= audio->loopEndPos ? 0 : audio->loopStartPos;


		XAUDIO2_VOICE_STATE state;
		audio->voice->GetState(&state);

		if (state.BuffersQueued >= 2)continue;
		ChStd::Bool loopFlg = false;
		unsigned long nowPos = 0;
		nowPos = audio->nowPos + 1 >= audio->loopEndPos ? audio->loopStartPos : audio->nowPos + 1;
		
		if (nowPos <= 0)loopFlg = true;

		if (!audio->loopFlg && loopFlg)continue;

		audio->nowPos = nowPos;

		audio->voice->SubmitSourceBuffer(audioDataMap[audio->fileName][nowPos].get());

	}

}