#include"ChCollider.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//HitTestObject Method
///////////////////////////////////////////////////////////////////////////////////////

bool Collider::IsHitSphereToPanel(ChVec3& _thisHitVectol, const bool _leftHandFlg, const ChVec3& _spherePos, const ChVec3& _sphereSize, const std::vector<ChVec3*>& _vertexs)
{
	if (_vertexs.size())return false;

	if (_vertexs.size() < 2)
		return IsHitSphereToPos(_thisHitVectol, _spherePos, _sphereSize, *_vertexs[0]);

	if (_vertexs.size() < 3)
		return IsHitSphereToLine(_thisHitVectol, _spherePos, _sphereSize, *_vertexs[0], *_vertexs[1]);

	ChVec3 tmpPos = MovePosToPanelUp(*_vertexs[0], *_vertexs[_leftHandFlg ? 1 : _vertexs.size() - 1], *_vertexs[_leftHandFlg ? 1 : _vertexs.size() - 2], _spherePos);

	ChVec3 posOnPanel = _spherePos - tmpPos;

	ChVec3 testNormal = ChVec3();

	bool hitTest = true;

	for (unsigned long i = 0; i < _vertexs.size() - 1; i++)
	{
		ChVec3 vertex1;
		ChVec3 vertex2;

		{
			unsigned long v1Num = i + 1;
			unsigned long v2Num = i + 2;
			vertex1 = *_vertexs[_leftHandFlg ? v1Num : _vertexs.size() - v1Num];
			vertex2 = *_vertexs[_leftHandFlg ? v2Num : _vertexs.size() - v2Num];
		}

		ChVec3 test = ChVec3::GetCross(posOnPanel - vertex1, vertex2 - vertex1);

		if (testNormal.GetLen() < 0.1f)
		{
			testNormal = test;
		}

		if (testNormal == test)continue;

		hitTest = false;

		break;
	}

	if (hitTest)
	{

	}

	return hitTest;
}

float Collider::CreateDat(const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3)
{
	ChMath::BaseMatrix3x3<float> mat;

	ChVec3 tmp[3] = { _vec1,_vec2,_vec3 };

	for (unsigned char i = 0; i < mat.m.GetColumn(); i++)
	{
		for (unsigned char j = 0; j < mat.m.GetRow(); j++)
		{
			mat.m[i][j] = tmp[j].val[i];
		}
	}
	return mat.m.GetDeterminant();
}

bool Collider::HitTestTri(
	ChVec3& _thisHitVectol, 
	const ChVec3& _pos,
	const ChVec3& _dir,
	const ChVec3& _vec1,
	const ChVec3& _vec2,
	const ChVec3& _vec3)
{
	//eg1 = (v1 - v0), eg2 = (v2 - v0);
	//hitPos = spos + (dir * len)
	//hitPos = (eg1 * u) + (eg2 * v) + v0
	//spos + (dir * len) = (eg1 * u) + (eg2 * v) + v0
	//spos - v0 = (eg1 * u) + (eg2 * v) - (dir * len)

	//spos1 - v01 = eg11 * u + eg21 * v - dir1 * len
	//spos2 - v02 = eg12 * u + eg22 * v - dir2 * len
	//spos3 - v03 = eg13 * u + eg23 * v - dir3 * len
	//spos - v0 = v2sp

	//u = dat(v2sp,eg2,-dir)/dat(eg1.eg2.-dir)
	//v = dat(eg1,v2sp,-dir)/dat(eg1.eg2.-dir)
	//len = dat(eg1,eg2,v2sp)/dat(eg1.eg2.-dir)

	_thisHitVectol = 0.0f;

	float u = 0.0f, v = 0.0f, len = 0.0f;

	ChVec3 eg1 = _vec2 - _vec1, eg2 = _vec3 - _vec1, v2sp = _pos - _vec1;

	ChVec3 mdir = _dir * -1;
	float divDat = 0.0f;

	ChVec3 cross = ChVec3::GetCross(eg1, eg2);
	if (ChVec3::GetCos(cross, _dir) == 0.0f)return false;


	divDat = CreateDat(eg1, eg2, mdir);

	if (divDat <= 0.0f)return false;

	u = CreateDat(v2sp, eg2, mdir);

	u = u / divDat;

	if (u < 0.0f || u > 1.0f)return false;

	v = CreateDat(eg1, v2sp, mdir);
	v = v / divDat;

	if (v < 0.0f || v > 1.0f)return false;

	float tmpVal = u + v;

	if (tmpVal < 0.0f || tmpVal > 1.0f)return false;

	len = CreateDat(eg1, eg2, v2sp);
	len = len / divDat;

	if (len <= 0.0f)return false;

	_thisHitVectol = _dir * len;

	return true;
}

ChVec3 Collider::MovePosToPanelUp(const ChVec3& _v1, const ChVec3& _v2, const ChVec3& _v3, const ChVec3& _pos)
{

	ChVec3 normal = ChVec3::GetCross(_v2 - _v1, _v3 - _v1);

	normal.Normalize();

	return normal * ChVec3::GetDot(_pos - _v1, normal);
}

bool Collider::IsHitSphereToLine(ChVec3& _thisHitVectol, const ChVec3& _spherePos, const ChVec3& _sphereSize, const ChVec3& _v1, const ChVec3& _v2)
{
	return false;
}

bool Collider::IsHitSphereToPos(ChVec3& _thisHitVectol, const ChVec3& _spherePos, const ChVec3& _sphereSize, const ChVec3& _vertex)
{
	return false;
}