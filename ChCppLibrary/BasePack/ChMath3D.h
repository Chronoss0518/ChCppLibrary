#ifndef Ch_CPP_Math3D_h
#define Ch_CPP_Math3D_h

#include"ChMath.h"

struct D3DXVECTOR4;
struct D3DXVECTOR3;
struct D3DXVECTOR2;

struct D3DXMATRIX;
struct D3DXQUATERNION;

namespace DirectX
{
	struct XMFLOAT3;
	struct XMFLOAT4;
	struct XMFLOAT4X4;
} // namespace DirectX

struct ChVector4;
struct ChVector3;
struct ChVector2;
struct ChRMatrix;
struct ChLMatrix;
struct ChUIMatrix;

struct ChVector2 : public ChMath::Vector2Base<float>
{
public://Static Functions//

	static ChVector2 FromPosition(const float& _x, const float& _y);
	static ChVector2 FromSize(const float& _w, const float& _h);
	static ChVector2 FromTime(const float& _start, const float& _end);
	static ChVector2 FromHighLow(const float& _high, const float& _low);

public://Operator Functions//

	ChVector2& operator*=(const float& _num);
	ChVector2 operator*(const float& _num) const;
	ChVector2& operator/=(const float& _num);
	ChVector2 operator/(const float& _num) const;
	ChVector2& operator=(const float& _num);

	ChVector2& operator=(const ChVector2& _vec);
	ChVector2& operator-=(const ChVector2& _vec);
	ChVector2 operator-(const ChVector2& _vec) const;
	ChVector2& operator+=(const ChVector2& _vec);
	ChVector2 operator+(const ChVector2& _vec) const;
	ChVector2& operator*=(const ChVector2& _vec);
	ChVector2 operator*(const ChVector2& _vec) const;
	ChVector2& operator/=(const ChVector2& _vec);
	ChVector2 operator/(const ChVector2& _vec) const;

	bool operator==(const ChVector2& _vec)const
	{
		return val == _vec.val;
	}

	bool operator!=(const ChVector2& _vec)const
	{
		return val != _vec.val;
	}

	operator const ChVector4() const;
	operator const ChVector3() const;

	operator const D3DXVECTOR2() const;
	operator const D3DXVECTOR2* () const;

	ChVector2& operator=(const D3DXVECTOR2&);

public://Constructor Destructor//

	inline ChVector2()
	{
		val.Identity();
	}

	inline ChVector2(const float _num)
	{
		val.Set(_num);
	}

	inline ChVector2(const float _x, const float _y)
	{
		x = _x;
		y = _y;
	}

	inline ChVector2(const ChVector2& _vec) { *this = _vec; }

	inline ChVector2(const D3DXVECTOR2& _vec) { *this = _vec; }

public://Serialize Deserialize//

	const char* Serialize(
		const char* _cutChar = ",",
		const char* _endChar = ";")const;

	const wchar_t* Serialize(
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";")const;

	void Deserialize(
		const char* _str,
		const size_t _fPos = 0,
		const char* _cutChar = ",",
		const char* _endChar = ";",
		const unsigned int _digit = 6);

	void Deserialize(
		const wchar_t* _str,
		const size_t _fPos = 0,
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";",
		const unsigned int _digit = 6);

public://Set Function//

	inline void SetLen(const float _len)
	{
		val.SetLen(_len);
	}

public://Get Function//

	static ChVector2 GetCross(
		const ChVector2& _vec1,
		const ChVector2& _vec2,
		const unsigned long _digit = 6);

	static float GetCos(
		const ChVector2& _vec1, 
		const ChVector2& _vec2,
		const unsigned long _digit = 6);

	static float GetRadian(
		const ChVector2& _vec1,
		const ChVector2& _vec2,
		const unsigned long _digit = 6);

	static float GetDot(
		const ChVector2& _vec1, 
		const ChVector2& _vec2,
		const unsigned long _digit = 6);

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	static ChVector2 GetCorrection(
		const ChVector2& _start, 
		const ChVector2& _end, 
		const float _Now);

	static float GetLen(
		const ChVector2& _vec1, 
		const ChVector2& _vec2,
		const unsigned long _digit = 6);

	static float GetElementsLen(
		const ChVector2& _vec1,
		const ChVector2& _vec2);

public://Other Functions//

	inline void Abs()
	{
		val.Abs();
	}

	inline void Abs(const ChVector2& _vec)
	{
		val.Abs(_vec.val);
	}

public:

