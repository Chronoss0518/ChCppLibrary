#ifndef Ch_D3D9_DiSo_h
#define Ch_D3D9_DiSo_h


#include"ChSoundData.h"

//※受け取り物//-----------------------------------------------------------------------------
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
///////////////////////////////////////////////////////////////////////////////

//(改良必)//
//大元のサウンドの名前とは別にストップ用のNoを持っておく//
template<typename CharaType>
class ChDirectSound9 :public ChCp::Initializer
{
public://Init And Release//

	void Init(HWND _hWnd);

	virtual void Release();

public://Set Functions//

	//リスナーの位置情報更新用//
	void SetListenerPos(const ChVec3_9 *_pos)
	{
		listenerPos = (ChVec3_9*)_pos;
	}

	//使用するディレクトリのパスをセット//
	void SetUseDirectory(
		const std::basic_string<CharaType>& _soundDirectoryName,
		const std::basic_string<CharaType>& _useSoundDirectory);

	//先に登録してあるDirectoryを利用してBGMをセット//
	void SetBGMSound(
		const std::basic_string<CharaType>& _soundName,
		const std::basic_string<CharaType>& _soundFilePath,
		const std::basic_string<CharaType>& _useSoundDirectory);

	//先に登録してあるDirectoryを利用してSEをセット//
	unsigned short SetSESound(
		const std::basic_string<CharaType>& _soundFilePath,
		const std::basic_string<CharaType>& _useSoundDirectory);

	//セットされたBGMのHzを変更//
	void SetHzForBGM(const std::basic_string<CharaType>& _soundName, const DWORD _hz);

	//セットされたBGMのVolumeを変更//
	void SetVolumeForBGM(const std::basic_string<CharaType>& _soundName, const long _volume);

	//セットされたBGMのHzを読み込んだ際のサイズに戻す//
	void SetBaseHzForBGM(const std::basic_string<CharaType>& _soundName);

	//セットされたBGMのVolumeを読み込んだ際のサイズに戻す//
	void SetBaseVolumeForBGM(const std::basic_string<CharaType>& _soundName);

	//セットされたSEのHzを変更//
	void SetHzForSE(const unsigned short _soundNo, const DWORD _hz);

	//セットされたSEのVolumeを変更//
	void SetVolumeForSE(const unsigned short _soundNo, const long _volume);

	//セットされたSEのHzを読み込んだ際のサイズに戻す//
	void SetBaseHzForSE(const unsigned short _soundNo);

	//セットされたSEのVolumeを読み込んだ際のサイズに戻す//
	void SetBaseVolumeForSE(const unsigned short _soundNo);

protected://Sound List Functions//

	ChSubSound9* GetSubSound(const unsigned short _soundNo);

	unsigned short GetSubSoundListCount();

	ChSubSound9* GetPlaySubSound(const unsigned short _soundNo);

	unsigned short GetPlaySubSoundListCount();

	void RemovePlaySubSound(const unsigned short _soundNo);

public://Update Functions//

	//止まっている一時使用のSEを解放//
	void Update();

public://Other Functions//

	//セットされたBGMをすべて解放//
	void ClearBGM();

	//登録時に保持した数値でSEデータを解放する//
	void ClearSE(const unsigned short _soundNo);

	//セットされたBGMをすべて解放//
	void ClearSE();

	//登録時に保持した数値でSEを再生する//
	void PlaySE(const unsigned short _soundNo);

	//セットされたBGMを再生//
	void PlayBGM(const std::basic_string<CharaType>& _soundName);

	//直接SEを再生する(Updateメソッドを設置する必要がある)//
	void PlaySE(
		const std::basic_string<CharaType>& _soundName,
		const std::basic_string<CharaType>& _useSoundDirectory,
		const ChVec3_9* _soundPos);

	//現在再生しているBGMを止める//
	void StopBGM();

	//登録時に保持した数値でSEを止める//
	void StopSE(const unsigned short _soundNo);

protected://Other Functions//

	void CreatePrimaryBuffer(HWND _hWnd);

	void LoadSound(
		LPDIRECTSOUNDBUFFER8& _lpSound,
		LPDIRECTSOUND3DBUFFER8& _lp3DSound,
		const char* _soundFileName,
		unsigned long _soundFileNameLength);

	void LoadSound(
		LPDIRECTSOUNDBUFFER8& _lpSound,
		LPDIRECTSOUND3DBUFFER8& _lp3DSound,
		const wchar_t* _soundFileName,
		unsigned long _soundFileNameLength);

	protected://Member Value//

	LPDIRECTSOUND3DLISTENER8 lpSListener;//リスナー(聞く人)//
	LPDIRECTSOUNDBUFFER primary;
	LPDIRECTSOUND8 lpDS;
	ChVec3_9* listenerPos;
	const float listenerBaseLen = 0.3f;

	const unsigned short maxSE = 10000;

	unsigned short seNo = 1;

	//UserData//
	std::map<std::basic_string<CharaType>, std::basic_string<CharaType>> directoryPathList;

	std::map<std::basic_string<CharaType>, ChPtr::Shared<ChMainSound9>>mainSoundList;
	std::map<unsigned short, ChPtr::Shared<ChSubSound9>>subSoundList;

	std::vector<ChPtr::Shared<ChSubSound9>>playSubSoundList;

	std::basic_string<CharaType> mainSoundName = ChStd::GetZeroChara<CharaType>();

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

using ChDirectSoundA9 = ChDirectSound9<char>;
using ChDirectSoundW9 = ChDirectSound9<wchar_t>;

inline ChDirectSoundA9& ChDSound9A() { return ChDirectSoundA9::GetIns(); }
inline ChDirectSoundW9& ChDSound9W() { return ChDirectSoundW9::GetIns(); }

#ifdef UNICODE
ChDirectSoundW9
#else
ChDirectSoundA9
#endif
& ChDSound9()
{
#ifdef UNICODE
	return ChDSound9W();
#else
	return ChDSound9A();
#endif
}


#endif