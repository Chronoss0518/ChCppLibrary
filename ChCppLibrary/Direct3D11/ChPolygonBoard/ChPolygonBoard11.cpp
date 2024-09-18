
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"ChPolygonBoard11.h"

using namespace ChD3D11;

void PolygonBoard11::Init()
{
	if (!D3D11API().IsInit())return;

	Init(D3D11Device());
}

void PolygonBoard11::Init(ID3D11Device* _device)
{
	SetInitSquare();

	material.diffuse = ChVec4(1.0f);
	material.specularColor = ChVec3(0.0f);
	material.specularPower = 1.0f;
	material.ambient = ChVec4(0.0f);
}
