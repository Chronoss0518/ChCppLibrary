#ifndef Ch_D3D9_DiSo_h
#define Ch_D3D9_DiSo_h


#include"ChSoundData.h"

//���󂯎�蕨//-----------------------------------------------------------------------------
// File: WavRead.h
//
// Desc: Support for loading and playing Wave files using DirectSound sound
//       buffers.
//
// Copyright (c) 1999 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Name: class CWaveSoundRead
// Desc: A class to read in sound data from a Wave file
//-----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////

//(���ǕK)//
//�匳�̃T�E���h�̖��O�Ƃ͕ʂɃX�g�b�v�p��No�������Ă���//
class ChDirectSound9 :public ChCp::Initializer
{
public://Init And Release//

	void Init(HWND _hWnd);

	virtual void Release();

public://Set Functions//

	//���X�i�[�̈ʒu���X�V�p//
	void SetListenerPos(const ChVec3_9 *_pos)
	{
		listenerPos = (ChVec3_9*)_pos;
	}

#ifdef CRT
	//�g�p����f�B���N�g���̃p�X���Z�b�g//
	void SetUseDirectory(
		const std::string _soundDirectoryName,
		const std::string _useSoundDirectory)
	{
		if (directoryPathList.find(_useSoundDirectory) != directoryPathList.end())return;

		directoryPathList.insert(std::pair<std::string, std::string>(_useSoundDirectory, _soundDirectoryName));
	}

	//��ɓo�^���Ă���Directory�𗘗p����BGM���Z�b�g//
	void SetBGMSound(
		const std::string _soundName,
		const std::string _soundFilePath,
		const std::string _useSoundDirectory)
	{
		if (mainSoundList.find(_soundName) != mainSoundList.end())return;

		std::string tmpString = _soundFilePath;

		if (tmpString.length() <= 0)return;

		if (directoryPathList.find(_useSoundDirectory)
			!= directoryPathList.end())
		{
			tmpString = directoryPathList[_useSoundDirectory] + '/' + tmpString;
		}

		auto bgm = ChPtr::Make_S<ChMainSound9>();

		if (bgm == nullptr)return;

		LoadSound(bgm->sound, bgm->dSound, tmpString.c_str(), tmpString.length());

		bgm->dSound->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);

		bgm->sound->GetFrequency(&bgm->hz);

		bgm->sound->GetVolume(&bgm->vol);

		mainSoundList.insert(std::pair<std::string, ChPtr::Shared<ChBGM9>>(_soundName, bgm));

}


	//��ɓo�^���Ă���Directory�𗘗p����SE���Z�b�g//
	unsigned short SetSESound(
		const std::string _soundFilePath,
		const std::string _useSoundDirectory)
	{
		if (subSoundList.size() >= maxSE)return 0;

		std::string tmpString = _soundFilePath;

		if (tmpString.length() <= 0)return 0;

		unsigned short tmpData = 0;
		while (1)
		{
			if (subSoundList.find(seNo) == subSoundList.end())break;
			++seNo %= maxSE;
			if (seNo == 0)seNo = 1;
}

		tmpData = seNo;

		if (directoryPathList.find(_useSoundDirectory)
			!= directoryPathList.end())
		{
			tmpString = directoryPathList[_useSoundDirectory] + '/' + tmpString;
		}
		ChPtr::Shared<ChSubSound9> se = nullptr;
		se = ChPtr::Make_S<ChSubSound9>();
		LoadSound(se->sound, se->dSound, tmpString.c_str(), tmpString.length());

		se->sound->GetFrequency(&se->hz);

		se->sound->GetVolume(&se->vol);

		subSoundList.insert(std::pair<unsigned short, ChPtr::Shared<ChSE9>>(tmpData, se));

		return tmpData;
}

	//�Z�b�g���ꂽBGM��Hz��ύX//
	inline void SetHzForBGM(const std::string _soundName, const DWORD _hz)
	{
		if (mainSoundList.find(_soundName) == mainSoundList.end())return;
		mainSoundList[_soundName]->sound->SetFrequency(_hz);
	}

	//�Z�b�g���ꂽBGM��Volume��ύX//
	inline void SetVolumeForBGM(const std::string _soundName, const long _volume)
	{
		if (mainSoundList.find(_soundName) == mainSoundList.end())return;
		mainSoundList[_soundName]->sound->SetVolume(_volume);
	}

	//�Z�b�g���ꂽBGM��Hz��ǂݍ��񂾍ۂ̃T�C�Y�ɖ߂�//
	inline void SetBaseHzForBGM(const std::string _soundName)
	{
		if (mainSoundList.find(_soundName) == mainSoundList.end())return;
		mainSoundList[_soundName]->sound->SetFrequency(mainSoundList[_soundName]->hz);
	}

	//�Z�b�g���ꂽBGM��Volume��ǂݍ��񂾍ۂ̃T�C�Y�ɖ߂�//
	inline void SetBaseVolumeForBGM(const std::string _soundName)
	{
		if (mainSoundList.find(_soundName) == mainSoundList.end())return;
		mainSoundList[_soundName]->sound->SetVolume(mainSoundList[_soundName]->vol);
	}