	inline float Len(const unsigned long _digit = 6) const
	{
		return GetLen(*this, ChVector2(),_digit);
	}

	inline float ElementsLen() const
	{
		return GetElementsLen(*this, ChVector2());
	}

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	inline void Correction(
		const ChVector2& _start,
		const ChVector2& _end,
		const float _Now)
	{
		*this = GetCorrection(_start, _end, _Now);
	}

	bool Normalize(const unsigned long _digit = 6)
	{
		return val.Normalize(_digit);
}

	void ElementsNormalize()
	{
		val.ElementsNormalize();
	}

	void Cross(
		const ChVector2& _vec1, 
		const ChVector2& _vec2,
		const unsigned long _digit = 6)
	{
		*this = GetCross(_vec1, _vec2, _digit);
	}


	static ChVector2 Lerp(
		const ChVector2& _start,
		const ChVector2& _end,
		const float _pow);

};

using ChVec2 = ChVector2;

struct ChVector3 : public ChMath::Vector3Base<float>
{
public://Static Functions//

	static ChVector3 FromPosition(const float& _x, const float& _y, const float _z);
	static ChVector3 FromColor(const float& _r, const float& _g, const float& _b);

public://Operator Functions//

	ChVector3& operator*=(const float& _num);
	ChVector3 operator*(const float& _num) const;
	ChVector3& operator/=(const float& _num);
	ChVector3 operator/(const float& _num) const;
	ChVector3& operator=(const float& _num);

	ChVector3& operator=(const ChVector3& _vec);
	ChVector3& operator-=(const ChVector3& _vec);
	ChVector3 operator-(const ChVector3& _vec) const;
	ChVector3& operator+=(const ChVector3& _vec);
	ChVector3 operator+(const ChVector3& _vec) const;
	ChVector3& operator*=(const ChVector3& _vec);
	ChVector3 operator*(const ChVector3& _vec) const;
	ChVector3& operator/=(const ChVector3& _vec);
	ChVector3 operator/(const ChVector3& _vec) const;

	bool operator==(const ChVector3& _vec)const
	{
		return val == _vec.val;
	}

	bool operator!=(const ChVector3& _vec)const
	{
		return val != _vec.val;
	}

	operator const ChVector4() const;
	operator const ChVector2() const;

	operator const D3DXVECTOR3() const;
	operator const D3DXVECTOR3* () const;

	operator const DirectX::XMFLOAT3() const;
	operator const DirectX::XMFLOAT3* () const;

	ChVector3& operator=(const D3DXVECTOR3&);
	ChVector3& operator=(const DirectX::XMFLOAT3&);

	ChVector3& operator=(const D3DXQUATERNION&);
	ChVector3& operator=(const DirectX::XMFLOAT4&);

	ChVector3& operator=(const D3DXMATRIX&);
	ChVector3& operator=(const DirectX::XMFLOAT4X4&);

public://Constructor Destructor//

	inline ChVector3()
	{
		val.Identity();
	}

	inline ChVector3(const float _num)
	{
		val.Set(_num);
	}

