#ifdef CRT

#ifdef Ch_CPP_HTM_h

#ifdef Ch_CPP_HTB_h

#ifndef Ch_CPP_HT_Shared_HTM_HTB
#define Ch_CPP_HT_Shared_HTM_HTB
template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsHit(HitTestBox* _target)
{
	return false;
}

template<typename CharaType>
bool  ChCpp::PolygonCollider<CharaType>::IsInnerHit(HitTestBox* _target)
{
	return false;
}
#endif

#endif


#ifdef Ch_CPP_HTS_h

#ifndef Ch_CPP_HT_Shared_HTM_HTS
#define Ch_CPP_HT_Shared_HTM_HTS
template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsHit(HitTestSphere* _target)
{
	auto model = GetModel();

	if (ChPtr::NullCheck(model))return false;

	return true;
}

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsInnerHit(HitTestSphere* _target)
{
	return false;
}

#endif

#endif

#ifdef Ch_CPP_RCollider_h

#ifndef Ch_CPP_HT_Shared_HTM_Ray
#define Ch_CPP_HT_Shared_HTM_Ray
template<typename CharaType>
bool  ChCpp::PolygonCollider<CharaType>::IsHit(HitTestRay* _target)
{

	auto model = GetModel();

	if (ChPtr::NullCheck(model))return false;

	float maxLen = _target->GetMaxLen();
	ChVec3 pos;
	ChVec3 ray = _target->GetRayDir();
	minLen = maxLen;

	{
		ChLMat tmp = _target->GetMat();
		pos = tmp.GetPosition();
		ray = tmp.TransformCoord(ray);
	}

	bool hitFlg = IsHitRayToMesh(*model, pos, ray, minLen);

	if (hitFlg)
		_target->SetHitVector(GetHitVectol() * -1.0f);

	return hitFlg;

}
#endif

#endif

#endif

#endif