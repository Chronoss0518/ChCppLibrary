#ifndef Ch_D3D9_Mate9_h
#define Ch_D3D9_Mate9_h

#include<string>

#include"ChMatrix_9.h"


//D3DMATERIAL9をパック化したクラス//
//このままでは利用できないため、いったんD3DMATERIAL9に直す必要がある//
template<typename CharaType>
struct ChBaseMaterial_9 :public D3DMATERIAL9
{

	ChBaseMaterial_9&operator=(const D3DMATERIAL9 _cm)
	{
		if (this == &_cm)return *this;
		D3DMATERIAL9::operator = (_cm);
		return *this;
	}

	D3DMATERIAL9&operator=(const ChBaseMaterial_9 _cm)
	{
		D3DMATERIAL9 tmpMat;
		tmpMat.Ambient = _cm.Ambient;
		tmpMat.Diffuse = _cm.Diffuse;
		tmpMat.Emissive = _cm.Emissive;
		tmpMat.Power = _cm.Power;
		tmpMat.Specular = _cm.Specular;
		return  tmpMat;
	}

	ChBaseMaterial_9(D3DMATERIAL9 &_cm) :D3DMATERIAL9(_cm) {};

	ChBaseMaterial_9(){}

	//SubSet描画時に移動させるマテリアルの行列//
	ChMat_9 mat;

	//Material名
	std::basic_string<CharaType> name = ChStd::GetZeroChara<CharaType>();
};


using ChMaterialA_9 = ChBaseMaterial_9<char>;
using ChMaterialW_9 = ChBaseMaterial_9<wchar_t>;


using ChMaterial_9 =
#ifdef UNICODE
	ChMaterialW_9;
#else
	ChMaterialA_9;
#endif

#endif