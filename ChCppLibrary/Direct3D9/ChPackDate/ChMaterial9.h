#ifndef Ch_D3D9_Mate9_h
#define Ch_D3D9_Mate9_h

#include"ChMatrix_9.h"


//D3DMATERIAL9をパック化したクラス//
//このままでは利用できないため、いったんD3DMATERIAL9に直す必要がある//
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

	//SubSet描画時に移動させるマテリアルの行列//
	ChMat_9 mat;

#ifdef CRT
	//Material名
	std::string name = "";
#endif

};

//D3DMATERIAL9をパック化したクラス//
//このままでは利用できないため、いったんD3DMATERIAL9に直す必要がある//
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

	//SubSet描画時に移動させるマテリアルの行列//
	ChMat_9 mat;

#ifdef CRT
	//Material名
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