
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"ChSoundData.h"
#include"ChDSound9.h"

///////////////////////////////////////////////////////////////////////////////////////
//ChDirectSound9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ChDirectSound9::CreatePrimaryBuffer(HWND _hWnd)
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

void ChDirectSound9::LoadSound(
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

void ChDirectSound9::Init(HWND _hWnd)
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

void ChDirectSound9::Update()
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
		0.0f
		, 0.0f
		, 0.0f
		, DS3D_IMMEDIATE);


	if (ChPtr::NullCheck(listenerPos))return;

	lpSListener->SetPosition(
		listenerPos->x
		, listenerPos->y
		, listenerPos->z
		, DS3D_IMMEDIATE);

}

void ChDirectSound9::SetHzForSE(const unsigned short _soundNo, const DWORD _hz)
{
	auto&& subSound = GetSubSound(_soundNo);
	if (ChPtr::NullCheck(subSound))return;
	subSound->sound->SetFrequency(_hz);
}

void ChDirectSound9::SetVolumeForSE(const unsigned short _soundNo, const long _volume)
{
	auto&& subSound = GetSubSound(_soundNo);
	if (ChPtr::NullCheck(subSound))return;
	subSound->sound->SetVolume(_volume);
}

void ChDirectSound9::SetBaseHzForSE(const unsigned short _soundNo)
{
	auto&& subSound = GetSubSound(_soundNo);
	if (ChPtr::NullCheck(subSound))return;
	subSound->sound->SetFrequency(subSound->hz);
}

void ChDirectSound9::SetBaseVolumeForSE(const unsigned short _soundNo)
{
	auto&& subSound = GetSubSound(_soundNo);
	if (ChPtr::NullCheck(subSound))return;
	subSound->sound->SetVolume(subSound->vol);
}

void ChDirectSound9::PlaySE(const unsigned short _soundNo)
{
	auto tmpBGM = GetSubSound(_soundNo);

	if (ChPtr::NullCheck(tmpBGM))return;

	tmpBGM->sound->SetCurrentPosition(0);
	tmpBGM->sound->Play(0, 0, 0);
}

void ChDirectSound9::StopSE(const unsigned short _soundNo)
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
	HMMIO hmmioIn
	, MMCKINFO* pckInRIFF
	, WAVEFORMATEX** ppwfxInfo)
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
	const CHAR* strFileName
	, HMMIO* phmmioIn
	, WAVEFORMATEX** ppwfxInfo
	, MMCKINFO* pckInRIFF)
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
// Name: WaveStartDataRead()
// Desc: Routine has to be called before WaveReadFile as it searches for the
//       chunk to descend into for reading, that is, the 'data' chunk.  For
//       simplicity, this used to be in the open routine, but was taken out and
//       moved to a separate routine so there was more control on the chunks
//       that are before the data chunk, such as 'fact', etc...
//-----------------------------------------------------------------------------
HRESULT CWaveSoundRead9::WaveStartDataRead(HMMIO* phmmioIn, MMCKINFO* pckIn,
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
HRESULT CWaveSoundRead9::WaveReadFile(HMMIO hmmioIn, UINT cbRead, BYTE* pbDest,
	MMCKINFO* pckIn, UINT* cbActualRead)
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
