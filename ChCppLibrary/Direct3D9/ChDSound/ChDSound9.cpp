
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"ChSoundData.h"
#include"ChDSound9.h"

///////////////////////////////////////////////////////////////////////////////////////
//ChDirectSound9メソッド
///////////////////////////////////////////////////////////////////////////////////////

template<typename CharaType>
void ChDirectSound9<CharaType>::Release()
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

template<typename CharaType>
ChSubSound9* ChDirectSound9<CharaType>::GetSubSound(const unsigned short _soundNo)
{
	auto&& it = subSoundList.find(_soundNo);
	if (it == subSoundList.end())return nullptr;
	return it->second.get();
}

template<typename CharaType>
unsigned short ChDirectSound9<CharaType>::GetSubSoundListCount()
{
	return subSoundList.size();
}

template<typename CharaType>
ChSubSound9* ChDirectSound9<CharaType>::GetPlaySubSound(const unsigned short _soundNo)
{
	if (playSubSoundList.size() <= _soundNo)return nullptr;
	return playSubSoundList[_soundNo].get();
}

template<typename CharaType>
unsigned short ChDirectSound9<CharaType>::GetPlaySubSoundListCount()
{
	return static_cast<unsigned short>(playSubSoundList.size());
}

template<typename CharaType>
void ChDirectSound9<CharaType>::RemovePlaySubSound(const unsigned short _soundNo)
{
	if (playSubSoundList.size() <= _soundNo)return;
	playSubSoundList.erase(playSubSoundList.begin() + _soundNo);
}

template<typename CharaType>
void ChDirectSound9<CharaType>::ClearBGM()
{
	if (mainSoundList.empty())return;
	StopBGM();
	mainSoundList.clear();
}

template<typename CharaType>
void ChDirectSound9<CharaType>::ClearSE(const unsigned short _soundNo)
{
	if (subSoundList.empty())return;
	if (subSoundList.find(_soundNo) == subSoundList.end())return;
	subSoundList.erase(_soundNo);
}

template<typename CharaType>
void ChDirectSound9<CharaType>::ClearSE()
{
	if (subSoundList.empty())return;
	subSoundList.clear();
}

template<typename CharaType>
void ChDirectSound9<CharaType>::PlayBGM(const std::basic_string<CharaType>& _soundName)
{
	if (mainSoundList.find(_soundName) == mainSoundList.end())return;
	StopBGM();
	mainSoundName = _soundName;

	mainSoundList[_soundName]->sound->SetCurrentPosition(0);
	mainSoundList[_soundName]->sound->Play(0, 0, DSBPLAY_LOOPING);

	return;
}

template<typename CharaType>
void ChDirectSound9<CharaType>::PlaySE(
	const std::basic_string<CharaType>& _soundName,
	const std::basic_string<CharaType>& _useSoundDirectory,
	const ChVec3_9* _soundPos)
{
	std::basic_string<CharaType> tmpString = _soundName;

	if (tmpString.length() <= 0)return;

	if (directoryPathList.find(_useSoundDirectory)
		!= directoryPathList.end())
	{
		tmpString = directoryPathList[_useSoundDirectory] + ChStd::GetSlashChara<CharaType>() + tmpString;
	}

	auto se = ChPtr::Make_S<ChSubSound9>();
	LoadSound(se->sound, se->dSound, tmpString.c_str(), tmpString.length());

	if (ChPtr::NotNullCheck(_soundPos))
	{
		se->dSound->SetPosition(_soundPos->x,
			_soundPos->y,
			_soundPos->z,
			DS3D_IMMEDIATE);
	}

	se->sound->SetCurrentPosition(0);
	se->sound->Play(0, 0, 0);

	playSubSoundList.push_back(se);

}

template<typename CharaType>
void ChDirectSound9<CharaType>::StopBGM()
{
	if (mainSoundName.length() <= 0)return;

	DWORD Flg;
	mainSoundList[mainSoundName]->sound->GetStatus(&Flg);
	if ((Flg & DSBSTATUS_PLAYING) != 0)
	{
		mainSoundList[mainSoundName]->sound->Stop();
	}
	mainSoundName = ChStd::GetZeroChara<CharaType>();
}

