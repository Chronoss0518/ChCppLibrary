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
///////////////////////////////////////////////////////////////////////////////

//(���ǕK)//
//�匳�̃T�E���h�̖��O�Ƃ͕ʂɃX�g�b�v�p��No�������Ă���//
template<typename CharaType>
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

	//�g�p����f�B���N�g���̃p�X���Z�b�g//
	void SetUseDirectory(
		const std::basic_string<CharaType>& _soundDirectoryName,
		const std::basic_string<CharaType>& _useSoundDirectory);

	//��ɓo�^���Ă���Directory�𗘗p����BGM���Z�b�g//
	void SetBGMSound(
		const std::basic_string<CharaType>& _soundName,
		const std::basic_string<CharaType>& _soundFilePath,
		const std::basic_string<CharaType>& _useSoundDirectory);

	//��ɓo�^���Ă���Directory�𗘗p����SE���Z�b�g//
	unsigned short SetSESound(
		const std::basic_string<CharaType>& _soundFilePath,
		const std::basic_string<CharaType>& _useSoundDirectory);

	//�Z�b�g���ꂽBGM��Hz��ύX//
	void SetHzForBGM(const std::basic_string<CharaType>& _soundName, const DWORD _hz);

	//�Z�b�g���ꂽBGM��Volume��ύX//
	void SetVolumeForBGM(const std::basic_string<CharaType>& _soundName, const long _volume);

	//�Z�b�g���ꂽBGM��Hz��ǂݍ��񂾍ۂ̃T�C�Y�ɖ߂�//
	void SetBaseHzForBGM(const std::basic_string<CharaType>& _soundName);

	//�Z�b�g���ꂽBGM��Volume��ǂݍ��񂾍ۂ̃T�C�Y�ɖ߂�//
	void SetBaseVolumeForBGM(const std::basic_string<CharaType>& _soundName);

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

	//�Z�b�g���ꂽBGM���Đ�//
	void PlayBGM(const std::basic_string<CharaType>& _soundName);

	//����SE���Đ�����(Update���\�b�h��ݒu����K�v������)//
	void PlaySE(
		const std::basic_string<CharaType>& _soundName,
		const std::basic_string<CharaType>& _useSoundDirectory,
		const ChVec3_9* _soundPos);

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

	void LoadSound(
		LPDIRECTSOUNDBUFFER8& _lpSound,
		LPDIRECTSOUND3DBUFFER8& _lp3DSound,
		const wchar_t* _soundFileName,
		unsigned long _soundFileNameLength);

	protected://Member Value//

	LPDIRECTSOUND3DLISTENER8 lpSListener;//���X�i�[(�����l)//
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