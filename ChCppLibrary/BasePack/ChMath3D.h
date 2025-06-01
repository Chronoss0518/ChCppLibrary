#ifndef Ch_CPP_Math3D_h
#define Ch_CPP_Math3D_h

#include"ChStr.h"
#include"ChMath.h"

#ifndef CH_MATH3D_METHOD
#define CH_MATH3D_METHOD(_OutClass,_InClass, _MemberValue,_Method,_MethodType)\
inline _OutClass & operator _MethodType (const _InClass& _val)\
{\
	_MemberValue._Method (_val._MemberValue);\
	return *this;\
}
#endif

#ifndef CH_MATH3D_METHOD_CONST
#define CH_MATH3D_METHOD_CONST(_OutClass,_InClass ,_MethodType, _MemberValue,_Method)\
inline _OutClass operator _MethodType(const _InClass& _val)const\
{\
	_OutClass res = *this;\
	res._MemberValue._Method(_val._MemberValue);\
	return res;\
}
#endif

#ifndef CH_MATH3D_METHOD_BOOL
#define CH_MATH3D_METHOD_BOOL(_InClass,_Operator, _MemberValue)\
inline bool operator _Operator(const _InClass& _val)const\
{\
	return _MemberValue _Operator _val._MemberValue;\
}
#endif

#ifndef CH_MATH3D_METHOD_VECTOR_CONSTRUCTOR
#define CH_MATH3D_METHOD_VECTOR_CONSTRUCTOR(_VectorSize,_Type)\
inline ChVector##_VectorSize() : Vector##_VectorSize##Base<_Type>() {}\
inline ChVector##_VectorSize(const _Type _num) : Vector##_VectorSize##Base<_Type>(_num) {}\
inline ChVector##_VectorSize(const ChVector##_VectorSize& _vec) : ChMath::Vector##_VectorSize##Base<_Type>(_vec) {}\
inline ChVector##_VectorSize(const ChMath::Vector##_VectorSize##Base<_Type>& _vec) : ChMath::Vector##_VectorSize##Base<_Type>(_vec) {}
#endif

#ifndef CH_MATH3D_METHOD_MATRIX_CONSTRUCTOR
#define CH_MATH3D_METHOD_MATRIX_CONSTRUCTOR(_BaseAxis, _Type)\
inline Ch##_BaseAxis##Matrix() : ChMath::BaseMatrix4x4<_Type>() {}\
inline Ch##_BaseAxis##Matrix(const ChMath::BaseMatrix4x4<_Type> _val) : ChMath::BaseMatrix4x4<_Type>(_val) {}
#endif