template<typename CharaType>
void ChDirectSound9<CharaType>::CreatePrimaryBuffer(HWND _hWnd)
{
	DirectSoundCreate8(NULL, &lpDS, NULL);

	//協調レベルを設定
	lpDS->SetCooperativeLevel(_hWnd, DSSCL_PRIORITY);

	// プライマリ・バッファの作成
	// DSBUFFERDESC構造体を設定
	DSBUFFERDESC dsbdesc;
	ChStd::MZero(&dsbdesc);
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	// プライマリ・バッファを指定
	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat = NULL;

	// バッファを作る
	lpDS->CreateSoundBuffer(&dsbdesc, &primary, NULL);

	
	// プライマリ・バッファのWaveフォーマットを設定
	// 　　　優先協調レベル以上の協調レベルが設定されている必要があります．
	WAVEFORMATEX pcmwf;
	ChStd::MZero(&pcmwf);
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = 2;		// ２チャンネル（ステレオ）
	pcmwf.nSamplesPerSec = 88200;	// サンプリング・レート　44.1kHz
	pcmwf.nBlockAlign = 4;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
	pcmwf.wBitsPerSample = 16;		// 16ビット
	primary->SetFormat(&pcmwf);

	CoInitialize(NULL);

	primary->QueryInterface(IID_IDirectSound3DListener8, (LPVOID *)&lpSListener);

	lpSListener->SetRolloffFactor(listenerBaseLen, DS3D_IMMEDIATE);

}

template<typename CharaType>
void ChDirectSound9<CharaType>::LoadSound(
	LPDIRECTSOUNDBUFFER8 &_LpSound,
	LPDIRECTSOUND3DBUFFER8 &_Lp3DSound,
	const char* _soundFileName,
	unsigned long _soundFileNameLength)
{
	HRESULT hr;

	CWaveSoundRead9 waveFile;
	// WAVEファイルを開く
	waveFile.Open(_soundFileName);

	// セカンダリ・バッファを作成する
	// DSBUFFERDESC構造体を設定
	DSBUFFERDESC dsbdesc;
	ChStd::MZero(&dsbdesc);
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);

	//(DSBCAPS_CTRL3D=３Ｄサウンドを使用)
	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRL3D |
		DSBCAPS_CTRLVOLUME | /*DSBCAPS_CTRLPAN |*/ DSBCAPS_CTRLFREQUENCY;
	dsbdesc.dwBufferBytes = waveFile.m_ckIn.cksize;
	dsbdesc.lpwfxFormat = waveFile.m_pwfx;

	//3DサウンドのHELアルゴリズムを選択
	dsbdesc.guid3DAlgorithm = DS3DALG_NO_VIRTUALIZATION;

	//	dsbdesc.guid3DAlgorithm=DS3DALG_DEFAULT;

		// バッファを作る
	LPDIRECTSOUNDBUFFER pDSTmp;
	//	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSData, NULL); 
	lpDS->CreateSoundBuffer(&dsbdesc, &pDSTmp, NULL);
	pDSTmp->QueryInterface(IID_IDirectSoundBuffer8, reinterpret_cast<LPVOID *>(&_LpSound));
	pDSTmp->Release();

	// セカンダリ・バッファにWaveデータを書き込む
	LPVOID lpvPtr1;		// 最初のブロックのポインタ
	DWORD dwBytes1;		// 最初のブロックのサイズ
	LPVOID lpvPtr2;		// ２番目のブロックのポインタ
	DWORD dwBytes2;		// ２番目のブロックのサイズ

	hr = _LpSound->Lock(0, waveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

	// DSERR_BUFFERLOSTが返された場合，Restoreメソッドを使ってバッファを復元する
	if (DSERR_BUFFERLOST == hr)
	{
		_LpSound->Restore();
		hr = _LpSound->Lock(0, waveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
	}
	if (SUCCEEDED(hr))
	{
		// ロック成功

		// ここで，バッファに書き込む
		// バッファにデータをコピーする
		UINT rsize;
		waveFile.Read(dwBytes1, (LPBYTE)lpvPtr1, &rsize);
		if (0 != dwBytes2)
			waveFile.Read(dwBytes2, (LPBYTE)lpvPtr2, &rsize);

		// 書き込みが終わったらすぐにUnlockする．
		hr = _LpSound->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
	}

	//3Dのセカンダリバッファを作る
	_LpSound->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)&_Lp3DSound);
}

