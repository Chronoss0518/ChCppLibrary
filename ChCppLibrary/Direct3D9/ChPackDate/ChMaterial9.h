#ifndef Ch_D3D9_Mate9_h
#define Ch_D3D9_Mate9_h

#include"ChMatrix_9.h"


//D3DMATERIAL9���p�b�N�������N���X//
//���̂܂܂ł͗��p�ł��Ȃ����߁A��������D3DMATERIAL9�ɒ����K�v������//
struct ChMaterialA_9 :public D3DMATERIAL9
{

	ChMaterialA_9&operator=(const D3DMATERIAL9 _cm)
	{
		if (this == &_cm)return *this;
		D3DMATERIAL9::operator = (_cm);
		return *this;
	}

	D3DMATERIAL9&operator=(const ChMaterialA_9 _cm)
	{
		D3DMATERIAL9 tmpMat;
		tmpMat.Ambient = _cm.Ambient;
		tmpMat.Diffuse = _cm.Diffuse;
		tmpMat.Emissive = _cm.Emissive;
		tmpMat.Power = _cm.Power;
		tmpMat.Specular = _cm.Specular;
		return  tmpMat;
	}

	ChMaterialA_9(D3DMATERIAL9 &_cm) :D3DMATERIAL9(_cm) {};

	ChMaterialA_9(){}

	//SubSet�`�掞�Ɉړ�������}�e���A���̍s��//
	ChMat_9 mat;

#ifdef CRT
	//Material��
	std::string name = "";
#endif

};

//D3DMATERIAL9���p�b�N�������N���X//
//���̂܂܂ł͗��p�ł��Ȃ����߁A��������D3DMATERIAL9�ɒ����K�v������//
struct ChMaterialW_9 :public D3DMATERIAL9
{

	ChMaterialW_9& operator=(const D3DMATERIAL9 _cm)
	{
		if (this == &_cm)return *this;
		D3DMATERIAL9::operator = (_cm);
		return *this;
	}

	D3DMATERIAL9& operator=(const ChMaterialW_9 _cm)
	{
		D3DMATERIAL9 tmpMat;
		tmpMat.Ambient = _cm.Ambient;
		tmpMat.Diffuse = _cm.Diffuse;
		tmpMat.Emissive = _cm.Emissive;
		tmpMat.Power = _cm.Power;
		tmpMat.Specular = _cm.Specular;
		return  tmpMat;
	}

	ChMaterialW_9(D3DMATERIAL9& _cm) :D3DMATERIAL9(_cm) {};

	ChMaterialW_9() {}

	//SubSet�`�掞�Ɉړ�������}�e���A���̍s��//
	ChMat_9 mat;

#ifdef CRT
	//Material��
	std::wstring name = L"";
#endif

};

using ChMaterial_9 =
#ifdef UNICODE
	ChMaterialW_9;
#else
	ChMaterialA_9;
#endif

#endif