#ifndef CH_MATH3D_METHOD_VECTOR_OPERATORS
#define CH_MATH3D_METHOD_VECTOR_OPERATORS(_VectorSize,_Type)\
CH_MATH3D_METHOD(ChVector##_VectorSize, ChVector##_VectorSize, val, Set, =);\
CH_MATH3D_METHOD(ChVector##_VectorSize, ChMath::Vector##_VectorSize##Base<_Type>, val, Set, =);\
CH_MATH3D_METHOD(ChVector##_VectorSize, ChMath::Vector##_VectorSize##Base<_Type>, val, Add, +=);\
CH_MATH3D_METHOD(ChVector##_VectorSize, ChMath::Vector##_VectorSize##Base<_Type>, val, Sub, -=);\
CH_MATH3D_METHOD(ChVector##_VectorSize, ChMath::Vector##_VectorSize##Base<_Type>, val, Mul, *=);\
CH_MATH3D_METHOD(ChVector##_VectorSize, ChMath::Vector##_VectorSize##Base<_Type>, val, Div, /=);\
CH_MATH_METHOD(ChVector##_VectorSize, _Type, val.Set, =);\
CH_MATH_METHOD(ChVector##_VectorSize, _Type, val.Add, +=);\
CH_MATH_METHOD(ChVector##_VectorSize, _Type, val.Sub, -=);\
CH_MATH_METHOD(ChVector##_VectorSize, _Type, val.Mul, *=);\
CH_MATH_METHOD(ChVector##_VectorSize, _Type, val.Div, /=);\
CH_MATH3D_METHOD_CONST(ChVector##_VectorSize, ChMath::Vector##_VectorSize##Base<_Type>, +, val, Add);\
CH_MATH_METHOD_CONST(ChVector##_VectorSize, _Type, +, val.Add);\
CH_MATH3D_METHOD_CONST(ChVector##_VectorSize, ChMath::Vector##_VectorSize##Base<_Type>, -, val, Sub);\
CH_MATH_METHOD_CONST(ChVector##_VectorSize, _Type, -, val.Sub);\
CH_MATH3D_METHOD_CONST(ChVector##_VectorSize, ChMath::Vector##_VectorSize##Base<_Type>, *, val, Mul);\
CH_MATH_METHOD_CONST(ChVector##_VectorSize, _Type, *, val.Mul);\
CH_MATH3D_METHOD_CONST(ChVector##_VectorSize, ChMath::Vector##_VectorSize##Base<_Type>, / , val ,Div);\
CH_MATH_METHOD_CONST(ChVector##_VectorSize, _Type, / , val.Div);\
CH_MATH3D_METHOD_BOOL(ChMath::Vector##_VectorSize##Base<_Type>, == , val);\
CH_MATH3D_METHOD_BOOL(ChMath::Vector##_VectorSize##Base<_Type>, != , val);
#endif

#ifndef CH_MATH3D_METHOD_VECTOR_SET_METHOD
#define CH_MATH3D_METHOD_VECTOR_SET_METHOD(_InClass)\
inline void SetLen(const float _len){val.SetLen(_len);}\
inline void SetCross(const _InClass& _vec1, const _InClass& _vec2, const unsigned long _digit = 6) { val.SetCross(_vec1.val, _vec2.val, _digit); }\
inline void SetLerp(const _InClass& _start,const _InClass& _end,const float _pow){val.SetLerp(_start.val, _end.val, _pow);}\
inline void SetSLerp(const _InClass& _start,const _InClass& _end,const float _pow){val.SetSLerp(_start.val, _end.val, _pow);}
#endif


#ifndef CH_MATH3D_METHOD_VECTOR_GET_METHOD
#define CH_MATH3D_METHOD_VECTOR_GET_METHOD \
inline float GetLen(const unsigned long _digit = 6)const{return val.GetLen(_digit);}\
inline float GetElementsLen()const{return val.GetElementsLen();}
#endif

#ifndef CH_MATH3D_METHOD_VECTOR_GET_STATIC_METHOD
#define CH_MATH3D_METHOD_VECTOR_GET_STATIC_METHOD(_InClass)\
inline static float GetLen(const _InClass& _vec1,const _InClass& _vec2,const unsigned long _digit = 6){_InClass tmp = _vec1 - _vec2;return tmp.GetLen(_digit);}\
inline static float GetElementsLen(const _InClass& _vec1,const _InClass& _vec2){_InClass tmp = _vec1 - _vec2;return tmp.GetElementsLen();}\
inline static _InClass GetCross(const _InClass& _vec1,const _InClass& _vec2,const unsigned long _digit = 6){_InClass tmpVec;tmpVec.val.SetCross(_vec1.val, _vec2.val, _digit);return tmpVec;}\
inline static float GetCos(const _InClass& _vec1,const _InClass& _vec2,const unsigned long _digit = 6){return _vec1.val.GetCos(_vec2.val, _digit);}\
inline static float GetRadian(const _InClass& _vec1,const _InClass& _vec2,const unsigned long _digit = 6){return _vec1.val.GetRadian(_vec2.val, _digit);}\
inline static float GetDot(const _InClass& _vec1,const _InClass& _vec2,const unsigned long _digit = 6){return _vec1.val.GetDot(_vec2.val, _digit);}\
inline static _InClass GetLerp(const _InClass& _vec1,const _InClass& _vec2,const float _pow){_InClass tmpVec;tmpVec.val.SetLerp(_vec1.val, _vec2.val, _pow);return tmpVec;}\
inline static _InClass GetSLerp(const _InClass& _vec1,const _InClass& _vec2,const float _pow){_InClass tmpVec;tmpVec.val.SetSLerp(_vec1.val, _vec2.val, _pow);return tmpVec;}
#endif

#ifndef	CH_MATH3D_METHOD_VECTOR_OTHER
#define	CH_MATH3D_METHOD_VECTOR_OTHER \
void Abs() { val.Abs(); }\
bool Normalize(const unsigned long _digit = 6) { return val.Normalize(_digit); }\
void ElementsNormalize() { val.ElementsNormalize(); }
#endif

#ifndef	CH_MATH3D_METHOD_MATRIX_GET_AXIS
#define	CH_MATH3D_METHOD_MATRIX_GET_AXIS(_MatrixType) \
	inline ChVector3 GetXAxisDirection()const { return ChVector3(_MatrixType##_11, _MatrixType##_12, _MatrixType##_13); }\
	inline ChVector3 GetYAxisDirection()const { return ChVector3(_MatrixType##_21, _MatrixType##_22, _MatrixType##_23); }\
	inline ChVector3 GetZAxisDirection()const { return ChVector3(_MatrixType##_31, _MatrixType##_32, _MatrixType##_33); }
#endif

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
struct ChQuaternion;
struct ChRMatrix;
struct ChLMatrix;
struct ChUIMatrix;


struct ChVector2 : public ChMath::Vector2Base<float>
{
public://Static Functions//
	
	static ChVector2 FromPosition(const float _x, const float _y);
	static ChVector2 FromSize(const float _w, const float _h);
	static ChVector2 FromTime(const float _start, const float _end);
	static ChVector2 FromHighLow(const float _high, const float _low);

public://Operator Functions//

	CH_MATH3D_METHOD_VECTOR_OPERATORS(2,float);

	operator const ChVector4() const;
	operator const ChVector3() const;

	operator const D3DXVECTOR2() const;
	operator const D3DXVECTOR2* () const;

	ChVector2& operator=(const D3DXVECTOR2&);

public://Constructor Destructor//

	CH_MATH3D_METHOD_VECTOR_CONSTRUCTOR(2, float);

	inline ChVector2(const float _x, const float _y) : Vector2Base<float>(_x, _y) {}

	inline ChVector2(const D3DXVECTOR2& _vec) { *this = _vec; }

public://Set Function//

	CH_MATH3D_METHOD_VECTOR_SET_METHOD(ChVector2);

public://Get Functions//

	CH_MATH3D_METHOD_VECTOR_GET_METHOD;

public://Statict Get Functions//

	CH_MATH3D_METHOD_VECTOR_GET_STATIC_METHOD(ChVector2);

public://Other Functions//

	CH_MATH3D_METHOD_VECTOR_OTHER;
};

using ChVec2 = ChVector2;

struct ChVector3 : public ChMath::Vector3Base<float>
{
public://Static Functions//

	static ChVector3 FromPosition(const float _x, const float _y, const float _z);
	static ChVector3 FromColor(const float _r, const float _g, const float _b);

public://Operator Functions//

	CH_MATH3D_METHOD_VECTOR_OPERATORS(3, float);

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

	CH_MATH3D_METHOD_VECTOR_CONSTRUCTOR(3, float);

	inline ChVector3(const float _x, const float _y, const float _z):Vector3Base<float>(_x,_y,_z){}

	inline ChVector3(const D3DXVECTOR3& _vec) { *this = _vec; }
	inline ChVector3(const DirectX::XMFLOAT3& _vec) { *this = _vec; }

	inline ChVector3(const D3DXQUATERNION& _Qua) { *this = _Qua; }
	inline ChVector3(const DirectX::XMFLOAT4& _Qua) { *this = _Qua; }

	inline ChVector3(const D3DXMATRIX& _mat) { *this = _mat; }
	inline ChVector3(const DirectX::XMFLOAT4X4& _mat) { *this = _mat; }

public://Set Function//

	CH_MATH3D_METHOD_VECTOR_SET_METHOD(ChVector3);

public://Get Functions//

	CH_MATH3D_METHOD_VECTOR_GET_METHOD;

public://Statict Get Functions//

	CH_MATH3D_METHOD_VECTOR_GET_STATIC_METHOD(ChVector3);

public://Other Functions//

	CH_MATH3D_METHOD_VECTOR_OTHER;

};

using ChVec3 = ChVector3;


struct ChVector4 : public ChMath::Vector4Base<float>
{
public://Static Functions//

	static ChVector4 FromPosition(const float _x, const float _y, const float _z, const float _w);

	static ChVector4 FromColor(const float _r, const float _g, const float _b, const float _a);

	static ChVector4 FromRect(const float _left, const float _top, const float _right, const float _bottom);

public://Operator Functions//

	CH_MATH3D_METHOD_VECTOR_OPERATORS(4, float);

	operator const ChVector3() const;
	operator const ChVector2() const;

	operator const D3DXVECTOR4() const;
	operator const D3DXVECTOR4* () const;

	ChVector4& operator=(const D3DXVECTOR4&);

public://Constructor Destructor//

	CH_MATH3D_METHOD_VECTOR_CONSTRUCTOR(4, float);
	
	inline ChVector4(const float _x, const float _y, const float _z, const float _w) : Vector4Base<float>(_x, _y, _z, _w) {}

	inline ChVector4(const D3DXVECTOR4& _vec) { *this = _vec; }

	inline void WParamSaturate() { w = w > -1.0f ? (w < 1.0f ? w : 1.0f) : -1.0f; }

public://Set Function//

	CH_MATH3D_METHOD_VECTOR_SET_METHOD(ChVector4);

public://Get Function//

	CH_MATH3D_METHOD_VECTOR_GET_METHOD;

public://Statict Get Functions//

	CH_MATH3D_METHOD_VECTOR_GET_STATIC_METHOD(ChVector4);

public://Other Functions//

	CH_MATH3D_METHOD_VECTOR_OTHER;

};

using ChVec4 = ChVector4;

struct ChLMatrix;
struct ChRMatrix;

struct ChQuaternion : public ChMath::QuaternionBase<float>
{
public://Operator Functions//

	CH_MATH3D_METHOD(ChQuaternion, ChQuaternion, val, Set, =);
	CH_MATH3D_METHOD(ChQuaternion, ChMath::QuaternionBase<float>, val, Set, =);
	CH_MATH3D_METHOD(ChQuaternion, ChMath::QuaternionBase<float>, val, Add, +=);
	inline ChQuaternion& operator*=(const ChMath::QuaternionBase<float>& _num) { SetMul(_num); return *this; }


	CH_MATH3D_METHOD_CONST(ChQuaternion, ChMath::QuaternionBase<float>, +, val, Add);
	inline ChQuaternion operator*(const ChMath::QuaternionBase<float>& _num)const
	{
		ChQuaternion res;
		res.SetMul(*this, _num);
		return res;
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

public://Constructor Destructor//

	inline ChQuaternion():ChMath::QuaternionBase<float>(){}
	
	inline ChQuaternion(const QuaternionBase<float>& _qua): ChMath::QuaternionBase<float>(_qua){}

	inline ChQuaternion(const float _x, const float _y, const float _z) : ChMath::QuaternionBase<float>(_x, _y, _z) {}

	inline ChQuaternion(const float _x, const float _y, const float _z, const float _w) : ChMath::QuaternionBase<float>(_x, _y, _z, _w) {}

	inline ChQuaternion(const ChMath::Vector3Base<float>& _vec) : ChMath::QuaternionBase<float>(_vec) {}

#if false
	inline ChQuaternion(const D3DXVECTOR3& _vec) { *this = _vec; }
	inline ChQuaternion(const DirectX::XMFLOAT3& _vec) { *this = _vec; }

	inline ChQuaternion(const D3DXQUATERNION& _qua) { *this = _qua; }
	inline ChQuaternion(const DirectX::XMFLOAT4& _qua) { *this = _qua; }

	inline ChQuaternion(const D3DXMATRIX& _mat) { *this = _mat; }
	inline ChQuaternion(const DirectX::XMFLOAT4X4& _mat) { *this = _mat; }
#endif

public://Sed Functions//

	void SetRotationLMatrix(const ChLMatrix& _mat);

	void SetRotationRMatrix(const ChRMatrix& _mat);

	void SetRotationXAxis(float _x);

	void SetRotationYAxis(float _y);

	void SetRotationZAxis(float _z);

	void SetRotation(const ChVector3& _axis, const float _angle);

	void SetRotation(const ChVector3& _from, const ChVector3& _to);

	inline void SetSLerp(const ChQuaternion& _start, const ChQuaternion& _end, const float _pow) { val.SetSLerp(_start.val, _end.val, _pow); }

public://Get Functions//

	ChLMatrix GetRotationLMatrix(const unsigned long _digit = 6)const;

	ChRMatrix GetRotationRMatrix(const unsigned long _digit = 6)const;

	ChVector3 GetAxis()const;

	float GetRadian()const;

	float GetCos()const;

	float GetSin()const;

	inline static ChQuaternion GetSLerp(const ChQuaternion& _vec1, const ChQuaternion& _vec2, const float _pow) 
	{
		ChQuaternion res;
		res.val.SetSLerp(_vec1.val, _vec2.val, _pow);
		return res;
	}

public://Add Functions//

	void AddRotationXAxis(float _x);

	void AddRotationYAxis(float _y);

	void AddRotationZAxis(float _z);

public://Other Functions//

};

using ChQua = ChQuaternion;

//LeftHandAxisMatrix//
struct ChLMatrix : public ChMath::BaseMatrix4x4<float>
{
public://Operator Functions//

	CH_MATH3D_METHOD(ChLMatrix, ChLMatrix, m, Set, =);
	CH_MATH3D_METHOD(ChLMatrix, ChMath::BaseMatrix4x4<float>, m, Set, =);
	CH_MATH3D_METHOD(ChLMatrix, ChMath::BaseMatrix4x4<float>, m, Add, +=);
	CH_MATH3D_METHOD(ChLMatrix, ChMath::BaseMatrix4x4<float>, m, Sub, -=);
	CH_MATH3D_METHOD(ChLMatrix, ChMath::BaseMatrix4x4<float>, m, Mul, *=);
	CH_MATH3D_METHOD(ChLMatrix, ChMath::BaseMatrix4x4<float>, m, Div, /=);

	CH_MATH3D_METHOD_CONST(ChLMatrix, ChMath::BaseMatrix4x4<float>, +, m, Add);
	CH_MATH3D_METHOD_CONST(ChLMatrix, ChMath::BaseMatrix4x4<float>, -, m, Sub);
	CH_MATH3D_METHOD_CONST(ChLMatrix, ChMath::BaseMatrix4x4<float>, *, m, Mul);
	CH_MATH3D_METHOD_CONST(ChLMatrix, ChMath::BaseMatrix4x4<float>, /, m, Div);

	CH_MATH3D_METHOD_BOOL(ChMath::BaseMatrix4x4<float>, ==, m);
	CH_MATH3D_METHOD_BOOL(ChMath::BaseMatrix4x4<float>, !=, m);

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

	CH_MATH3D_METHOD_MATRIX_CONSTRUCTOR(L,float);

	inline ChLMatrix(const D3DXVECTOR3& _vec) { *this = _vec; }
	inline ChLMatrix(const DirectX::XMFLOAT3& _vec) { *this = _vec; }

	inline ChLMatrix(const D3DXQUATERNION& _Qua) { *this = _Qua; }
	inline ChLMatrix(const DirectX::XMFLOAT4& _Qua) { *this = _Qua; }

	inline ChLMatrix(const D3DXMATRIX& _mat) { *this = _mat; }
	inline ChLMatrix(const DirectX::XMFLOAT4X4& _mat) { *this = _mat; }

public://Set Functions//

	void SetPosition(const ChVector3& _vec);

	void SetPosition(const float _x, const float _y, const float _z);

	void SetRotation(const ChQuaternion& _qua, const unsigned long _digit = 6);

	void SetRotationYPR(const float _x, const float _y, const float _z, const unsigned long _digit = 6);

	void SetRotationYPR(const ChVector3& _vec, const unsigned long _digit = 6);

	void SetRotationXAxis(const float _x);

	void SetRotationYAxis(const float _y);

	void SetRotationZAxis(const float _z);

	void SetScalling(
		const ChVector3& _vec,
		const unsigned long _digit = 6);

	void SetScalling(
		const float _x,
		const float _y,
		const float _z,
		const unsigned long _digit = 6);

	inline void SetLerp(
		const ChLMatrix& _start,
		const ChLMatrix& _end,
		const float _pow)
	{
		m.SetLerp(_start.m, _end.m, _pow);
	}

public://Get Functions//

	ChVector3 GetPosition()const;

	ChQuaternion GetRotation(const unsigned long _digit = 6)const;

	ChMath::ChEularXYZ<float> GetEulerRotationXYZ(const unsigned long _digit = 6)const;

	ChMath::ChEularXZY<float> GetEulerRotationXZY(const unsigned long _digit = 6)const;

	ChMath::ChEularYXZ<float> GetEulerRotationYXZ(const unsigned long _digit = 6)const;

	ChMath::ChEularYZX<float> GetEulerRotationYZX(const unsigned long _digit = 6)const;

	ChMath::ChEularZXY<float> GetEulerRotationZXY(const unsigned long _digit = 6)const;

	ChMath::ChEularZYX<float> GetEulerRotationZYX(const unsigned long _digit = 6)const;

	ChVector3 GetScalling(const unsigned long _digit = 6)const;

	CH_MATH3D_METHOD_MATRIX_GET_AXIS(l);

public://Other Functions//

	ChVector4 Transform(const ChVector4& _Base)const;

	ChVector4 TransformCoord(const ChVector4& _Base)const;
};


//RightHandAxisMatrix//
struct ChRMatrix : public ChMath::BaseMatrix4x4<float>
{
public://Operator Functions//

	CH_MATH3D_METHOD(ChRMatrix, ChRMatrix, m, Set, =);
	CH_MATH3D_METHOD(ChRMatrix, ChMath::BaseMatrix4x4<float>, m, Set, =);
	CH_MATH3D_METHOD(ChRMatrix, ChMath::BaseMatrix4x4<float>, m, Add, +=);
	CH_MATH3D_METHOD(ChRMatrix, ChMath::BaseMatrix4x4<float>, m, Sub, -=);
	CH_MATH3D_METHOD(ChRMatrix, ChMath::BaseMatrix4x4<float>, m, Mul, *=);
	CH_MATH3D_METHOD(ChRMatrix, ChMath::BaseMatrix4x4<float>, m, Div, /=);

	CH_MATH3D_METHOD_CONST(ChRMatrix, ChMath::BaseMatrix4x4<float>, +, m, Add);
	CH_MATH3D_METHOD_CONST(ChRMatrix, ChMath::BaseMatrix4x4<float>, -, m, Sub);
	CH_MATH3D_METHOD_CONST(ChRMatrix, ChMath::BaseMatrix4x4<float>, *, m, Mul);
	CH_MATH3D_METHOD_CONST(ChRMatrix, ChMath::BaseMatrix4x4<float>, /, m, Div);

	CH_MATH3D_METHOD_BOOL(ChMath::BaseMatrix4x4<float>, ==, m);
	CH_MATH3D_METHOD_BOOL(ChMath::BaseMatrix4x4<float>, !=, m);

public://Constructor Destructor//

	CH_MATH3D_METHOD_MATRIX_CONSTRUCTOR(R, float);

public://Set Functions//

	void SetPosition(const ChVector3& _vec);

	void SetPosition(const float _x, const float _y, const float _z);

	void SetRotation(const ChQuaternion& _qua, const unsigned long _digit = 6);

	void SetRotationXAxis(const float _x);

	void SetRotationYAxis(const float _y);

	void SetRotationZAxis(const float _z);

	void SetScalling(
		const ChVector3& _vec,
		const unsigned long _digit = 6);

	void SetScalling(
		const float _x,
		const float _y,
		const float _z,
		const unsigned long _digit = 6);

	ChRMatrix SetLerp(
		const ChRMatrix& _start,
		const ChRMatrix& _end,
		const float _pow)
	{
		m.SetLerp(_start.m, _end.m, _pow);
	}

public://Get Functions//

	ChVector3 GetPosition()const;

	ChVector3 GetScalling(const unsigned long _digit = 6)const;

	CH_MATH3D_METHOD_MATRIX_GET_AXIS(r);

public://Other Functions//

	ChVector4 Transform(const ChVector4& _Base)const;

	ChVector4 TransformCoord(const ChVector4& _Base)const;

	void Identity()
	{
		m.Identity();
	}

	void Inverse()
	{
		m.Inverse();
	}
};

using ChRMat = ChRMatrix;
using ChLMat = ChLMatrix;

struct ChUIMatrix : public ChMath::BaseMatrix4x4<unsigned long>
{
public://Operator Functions//

	CH_MATH3D_METHOD(ChUIMatrix, ChUIMatrix, m, Set, =);
	CH_MATH3D_METHOD(ChUIMatrix, ChMath::BaseMatrix4x4<unsigned long>, m, Set, =);
	CH_MATH3D_METHOD(ChUIMatrix, ChMath::BaseMatrix4x4<unsigned long>, m, Add, +=);
	CH_MATH3D_METHOD(ChUIMatrix, ChMath::BaseMatrix4x4<unsigned long>, m, Sub, -=);
	CH_MATH3D_METHOD(ChUIMatrix, ChMath::BaseMatrix4x4<unsigned long>, m, Mul, *=);
	CH_MATH3D_METHOD(ChUIMatrix, ChMath::BaseMatrix4x4<unsigned long>, m, Div, /=);

public://Constructor Destructor//

	CH_MATH3D_METHOD_MATRIX_CONSTRUCTOR(UI, unsigned long);
};

using ChUIMat = ChUIMatrix;

namespace ChMath
{
	ChVector3 GetFaceNormal(
		const ChVec3& _Pos1,
		const ChVec3& _Pos2,
		const ChVec3& _Pos3,
		const unsigned long _digit = 6);

	//RadianŠp‚©‚çDegreeŠp‚Ö//
	static inline float ToDegree(const float _Radian) { return (_Radian * 180.0f / PI); }

	//DegreeŠp‚©‚çRadianŠp‚Ö//
	static inline float ToRadian(const float _degree) { return (_degree * PI / 180.0f); }

	//³‚Ì•„†‚©‚Ç‚¤‚©‚ðŠm”F‚·‚é//
	static inline bool IsPSign(const int _val) { return _val >= 0; }
	static inline bool IsPSign(const char _val) { return _val >= 0; }
	static inline bool IsPSign(const short _val) { return _val >= 0; }
	static inline bool IsPSign(const long _val) { return _val >= 0; }
	static inline bool IsPSign(const float _val) { return _val >= 0.0f; }
	static inline bool IsPSign(const double _val) { return _val >= 0.0; }

} // namespace ChMath

#endif