template<typename CharaType>
void ChDirectSound9<CharaType>::LoadSound(
	LPDIRECTSOUNDBUFFER8& _LpSound,
	LPDIRECTSOUND3DBUFFER8& _Lp3DSound,
	const wchar_t* _soundFileName,
	unsigned long _soundFileNameLength)
{
	HRESULT hr;

	CWaveSoundRead9 waveFile;
	// WAVEファイルを開く
	waveFile.Open(_soundFileName);

	// セカンダリ・バッファを作成する
	// DSBUFFERDESC構造体を設定
	DSBUFFERDESC dsbdesc;
	ChStd::MZero(&dsbdesc);
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);

	//(DSBCAPS_CTRL3D=３Ｄサウンドを使用)
	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRL3D |
		DSBCAPS_CTRLVOLUME | /*DSBCAPS_CTRLPAN |*/ DSBCAPS_CTRLFREQUENCY;
	dsbdesc.dwBufferBytes = waveFile.m_ckIn.cksize;
	dsbdesc.lpwfxFormat = waveFile.m_pwfx;

	//3DサウンドのHELアルゴリズムを選択
	dsbdesc.guid3DAlgorithm = DS3DALG_NO_VIRTUALIZATION;

	//	dsbdesc.guid3DAlgorithm=DS3DALG_DEFAULT;

		// バッファを作る
	LPDIRECTSOUNDBUFFER pDSTmp;
	//	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSData, NULL); 
	lpDS->CreateSoundBuffer(&dsbdesc, &pDSTmp, NULL);
	pDSTmp->QueryInterface(IID_IDirectSoundBuffer8, reinterpret_cast<LPVOID*>(&_LpSound));
	pDSTmp->Release();

	// セカンダリ・バッファにWaveデータを書き込む
	LPVOID lpvPtr1;		// 最初のブロックのポインタ
	DWORD dwBytes1;		// 最初のブロックのサイズ
	LPVOID lpvPtr2;		// ２番目のブロックのポインタ
	DWORD dwBytes2;		// ２番目のブロックのサイズ

	hr = _LpSound->Lock(0, waveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

	// DSERR_BUFFERLOSTが返された場合，Restoreメソッドを使ってバッファを復元する
	if (DSERR_BUFFERLOST == hr)
	{
		_LpSound->Restore();
		hr = _LpSound->Lock(0, waveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
	}
	if (SUCCEEDED(hr))
	{
		// ロック成功

		// ここで，バッファに書き込む
		// バッファにデータをコピーする
		UINT rsize;
		waveFile.Read(dwBytes1, (LPBYTE)lpvPtr1, &rsize);
		if (0 != dwBytes2)
			waveFile.Read(dwBytes2, (LPBYTE)lpvPtr2, &rsize);

		// 書き込みが終わったらすぐにUnlockする．
		hr = _LpSound->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
	}

	//3Dのセカンダリバッファを作る
	_LpSound->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)&_Lp3DSound);
}

template<typename CharaType>
void ChDirectSound9<CharaType>::Init(HWND _hWnd)
{
	//COM(コンポーネントオブジェクトモデル)の初期化
	CoInitialize(NULL);

	//DirectSoundObject作成
	if (DirectSoundCreate8(NULL, &lpDS, NULL) != S_OK)return;

	if (lpDS->SetCooperativeLevel(_hWnd, DSSCL_EXCLUSIVE | DSSCL_PRIORITY) != DS_OK)
	{
		lpDS->Release();
		lpDS = nullptr;
		return;
	}

	CreatePrimaryBuffer(_hWnd);

	SetInitFlg(true);
}

template<typename CharaType>
void ChDirectSound9<CharaType>::Update()
{
	DWORD Flg;
	if (GetPlaySubSoundListCount() <= 0)return;
	auto Obj = GetPlaySubSound(0);
	for(unsigned char i = 0;i< GetPlaySubSoundListCount();i++)
	{
		GetPlaySubSound(i)->sound->GetStatus(&Flg);
		if ((Flg & DSBSTATUS_PLAYING) == 0) {
			RemovePlaySubSound(i);
			i -= 1;
			continue;
		}
	}
	lpSListener->SetPosition(
		0.0f,
		0.0f,
		0.0f,
		DS3D_IMMEDIATE);


	if (ChPtr::NullCheck(listenerPos))return;

	lpSListener->SetPosition(
		listenerPos->x,
		listenerPos->y,
		listenerPos->z,
		DS3D_IMMEDIATE);

}

