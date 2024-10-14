#ifndef Ch_D3D9_SDDa_h
#define Ch_D3D9_SDDa_h


class CWaveSoundRead9
{
public:
	WAVEFORMATEX* m_pwfx;        // Pointer to WAVEFORMATEX structure//
	HMMIO         m_hmmioIn;     // MM I/O handle for the WAVE//
	MMCKINFO      m_ckIn;        // Multimedia RIFF chunk//
	MMCKINFO      m_ckInRiff;    // Use in opening a WAVE file//

public://WAVE Control Functions//

	HRESULT static ReadMMIO(
		HMMIO hmmioIn,
		MMCKINFO* pckInRIFF,
		WAVEFORMATEX** ppwfxInfo);

	HRESULT static WaveOpenFile(
		const CHAR* strFileName,
		HMMIO* phmmioIn,
		WAVEFORMATEX** ppwfxInfo,
		MMCKINFO* pckInRIFF);

	HRESULT static WaveOpenFile(
		const WCHAR* strFileName,
		HMMIO* phmmioIn,
		WAVEFORMATEX** ppwfxInfo,
		MMCKINFO* pckInRIFF);

	HRESULT static WaveStartDataRead(
		HMMIO* phmmioIn,
		MMCKINFO* pckIn,
		MMCKINFO* pckInRIFF);

	HRESULT static WaveReadFile(
		HMMIO hmmioIn,
		UINT cbRead,
		BYTE* pbDest,
		MMCKINFO* pckIn,
		UINT* cbActualRead);

public://Constructer Destructer//

	CWaveSoundRead9();

	virtual ~CWaveSoundRead9();

public://Control Functions//

	HRESULT Open(const CHAR* strFilename);

	HRESULT Open(const WCHAR* strFilename);

	HRESULT Reset();

	HRESULT Read(UINT nSizeToRead, BYTE* pbData, UINT* pnSizeRead);

	HRESULT Close();
};

//BGMクラス//
typedef struct ChMainSound9
{
public://Operator Functions//

	ChMainSound9& operator = (const ChMainSound9& _cm)
	{
		*sound = *_cm.sound;
		*dSound = *_cm.dSound;
		return *this;
	}

public://Constructor Destructor//

	virtual ~ChMainSound9()
	{
		Release();
	}

public://Init And Release//

	inline virtual void Release()
	{

		DWORD flg;
		if (ChPtr::NullCheck(sound) && ChPtr::NullCheck(dSound))return;
		sound->GetStatus(&flg);
		if ((flg & DSBSTATUS_PLAYING) != 0)sound->Stop();
		sound->Release();
		dSound->Release();
	}

public://Member Functions//

	LPDIRECTSOUNDBUFFER8 sound;
	LPDIRECTSOUND3DBUFFER8 dSound;
	DWORD hz;
	long vol;

}ChBGM9;

//SEクラス//
typedef struct ChSubSound9
{

	ChSubSound9& operator = (const ChSubSound9& _cm)
	{
		*sound = *_cm.sound;
		*dSound = *_cm.dSound;
		return *this;
	}

public://Constructor Destructor//

	virtual ~ChSubSound9()
	{
		Release();
	}

public://Init And Release//

	inline virtual void Release()
	{

		DWORD flg;
		if (ChPtr::NullCheck(sound) && ChPtr::NullCheck(dSound))return;
		sound->GetStatus(&flg);
		if ((flg & DSBSTATUS_PLAYING) != 0)sound->Stop();
		sound->Release();
		dSound->Release();
	}

public://Member Value//

	LPDIRECTSOUNDBUFFER8 sound;
	LPDIRECTSOUND3DBUFFER8 dSound;
	DWORD hz;
	long vol;

}ChSE9;

#endif