	inline ChVector3(
		const float _x, const float _y, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	inline ChVector3(const ChVector3& _vec) { *this = _vec; }

	inline ChVector3(const D3DXVECTOR3& _vec) { *this = _vec; }
	inline ChVector3(const DirectX::XMFLOAT3& _vec) { *this = _vec; }

	inline ChVector3(const D3DXQUATERNION& _Qua) { *this = _Qua; }
	inline ChVector3(const DirectX::XMFLOAT4& _Qua) { *this = _Qua; }

	inline ChVector3(const D3DXMATRIX& _mat) { *this = _mat; }
	inline ChVector3(const DirectX::XMFLOAT4X4& _mat) { *this = _mat; }

public://Serialize Deserialize//

	inline const char* Serialize(
		const char* _cutChar = ",",
		const char* _endChar = ";")const
	{
		return val.Serialize(_cutChar, _endChar);
	}

	inline const wchar_t* Serialize(
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";")const
	{
		return val.Serialize(_cutChar, _endChar);
	}

	inline void Deserialize(
		const char* _str,
		const size_t _fPos = 0,
		const char* _cutChar = ",",
		const char* _endChar = ";",
		const unsigned int _digit = 6)
	{
		val.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
	}

	inline void Deserialize(
		const wchar_t* _str,
		const size_t _fPos = 0,
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";",
		const unsigned int _digit = 6)
	{
		val.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
	}

public://Set Function//

	inline void SetLen(const float _len)
	{
		val.SetLen(_len);
	}

public://Get Function//

	static ChVector3 GetCross(
		const ChVector3& _vec1,
		const ChVector3& _vec2,
		const unsigned long _digit = 6);

	static float GetCos(
		const ChVector3& _vec1,
		const ChVector3& _vec2,
		const unsigned long _digit = 6);

	static float GetRadian(
		const ChVector3& _vec1,
		const ChVector3& _vec2,
		const unsigned long _digit = 6);

	static float GetDot(
		const ChVector3& _vec1,
		const ChVector3& _vec2,
		const unsigned long _digit = 6);

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	static ChVector3 GetCorrection(
		const ChVector3& _start,
		const ChVector3& _end,
		const float _Now);

	static float GetLen(
		const ChVector3& _vec1,
		const ChVector3& _vec2,
		const unsigned long _digit = 6);

	static float GetElementsLen(
		const ChVector3& _vec1,
		const ChVector3& _vec2);

public://Other Functions//

	inline void Abs()
	{
		val.Abs();
	}

	inline void Abs(const ChVector3& _vec)
	{
		val.Abs(_vec.val);
	}

public:

	inline float Len(const unsigned long _digit = 6) const
	{
		return GetLen(*this, ChVector3(), _digit);
	}

	inline float ElementsLen()const
	{
		return GetElementsLen(*this, ChVector3());
	}

	inline float Dot(
		const ChVector3& _vec,
		const unsigned long _digit = 6)
	{
		return GetDot(*this, _vec, _digit);
	}

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	inline void Correction(
		const ChVector3& _start,
		const ChVector3& _end,
		const float _Now)
	{
		*this = GetCorrection(_start, _end, _Now);
	}

	bool Normalize(const unsigned long _digit = 6)
	{
		return val.Normalize(_digit);
	}

	void ElementsNormalize()
	{
		val.ElementsNormalize();
	}

	void Cross(
		const ChVector3& _vec1,
		const ChVector3& _vec2,
		const unsigned long _digit = 6)
	{
		*this = GetCross(_vec1, _vec2, _digit);
	}

	static ChVector3 Lerp(
		const ChVector3& _start,
		const ChVector3& _end,
		const float _pow)
	{
		ChVector3 out;
		out.val.Set(ChMath::VectorBase<float, 3>::Lerp(_start.val, _end.val, _pow));
		return out;
	}

};

using ChVec3 = ChVector3;

///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////

struct ChVector4 : public ChMath::Vector4Base<float>
{
public://Static Functions//

	static ChVector4 FromPosition(const float& _x, const float& _y, const float _z, const float& _w);
	static ChVector4 FromColor(const float& _r, const float& _g, const float& _b, const float& _a);
	static ChVector4 FromRect(const float& _left, const float& _top, const float& _right, const float& _bottom);

public://Operator Functions//

	ChVector4& operator*=(const float& _num);
	ChVector4 operator*(const float& _num) const;
	ChVector4& operator/=(const float& _num);
	ChVector4 operator/(const float& _num) const;
	ChVector4& operator=(const float& _num);

	ChVector4& operator=(const ChVector4& _vec);
	ChVector4& operator-=(const ChVector4& _vec);
	ChVector4 operator-(const ChVector4& _vec) const;
	ChVector4& operator+=(const ChVector4& _vec);
	ChVector4 operator+(const ChVector4& _vec) const;
	ChVector4& operator*=(const ChVector4& _vec);
	ChVector4 operator*(const ChVector4& _vec) const;
	ChVector4& operator/=(const ChVector4& _vec);
	ChVector4 operator/(const ChVector4& _vec) const;

	bool operator==(const ChVector4& _vec)const
	{
		return val == _vec.val;
	}

	bool operator!=(const ChVector4& _vec)const
	{
		return val != _vec.val;
	}

	operator const ChVector3() const;
	operator const ChVector2() const;

	operator const D3DXVECTOR4() const;
	operator const D3DXVECTOR4* () const;

	ChVector4& operator=(const D3DXVECTOR4&);

public://Constructor Destructor//

	inline ChVector4()
	{
		val.Identity();
	}

	inline ChVector4(const float _num)
	{
		val.Set(_num);
	}