template<typename CharaType>
void ChDirectSound9<CharaType>::SetUseDirectory(
	const std::basic_string<CharaType>& _soundDirectoryName,
	const std::basic_string<CharaType>& _useSoundDirectory)
{
	if (directoryPathList.find(_useSoundDirectory) != directoryPathList.end())return;

	directoryPathList[_useSoundDirectory] = _soundDirectoryName;
}

template<typename CharaType>
void ChDirectSound9<CharaType>::SetBGMSound(
	const std::basic_string<CharaType>& _soundName,
	const std::basic_string<CharaType>& _soundFilePath,
	const std::basic_string<CharaType>& _useSoundDirectory)
{
	if (mainSoundList.find(_soundName) != mainSoundList.end())return;

	std::basic_string<CharaType> tmpString = _soundFilePath;

	if (tmpString.length() <= 0)return;

	if (directoryPathList.find(_useSoundDirectory)
		!= directoryPathList.end())
	{
		tmpString = directoryPathList[_useSoundDirectory] + ChStd::GetSlashChara<CharaType>() + tmpString;
	}

	auto bgm = ChPtr::Make_S<ChMainSound9>();

	if (bgm == nullptr)return;

	LoadSound(bgm->sound, bgm->dSound, tmpString.c_str(), tmpString.length());

	bgm->dSound->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);

	bgm->sound->GetFrequency(&bgm->hz);

	bgm->sound->GetVolume(&bgm->vol);

	mainSoundList[_soundName] = bgm;
}


template<typename CharaType>
unsigned short ChDirectSound9<CharaType>::SetSESound(
	const std::basic_string<CharaType>& _soundFilePath,
	const std::basic_string<CharaType>& _useSoundDirectory)
{
	if (subSoundList.size() >= maxSE)return 0;

	std::basic_string<CharaType> tmpString = _soundFilePath;

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
		tmpString = directoryPathList[_useSoundDirectory] + ChStd::GetSlashChara<CharaType>() + tmpString;
	}
	ChPtr::Shared<ChSubSound9> se = nullptr;
	se = ChPtr::Make_S<ChSubSound9>();
	LoadSound(se->sound, se->dSound, tmpString.c_str(), tmpString.length());

	se->sound->GetFrequency(&se->hz);

	se->sound->GetVolume(&se->vol);

	subSoundList.insert(std::pair<unsigned short, ChPtr::Shared<ChSE9>>(tmpData, se));

	return tmpData;
}

template<typename CharaType>
void ChDirectSound9<CharaType>::SetHzForBGM(const std::basic_string<CharaType>& _soundName, const DWORD _hz)
{
	if (mainSoundList.find(_soundName) == mainSoundList.end())return;
	mainSoundList[_soundName]->sound->SetFrequency(_hz);
}

template<typename CharaType>
void ChDirectSound9<CharaType>::SetVolumeForBGM(const std::basic_string<CharaType>& _soundName, const long _volume)
{
	if (mainSoundList.find(_soundName) == mainSoundList.end())return;
	mainSoundList[_soundName]->sound->SetVolume(_volume);
}

template<typename CharaType>
void ChDirectSound9<CharaType>::SetBaseHzForBGM(const std::basic_string<CharaType>& _soundName)
{
	if (mainSoundList.find(_soundName) == mainSoundList.end())return;
	mainSoundList[_soundName]->sound->SetFrequency(mainSoundList[_soundName]->hz);
}

template<typename CharaType>
void ChDirectSound9<CharaType>::SetBaseVolumeForBGM(const std::basic_string<CharaType>& _soundName)
{
	if (mainSoundList.find(_soundName) == mainSoundList.end())return;
	mainSoundList[_soundName]->sound->SetVolume(mainSoundList[_soundName]->vol);
}

template<typename CharaType>
void ChDirectSound9<CharaType>::SetHzForSE(const unsigned short _soundNo, const DWORD _hz)
{
	auto&& subSound = GetSubSound(_soundNo);
	if (ChPtr::NullCheck(subSound))return;
	subSound->sound->SetFrequency(_hz);
}

