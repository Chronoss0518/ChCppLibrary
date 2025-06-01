#ifndef Ch_CPP_BMath_h
#define Ch_CPP_BMath_h

#include<string>

#include"ChStd.h"
#include"ChStr.h"


#ifndef Ch_FLOAT_TEST_VALUE
#define Ch_FLOAT_TEST_VALUE 0.0001f
#endif

#ifndef CH_FLOAT_TEST
#define CH_FLOAT_TEST(val, testSize) ChMath::GetAbs( val ) <= testSize
#endif

#ifndef CH_MATH_LONG_TYPE
#define CH_MATH_LONG_TYPE(_type) long _type
#endif

#ifndef CH_MATH_SIGNED_TYPE
#define CH_MATH_SIGNED_TYPE(_type) signed _type
#endif


#ifndef CH_MATH_METHOD_SIGNED_ABS
#define CH_MATH_METHOD_SIGNED_ABS(_type) inline _type GetAbs( _type _val ){return _val < 0 ? -_val : _val;}
#endif

#ifndef CH_MATH_METHOD_UNSIGNED_ABS
#define CH_MATH_METHOD_UNSIGNED_ABS(_type) inline unsigned _type GetAbs(unsigned _type _val){return _val;}
#endif

#ifndef CH_MATH_VECTOR_OPERATOR_ACT
#define CH_MATH_VECTOR_OPERATOR_ACT(_Operator,_TargetValue) \
for (unsigned long i = 0; i < Array; i++){val[i] _Operator _TargetValue ;}
#endif

#ifndef CH_MATH_METHOD
#define CH_MATH_METHOD(_OutClass,_InClass,_Method,_MethodType)\
inline _OutClass & operator _MethodType (const _InClass & _val)\
{\
	_Method (_val);\
	return *this;\
}
#endif

#ifndef CH_MATH_METHOD_CONST
#define CH_MATH_METHOD_CONST(_OutClass,_InClass,_MethodType,_Method)\
inline _OutClass operator _MethodType(const _InClass & _val)const\
{\
	_OutClass res = *this;\
	res._Method(_val);\
	return res;\
}
#endif
#ifndef	CH_MATH_METHOD_MATRIX_EQUALS
#define	CH_MATH_METHOD_MATRIX_EQUALS(_InClass,_Flg,_Operator,_Array)\
inline bool operator _Operator(const _InClass& _val)const\
{\
	for (unsigned long i = 0; i < _Array; i++)\
	{\
		if (_val.m[i] _Operator m[i])continue;\
		return !( _Flg );\
	}\
	return ( _Flg );\
}
#endif

#ifndef CH_MATH_METHOD_VECTOR_CONSTRUCTOR
#define CH_MATH_METHOD_VECTOR_CONSTRUCTOR(_BaseClass)\
inline _BaseClass() { val.Identity(); }\
inline _BaseClass(const T _num) { val.Set(_num); }\
inline _BaseClass(const _BaseClass<T>&_vec) { val = _vec.val; }
#endif