	inline ChVector4(
		const float _x, const float _y, const float _z, const float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	inline ChVector4(const ChVector4& _vec) { *this = _vec; }

	inline ChVector4(const D3DXVECTOR4& _vec) { *this = _vec; }

public://Serialize Deserialize//

	inline const char* Serialize(
		const char* _cutChar = ",",
		const char* _endChar = ";")const
	{
		return val.Serialize(_cutChar, _endChar);
	}

	inline const wchar_t* Serialize(
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";")const
	{
		return val.Serialize(_cutChar, _endChar);
	}

	const char* SerializeARGB(
		const char* _cutChar = ",",
		const char* _endChar = ";")const;

	const wchar_t* SerializeARGB(
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";")const;

	inline void Deserialize(
		const char* _str,
		const size_t _fPos = 0,
		const char* _cutChar = ",",
		const char* _endChar = ";",
		const unsigned int _digit = 6)
	{
		val.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
	}

	inline void Deserialize(
		const wchar_t* _str,
		const size_t _fPos = 0,
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";",
		const unsigned int _digit = 6)
	{
		val.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
	}

	void DeserializeARGB(
		const char* _str,
		const size_t _fPos = 0,
		const char* _cutChar = ",",
		const char* _endChar = ";",
		const unsigned int _digit = 6);

	void DeserializeARGB(
		const wchar_t* _str,
		const size_t _fPos = 0,
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";",
		const unsigned int _digit = 6);

public:

	inline void WParamSaturate()
	{
		w = w > -1.0f ? (w < 1.0f ? w : 1.0f) : -1.0f;
	}

public://Set Function//

	inline void SetLen(const float _len)
	{
		val.SetLen(_len);
	}

public://Get Function//

	inline static ChVector4 GetCross(
		const ChVector4& _vec1,
		const ChVector4& _vec2,
		const unsigned long _digit = 6)
	{
		ChVector4 tmpVec;
		tmpVec.val.Cross(_vec1.val, _vec2.val, _digit);
		return tmpVec;
	}

	static float GetCos(
		const ChVector4& _vec1,
		const ChVector4& _vec2,
		const unsigned long _digit = 6)
	{
		return _vec1.val.GetCos(_vec2.val, _digit);
	}

	static float GetRadian(
		const ChVector4& _vec1,
		const ChVector4& _vec2,
		const unsigned long _digit = 6)
	{
		return _vec1.val.GetRadian(_vec2.val, _digit);
	}

	static float GetDot(
		const ChVector4& _vec1,
		const ChVector4& _vec2,
		const unsigned long _digit = 6)
	{
		return _vec1.val.GetDot(_vec2.val, _digit);
	}

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	static ChVector4 GetCorrection(
		const ChVector4& _start,
		const ChVector4& _end,
		const float _Now)
	{
		ChVector4 tmpVec;
		tmpVec.val.Correction(_start.val, _end.val, _Now);
		return tmpVec;
	}

	static float GetLen(
		const ChVector4& _vec1,
		const ChVector4& _vec2,
		const unsigned long _digit = 6)
	{
		ChVector4 tmpVec = _vec1 - _vec2;
		return  tmpVec.val.GetLen(_digit);
	}

	static float GetElementsLen(
		const ChVector4& _vec1,
		const ChVector4& _vec2)
	{
		ChVector4 tmpVec = _vec1 - _vec2;
		return  tmpVec.val.GetElementsLen();
	}

public://Other Functions//

	inline void Abs()
	{
		val.Abs();
	}

	inline void Abs(const ChVector4& _vec)
	{
		val.Abs(_vec.val);
	}

public:

	inline float Len(const unsigned long _digit = 6) const
	{
		return GetLen(*this, ChVector4(), _digit);
	}

	inline float ElementsLen()const
	{
		return GetElementsLen(*this, ChVector4());
	}

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	inline void Correction(
		const ChVector4& _start,
		const ChVector4& _end,
		const float _Now)
	{
		*this = GetCorrection(_start, _end, _Now);
	}

	inline bool Normalize(const unsigned long _digit = 6)
	{
		return val.Normalize(_digit);
	}

	void Cross(
		const ChVector4& _vec1,
		const ChVector4& _vec2,
		const unsigned long _digit = 6)
	{
		val.Cross(_vec1.val, _vec2.val, _digit);
	}

	void ElementsNormalize()
	{
		val.ElementsNormalize();
	}

	static ChVector4 Lerp(
		const ChVector4& _start,
		const ChVector4& _end,
		const float _pow)
	{
		ChVector4 out;
		out.val.Set(ChMath::VectorBase<float, 4>::Lerp(_start.val, _end.val, _pow));
		return out;
	}

};

using ChVec4 = ChVector4;

struct ChEularXYZ : public ChVector3 {};
struct ChEularXZY : public ChVector3 {};
struct ChEularYXZ : public ChVector3 {};
struct ChEularYZX : public ChVector3 {};
struct ChEularZXY : public ChVector3 {};
struct ChEularZYX : public ChVector3 {};

struct ChLMatrix;
struct ChRMatrix;

struct ChQuaternion : public ChMath::QuaternionBase<float>
{
public://Operator Functions//