template<typename CharaType>
void ChDirectSound9<CharaType>::SetVolumeForSE(const unsigned short _soundNo, const long _volume)
{
	auto&& subSound = GetSubSound(_soundNo);
	if (ChPtr::NullCheck(subSound))return;
	subSound->sound->SetVolume(_volume);
}

template<typename CharaType>
void ChDirectSound9<CharaType>::SetBaseHzForSE(const unsigned short _soundNo)
{
	auto&& subSound = GetSubSound(_soundNo);
	if (ChPtr::NullCheck(subSound))return;
	subSound->sound->SetFrequency(subSound->hz);
}

template<typename CharaType>
void ChDirectSound9<CharaType>::SetBaseVolumeForSE(const unsigned short _soundNo)
{
	auto&& subSound = GetSubSound(_soundNo);
	if (ChPtr::NullCheck(subSound))return;
	subSound->sound->SetVolume(subSound->vol);
}

template<typename CharaType>
void ChDirectSound9<CharaType>::PlaySE(const unsigned short _soundNo)
{
	auto tmpBGM = GetSubSound(_soundNo);

	if (ChPtr::NullCheck(tmpBGM))return;

	tmpBGM->sound->SetCurrentPosition(0);
	tmpBGM->sound->Play(0, 0, 0);
}

template<typename CharaType>
void ChDirectSound9<CharaType>::StopSE(const unsigned short _soundNo)
{
	auto tmpBuffer = GetSubSound(_soundNo);

	if (ChPtr::NullCheck(tmpBuffer))return;

	DWORD Flg;
	tmpBuffer->sound->GetStatus(&Flg);

	if ((Flg & DSBSTATUS_PLAYING) == 0)
		return;

	tmpBuffer->sound->Stop();
}

///////////////////////////////////////////////////////////////////////////////////////
//ChSoundDateメソッド
///////////////////////////////////////////////////////////////////////////////////////

//※受け取り物
//-----------------------------------------------------------------------------
// File: WavRead.cpp
//
// Desc: Wave file support for loading and playing Wave files using DirectSound 
//       buffers.
//
// Copyright (c) 1999 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }


