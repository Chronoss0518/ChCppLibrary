#ifndef Ch_CPP_Math3D_h
#define Ch_CPP_Math3D_h

#include <float.h>
#include <cmath>

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

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChVector2()
	{
		val.Identity();
	}

	inline ChVector2(const float _num)
	{
		val.Set(_num);
	}

	inline ChVector2(
		const float _x, const float _y)
	{
		x = _x;
		y = _y;
	}

	inline ChVector2(const ChVector2& _vec) { *this = _vec; }

	inline ChVector2(const D3DXVECTOR2& _vec) { *this = _vec; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";");

	void Deserialize(
		const std::string& _str
		, const size_t _fPos = 0
		, const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const unsigned int _digit = 6);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

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

	//???????s??(Now??0?`1)
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

	///////////////////////////////////////////////////////////////////////////////////

	inline float Len(const unsigned long _digit = 6) const
	{
		return GetLen(*this, ChVector2(),_digit);
	}

	inline float ElementsLen() const
	{
		return GetElementsLen(*this, ChVector2());
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Abs()
	{
		val.Abs();
	}

	inline void Abs(const ChVector2& _vec)
	{
		val.Abs(_vec.val);
	}

	///////////////////////////////////////////////////////////////////////////////////

	//???????s??(Now??0?`1)
	inline void Correction(
		const ChVector2& _start, const ChVector2& _end, const float _Now)
	{
		*this = GetCorrection(_start, _end, _Now);
	}

	///////////////////////////////////////////////////////////////////////////////////

	ChStd::Bool Normalize(const unsigned long _digit = 6);

	void ElementsNormalize();

	///////////////////////////////////////////////////////////////////////////////////

	void Cross(
		const ChVector2& _vec1, 
		const ChVector2& _vec2,
		const unsigned long _digit = 6);

};

using ChVec2 = ChVector2;