	ChQuaternion& operator=(const ChQuaternion& _qua);

	ChQuaternion& operator+=(const ChQuaternion& _num);
	ChQuaternion operator+(const ChQuaternion& _num) const;

	ChQuaternion& operator*=(const ChQuaternion& _num);
	ChQuaternion operator*(const ChQuaternion& _num) const;

	operator const D3DXQUATERNION() const;
	operator const D3DXQUATERNION* () const;

	operator const DirectX::XMFLOAT4() const;
	operator const DirectX::XMFLOAT4* () const;

	ChQuaternion& operator=(const D3DXVECTOR3&);
	ChQuaternion& operator=(const DirectX::XMFLOAT3&);

	ChQuaternion& operator=(const D3DXQUATERNION&);
	ChQuaternion& operator=(const DirectX::XMFLOAT4&);

	ChQuaternion& operator=(const D3DXMATRIX&);
	ChQuaternion& operator=(const DirectX::XMFLOAT4X4&);

public://Constructor Destructor//

	inline ChQuaternion()
	{
		Identity();
	}

	inline ChQuaternion(const float _x, const float _y, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
		w = 0.0f;
	}

	inline ChQuaternion(const ChQuaternion& _qua) 
	{
		val.Set(_qua.val);
	}

#if false
	inline ChQuaternion(const D3DXVECTOR3& _vec) { *this = _vec; }
	inline ChQuaternion(const DirectX::XMFLOAT3& _vec) { *this = _vec; }

	inline ChQuaternion(const D3DXQUATERNION& _qua) { *this = _qua; }
	inline ChQuaternion(const DirectX::XMFLOAT4& _qua) { *this = _qua; }

	inline ChQuaternion(const D3DXMATRIX& _mat) { *this = _mat; }
	inline ChQuaternion(const DirectX::XMFLOAT4X4& _mat) { *this = _mat; }
#endif

public://Serialize Deserialize//

	inline const char* Serialize(
		const char* _cutChar = ",",
		const char* _endChar = ";")const
	{
		return val.Serialize(_cutChar, _endChar);
	}

	inline const wchar_t* Serialize(
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";")const
	{
		return val.Serialize(_cutChar, _endChar);
	}

	inline void Deserialize(
		const char* _str,
		const size_t _fPos = 0,
		const char* _cutChar = ",",
		const char* _endChar = ";",
		const unsigned int _digit = 6)
	{
		val.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
	}

	inline void Deserialize(
		const wchar_t* _str,
		const size_t _fPos = 0,
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";",
		const unsigned int _digit = 6)
	{
		val.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
	}

public://Sed Functions//
	
	void SetRotationLMatrix(const ChLMatrix& _mat);

	void SetRotationRMatrix(const ChRMatrix& _mat);

	void SetRotationXAxis(float _x);

	void SetRotationYAxis(float _y);

	void SetRotationZAxis(float _z);

	void SetRotation(const ChVec3& _axis, const float _angle);

	void SetRotation(const ChVec3& _from, const ChVec3& _to);

public://Get Functions//

	ChLMatrix GetRotationLMatrix(const unsigned long _digit = 6)const;

	ChRMatrix GetRotationRMatrix(const unsigned long _digit = 6)const;

	ChVec3 GetAxis()const;

	ChEularXYZ GetEulerRotationXYZ(const unsigned long _digit = 6)const;

	ChEularXZY GetEulerRotationXZY(const unsigned long _digit = 6)const;

	ChEularYXZ GetEulerRotationYXZ(const unsigned long _digit = 6)const;

	ChEularYZX GetEulerRotationYZX(const unsigned long _digit = 6)const;

	ChEularZXY GetEulerRotationZXY(const unsigned long _digit = 6)const;

	ChEularZYX GetEulerRotationZYX(const unsigned long _digit = 6)const;

	float GetRadian()const;

	float GetCos()const;

	float GetSin()const;

	static ChQuaternion GetSum(const ChQuaternion& _qua1, const ChQuaternion& _qua2);

