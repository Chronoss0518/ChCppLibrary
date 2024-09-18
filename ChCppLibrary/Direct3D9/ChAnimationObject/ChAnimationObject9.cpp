
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChFile/ChFile.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"ChAnimationObject9.h"

///////////////////////////////////////////////////////////////////////////////////////
//ChAnimationObject9メソッド
///////////////////////////////////////////////////////////////////////////////////////

const char ChAnimationSupporter9::animationCheck[] = "AnimationSet Global {";

const char ChAnimationSupporter9::animation[] = "Animation {";

const char ChAnimationSupporter9::aniKey[] = "AnimationKey {";

ChMat_9 ChAniObj9::Update()
{
	if (!aniPlayFlg)return lastPlayMat;

	if (nowFrame + 1 >= GetAniCnt())
	{
		Stop();
		return  lastPlayMat;
	}

	AniObject sAni, eAni, nAni;

	sAni = GetAnimation(nowFrame);

	if (nowFrame < 0 && ChPtr::NotNullCheck(tmpStartMat))
	{

		auto tmpMat = *tmpStartMat;
		sAni.pos = tmpMat;
		sAni.rot = tmpMat;
		sAni.sca = tmpMat.GetScaleSize();

	}

	eAni = GetAnimation(nowFrame + 1);

	nAni.Lerp(sAni, eAni, nowTime);

	nowTime += oneFrameTime;

	if (nowTime > 1.0f)
	{
		nowTime -= 1.0f;
		nowFrame++;
		funcFlg = false;
	}

	lastPlayMat.Identity();
	lastPlayMat.Scaling(nAni.sca);
	lastPlayMat *= nAni.rot;
	lastPlayMat = nAni.pos;

	RunFunction(nAni);

	return lastPlayMat;
}

///////////////////////////////////////////////////////////////////////////////////////
//ChAnimationSupporter9メソッド
///////////////////////////////////////////////////////////////////////////////////////