struct ChVector3 : public ChMath::Vector3Base<float>
{

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

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

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

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";");

	void Deserialize(
		const std::string& _str
		, const size_t _fPos = 0
		, const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const unsigned int _digit = 6);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

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

	//???????s??(Now??0?`1)
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

	///////////////////////////////////////////////////////////////////////////////////

	inline float Len(const unsigned long _digit = 6) const
	{
		return GetLen(*this, ChVector3(), _digit);
	}

	inline float ElementsLen()const
	{
		return GetElementsLen(*this, ChVector3());
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Abs()
	{
		val.Abs();
	}

	inline void Abs(const ChVector3& _vec)
	{
		val.Abs(_vec.val);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline float Dot(
		const ChVector3& _vec,
		const unsigned long _digit = 6)
	{
		return GetDot(*this, _vec, _digit);
	}

	///////////////////////////////////////////////////////////////////////////////////

	//???????s??(Now??0?`1)
	inline void Correction(
		const ChVector3& _start, const ChVector3& _end, const float _Now)
	{
		*this = GetCorrection(_start, _end, _Now);
	}

	///////////////////////////////////////////////////////////////////////////////////

	ChStd::Bool Normalize(
		const unsigned long _digit = 6);

	void ElementsNormalize();

	///////////////////////////////////////////////////////////////////////////////////

	void Cross(
		const ChVector3& _vec1,
		const ChVector3& _vec2,
		const unsigned long _digit = 6);

};

using ChVec3 = ChVector3;

///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////

struct ChVector4 : public ChMath::Vector4Base<float>
{

	///////////////////////////////////////////////////////////////////////////////////
	//StaticFunction//


	///////////////////////////////////////////////////////////////////////////////////
	//Operator//

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

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

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

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";");

	std::string SerializeARGB(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";");

	void Deserialize(
		const std::string& _str
		, const size_t _fPos = 0
		, const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const unsigned int _digit = 6);

	void DeserializeARGB(
		const std::string& _str
		, const size_t _fPos = 0
		, const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const unsigned int _digit = 6);

	inline void WParamSaturate()
	{
		w = w > -1.0f ? (w < 1.0f ? w : 1.0f) : -1.0f;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	static ChVector4 GetCross(
		const ChVector4& _vec1,
		const ChVector4& _vec2,
		const unsigned long _digit = 6);

	static float GetCos(
		const ChVector4& _vec1,
		const ChVector4& _vec2,
		const unsigned long _digit = 6);

	static float GetRadian(
		const ChVector4& _vec1,
		const ChVector4& _vec2,
		const unsigned long _digit = 6);

	static float GetDot(
		const ChVector4& _vec1,
		const ChVector4& _vec2,
		const unsigned long _digit = 6);

	//???????s??(Now??0?`1)
	static ChVector4 GetCorrection(
		const ChVector4& _start,
		const ChVector4& _end,
		const float _Now);

	static float GetLen(
		const ChVector4& _vec1,
		const ChVector4& _vec2,
		const unsigned long _digit = 6);

	static float GetElementsLen(
		const ChVector4& _vec1,
		const ChVector4& _vec2);

	///////////////////////////////////////////////////////////////////////////////////

	inline float Len(const unsigned long _digit = 6) const
	{
		return GetLen(*this, ChVector4(), _digit);
	}

	inline float ElementsLen()const
	{
		return GetElementsLen(*this, ChVector4());
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Abs()
	{
		val.Abs();
	}

	inline void Abs(const ChVector4& _vec)
	{
		val.Abs(_vec.val);
	}

	///////////////////////////////////////////////////////////////////////////////////

	//???????s??(Now??0?`1)
	inline void Correction(
		const ChVector4& _start,
		const ChVector4& _end,
		const float _Now)
	{
		*this = GetCorrection(_start, _end, _Now);
	}

	///////////////////////////////////////////////////////////////////////////////////

	ChStd::Bool Normalize(const unsigned long _digit = 6);

	void ElementsNormalize();

	///////////////////////////////////////////////////////////////////////////////////

	void Cross(
		const ChVector4& _vec1,
		const ChVector4& _vec2,
		const unsigned long _digit = 6);

	inline ChStd::Bool IsOverlaps(const ChVector4& _vec)
	{
		return ChMath::Vector4Base<float>::IsOverlaps(_vec);
	}

	inline ChVector4 OverlapsRect(const ChVector4& _vec)
	{
		ChVector4 out;
		out.val.Set(ChMath::Vector4Base<float>::OverlapsRect(_vec).val);
		return out;
	}

};

using ChVec4 = ChVector4;

///////////////////////////////////////////////////////////////////////////////////

struct ChQuaternion : public ChMath::Vector4Base<float>
{

	inline ChQuaternion& operator=(const ChQuaternion& _qua)
	{
		val.Set(_qua.val);
	}

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

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChQuaternion()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	inline ChQuaternion(const float _num)
	{
		x = _num;
		y = _num;
		z = _num;
	}

	inline ChQuaternion(
		const float _x, const float _y, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	inline ChQuaternion(const ChQuaternion& _qua) { *this = _qua; }

	inline ChQuaternion(const D3DXVECTOR3& _vec) { *this = _vec; }
	inline ChQuaternion(const DirectX::XMFLOAT3& _vec) { *this = _vec; }

	inline ChQuaternion(const D3DXQUATERNION& _qua) { *this = _qua; }
	inline ChQuaternion(const DirectX::XMFLOAT4& _qua) { *this = _qua; }

	inline ChQuaternion(const D3DXMATRIX& _mat) { *this = _mat; }
	inline ChQuaternion(const DirectX::XMFLOAT4X4& _mat) { *this = _mat; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";");

	void Deserialize(
		const std::string& _str
		, const size_t _fPos = 0,
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const unsigned int _digit = 6);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	ChVec3 GetEulerAngleForVec3() const;

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotYPR(const ChVec3& _vec)
	{
		RotYPR(_vec.x, _vec.y, _vec.z);
	}

	void RotYPR(
		const float _x, const float _y, const float _z);

};

using ChQua = ChQuaternion;

struct ChLMatrix;
struct ChRMatrix;

//LeftHandAxisMatrix//
struct ChLMatrix : public ChMath::BaseMatrix4x4<float>
{
	///////////////////////////////////////////////////////////////////////////////////
	//Operator//

	ChLMatrix& operator =(const ChLMatrix& _mat);

	ChLMatrix& operator += (const ChLMatrix& _mat);
	ChLMatrix const operator + (const ChLMatrix& _mat)const;

	ChLMatrix& operator -= (const ChLMatrix& _mat);
	ChLMatrix const operator - (const ChLMatrix& _mat)const;

	ChLMatrix& operator *= (const ChLMatrix& _mat);
	ChLMatrix const operator * (const ChLMatrix& _mat)const;

	ChLMatrix& operator /= (const ChLMatrix& _mat);
	ChLMatrix const operator / (const ChLMatrix& _mat)const;

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

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

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

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	inline std::string Serialize(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";")
	{
		return m.Serialize(_cutChar);
	}

	inline std::string SerializeUpper(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const std::string& _cutTo4Char = "\n")
	{
		return m.SerializeUpper(_cutChar, _endChar, _cutTo4Char);
	}

	inline void Deserialize(
		const std::string& _str
		, const size_t _fPos = 0
		, const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const unsigned int _digit = 6)
	{
		m.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
	}


	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	void SetPosition(const ChVec3& _vec);

	void SetPosition(const float _x, const float _y, const float _z);

	void SetRotation(
		const ChVec3& _vec,
		const unsigned long _digit = 6);

	void SetRotation(
		const float _x, 
		const float _y, 
		const float _z,
		const unsigned long _digit = 6);

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

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	ChVec3 GetPosition()const;

	ChVec3 GetRotation(const unsigned long _digit = 6)const;

	ChVec3 GetScalling(const unsigned long _digit = 6)const;

	///////////////////////////////////////////////////////////////////////////////////

	ChVec4 Transform(const ChVec4& _Base)const;

	ChVec4 TransformCoord(const ChVec4& _Base)const;

	///////////////////////////////////////////////////////////////////////////////////

	void Identity()
	{
		m.Identity();
	}

	///////////////////////////////////////////////////////////////////////////////////

	void Inverse()
	{
		m.Inverse();
	}

	///////////////////////////////////////////////////////////////////////////////////

	ChRMatrix ConvertAxis();

};


//RightHandAxisMatrix//
struct ChRMatrix : public ChMath::BaseMatrix4x4<float>
{
	ChRMatrix& operator =(const ChRMatrix& _mat);

	ChRMatrix& operator += (const ChRMatrix& _mat);
	ChRMatrix const operator + (const ChRMatrix& _mat)const;

	ChRMatrix& operator -= (const ChRMatrix& _mat);
	ChRMatrix const operator - (const ChRMatrix& _mat)const;

	ChRMatrix& operator *= (const ChRMatrix& _mat);
	ChRMatrix const operator * (const ChRMatrix& _mat)const;

	ChRMatrix& operator /= (const ChRMatrix& _mat);
	ChRMatrix const operator / (const ChRMatrix& _mat)const;

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChRMatrix()
	{
		Identity();
	}

	inline ChRMatrix(const ChRMatrix& _mat) { m.Set(_mat.m); }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	inline std::string Serialize(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";")
	{
		return m.Serialize(_cutChar);
	}

	inline std::string SerializeUpper(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const std::string& _cutTo4Char = "\n")
	{
		return m.SerializeUpper(_cutChar, _endChar, _cutTo4Char);
	}

	inline void Deserialize(
		const std::string& _str
		, const size_t _fPos = 0
		, const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const unsigned int _digit = 6)
	{
		m.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
	}

	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	void SetPosition(const ChVec3& _vec);

	void SetPosition(const float _x, const float _y, const float _z);

	void SetRotation(
		const ChVec3& _vec,
		const unsigned long _digit = 6);

	void SetRotation(
		const float _x, 
		const float _y, 
		const float _z,
		const unsigned long _digit = 6);

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

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	ChVec3 GetPosition()const;

	ChVec3 GetRotation(const unsigned long _digit = 6)const;

	ChVec3 GetScalling(const unsigned long _digit = 6)const;

	///////////////////////////////////////////////////////////////////////////////////

	ChVec4 Transform(const ChVec4 _Base)const;

	ChVec4 TransformCoord(const ChVec4 _Base)const;

	///////////////////////////////////////////////////////////////////////////////////

	void Identity()
	{
		m.Identity();
	}

	///////////////////////////////////////////////////////////////////////////////////

	void Inverse()
	{
		m.Inverse();
	}

	///////////////////////////////////////////////////////////////////////////////////

	ChLMatrix ConvertAxis();

};

using ChRMat = ChRMatrix;
using ChLMat = ChLMatrix;

struct ChUIMatrix : public ChMath::BaseMatrix4x4<unsigned long>
{
	///////////////////////////////////////////////////////////////////////////////////
	//Operator//

	ChUIMatrix& operator =(const ChUIMatrix _mat);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChUIMatrix()
	{
		m.Set(0UL);
	}

	inline ChUIMatrix(const ChUIMatrix& _mat) { m.Set(_mat.m); }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";");

	std::string SerializeUpper(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const std::string& _cutTo4Char = "\n");

	void Deserialize(
		const std::string& _str
		, const size_t _fPos = 0
		, const std::string& _cutChar = ","
		, const std::string& _endChar = ";");

	///////////////////////////////////////////////////////////////////////////////////

};

using ChUIMat = ChUIMatrix;

namespace ChMath
{

	class Degree;
	class Radian;

	//?x???@???????????????p?x???????????????N???X//
	class Degree
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//operator
		///////////////////////////////////////////////////////////////////////////////////

		inline Degree& operator=(const Degree _num)
		{
			val = _num;
			return *this;
		}

		Degree& operator=(const float _num);
		Degree& operator=(const Radian _num);

		Degree& operator+=(const float _num);
		Degree operator+(const float _num) const;

		Degree& operator-=(const float _num);
		Degree operator-(const float _num) const;

		Degree& operator*=(const float _num);
		Degree operator*(const float _num) const;

		Degree& operator/=(const float _num);
		Degree operator/(const float _num) const;

		operator float() const;

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer
		///////////////////////////////////////////////////////////////////////////////////

		Degree();

		Degree(const float _val);

		Degree(const Degree& _val);

		Degree(const Radian& _val);

		///////////////////////////////////////////////////////////////////////////////////

	private:
		void Math();

		float val;
	};

	//???x?@(?~????)???????????????p?x???????????????N???X//
	class Radian
	{

	public:
		///////////////////////////////////////////////////////////////////////////////////
		//operator
		///////////////////////////////////////////////////////////////////////////////////

		inline Radian operator=(const Radian _num)
		{
			val = _num;
			return *this;
		}

		Radian& operator=(const float _num);
		Radian& operator=(const Degree _num);

		Radian& operator+=(const float _num);
		Radian operator+(const float _num) const;

		Radian& operator-=(const float _num);
		Radian operator-(const float _num) const;

		Radian& operator*=(const float _num);
		Radian operator*(const float _num) const;

		Radian& operator/=(const float _num);
		Radian operator/(const float _num) const;

		operator float() const;

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer
		///////////////////////////////////////////////////////////////////////////////////

		Radian();

		Radian(const float _val);

		Radian(const Radian& _val);

		Radian(const Degree& _val);

		///////////////////////////////////////////////////////////////////////////////////

	private:
		void Math();

		float val;
	};

	//?O?p?????\??????3???_??????????????//
	typedef struct TriVertex
	{
		ChVec3 Ver1, Ver2, Ver3;
		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		inline TriVertex() {}

		inline TriVertex(
			const ChVec3& _1, const ChVec3& _2, const ChVec3& _3)
		{
			Ver1 = _1;
			Ver2 = _2;
			Ver3 = _3;
		}

	} TriVer;

	//3???_?????@????????????//
	//?@?????O???_???O??(?????????x?N?g??)???Z?o??????????????//
	ChVector3 GetFaceNormal(
		const TriVertex& _PlEq,
		const unsigned long _digit = 6);

	ChVector3 GetFaceNormal(
		const ChVec3& _Pos1, 
		const ChVec3& _Pos2,
		const ChVec3& _Pos3,
		const unsigned long _digit = 6);

	//Radian?p????Degree?p??//
	static inline float ToDegree(const float _Radian) { return (_Radian * 180.0f / PI); }

	//Degree?p????Radian?p??//
	static inline float ToRadian(const float _degree) { return (_degree * PI / 180.0f); }

	//???????????????????m?F????//
	static inline ChStd::Bool IsPSign(const int _val) { return _val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const char _val) { return _val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const short _val) { return _val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const long _val) { return _val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const float _val) { return _val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const double _val) { return _val >= 0.0f ? true : false; }

} // namespace ChMath

#endif