	static ChQuaternion GetMul(const ChQuaternion& _qua1, const ChQuaternion& _qua2);

	static ChVec3 GetMul(const ChQuaternion& _qua, const ChVec3& _dir);

public://Add Functions//

	void AddRotationXAxis(float _x);

	void AddRotationYAxis(float _y);

	void AddRotationZAxis(float _z);

public://Operator Math Functions//
	
	void Sum(const ChQuaternion& _value);

	void Mul(const ChQuaternion& _value);

	ChVec3 Mul(const ChVec3& _dir);

public://Other Functions//

	static ChQuaternion SLerp(const ChQuaternion& _start, const ChQuaternion& _end, const float _pow);

	void Identity()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}

	void Inverse()
	{
		x = -x;
		y = -y;
		z = -z;
	}

};

using ChQua = ChQuaternion;


//LeftHandAxisMatrix//
struct ChLMatrix : public ChMath::BaseMatrix4x4<float>
{
public://Operator Functions//

	ChLMatrix& operator =(const ChLMatrix& _mat);

	ChLMatrix& operator += (const ChLMatrix& _mat);
	ChLMatrix const operator + (const ChLMatrix& _mat)const;

	ChLMatrix& operator -= (const ChLMatrix& _mat);
	ChLMatrix const operator - (const ChLMatrix& _mat)const;

	ChLMatrix& operator *= (const ChLMatrix& _mat);
	ChLMatrix const operator * (const ChLMatrix& _mat)const;

	ChLMatrix& operator /= (const ChLMatrix& _mat);
	ChLMatrix const operator / (const ChLMatrix& _mat)const;

	bool operator == (const ChLMatrix& _mat)const;
	bool operator != (const ChLMatrix& _mat)const;

	operator const D3DXMATRIX() const;
	operator const D3DXMATRIX* () const;

	operator const DirectX::XMFLOAT4X4() const;
	operator const DirectX::XMFLOAT4X4* () const;

	ChLMatrix& operator=(const D3DXVECTOR3&);
	ChLMatrix& operator=(const DirectX::XMFLOAT3&);

	ChLMatrix& operator=(const D3DXQUATERNION&);
	ChLMatrix& operator=(const DirectX::XMFLOAT4&);

	ChLMatrix& operator=(const D3DXMATRIX&);
	ChLMatrix& operator=(const DirectX::XMFLOAT4X4&);

public://Constructor Destructor//

	inline ChLMatrix()
	{
		Identity();
	}

	inline ChLMatrix(const ChLMatrix& _mat) { m.Set(_mat.m); }

	inline ChLMatrix(const D3DXVECTOR3& _vec) { *this = _vec; }
	inline ChLMatrix(const DirectX::XMFLOAT3& _vec) { *this = _vec; }

	inline ChLMatrix(const D3DXQUATERNION& _Qua) { *this = _Qua; }
	inline ChLMatrix(const DirectX::XMFLOAT4& _Qua) { *this = _Qua; }

	inline ChLMatrix(const D3DXMATRIX& _mat) { *this = _mat; }
	inline ChLMatrix(const DirectX::XMFLOAT4X4& _mat) { *this = _mat; }

public://Serialize Deserialize//

	inline const char* Serialize(
		const char* _cutChar = ",",
		const char* _endChar = ";")const
	{
		return m.Serialize(_cutChar);
	}

	inline const wchar_t* Serialize(
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";")const
	{
		return m.Serialize(_cutChar);
	}

	inline const char* SerializeUpper(
		const char* _cutChar = ",",
		const char* _endChar = ";",
		const char* _cutTo4Char = "\n")const
	{
		return m.SerializeUpper(_cutChar, _endChar, _cutTo4Char);
	}

	inline const wchar_t* SerializeUpper(
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";",
		const wchar_t* _cutTo4Char = L"\n")const
	{
		return m.SerializeUpper(_cutChar, _endChar, _cutTo4Char);
	}

	inline void Deserialize(
		const char* _str,
		const size_t _fPos = 0,
		const char* _cutChar = ",",
		const char* _endChar = ";",
		const unsigned int _digit = 6)
	{
		m.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
	}

	inline void Deserialize(
		const wchar_t* _str,
		const size_t _fPos = 0,
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";",
		const unsigned int _digit = 6)
	{
		m.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
	}

public://Set Functions//

	void SetPosition(const ChVec3& _vec);

	void SetPosition(const float _x, const float _y, const float _z);