//-----------------------------------------------------------------------------
// Name: ReadMMIO()
// Desc: Support function for reading from a multimedia I/O stream
//-----------------------------------------------------------------------------
HRESULT CWaveSoundRead9::ReadMMIO(
	HMMIO hmmioIn,
	MMCKINFO* pckInRIFF,
	WAVEFORMATEX** ppwfxInfo)
{
	MMCKINFO        ckIn;           // chunk info. for general use.
	PCMWAVEFORMAT   pcmWaveFormat;  // Temp PCM structure to load in.       

	*ppwfxInfo = NULL;

	if ((0 != mmioDescend(hmmioIn, pckInRIFF, NULL, 0)))
		return E_FAIL;

	if ((pckInRIFF->ckid != FOURCC_RIFF) ||
		(pckInRIFF->fccType != mmioFOURCC('W', 'A', 'V', 'E')))
		return E_FAIL;

	// Search the input file for for the 'fmt ' chunk.
	ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (0 != mmioDescend(hmmioIn, &ckIn, pckInRIFF, MMIO_FINDCHUNK))
		return E_FAIL;

	// Expect the 'fmt' chunk to be at least as large as <PCMWAVEFORMAT>;
	// if there are extra parameters at the end, we'll ignore them
	if (ckIn.cksize < (LONG) sizeof(PCMWAVEFORMAT))
		return E_FAIL;

	// Read the 'fmt ' chunk into <pcmWaveFormat>.
	if (mmioRead(hmmioIn, (HPSTR)&pcmWaveFormat,
		sizeof(pcmWaveFormat)) != sizeof(pcmWaveFormat))
		return E_FAIL;

	// Allocate the waveformatex, but if its not pcm format, read the next
	// word, and thats how many extra bytes to allocate.
	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
	{
		if (NULL == (*ppwfxInfo = new WAVEFORMATEX))
			return E_FAIL;

		// Copy the bytes from the pcm structure to the waveformatex structure
		memcpy(*ppwfxInfo, &pcmWaveFormat, sizeof(pcmWaveFormat));
		(*ppwfxInfo)->cbSize = 0;
	}
	else
	{
		// Read in length of extra bytes.
		WORD cbExtraBytes = 0L;
		if (mmioRead(hmmioIn, (CHAR*)&cbExtraBytes, sizeof(WORD)) != sizeof(WORD))
			return E_FAIL;

		*ppwfxInfo = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX) + cbExtraBytes];
		if (NULL == *ppwfxInfo)
			return E_FAIL;

		// Copy the bytes from the pcm structure to the waveformatex structure
		memcpy(*ppwfxInfo, &pcmWaveFormat, sizeof(pcmWaveFormat));
		(*ppwfxInfo)->cbSize = cbExtraBytes;

		// Now, read those extra bytes into the structure, if cbExtraAlloc != 0.
		if (mmioRead(hmmioIn, (CHAR*)(((BYTE*)&((*ppwfxInfo)->cbSize)) + sizeof(WORD)),
			cbExtraBytes) != cbExtraBytes)
		{
			delete *ppwfxInfo;
			*ppwfxInfo = NULL;
			return E_FAIL;
		}
	}

	// Ascend the input file out of the 'fmt ' chunk.
	if (0 != mmioAscend(hmmioIn, &ckIn, 0))
	{
		delete *ppwfxInfo;
		*ppwfxInfo = NULL;
		return E_FAIL;
	}

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: WaveOpenFile()
// Desc: This function will open a wave input file and prepare it for reading,
//       so the data can be easily read with WaveReadFile. Returns 0 if
//       successful, the error code if not.
//-----------------------------------------------------------------------------
HRESULT CWaveSoundRead9::WaveOpenFile(
	const CHAR* strFileName,
	HMMIO* phmmioIn,
	WAVEFORMATEX** ppwfxInfo,
	MMCKINFO* pckInRIFF)
{
	HRESULT hr;
	HMMIO   hmmioIn = NULL;

	if (NULL == (hmmioIn = mmioOpenA((char *)strFileName, NULL, MMIO_ALLOCBUF | MMIO_READ)))
		return E_FAIL;

	if (FAILED(hr = ReadMMIO(hmmioIn, pckInRIFF, ppwfxInfo)))
	{
		mmioClose(hmmioIn, 0);
		return hr;
	}

	*phmmioIn = hmmioIn;

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: WaveOpenFile()
// Desc: This function will open a wave input file and prepare it for reading,
//       so the data can be easily read with WaveReadFile. Returns 0 if
//       successful, the error code if not.
//-----------------------------------------------------------------------------
HRESULT CWaveSoundRead9::WaveOpenFile(
	const WCHAR* strFileName,
	HMMIO* phmmioIn,
	WAVEFORMATEX** ppwfxInfo,
	MMCKINFO* pckInRIFF)
{
	HRESULT hr;
	HMMIO   hmmioIn = NULL;

	if (NULL == (hmmioIn = mmioOpenW((wchar_t*)strFileName, NULL, MMIO_ALLOCBUF | MMIO_READ)))
		return E_FAIL;

	if (FAILED(hr = ReadMMIO(hmmioIn, pckInRIFF, ppwfxInfo)))
	{
		mmioClose(hmmioIn, 0);
		return hr;
	}

	*phmmioIn = hmmioIn;

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: WaveStartDataRead()
// Desc: Routine has to be called before WaveReadFile as it searches for the
//       chunk to descend into for reading, that is, the 'data' chunk.  For
//       simplicity, this used to be in the open routine, but was taken out and
//       moved to a separate routine so there was more control on the chunks
//       that are before the data chunk, such as 'fact', etc...
//-----------------------------------------------------------------------------
HRESULT CWaveSoundRead9::WaveStartDataRead(
	HMMIO* phmmioIn,
	MMCKINFO* pckIn,
	MMCKINFO* pckInRIFF)
{
	// Seek to the data
	if (-1 == mmioSeek(*phmmioIn, pckInRIFF->dwDataOffset + sizeof(FOURCC),
		SEEK_SET))
		return E_FAIL;

	// Search the input file for for the 'data' chunk.
	pckIn->ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (0 != mmioDescend(*phmmioIn, pckIn, pckInRIFF, MMIO_FINDCHUNK))
		return E_FAIL;

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: WaveReadFile()
// Desc: Reads wave data from the wave file. Make sure we're descended into
//       the data chunk before calling this function.
//          hmmioIn      - Handle to mmio.
//          cbRead       - # of bytes to read.   
//          pbDest       - Destination buffer to put bytes.
//          cbActualRead - # of bytes actually read.
//-----------------------------------------------------------------------------
HRESULT CWaveSoundRead9::WaveReadFile(
	HMMIO hmmioIn,
	UINT cbRead,
	BYTE* pbDest,
	MMCKINFO* pckIn,
	UINT* cbActualRead)
{
	MMIOINFO mmioinfoIn;         // current status of <hmmioIn>

	*cbActualRead = 0;

	if (0 != mmioGetInfo(hmmioIn, &mmioinfoIn, 0))
		return E_FAIL;

	UINT cbDataIn = cbRead;
	if (cbDataIn > pckIn->cksize)
		cbDataIn = pckIn->cksize;

	pckIn->cksize -= cbDataIn;

	for (DWORD cT = 0; cT < cbDataIn; cT++)
	{
		// Copy the bytes from the io to the buffer.
		if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
		{
			if (0 != mmioAdvance(hmmioIn, &mmioinfoIn, MMIO_READ))
				return E_FAIL;

			if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
				return E_FAIL;
		}

		// Actual copy.
		*((BYTE*)pbDest + cT) = *((BYTE*)mmioinfoIn.pchNext);
		mmioinfoIn.pchNext++;
	}

	if (0 != mmioSetInfo(hmmioIn, &mmioinfoIn, 0))
		return E_FAIL;

	*cbActualRead = cbDataIn;
	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: CWaveSoundRead()
// Desc: Constructs the class
//-----------------------------------------------------------------------------
CWaveSoundRead9::CWaveSoundRead9()
{
	m_pwfx = NULL;
}

//-----------------------------------------------------------------------------
// Name: ~CWaveSoundRead()
// Desc: Destructs the class
//-----------------------------------------------------------------------------
CWaveSoundRead9::~CWaveSoundRead9()
{
	Close();
	SAFE_DELETE(m_pwfx);
}

//-----------------------------------------------------------------------------
// Name: Open()
// Desc: Opens a wave file for reading
//-----------------------------------------------------------------------------
HRESULT CWaveSoundRead9::Open(const CHAR* strFilename)
{
	SAFE_DELETE(m_pwfx);

	HRESULT  hr;

	if (FAILED(hr = WaveOpenFile(strFilename, &m_hmmioIn, &m_pwfx, &m_ckInRiff)))
		return hr;

	if (FAILED(hr = Reset()))
		return hr;

	return hr;
}

//-----------------------------------------------------------------------------
// Name: Open()
// Desc: Opens a wave file for reading
//-----------------------------------------------------------------------------
HRESULT CWaveSoundRead9::Open(const WCHAR* strFilename)
{
	SAFE_DELETE(m_pwfx);

	HRESULT  hr;

	if (FAILED(hr = WaveOpenFile(strFilename, &m_hmmioIn, &m_pwfx, &m_ckInRiff)))
		return hr;

	if (FAILED(hr = Reset()))
		return hr;

	return hr;
}

//-----------------------------------------------------------------------------
// Name: Reset()
// Desc: Resets the internal m_ckIn pointer so reading starts from the 
//       beginning of the file again 
//-----------------------------------------------------------------------------
HRESULT CWaveSoundRead9::Reset()
{
	return WaveStartDataRead(&m_hmmioIn, &m_ckIn, &m_ckInRiff);
}

//-----------------------------------------------------------------------------
// Name: Read()
// Desc: Reads a wave file into a pointer and returns how much read
//       using m_ckIn to determine where to start reading from
//-----------------------------------------------------------------------------
HRESULT CWaveSoundRead9::Read(UINT nSizeToRead, BYTE* pbData, UINT* pnSizeRead)
{
	return WaveReadFile(m_hmmioIn, nSizeToRead, pbData, &m_ckIn, pnSizeRead);
}

//-----------------------------------------------------------------------------
// Name: Close()
// Desc: Closes an open wave file 
//-----------------------------------------------------------------------------
HRESULT CWaveSoundRead9::Close()
{
	mmioClose(m_hmmioIn, 0);
	return S_OK;
}

CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION(ChDirectSound9);
