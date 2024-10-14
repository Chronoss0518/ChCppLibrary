#ifndef Ch_D3D9_Mate9_h
#define Ch_D3D9_Mate9_h

#include"ChMatrix_9.h"


//D3DMATERIAL9をパック化したクラス//
//このままでは利用できないため、いったんD3DMATERIAL9に直す必要がある//
struct ChMaterial9 :public D3DMATERIAL9
{

	ChMaterial9&operator=(const D3DMATERIAL9 _cm)
	{
		if (this == &_cm)return *this;
		D3DMATERIAL9::operator = (_cm);
		return *this;
	}

	D3DMATERIAL9&operator=(const ChMaterial9 _cm)
	{
		D3DMATERIAL9 tmpMat;
		tmpMat.Ambient = _cm.Ambient;
		tmpMat.Diffuse = _cm.Diffuse;
		tmpMat.Emissive = _cm.Emissive;
		tmpMat.Power = _cm.Power;
		tmpMat.Specular = _cm.Specular;
		return  tmpMat;
	}

	ChMaterial9(D3DMATERIAL9 &_cm) :D3DMATERIAL9(_cm) {};

	ChMaterial9(){}

	//SubSet描画時に移動させるマテリアルの行列//
	ChMat_9 mat;

	//Material名
	std::string name = "";

};

#endif