#endif

	//�Z�b�g���ꂽSE��Hz��ύX//
	void SetHzForSE(const unsigned short _soundNo, const DWORD _hz);

	//�Z�b�g���ꂽSE��Volume��ύX//
	void SetVolumeForSE(const unsigned short _soundNo, const long _volume);

	//�Z�b�g���ꂽSE��Hz��ǂݍ��񂾍ۂ̃T�C�Y�ɖ߂�//
	void SetBaseHzForSE(const unsigned short _soundNo);

	//�Z�b�g���ꂽSE��Volume��ǂݍ��񂾍ۂ̃T�C�Y�ɖ߂�//
	void SetBaseVolumeForSE(const unsigned short _soundNo);

protected://Sound List Functions//

	ChSubSound9* GetSubSound(const unsigned short _soundNo);

	unsigned short GetSubSoundListCount();

	ChSubSound9* GetPlaySubSound(const unsigned short _soundNo);

	unsigned short GetPlaySubSoundListCount();

	void RemovePlaySubSound(const unsigned short _soundNo);

public://Update Functions//

	//�~�܂��Ă���ꎞ�g�p��SE�����//
	void Update();

public://Other Functions//

	//�Z�b�g���ꂽBGM�����ׂĉ��//
	void ClearBGM();

	//�o�^���ɕێ��������l��SE�f�[�^���������//
	void ClearSE(const unsigned short _soundNo);

	//�Z�b�g���ꂽBGM�����ׂĉ��//
	void ClearSE();

	//�o�^���ɕێ��������l��SE���Đ�����//
	void PlaySE(const unsigned short _soundNo);

#ifdef CRT
	//�Z�b�g���ꂽBGM���Đ�//
	void PlayBGM(const std::string _soundName);

	//����SE���Đ�����(Update���\�b�h��ݒu����K�v������)//
	void PlaySE(
		const std::string _soundName,
		const std::string _useSoundDirectory,
		const ChVec3_9* _soundPos);
#endif
	//���ݍĐ����Ă���BGM���~�߂�//
	void StopBGM();

	//�o�^���ɕێ��������l��SE���~�߂�//
	void StopSE(const unsigned short _soundNo);

protected://Other Functions//

	void CreatePrimaryBuffer(HWND _hWnd);

	void LoadSound(
		LPDIRECTSOUNDBUFFER8& _lpSound,
		LPDIRECTSOUND3DBUFFER8& _lp3DSound,
		const char* _soundFileName,
		unsigned long _soundFileNameLength);

	protected://Member Value//

	LPDIRECTSOUND3DLISTENER8 lpSListener;//���X�i�[(�����l)//
	LPDIRECTSOUNDBUFFER primary;
	LPDIRECTSOUND8 lpDS;
	ChVec3_9* listenerPos;
	const float listenerBaseLen = 0.3f;

	const unsigned short maxSE = 10000;

	unsigned short seNo = 1;

#ifdef CRT
	//UserData//
	std::map<std::string, std::string> directoryPathList;

	std::map<std::string, ChPtr::Shared<ChMainSound9>>mainSoundList;
	std::map<unsigned short, ChPtr::Shared<ChSubSound9>>subSoundList;

	std::vector<ChPtr::Shared<ChSubSound9>>playSubSoundList;

	std::string mainSoundName = "";
