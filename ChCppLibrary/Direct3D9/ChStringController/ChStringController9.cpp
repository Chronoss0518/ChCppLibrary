
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"../ChSprite/ChSprite9.h"
#include"ChStringController9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////////
//ChStringController9ÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void StringController9::SetStringColor(const ChVec4& _color)
{
	strTex.GetBaseColor() = _color;
}