#ifndef CH_MATH_METHOD_VECTOR_SET
#define CH_MATH_METHOD_VECTOR_SET(_MethodName, _ArgType, _ArgName, _DefaultArg)\
inline void Set##_MethodName(\
const VectorBase& _vec1,\
const VectorBase& _vec2,\
const _ArgType _ArgName _DefaultArg){Set(Get##_MethodName(_vec1, _vec2, _ArgName));}
#endif

#ifndef CH_MATH_METHOD_MATRIX_CONSTRUCTOR
#define CH_MATH_METHOD_MATRIX_CONSTRUCTOR(_BaseClass)\
inline _BaseClass() { m.Identity(); }\
inline _BaseClass(const _BaseClass<T>& _mat) { m = _mat.m; }
#endif

#ifndef CH_MATH3D_METHOD_SERIALIZE
#define CH_MATH3D_METHOD_SERIALIZE(_Value) \
template<typename CharaType>\
inline std::basic_string<CharaType> Serialize(\
const std::basic_string<CharaType>& _cutChar = ChStd::GetCommaChara<CharaType>(),\
const std::basic_string<CharaType>& _endChar =  ChStd::GetSemiColonChara<CharaType>())\
{return _Value.Serialize(_cutChar, _endChar);}
#endif

#ifndef CH_MATH3D_METHOD_DESERIALIZE
#define CH_MATH3D_METHOD_DESERIALIZE(_Value) \
template<typename CharaType>\
inline void Deserialize(\
const std::basic_string<CharaType>& _str,\
const size_t _fPos = 0,\
const std::basic_string<CharaType>& _cutChar = ChStd::GetCommaChara<CharaType>(),\
const std::basic_string<CharaType>& _endChar = ChStd::GetSemiColonChara<CharaType>(),\
const unsigned int _digit = 6)\
{_Value.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);}
#endif

#ifndef CH_MATH3D_METHOD_MATRIX_DESERIALIZE_UPPER
#define CH_MATH3D_METHOD_MATRIX_DESERIALIZE_UPPER \
template<typename CharaType>\
inline std::basic_string<CharaType> SerializeUpper(\
const std::basic_string<CharaType>&_cutChar = ChStd::GetCommaChara<CharaType>(),\
const std::basic_string<CharaType>&_endChar = ChStd::GetSemiColonChara<CharaType>(),\
const std::basic_string<CharaType>&_cutTo4Char = ChStd::GetCRLFChara<CharaType>())\
{return m.SerializeUpper(_cutChar, _endChar, _cutTo4Char);}
#endif


#ifndef CH_MATH_METHOD_QUATERNION_GET_EULER_ROTATION
#define CH_MATH_METHOD_QUATERNION_GET_EULER_ROTATION(_AxisOrder,_ZeroTestAxis,_ZeroTestAxisFunction,_Axiz1,_ZeroAxiz1Function,_NotZeroAxiz1Function,_Axiz2,_ZeroAxiz2Function,_NotZeroAxiz2Function)\
inline ChEular##_AxisOrder<T> GetEulerRotation##_AxisOrder(const unsigned long _digit = 6)const\
{\
	ChEular##_AxisOrder<T> res;\
	res._ZeroTestAxis = ChMath::GetSin _ZeroTestAxisFunction;\
	T ww = w * w * static_cast<T>(2.0f);\
	if (CH_FLOAT_TEST(ChMath::GetCos(res._ZeroTestAxis), Ch_FLOAT_TEST_VALUE)){\
		res._Axiz1 = _ZeroAxiz1Function;\
		res._Axiz2 =_ZeroAxiz2Function;\
	}else{\
		res._Axiz1 = _NotZeroAxiz1Function;\
		res._Axiz2 = _NotZeroAxiz2Function;\
	}\
	return res;\
}
#endif


namespace ChMath
{
	double Round(const double& _val, const unsigned long _digit = 307);

	float Round(const float& _val, const unsigned long _digit = 37);

	long double SqrtEx(const long double& _base, const unsigned long _digit = 4931);

	double SqrtEx(const double& _base, const unsigned long _digit = 307);

	float SqrtEx(const float& _base, const unsigned long _digit = 37);

	float GetSin(float _val);
	double GetSin(double _val);
	long double GetSin(long double _val);

	float GetASin(float _val);
	double GetASin(double _val);
	long double GetASin(long double _val);

	float GetACos(float _val);
	double GetACos(double _val);
	long double GetACos(long double _val);

	float GetCos(float _val);
	double GetCos(double _val);
	long double GetCos(long double _val);

	float GetATan(float _val);
	double GetATan(double _val);
	long double GetATan(long double _val);

	float GetFMod(float _valx, float _valy);
	double GetFMod(double _valx, double _valy);
	long double GetFMod(long double _valx, long double _valy);

	float GetMaxFloat();

	CH_MATH_METHOD_SIGNED_ABS(CH_MATH_SIGNED_TYPE(char));
	CH_MATH_METHOD_SIGNED_ABS(CH_MATH_SIGNED_TYPE(short));
	CH_MATH_METHOD_SIGNED_ABS(CH_MATH_SIGNED_TYPE(int));
	CH_MATH_METHOD_SIGNED_ABS(CH_MATH_SIGNED_TYPE(long));
	CH_MATH_METHOD_SIGNED_ABS(CH_MATH_SIGNED_TYPE(CH_MATH_LONG_TYPE(long)));
	CH_MATH_METHOD_SIGNED_ABS(float);
	CH_MATH_METHOD_SIGNED_ABS(double);
	CH_MATH_METHOD_SIGNED_ABS(CH_MATH_LONG_TYPE(double));

	CH_MATH_METHOD_UNSIGNED_ABS(char);
	CH_MATH_METHOD_UNSIGNED_ABS(short);
	CH_MATH_METHOD_UNSIGNED_ABS(int);
	CH_MATH_METHOD_UNSIGNED_ABS(long);
	CH_MATH_METHOD_UNSIGNED_ABS(CH_MATH_LONG_TYPE(long));

	//2の平方根(有効桁数8桁)//
	static const float SQUARE_ROOT = 1.41421356f;

	//円周率//
	static const float PI = 3.1415f;

	template<typename T, unsigned long Array>
	class VectorBase
	{

	public://Operator Function//

		template<unsigned long _ArrayCount>
		inline operator VectorBase<T, _ArrayCount>()const
		{
			VectorBase<T, _ArrayCount> res;

			unsigned long maxVal = _ArrayCount > Array ? Array : _ArrayCount;

			for (unsigned long i = 0; i < maxVal; i++)
			{
				res[i] = val[i];
			}

			return res;
		}

		template<typename _T>
		inline operator VectorBase<_T, Array>()const
		{
			VectorBase<_T, Array> res;

			for (unsigned long i = 0; i < Array; i++)
			{
				res[i] = static_cast<_T>(val[i]);
			}

			return res;
		}

		inline T& operator [](const unsigned long _val)
		{
			return val[_val % Array];
		}

		inline T operator [](const unsigned long _val)const
		{
			return val[_val % Array];
		}

		inline explicit operator const T* const ()const
		{
			return val;
		}

		CH_MATH_METHOD(VectorBase, VectorBase, Set, =);
		CH_MATH_METHOD(VectorBase, T, Set, =);
		CH_MATH_METHOD(VectorBase, VectorBase, Add, +=);
		CH_MATH_METHOD(VectorBase, T, Add, +=);
		CH_MATH_METHOD(VectorBase, VectorBase, Sub, -=);
		CH_MATH_METHOD(VectorBase, T, Sub, -=);
		CH_MATH_METHOD(VectorBase, VectorBase, Mul, *=);
		CH_MATH_METHOD(VectorBase, T, Mul, *=);
		CH_MATH_METHOD(VectorBase, VectorBase, Div, /=);
		CH_MATH_METHOD(VectorBase, T, Div, /=);

		CH_MATH_METHOD_CONST(VectorBase, VectorBase, +, Add);
		CH_MATH_METHOD_CONST(VectorBase, T, +, Add);
		CH_MATH_METHOD_CONST(VectorBase, VectorBase, -, Sub);
		CH_MATH_METHOD_CONST(VectorBase, T, -, Sub);
		CH_MATH_METHOD_CONST(VectorBase, VectorBase, *, Mul);
		CH_MATH_METHOD_CONST(VectorBase, T, *, Mul);
		CH_MATH_METHOD_CONST(VectorBase, VectorBase, / , Div);
		CH_MATH_METHOD_CONST(VectorBase, T, / , Div);

		inline bool operator ==(const VectorBase& _val)const
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				if (!(CH_FLOAT_TEST(val[i] - _val.val[i], static_cast<T>(Ch_FLOAT_TEST_VALUE))))
					return false;
			}
			return true;
		}

		inline bool operator !=(const VectorBase& _val)const
		{
			bool flg = true;
			for (unsigned long i = 0; i < Array; i++)
			{
				if (!(CH_FLOAT_TEST(val[i] - _val.val[i], static_cast<T>(Ch_FLOAT_TEST_VALUE))))
					return true;
			}
			return false;
		}

	public://Constructor Destructor//

		inline VectorBase() { Identity(); }

		inline VectorBase(const T(&_val)[Array]) 
		{
			for (unsigned long i = 0; i < Array;i++)
				val[i] = _val[i];
		}

		inline VectorBase(const T(&_val)) { Set(_val); }

		inline VectorBase(const VectorBase& _val) { Set(_val); }

	public://Operator Math Function//

		inline void Set(const VectorBase& _vec)
		{
			if (this == &_vec)return;
			CH_MATH_VECTOR_OPERATOR_ACT(=, _vec.val[i]);
		}

		inline void Set(const T& _val)
		{
			CH_MATH_VECTOR_OPERATOR_ACT(=, _val);
		}

		inline void Set(const T(&_arrayVal)[Array])
		{
			CH_MATH_VECTOR_OPERATOR_ACT(=, _arrayVal[i]);
		}

		inline void Add(const VectorBase& _vec)
		{
			CH_MATH_VECTOR_OPERATOR_ACT(+=, _vec.val[i]);
		}

		inline void Add(const T& _val)
		{
			CH_MATH_VECTOR_OPERATOR_ACT(+=, _val);
		}

		inline void Sub(const VectorBase& _vec)
		{
			CH_MATH_VECTOR_OPERATOR_ACT(-=, _vec.val[i]);
		}

		inline void Sub(const T& _val)
		{
			CH_MATH_VECTOR_OPERATOR_ACT(-=, _val);
		}

		inline void Mul(const VectorBase& _vec)
		{
			CH_MATH_VECTOR_OPERATOR_ACT(*=, _vec.val[i]);
		}

		inline void Mul(const T& _val)
		{
			CH_MATH_VECTOR_OPERATOR_ACT(*=, _val);
		}

		inline void Div(const VectorBase& _vec)
		{
			CH_MATH_VECTOR_OPERATOR_ACT(/=, _vec.val[i] != static_cast<T>(0.0f) ? _vec.val[i] : static_cast<T>(1.0f));
		}

		inline void Div(const T& _val)
		{
			T tmp = _val != static_cast<T>(0.0f) ? _val : static_cast<T>(1.0f);
			CH_MATH_VECTOR_OPERATOR_ACT(/=, tmp);
		}

	public://Serialize Deserialize//

		template<typename CharaType>
		inline std::basic_string<CharaType> Serialize(
			const std::basic_string<CharaType>& _cutChar = ChStd::GetCommaChara<CharaType>(),
			const std::basic_string<CharaType>& _endChar = ChStd::GetSemiColonChara<CharaType>())
		{
			std::basic_string<CharaType> tmp = ChStd::GetZeroChara<CharaType>();
			for (unsigned char i = 0; i < Array; i++)
			{
				tmp += ChStr::GetTextFromNum<CharaType, T>(val[i]);
				if (i == (Array - 1))break;
				tmp += _cutChar;
			}
			tmp += _endChar;

			return tmp;
		}

		template<typename CharaType>
		inline void Deserialize(
			const std::basic_string<CharaType>& _str,
			const size_t _fPos = 0,
			const std::basic_string<CharaType>& _cutChar = ChStd::GetCommaChara<CharaType>(),
			const std::basic_string<CharaType>& _endChar = ChStd::GetSemiColonChara<CharaType>(),
			const unsigned int _digit = 6)
		{

			std::basic_string<CharaType> tmpStr = _str;

			size_t tmpFPos = _fPos;
			size_t EPos = tmpStr.find(_endChar, tmpFPos);

			if (EPos == tmpStr.npos)EPos = tmpStr.size();

			tmpStr = tmpStr.substr(tmpFPos, EPos - tmpFPos);

			tmpFPos = 0;

			EPos = tmpStr.length();

			size_t tmp = tmpFPos;

			for (unsigned char i = 0; i < Array; i++)
			{
				size_t Test = tmpStr.find(_cutChar, tmp);
				if (Test > EPos)Test = EPos;
				{
					tmpFPos = Test;

					std::basic_string<CharaType> Num = tmpStr.substr(tmp, tmpFPos - tmp);

					val[i] = ChStr::GetNumFromText<T>(Num);

					//val[i] = ChMath::Round(val[i], _digit);

					tmp += Num.length();
					tmp += 1;

				}
				if (Test >= EPos)return;
			}
		}

	public://Set Functions//

		inline void SetLen(const T _len)
		{
			if (GetLen() == 0.0f)return;

			Normalize();

			T tmp = _len * _len;

			/*
			x^2 + y^2 + z^2 = r^2

			(nx * l)^2 + (ny * l)^2 + (nz * l)^2 = r^2

			l^2 = r^2 /(nx^2 + ny^2 + nz^2)
			*/

			T add = static_cast<T>(0.0f);

			for (unsigned long i = 0; i < Array; i++)
			{
				add += val[i] * val[i];
			}

			tmp = tmp / add;

			tmp = static_cast<T>(SqrtEx(static_cast<long double>(tmp)));
			Mul(tmp);
		}


		CH_MATH_METHOD_VECTOR_SET(Cross,unsigned long, _digit, = 6);
		
		CH_MATH_METHOD_VECTOR_SET(Lerp, float, _pow, );

		CH_MATH_METHOD_VECTOR_SET(SLerp, float, _pow, );

	public://Get Functions//

		inline constexpr const unsigned long GetArray()const { return Array; }

		//ベクトルの要素の大きさを得る//
		inline T GetElementsLen()const
		{
			T out = static_cast<T>(0.0f);
			for (unsigned long i = 0; i < Array; i++)
			{
				out += val[i] >= 0.0f ? val[i] : -val[i];
			}

			return out;
		}

		//ベクトルの大きさを得る//
		inline T GetLen(const unsigned long _digit = 6)const
		{
			T len = static_cast<T>(0.0f);

			for (unsigned long i = 0; i < Array; i++)
			{
				len += val[i] * val[i];
			}

			return static_cast<T>(SqrtEx(static_cast<long double>(len), _digit));
		}

		inline T GetCos(
			const VectorBase& _vec,
			const unsigned long _digit = 6)const
		{
			VectorBase tmp1 = *this, tmp2 = _vec;

			T len1 = tmp1.GetLen();
			T len2 = tmp2.GetLen();

			if (len1 <= static_cast<T>(0.0f) || len2 <= static_cast<T>(0.0f))return 0.0f;

			T testVal = static_cast<T>(1.0f);

			for (unsigned long i = 0; i < Array; i++)
			{
				tmp1.val[i] = len1 == testVal ? tmp1.val[i] : tmp1.val[i] / len1;
				tmp2.val[i] = len2 == testVal ? tmp2.val[i] : tmp2.val[i] / len1;
			}

			return tmp1.GetDot(tmp2);
		}

		inline T GetRadian(
			const VectorBase& _vec,
			const unsigned long _digit = 6)const
		{
			T tmp = GetCos(_vec, _digit);

			return ChMath::GetACos(tmp);
		}


		inline T GetDot(
			const VectorBase& _vec,
			const unsigned long _digit = 6)const
		{
			T tmpLen = 0.0f;

			for (unsigned long i = 0; i < Array; i++)
			{
				tmpLen += val[i] * _vec.val[i];
			}

			return tmpLen;
		}

		inline VectorBase GetCross(
			const VectorBase& _vec1,
			const VectorBase& _vec2,
			const unsigned long _digit = 6)const
		{
			VectorBase res;

			for (unsigned char i = 0; i < Array; i++)
			{
				res.val[i] =
					(_vec1.val[(i + 1) % Array] * _vec2.val[(i + 2) % Array])
					- (_vec1.val[(i + 2) % Array] * _vec2.val[(i + 1) % Array]);
			}

			res.Normalize(_digit);

			return res;
		}

		inline VectorBase GetLerp(
			const VectorBase& _start,
			const VectorBase& _end,
			const float _pow)const
		{
			if (_pow <= 0.0f)return _start;
			if (_pow >= 1.0f)return _end;

			return (_start * (1.0f - _pow)) + (_end * _pow);
		}

		inline VectorBase GetSLerp(
			const VectorBase& _start,
			const VectorBase& _end,
			const float _pow)const
		{

			if (_pow >= 1.0f)return _end;
			if (_pow <= 0.0f)return _start;

			VectorBase start = _start;
			VectorBase end = _end;

			T rad = start.GetDot(end);
			rad = GetACos(rad);
			if (rad == 0.0f)return start;

			float baseSin = GetSin(rad);

			if (baseSin == 0.0f)return start;

			start.Mul(GetSin((1.0f - _pow) * rad) / baseSin);
			end.Mul(GetSin(_pow * rad) / baseSin);

			return (start + end);
		}

		inline const T* const GetVal()const
		{
			return val;
		}

	public://Other Functions//

		inline void Abs()
		{
			CH_MATH_VECTOR_OPERATOR_ACT(=, ChMath::GetAbs(val[i]));
		}

		inline void Identity()
		{
			CH_MATH_VECTOR_OPERATOR_ACT(=, static_cast<T>((i % 4) + 1 != 4 ? 0.0f : 1.0f));
		}

		//ベクトルの長さを1にする//
		inline bool Normalize(const unsigned long _digit = 6)
		{
			T len = GetLen(_digit);

			if (len == static_cast<T>(1.0))return true;
			if (len == static_cast<T>(0.0))return false;

			CH_MATH_VECTOR_OPERATOR_ACT(/=, len);

			return true;
		}

		//ベクトルの要素の合計を1にする//
		inline bool ElementsNormalize()
		{
			T len = GetElementsLen();

			if (len == static_cast<T>(1.0))return true;
			if (len == static_cast<T>(0.0))return false;

			CH_MATH_VECTOR_OPERATOR_ACT(/=, len);

			return true;
		}

	private:

		T val[Array];

	};

	template<typename T, unsigned long Row, unsigned long Column>
	class MatrixBase
	{
	public:

		struct ULMatrix
		{
			MatrixBase uMat;
			MatrixBase lMat;
		};

	public://Operator Functions//

		template<unsigned long _Row, unsigned long _Column>
		inline operator MatrixBase<T, _Row, _Column>()const
		{
			MatrixBase<T, _Row, _Column> out;

			unsigned long minRow = _Row > Row ? Row : _Row;
			unsigned long minColumn = _Column > Column ? Column : _Column;

			for (unsigned long i = 0; i < minColumn; i++)
			{
				for (unsigned long j = 0; j < minRow; j++)
				{
					out[i][j] = m[i][j];
				}
			}

			return out;
		}

		inline VectorBase<T, Row>& operator [](const unsigned long _col)
		{
			return m[_col % Row];
		}

		inline VectorBase<T, Row> operator [](const unsigned long _col)const
		{
			return m[_col % Row];
		}

		inline explicit operator const T** const ()const
		{
			return m;
		}

		CH_MATH_METHOD(MatrixBase, MatrixBase, Set, =);
		CH_MATH_METHOD(MatrixBase, MatrixBase, Add, +=);
		CH_MATH_METHOD(MatrixBase, MatrixBase, Sub, -=);
		CH_MATH_METHOD(MatrixBase, MatrixBase, Mul, *=);
		CH_MATH_METHOD(MatrixBase, MatrixBase, Div, /=);

		CH_MATH_METHOD_CONST(MatrixBase, MatrixBase, +, Add);
		CH_MATH_METHOD_CONST(MatrixBase, MatrixBase, -, Sub);
		CH_MATH_METHOD_CONST(MatrixBase, MatrixBase, *, Mul);
		CH_MATH_METHOD_CONST(MatrixBase, MatrixBase, / , Div);

		CH_MATH_METHOD_MATRIX_EQUALS(MatrixBase, true, == , Row);
		CH_MATH_METHOD_MATRIX_EQUALS(MatrixBase, false, != , Row);

	public://Contructor Destructor//

		inline MatrixBase()
		{
			Identity();
		}

		inline MatrixBase(const MatrixBase& _Mat)
		{
			Set(_Mat);
		}

	public://Operator Math Function//

		inline void Set(const MatrixBase& _mat)
		{
			for (unsigned long i = 0; i < Column; i++)
			{
				m[i].Set(_mat.m[i]);
			}
		}

		inline void Set(const T& _val)
		{
			for (unsigned long i = 0; i < Column; i++)
			{
				m[i].Set(_val);
			}
		}

		inline void Add(const MatrixBase& _mat)
		{
			for (unsigned long i = 0; i < Column; i++)
			{
				m[i].Add(_mat.m[i]);
			}
		}

		inline void Sub(const MatrixBase& _mat)
		{
			for (unsigned long i = 0; i < Column; i++)
			{
				m[i].Sub(_mat.m[i]);
			}
		}

		inline void Mul(const MatrixBase& _mat)
		{
			MatrixBase tmp;
			tmp.Set(*this);

			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Column; j++)
				{
					m[i][j] = tmp[i][0] * _mat.m[0][j];

					for (unsigned long k = 1; k < Row; k++)
					{
						m[i][j] += tmp[i][k] * _mat.m[k][j];
					}
				}
			}

		}

		//縦軸の掛け算//
		template<unsigned long _Arrarys>
		inline VectorBase<T, _Arrarys> VerticalMul(const VectorBase<T, _Arrarys> _vec)const
		{
			MatrixBase<T, Row, Column> tmpMat;

			tmpMat.Set(static_cast<T>(0.0f));

			unsigned long maxSize = _Arrarys >= Row ? Row : _Arrarys;

			unsigned long i = 0;
			for (i = 0; i < maxSize; i++)
			{
				tmpMat.m[i][0] = _vec[i];
			}

			tmpMat = (*this) * tmpMat;

			VectorBase<T, _Arrarys> out;

			for (i = 0; i < maxSize; i++)
			{
				out[i] = tmpMat.m[i][0];
			}

			return out;
		}


		//横軸の掛け算//
		template<unsigned long _Arrarys>
		inline VectorBase<T, _Arrarys>HorizontalMul(const VectorBase<T, _Arrarys> _vec)const
		{
			MatrixBase<T, Row, Column> tmpMat;

			tmpMat.Set(static_cast<T>(0.0f));

			unsigned long maxSize = _Arrarys >= Column ? Column : _Arrarys;

			unsigned long i = 0;
			for (i = 0; i < maxSize; i++)
			{
				tmpMat.m[0][i] = _vec[i];
			}

			tmpMat = tmpMat * (*this);

			VectorBase<T, _Arrarys> out;

			for (i = 0; i < maxSize; i++)
			{
				out[i] = tmpMat.m[0][i];
			}

			return out;
		}

		inline void Div(const MatrixBase& _mat)
		{
			MatrixBase tmpMat;
			tmpMat = _mat;

			tmpMat.Inverse();

			Mul(tmpMat);
		}

	public://Serialize Deserialize//

		template<typename CharaType>
		inline std::basic_string<CharaType> Serialize(
			const std::basic_string<CharaType>& _cutChar = ChStd::GetCommaChara<CharaType>(),
			const std::basic_string<CharaType>& _endChar = ChStd::GetSemiColonChara<CharaType>())
		{
			std::basic_string<CharaType> tmp = ChStd::GetZeroChara<CharaType>();
			for (unsigned char i = 0; i < Column; i++)
			{
				for (unsigned char j = 0; j < Row; j++)
				{
					if (i == 3 && j == 3)break;
					tmp += ChStr::GetTextFromNum<CharaType, T>(m[i][j]);
					tmp += _cutChar;
				}
			}

			tmp += ChStr::GetTextFromNum<CharaType, T>(m[3][3]);
			tmp += _endChar;

			return tmp;
		}

		template<typename CharaType>
		inline std::basic_string<CharaType> SerializeUpper(
			const std::basic_string<CharaType>& _cutChar = ChStd::GetCommaChara<CharaType>(),
			const std::basic_string<CharaType>& _endChar = ChStd::GetSemiColonChara<CharaType>(),
			const std::basic_string<CharaType>& _cutTo4Char = ChStd::GetCRLFChara<CharaType>())
		{
			std::basic_string<CharaType> tmp = ChStd::GetZeroChara<CharaType>();
			for (unsigned char i = 0; i < Column; i++)
			{
				for (unsigned char j = 0; j < Row; j++)
				{
					if (i == 3 && j == 3)break;
					tmp += ChStr::GetTextFromNum<CharaType, T>(m[i][j]);
					tmp += _cutChar;

					if (j < 3)continue;
					tmp += _cutTo4Char;
				}
			}

			tmp += ChStr::GetTextFromNum<CharaType, T>(m[3][3]);
			tmp += _endChar;

			return tmp;
		}

		template<typename CharaType>
		inline void Deserialize(
			const std::basic_string<CharaType>& _str,
			const size_t _fPos = 0,
			const std::basic_string<CharaType>& _cutChar = ChStd::GetCommaChara<CharaType>(),
			const std::basic_string<CharaType>& _endChar = ChStd::GetSemiColonChara<CharaType>(),
			const unsigned int _digit = 6)
		{
			std::basic_string<CharaType> tmpStr = _str;

			size_t tmpFPos = _fPos;

			size_t EPos = tmpStr.find(_endChar, tmpFPos);

			if (EPos == tmpStr.npos)EPos = tmpStr.size() - 1;

			tmpStr = tmpStr.substr(tmpFPos, EPos - tmpFPos);

			tmpFPos = 0;

			EPos = tmpStr.length();

			size_t tmp = tmpFPos;

			for (unsigned char i = 0; i < Column; i++)
			{
				for (unsigned char j = 0; j < Row; j++)
				{
					size_t test = tmpStr.find(_cutChar, tmp);

					if (test > EPos)test = EPos;

					tmpFPos = test;

					std::basic_string<CharaType> Num = tmpStr.substr(tmp, tmpFPos - tmp);

					m[i][j] = ChStr::GetNumFromText<T>(Num);

					tmp = test + 1;

					if (test >= EPos)return;
				}
			}
		}

	public://Set Functions//

		inline void SetLerp(
			const MatrixBase& _start,
			const MatrixBase& _end,
			const float _pow)
		{
			for (unsigned long i = 0; i < Row; i++)
			{
				m[i].SetLerp(_start.m[i], _end.m[i], _pow);
			}
		}

	public://Get Functions//

		inline T GetLen()const
		{
			T out = static_cast<T>(0.0f);

			if (Row != Column)return out;

			for (unsigned long i = 0; i < Column; i++)
			{
				T add = m[0][i];
				T sub = m[0][i];

				for (unsigned long j = 1; j < Row; j++)
				{
					add *= m[j % Column][(i + j) % Row];

					sub *= m[j % Column][(Row + i - j) % Row];
				}

				out = out + add - sub;
			}
			return out;
		}

		inline MatrixBase GetCofactor(const unsigned long _Row, const unsigned long _Col)const
		{
			MatrixBase out;

			if (_Row >= Row || _Col >= Column)return out;

			bool colFlg = false;

			for (unsigned long i = 0; i < Column - 1; i++)
			{
				if (i == _Col)colFlg = true;

				bool rowFlg = false;

				for (unsigned long j = 0; j < Row - 1; j++)
				{
					if (j == _Row)rowFlg = true;
					out.m[i][j] = m[colFlg ? i + 1 : i][rowFlg ? j + 1 : j];
				}
			}
		}

		//行列式//
		inline T GetDeterminant()const
		{
			return GetLen();
		}

		//掃き出し法による逆行列//
		inline MatrixBase GetInverse()const
		{
			if (Row != Column)return *this;

			T detVal = GetLen();
			if (detVal == static_cast<T>(0.0f))return *this;
			detVal = static_cast<T>(1.0f) / detVal;

			MatrixBase out;
			bool findColFlg = false;
			bool findRowFlg = false;

			MatrixBase<T, Row - 1, Column - 1>massMat;

			for (unsigned long col = 0; col < Column; col++)
			{
				for (unsigned long row = 0; row < Row; row++)
				{
					findColFlg = false;
					for (unsigned long massCol = 0; massCol < Column - 1; massCol++)
					{
						findRowFlg = false;
						findColFlg = massCol == col ? true : findColFlg;
						for (unsigned long massRow = 0; massRow < Row - 1; massRow++)
						{
							findRowFlg = massRow == row ? true : findRowFlg;
							massMat[massRow][massCol] = m[findRowFlg ? massRow + 1 : massRow][findColFlg ? massCol + 1 : massCol];
						}
					}
					out[col][row] = massMat.GetLen() / detVal;
					if ((row + col) % 2 == 1)out[col][row] *= static_cast<T>(-1.0f);
				}
			}
			return out;
		}

		//ドゥーリトル法三角行列//
		inline ULMatrix GetDLUMatrix()const
		{
			ULMatrix luMat;

			if (Row != Column)return luMat;

			luMat.uMat.Set(*this);

			for (unsigned long i = 1; i < Row; i++)
			{
				auto col = luMat.uMat[i - 1];

				for (unsigned long j = i; j < Row; j++)
				{
					if (luMat.uMat[j][i - 1] == 0.0f)continue;
					if (col[i - 1] == 0.0f)continue;

					T k = luMat.uMat[j][i - 1] / col[i - 1];

					auto tmpCol = col;

					tmpCol *= k;

					luMat.lMat[j][i - 1] = tmpCol[i - 1];

					luMat.uMat[j] -= tmpCol;
				}
			}
			return luMat;
		}

		/*
		//クラウト法上三角行列//
		MatrixBase<T, Row, Column> GetLUMatrix()const
		{
			MatrixBase<T, Row, Column> tmpDetMat;

			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{

				}
			}
		}
		*/

		inline constexpr const unsigned long GetColumn()const { return Column; }

		inline constexpr const unsigned long GetRow()const { return Row; }

	public://Other Functions//

		inline void Identity()
		{
			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					m[i][j] = static_cast<T>(i != j ? 0.0f : 1.0f);
				}
			}
		}

		inline void Inverse()
		{
			Set(GetInverse());
		}

		inline void Inverse(const MatrixBase<T, Row, Column>& _mat)
		{
			Set(_mat.GetInverse());
		}

	private:

		VectorBase<T, Column> m[Row];

	};

	template<typename T, unsigned long Array>
	using SquareMatrixBase = MatrixBase<T, Array, Array>;

	template<typename T>
	struct Vector2Base
	{
		union {
			struct { T x, y; };
			struct { T w, h; };
			struct { T start, end; };
			struct { T high, low; };
			VectorBase<T, 2> val = VectorBase<T, 2>();
		};

	public://Constructor Destructor//

		CH_MATH_METHOD_VECTOR_CONSTRUCTOR(Vector2Base);

		inline Vector2Base(const T _x, const T _y)
		{
			x = _x;
			y = _y;
		}

	public://Serialize Deserialize//

		CH_MATH3D_METHOD_SERIALIZE(val);

		CH_MATH3D_METHOD_DESERIALIZE(val);


	};

	template<typename T>
	struct Vector3Base
	{
		union {
			struct { T x, y, z; };
			struct { T r, g, b; };
			VectorBase<T, 3> val = VectorBase<T, 3>();
		};

	public://Constructor Destructor//

		CH_MATH_METHOD_VECTOR_CONSTRUCTOR(Vector3Base);

		inline Vector3Base(const T _x, const T _y, const T _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}

	public://Serialize Deserialize//

		CH_MATH3D_METHOD_SERIALIZE(val);

		CH_MATH3D_METHOD_DESERIALIZE(val);

	};

	template<typename T>
	struct Vector4Base
	{
		union {
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			struct { T left, top, right, bottom; };
			VectorBase<T, 4> val = VectorBase<T, 4>();
		};

	public://Constructor Destructor//

		CH_MATH_METHOD_VECTOR_CONSTRUCTOR(Vector4Base);

		Vector4Base(const T _x, const T _y, const T _z, const T _w)
		{
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}

	public://Set Functions//

		//スクリーン上の座標に合わせて数値をセットする。//
		//スクリーン座標では左上が0,0の位置になり、右下に行けば行くほど数値が増える//
		inline void SetScreenCoordinates(const Vector2Base<T>& _pos, const Vector2Base<T>& _size)
		{
			left = _pos.x;
			right = _pos.x + _size.w;
			top = _pos.y;
			bottom = _pos.y + _size.h;
		}

		//投影座標に合わせて数値をセットする。//
		//投影座標では中央が0,0の位置になり、右上に行けば行くほど数値が増える//
		inline void SetProjectionCoordinates(const Vector2Base<T>& _pos, const Vector2Base<T>& _size)
		{
			auto tmpSize = _size;
			tmpSize.w *= 0.5f;
			tmpSize.h *= 0.5f;

			left = _pos.x - tmpSize.w;
			right = _pos.x + tmpSize.w;
			bottom = _pos.y - tmpSize.h;
			top = _pos.y + tmpSize.h;
		}

		//対象のVectorlで表される四角形と引数で入れたVectorlであらわされる四角形に重なっている四角形をあらわした　Vectorlを取得する//
		inline void SetOverlapsRect(const Vector4Base<T>& _vec)
		{
			if (!IsOverlaps(_vec))return;

			val.Set(GetOverlapsRect(*this, _vec).val);

			return;
		}

	public://Get Functions//

		inline Vector2Base<T> GetCoordinatesSizeFromCenter()const
		{
			Vector2Base<T> res;
			res.w = (right - left);
			res.w = (res.w < 0 ? -res.w : res.w) * 0.5f;
			res.h = (top - bottom) * 0.5f;
			res.h = (res.h < 0 ? -res.h : res.h) * 0.5f;
			return res;
		}

		inline Vector2Base<T> GetCoordinatesCenterPos()const
		{
			Vector2Base<T> res = GetCoordinatesSizeFromCenter();

			res.x += left;
			res.y += bottom;

			return res;
		}

	public://Static Get Functions//

		//対象のVectorlで表される四角形と引数で入れたVectorlであらわされる四角形に重なっている四角形をあらわした　Vectorlを取得する//
		inline static Vector4Base<T> GetOverlapsRect(const Vector4Base<T>& _vec1, const Vector4Base<T>& _vec2)
		{
			if (!_vec1.IsOverlaps(_vec2))return _vec1;

			Vector4Base<T> overlapsRect;

			overlapsRect.top = _vec2.top >= _vec1.top ? _vec1.top : _vec2.top;
			overlapsRect.left = _vec2.left <= _vec1.left ? _vec1.left : _vec2.left;
			overlapsRect.bottom = _vec2.bottom <= _vec1.bottom ? _vec1.bottom : _vec2.bottom;
			overlapsRect.right = _vec2.right >= _vec1.right ? _vec1.right : _vec2.right;

			return overlapsRect;
		}

	public://Is Functions//

		//対象のVectorlで表される四角形に引数で入れたVectorlであらわされる四角形が重なっているかの確認//
		inline bool IsOverlaps(const Vector4Base<T>& _target) const
		{
			return right >= _target.left &&
				left <= _target.right &&
				top >= _target.bottom &&
				bottom <= _target.top;
		}

		//対象のVectorlで表される四角形に引数で入れたVectorlで表される位置が重なっているかの確認//
		inline bool IsOnPoint(const Vector2Base<T>& _target) const
		{
			return right >= _target.x &&
				left <= _target.x &&
				top >= _target.y &&
				bottom <= _target.y;
		}

	public://Serialize Deserialize//

		CH_MATH3D_METHOD_SERIALIZE(val);

		template<typename CharaType>
		inline std::basic_string<CharaType> SerializeARGB(
			const std::basic_string<CharaType>& _cutChar = ChStd::GetCommaChara<CharaType>(),
			const std::basic_string<CharaType>& _endChar = ChStd::GetSemiColonChara<CharaType>())
		{
			Vector4Base<T> tmpVec;

			for (unsigned char i = 0; i < 4; i++)
			{
				tmpVec.val[(i + 1) % 4] = val[i];
			}

			return tmpVec.Serialize<CharaType>(_cutChar, _endChar);
		}

		CH_MATH3D_METHOD_DESERIALIZE(val);

		template<typename CharaType>
		void DeserializeARGB(
			const std::basic_string<CharaType>& _str,
			const size_t _fPos = 0,
			const std::basic_string<CharaType>& _cutChar = ChStd::GetCommaChara<CharaType>(),
			const std::basic_string<CharaType>& _endChar = ChStd::GetSemiColonChara<CharaType>(),
			const unsigned int _digit = 6)
		{
			Vector4Base<T> tmpVec;
			tmpVec.Deserialize<CharaType>(_str, _fPos, _cutChar, _endChar, _digit);

			for (unsigned char i = 0; i < 4; i++)
			{
				val[i] = tmpVec.val[(i + 1) % 4];
			}
		}
	};

	template<typename T>
	struct ChEularXYZ : public Vector3Base<T> {};

	template<typename T>
	struct ChEularXZY : public Vector3Base<T> {};

	template<typename T>
	struct ChEularYXZ : public Vector3Base<T> {};

	template<typename T>
	struct ChEularYZX : public Vector3Base<T> {};

	template<typename T>
	struct ChEularZXY : public Vector3Base<T> {};

	template<typename T>
	struct ChEularZYX : public Vector3Base<T> {};

	template<typename T>
	struct QuaternionBase
	{
		union {
			struct
			{
				T x, y, z, w;
			};
			VectorBase<T, 4> val = VectorBase<T, 4>();
		};

		inline QuaternionBase() { val.Identity(); }

		inline QuaternionBase(const QuaternionBase<T>& _qua) { val = _qua.val; }

		inline QuaternionBase(const T _x, const T _y, const T _z)
		{
			x = _x;
			y = _y;
			z = _z;
			w = 0.0f;
		}

		inline QuaternionBase(const T _x, const T _y, const T _z, const T _w)
		{
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}

		inline QuaternionBase(const Vector3Base<T>& _vec) { val = _vec.val; w = 0.0f; }

	public://Serialize Deserialize//

		CH_MATH3D_METHOD_SERIALIZE(val);

		CH_MATH3D_METHOD_DESERIALIZE(val);

	public://Set Functions//


		inline void SetSum(const QuaternionBase<T>& _qua1, const QuaternionBase<T>& _qua2) { val.Set(_qua1.val + _qua2.val); }

		////
		//https://qiita.com/drken/items/0639cf34cce14e8d58a5#1-4-%E3%82%AF%E3%82%A9%E3%83%BC%E3%82%BF%E3%83%8B%E3%82%AA%E3%83%B3%E3%81%AE%E3%81%8B%E3%81%91%E7%AE%97
		////
		// = q1 * q2;
		inline void SetMul(const QuaternionBase<T>& _qua1, const QuaternionBase<T>& _qua2)
		{
			QuaternionBase<T> tmp1 = _qua1, tmp2 = _qua2;
			x = (tmp1.w * tmp2.x) - (tmp1.z * tmp2.y) + (tmp1.y * tmp2.z) + (tmp1.x * tmp2.w);
			y = (tmp1.z * tmp2.x) + (tmp1.w * tmp2.y) - (tmp1.x * tmp2.z) + (tmp1.y * tmp2.w);
			z = -(tmp1.y * tmp2.x) + (tmp1.x * tmp2.y) + (tmp1.w * tmp2.z) + (tmp1.z * tmp2.w);

			w = (tmp1.w * tmp2.w) - (tmp1.x * tmp2.x) - (tmp1.y * tmp2.y) - (tmp1.z * tmp2.z);
		}

		inline void SetSum(const QuaternionBase<T>& _value) { SetSum(*this, _value); }

		inline void SetMul(const QuaternionBase<T>& _value) { SetMul(*this, _value); }

	public://Get Functions//

		inline Vector3Base<T> GetMul(const Vector3Base<T>& _dir) const { return QuaternionBase<T>::GetMul(*this, _dir); }

		CH_MATH_METHOD_QUATERNION_GET_EULER_ROTATION(
			XYZ,
			y,
			(2.0f * x * z + 2.0f * y * w),
			x,
			ChMath::GetATan((y* z + x * w) / (ww + 2.0f * y * y - 1.0f)),
			ChMath::GetATan(-(y * z - x * w) / (ww + 2.0f * z * z - 1.0f)),
			z,
			0.0f,
			ChMath::GetATan(-(2.0f * x * y - 2.0f * z * w) / (ww + 2.0f * x * x - 1.0f)));

		CH_MATH_METHOD_QUATERNION_GET_EULER_ROTATION(
			XZY,
			z,
			(-(2.0f * x * y - 2.0f * z * w)),
			x,
			ChMath::GetATan(-(y * z - x * w) / (ww + 2.0f * z * z - 1.0f)),
			ChMath::GetATan((y* z + x * w) / (ww + 2.0f * y * y - 1.0f)),
			y,
			0.0f,
			ChMath::GetATan((2.0f * x * z + 2.0f * y * w) / (ww + 2.0f * x * x - 1.0f))
		);

		CH_MATH_METHOD_QUATERNION_GET_EULER_ROTATION(
			YXZ,
			x,
			(-(2.0f * y * z - 2.0f * x * w)),
			y,
			ChMath::GetATan(-(x * z - y * w) / (ww + 2.0f * x * x - 1.0f)),
			ChMath::GetATan((x* z + y * w) / (ww + 2.0f * z * z - 1.0f)),
			z,
			0.0f,
			ChMath::GetATan((2.0f * x * y + 2.0f * z * w) / (ww + 2.0f * y * y - 1.0f))
		);

		CH_MATH_METHOD_QUATERNION_GET_EULER_ROTATION(
			YZX,
			z,
			(2.0f * x * y + 2.0f * z * w),
			x,
			0.0f,
			ChMath::GetATan(-(2.0f * y * z - 2.0f * x * w) / (ww + 2.0f * y * y - 1.0f)),
			y,
			ChMath::GetATan((x* z + y * w) / (ww + 2.0f * z * z - 1.0f)),
			ChMath::GetATan(-(x * z - y * w) / (ww + 2.0f * x * x - 1.0f))
		);

		CH_MATH_METHOD_QUATERNION_GET_EULER_ROTATION(
			ZXY,
			x,
			((2.0f * y * z + 2.0f * x * w)),
			y,
			0.0f,
			ChMath::GetATan(-(2.0f * x * y - 2.0f * z * w) / (ww + 2.0f * y * y - 1.0f)),
			z,
			ChMath::GetATan((x* z + y * w) / (ww + 2.0f * x * x - 1.0f)),
			ChMath::GetATan(-(x * z - y * w) / (ww + 2.0f * z * z - 1.0f))
		);

		CH_MATH_METHOD_QUATERNION_GET_EULER_ROTATION(
			ZYX,
			y,
			(-(2.0f * x * z - 2.0f * y * w)),
			x,
			0.0f,
			ChMath::GetATan((2.0f * y * z + 2.0f * x * w) / (ww + 2.0f * z * z - 1.0f)),
			z,
			ChMath::GetATan(-(x * y - z * w) / (ww + 2.0f * y * y - 1.0f)),
			ChMath::GetATan((x* y + z * w) / (ww + 2.0f * x * x - 1.0f))
		);

	public://Static Get Functions//

		inline static Vector3Base<T> GetMul(const QuaternionBase<T>& _qua, const Vector3Base<T>& _dir)
		{
			Vector3Base<T> res = _dir;
			res.val.Normalize();

			QuaternionBase<T> tmp = QuaternionBase<T>(res);

			QuaternionBase<T> idn = _qua;
			idn.Inverse();

			tmp.SetMul(tmp, idn);
			tmp.SetMul(_qua, tmp);

			res.val = tmp.val;

			return res;
		}

	public://Other Functions//

		void Identity() { val.Identity(); }

		void Inverse()
		{
			x = -x;
			y = -y;
			z = -z;
		}
	};

	template<typename T>
	struct BaseMatrix1x1
	{
		union
		{
			struct
			{
				T l_11;
			};
			struct
			{
				T r_11;
			};
			SquareMatrixBase<T, 1> m = SquareMatrixBase<T, 1>();
		};

	public://Constructor Destructor//

		CH_MATH_METHOD_MATRIX_CONSTRUCTOR(BaseMatrix1x1);

	public://Serialize Deserialize//

		CH_MATH3D_METHOD_SERIALIZE(m);

		CH_MATH3D_METHOD_DESERIALIZE(m);

		CH_MATH3D_METHOD_MATRIX_DESERIALIZE_UPPER;

	public://Other Functions//

		void Identity() { m.Identity(); }

		void Inverse() { m.Inverse(); }

	};

	template<typename T>
	struct BaseMatrix2x2
	{
		union
		{
			struct
			{
				T l_11, l_12;
				T l_21, l_22;
			};
			struct
			{
				T r_11, r_21;
				T r_12, r_22;
			};
			SquareMatrixBase<T, 2> m = SquareMatrixBase<T, 2>();
		};

	public://Constructor Destructor//

		CH_MATH_METHOD_MATRIX_CONSTRUCTOR(BaseMatrix2x2);

	public://Serialize Deserialize//

		CH_MATH3D_METHOD_SERIALIZE(m);

		CH_MATH3D_METHOD_DESERIALIZE(m);

		CH_MATH3D_METHOD_MATRIX_DESERIALIZE_UPPER;

	public://Other Functions//

		void Identity() { m.Identity(); }

		void Inverse() { m.Inverse(); }

	};

	template<typename T>
	struct BaseMatrix3x3
	{
		union
		{
			struct
			{
				T l_11, l_12, l_13;
				T l_21, l_22, l_23;
				T l_31, l_32, l_33;
			};
			struct
			{
				T r_11, r_21, r_31;
				T r_12, r_22, r_32;
				T r_13, r_23, r_33;
			};
			SquareMatrixBase<T, 3> m = SquareMatrixBase<T, 3>();
		};

	public://Constructor Destructor//

		CH_MATH_METHOD_MATRIX_CONSTRUCTOR(BaseMatrix3x3);

	public://Serialize Deserialize//


		CH_MATH3D_METHOD_SERIALIZE(m);

		CH_MATH3D_METHOD_DESERIALIZE(m);

		CH_MATH3D_METHOD_MATRIX_DESERIALIZE_UPPER;

	public://Other Functions//

		void Identity() { m.Identity(); }

		void Inverse() { m.Inverse(); }

	};

	template<typename T>
	struct BaseMatrix4x4
	{
		union
		{
			struct
			{
				T l_11, l_12, l_13, l_14;
				T l_21, l_22, l_23, l_24;
				T l_31, l_32, l_33, l_34;
				T l_41, l_42, l_43, l_44;
			};
			struct
			{
				T r_11, r_21, r_31, r_41;
				T r_12, r_22, r_32, r_42;
				T r_13, r_23, r_33, r_43;
				T r_14, r_24, r_34, r_44;
			};
			SquareMatrixBase<T, 4> m = SquareMatrixBase<T, 4>();
		};

	public://Constructor Destructor//

		CH_MATH_METHOD_MATRIX_CONSTRUCTOR(BaseMatrix4x4);

	public://Serialize Deserialize//

		CH_MATH3D_METHOD_SERIALIZE(m);

		CH_MATH3D_METHOD_DESERIALIZE(m);

		CH_MATH3D_METHOD_MATRIX_DESERIALIZE_UPPER;

	public://Get Functions//

		BaseMatrix4x4 GetConvertAxis()const
		{
			BaseMatrix4x4 tmp;

			for (unsigned long i = 0; i < m.GetColumn(); i++)
			{
				for (unsigned long j = 0; j < m.GetRow(); j++)
				{
					tmp.m[i][j] = m[j][i];
				}
			}

			return tmp;
		}

	public://Other Functions//

		void Identity() { m.Identity(); }

		void Inverse() { m.Inverse(); }

	};
}

#endif