#endif

protected://ConstructerDestructer//

	ChDirectSound9() {};

	virtual ~ChDirectSound9() { Release(); };

public:

	static ChDirectSound9& GetIns()
	{
		static ChDirectSound9 ins;
		return ins;
	}

};

inline ChDirectSound9& ChDSound9() { return ChDirectSound9::GetIns(); }

#ifdef CRT

void ChDirectSound9::Release()
{
	if (!mainSoundList.empty())mainSoundList.clear();
	if (!subSoundList.empty())subSoundList.clear();

	if (primary != nullptr)
	{
		primary->Release();
		primary = nullptr;
	}

	if (lpDS != nullptr)
	{
		lpDS->Release();
		lpDS = nullptr;
	}

	CoUninitialize();

	SetInitFlg(false);
}

ChSubSound9* ChDirectSound9::GetSubSound(const unsigned short _soundNo)
{
	auto&& it = subSoundList.find(_soundNo);
	if (it == subSoundList.end())return nullptr;
	return it->second.get();
}

unsigned short ChDirectSound9::GetSubSoundListCount()
{
	return subSoundList.size();
}

ChSubSound9* ChDirectSound9::GetPlaySubSound(const unsigned short _soundNo)
{
	if (playSubSoundList.size() <= _soundNo)return nullptr;
	return playSubSoundList[_soundNo].get();
}

unsigned short ChDirectSound9::GetPlaySubSoundListCount()
{
	return static_cast<unsigned short>(playSubSoundList.size());
}

void ChDirectSound9::RemovePlaySubSound(const unsigned short _soundNo)
{
	if (playSubSoundList.size() <= _soundNo)return;
	playSubSoundList.erase(playSubSoundList.begin() + _soundNo);
}

void ChDirectSound9::ClearBGM()
{
	if (mainSoundList.empty())return;
	StopBGM();
	mainSoundList.clear();
}

void ChDirectSound9::ClearSE(const unsigned short _soundNo)
{
	if (subSoundList.empty())return;
	if (subSoundList.find(_soundNo) == subSoundList.end())return;
	subSoundList.erase(_soundNo);
}

void ChDirectSound9::ClearSE()
{
	if (subSoundList.empty())return;
	subSoundList.clear();
}

void ChDirectSound9::PlayBGM(const std::string _soundName)
{
	if (mainSoundList.find(_soundName) == mainSoundList.end())return;
	StopBGM();
	mainSoundName = _soundName;

	mainSoundList[_soundName]->sound->SetCurrentPosition(0);
	mainSoundList[_soundName]->sound->Play(0, 0, DSBPLAY_LOOPING);

	return;
}

void ChDirectSound9::PlaySE(
	const std::string _soundName,
	const std::string _useSoundDirectory,
	const ChVec3_9* _soundPos)
{
	std::string tmpString = _soundName;

	if (tmpString.length() <= 0)return;

	if (directoryPathList.find(_useSoundDirectory)
		!= directoryPathList.end())
	{
		tmpString = directoryPathList[_useSoundDirectory] + '/' + tmpString;
	}

	auto se = ChPtr::Make_S<ChSubSound9>();
	LoadSound(se->sound, se->dSound, tmpString.c_str(), tmpString.length());

	if (ChPtr::NotNullCheck(_soundPos))
	{
		se->dSound->SetPosition(_soundPos->x
			, _soundPos->y
			, _soundPos->z
			, DS3D_IMMEDIATE);
	}

	se->sound->SetCurrentPosition(0);
	se->sound->Play(0, 0, 0);

	playSubSoundList.push_back(se);

}

void ChDirectSound9::StopBGM()
{
	if (mainSoundName.length() <= 0)return;

	DWORD Flg;
	mainSoundList[mainSoundName]->sound->GetStatus(&Flg);
	if ((Flg & DSBSTATUS_PLAYING) != 0)
	{
		mainSoundList[mainSoundName]->sound->Stop();
	}
	mainSoundName = "";
}

#endif

#endif