	void SetRotationYPR(const float _x, const float _y, const float _z, const unsigned long _digit = 6);

	void SetRotation(const ChQua& _qua, const unsigned long _digit = 6);

	void SetRotationYPR(const ChVec3& _vec, const unsigned long _digit = 6);

	void SetRotationXAxis(const float _x);

	void SetRotationYAxis(const float _y);

	void SetRotationZAxis(const float _z);

	void SetScalling(
		const ChVec3& _vec,
		const unsigned long _digit = 6);

	void SetScalling(
		const float _x, 
		const float _y,
		const float _z,
		const unsigned long _digit = 6);

public://Get Functions//

	ChVec3 GetPosition()const;

	ChQua GetRotation(const unsigned long _digit = 6)const;

	ChEularXYZ GetEulerRotationXYZ(const unsigned long _digit = 6)const;

	ChEularXZY GetEulerRotationXZY(const unsigned long _digit = 6)const;

	ChEularYXZ GetEulerRotationYXZ(const unsigned long _digit = 6)const;

	ChEularYZX GetEulerRotationYZX(const unsigned long _digit = 6)const;

	ChEularZXY GetEulerRotationZXY(const unsigned long _digit = 6)const;

	ChEularZYX GetEulerRotationZYX(const unsigned long _digit = 6)const;

	ChVec3 GetScalling(const unsigned long _digit = 6)const;

	ChVec3 GetXAxisDirection()const;

	ChVec3 GetYAxisDirection()const;

	ChVec3 GetZAxisDirection()const;

public://Transform Functions//

	ChVec4 Transform(const ChVec4& _Base)const;

	ChVec4 TransformCoord(const ChVec4& _Base)const;

public://Other Functions//

	void Identity()
	{
		m.Identity();
	}

	void Inverse()
	{
		m.Inverse();
	}

	static ChLMatrix Lerp(
		const ChLMatrix& _start,
		const ChLMatrix& _end,
		const float _pow)
	{
		ChLMatrix out;
		out.m.Set(ChMath::SquareMatrixBase<float, 4>::Lerp(_start.m, _end.m, _pow));
		return out;
	}

	ChRMatrix ConvertAxis();
};


//RightHandAxisMatrix//
struct ChRMatrix : public ChMath::BaseMatrix4x4<float>
{
public://Operator Functions//

	ChRMatrix& operator =(const ChRMatrix& _mat);

	ChRMatrix& operator += (const ChRMatrix& _mat);
	ChRMatrix const operator + (const ChRMatrix& _mat)const;

	ChRMatrix& operator -= (const ChRMatrix& _mat);
	ChRMatrix const operator - (const ChRMatrix& _mat)const;

	ChRMatrix& operator *= (const ChRMatrix& _mat);
	ChRMatrix const operator * (const ChRMatrix& _mat)const;

	ChRMatrix& operator /= (const ChRMatrix& _mat);
	ChRMatrix const operator / (const ChRMatrix& _mat)const;

	bool operator == (const ChRMatrix& _mat)const;
	bool operator != (const ChRMatrix& _mat)const;

public://Constructor Destructor//

	inline ChRMatrix()
	{
		Identity();
	}

	inline ChRMatrix(const ChRMatrix& _mat) { m.Set(_mat.m); }

public://Serialize Deserialize//

	inline const char* Serialize(
		const char* _cutChar = ",",
		const char* _endChar = ";")const
	{
		return m.Serialize(_cutChar);
	}

	inline const wchar_t* Serialize(
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";")const
	{
		return m.Serialize(_cutChar);
	}

	inline const char* SerializeUpper(
		const char* _cutChar = ",",
		const char* _endChar = ";",
		const char* _cutTo4Char = "\n")const
	{
		return m.SerializeUpper(_cutChar, _endChar, _cutTo4Char);
	}

	inline const wchar_t* SerializeUpper(
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";",
		const wchar_t* _cutTo4Char = L"\n")const
	{
		return m.SerializeUpper(_cutChar, _endChar, _cutTo4Char);
	}

	inline void Deserialize(
		const char* _str,
		const size_t _fPos = 0,
		const char* _cutChar = ",",
		const char* _endChar = ";",
		const unsigned int _digit = 6)
	{
		m.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
	}

	inline void Deserialize(
		const wchar_t* _str,
		const size_t _fPos = 0,
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";",
		const unsigned int _digit = 6)
	{
		m.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
	}

public://Set Functions//

	void SetPosition(const ChVec3& _vec);

	void SetPosition(const float _x, const float _y, const float _z);

	void SetRotation(const ChQua& _qua, const unsigned long _digit = 6);

	void SetRotationXAxis(const float _x);

	void SetRotationYAxis(const float _y);

	void SetRotationZAxis(const float _z);

	void SetScalling(
		const ChVec3& _vec,
		const unsigned long _digit = 6);

	void SetScalling(
		const float _x,
		const float _y, 
		const float _z,
		const unsigned long _digit = 6);

public://Get Functions//

	ChVec3 GetPosition()const;

	ChVec3 GetScalling(const unsigned long _digit = 6)const;

	ChVec3 GetXAxisDirection()const;

	ChVec3 GetYAxisDirection()const;

	ChVec3 GetZAxisDirection()const;

public://Transform Functions//

	ChVec4 Transform(const ChVec4 _Base)const;

	ChVec4 TransformCoord(const ChVec4 _Base)const;

public://Other Functions//

	void Identity()
	{
		m.Identity();
	}

	void Inverse()
	{
		m.Inverse();
	}

	static ChRMatrix Lerp(
		const ChRMatrix& _start,
		const ChRMatrix& _end,
		const float _pow)
	{
		ChRMatrix out;
		out.m.Set(ChMath::SquareMatrixBase<float, 4>::Lerp(_start.m, _end.m, _pow));
		return out;
	}

	ChLMatrix ConvertAxis()const;
};

using ChRMat = ChRMatrix;
using ChLMat = ChLMatrix;

struct ChUIMatrix : public ChMath::BaseMatrix4x4<unsigned long>
{
public://Operator Functions//

	ChUIMatrix& operator =(const ChUIMatrix _mat);

public://Constructor Destructor//

	inline ChUIMatrix()
	{
		m.Set(0UL);
	}

	inline ChUIMatrix(const ChUIMatrix& _mat) { m.Set(_mat.m); }

public://Serialize Deserialize//

	inline const char* Serialize(
		const char* _cutChar = ",",
		const char* _endChar = ";")const
	{
		return m.Serialize(_cutChar, _endChar);
	}

	inline const char* SerializeUpper(
		const char* _cutChar = ",",
		const char* _endChar = ";",
		const char* _cutTo4Char = "\n")const
	{
		return m.SerializeUpper(_cutChar, _endChar, _cutTo4Char);
	}

	inline void Deserialize(
		const char* _str,
		const size_t _fPos = 0,
		const char* _cutChar = ",",
		const char* _endChar = ";")
	{
		m.Deserialize(_str, _fPos, _cutChar, _endChar);
	}

	inline const wchar_t* Serialize(
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";")const
	{
		return m.Serialize(_cutChar, _endChar);
	}

	inline const wchar_t* SerializeUpper(
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";",
		const wchar_t* _cutTo4Char = L"\n")const
	{
		return m.SerializeUpper(_cutChar, _endChar, _cutTo4Char);
	}

	inline void Deserialize(
		const wchar_t* _str,
		const size_t _fPos = 0,
		const wchar_t* _cutChar = L",",
		const wchar_t* _endChar = L";")
	{
		m.Deserialize(_str, _fPos, _cutChar, _endChar);
	}
};

using ChUIMat = ChUIMatrix;

namespace ChMath
{

	ChVector3 GetFaceNormal(
		const ChVec3& _Pos1, 
		const ChVec3& _Pos2,
		const ChVec3& _Pos3,
		const unsigned long _digit = 6);

	//RadianäpÇ©ÇÁDegreeäpÇ÷//
	static constexpr inline float ToDegree(const float _Radian) { return (_Radian * 180.0f / PI); }

	//DegreeäpÇ©ÇÁRadianäpÇ÷//
	static constexpr inline float ToRadian(const float _degree) { return (_degree * PI / 180.0f); }

	//ê≥ÇÃïÑçÜÇ©Ç«Ç§Ç©ÇämîFÇ∑ÇÈ//
	static inline bool IsPSign(const int _val) { return _val >= 0.0f; }
	static inline bool IsPSign(const char _val) { return _val >= 0.0f; }
	static inline bool IsPSign(const short _val) { return _val >= 0.0f; }
	static inline bool IsPSign(const long _val) { return _val >= 0.0f; }
	static inline bool IsPSign(const float _val) { return _val >= 0.0f; }
	static inline bool IsPSign(const double _val) { return _val >= 0.0f; }

} // namespace ChMath

#endif