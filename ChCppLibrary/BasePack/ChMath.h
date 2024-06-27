#ifndef Ch_CPP_BMath_h
#define Ch_CPP_BMath_h

#include"ChStd.h"
#include"ChStr.h"

#ifndef CRLF_CHARA_FUNCTION
#define CRLF_CHARA_FUNCTION(type) NUMBER_FUNCTION_BASE(GetCRLFChara,type)
#endif

#ifndef COMMA_CHARA_FUNCTION
#define COMMA_CHARA_FUNCTION(type) NUMBER_FUNCTION_BASE(GetCommaChara,type)
#endif


#ifndef SEMICOLON_CHARA_FUNCTION
#define SEMICOLON_CHARA_FUNCTION(type) NUMBER_FUNCTION_BASE(GetSemiColonChara,type)
#endif

namespace ChStd
{
#ifdef CRT
	TO_NUMBER_FUNCTION(CRLF_CHARA_FUNCTION, "\r\n");
#endif

#ifdef CRT
	TO_NUMBER_FUNCTION(COMMA_CHARA_FUNCTION, ",");
#endif

#ifdef CRT
	TO_NUMBER_FUNCTION(SEMICOLON_CHARA_FUNCTION, ";");
#endif
}

namespace ChMath
{
#ifdef CRT
	double Round(const double& _val, const unsigned long _digit = 307)
	{
		if (_val == 0.0)return 0.0;

		double out = _val * std::powl(10, static_cast<double>(_digit - 1));
		out = std::round(out);
		out = out * std::powl(0.1, static_cast<double>(_digit - 1));

		return out;
	}
#else
	double Round(const double& _val, const unsigned long _digit = 307);
#endif

	float Round(const float& _val, const unsigned long _digit = 37);

#ifdef CRT
	long double SqrtEx(const long double& _base, const unsigned long _digit = 4931)
	{
		if (_base == 0.0)return 0.0;

		long double out = std::sqrt(_base);

		//微分積分自分で使えるようになってから再度考える//
		return out;

		unsigned long maxCount = _digit > 4931 ? 4931 : _digit;

		//以下を参照//
		//https://qiita.com/rytaryu/items/e5d760a80f9ce5db860f
		//

		for (unsigned long i = 0; i < maxCount; i++)
		{
			out = ((out * out) + _base) / (2 * out);
		}

		return out;
	}
#else
	long double SqrtEx(const long double& _base, const unsigned long _digit = 4931);
#endif

	double SqrtEx(const double& _base, const unsigned long _digit = 307);

	float SqrtEx(const float& _base, const unsigned long _digit = 37);

#ifdef CRT
	template<typename Floating>
	Floating GetSin(Floating _val)
	{
		return std::sin(_val);
	}
#else
	template<typename Floating>
	Floating GetSin(Floating _val);
#endif

#ifdef CRT
	template<typename Floating>
	Floating GetACos(Floating _val)
	{
		return std::acos(_val);
	}
#else
	template<typename Floating>
	Floating GetACos(Floating _val);
#endif

#ifdef CRT
	template<typename Floating>
	Floating GetCos(Floating _val)
	{
		return std::cos(_val);
	}
#else
	template<typename Floating>
	Floating GetCos(Floating _val);
#endif



	//2の平方根(有効桁数8桁)//
	static const float SQUARE_ROOT = 1.41421356f;

	//円周率//
	static const float PI = 3.1415f;

	template<typename T, unsigned long Array>
	class VectorBase
	{

	public://Operator Function//

		template<unsigned long _ArrayCount>
		operator VectorBase<T, _ArrayCount>()const
		{
			VectorBase<T, _ArrayCount> out;

			unsigned long maxVal = _ArrayCount > Array ? Array : _ArrayCount;

			for (unsigned long i = 0; i < maxVal; i++)
			{
				out[i] = val[i];
			}

			return out;
		}

		template<typename _T>
		operator VectorBase<_T, Array>()const
		{
			VectorBase<_T, Array> out;

			for (unsigned long i = 0; i < Array; i++)
			{
				out[i] = static_cast<_T>(val[i]);
			}

			return out;
		}

		T& operator [](const unsigned long _val)
		{
			return val[_val % Array];
		}

		T operator [](const unsigned long _val)const
		{
			return val[_val % Array];
		}

		explicit operator const T* const ()const
		{
			return val;
		}

		VectorBase& operator =(const VectorBase& _Array)
		{
			Set(_Array);
			return *this;
		}

		VectorBase& operator =(const T& _val)
		{
			Set(_val);
			return *this;
		}

		VectorBase& operator +=(const VectorBase& _Array)
		{
			Add(_Array);
			return *this;
		}
		VectorBase& operator -=(const VectorBase& _Array)
		{
			Sub(_Array);
			return *this;
		}
		VectorBase& operator *=(const VectorBase& _Array)
		{
			Mul(_Array);
			return *this;
		}
		VectorBase& operator /=(const VectorBase& _Array)
		{
			Div(_Array);
			return *this;
		}

		VectorBase operator +(const VectorBase& _Array)const
		{
			VectorBase out= *this;
			out.Add(_Array);
			return out;
		}
		VectorBase operator -(const VectorBase& _Array)const
		{
			VectorBase out = *this;
			out.Sub(_Array);
			return out;
		}
		VectorBase operator *(const VectorBase& _Array)const
		{
			VectorBase out= *this;
			out.Mul(_Array);
			return out;
		}
		VectorBase operator /(const VectorBase& _Array)const
		{
			VectorBase<T, Array> out = *this;
			out.Div(_Array);
			return out;
		}

		VectorBase& operator +=(const T& _val)
		{
			Add(_val);
			return *this;
		}
		VectorBase& operator -=(const T& _val)
		{
			Sub(_val);
			return *this;
		}
		VectorBase& operator *=(const T& _val)
		{
			Mul(_val);
			return *this;
		}
		VectorBase& operator /=(const T& _val)
		{
			Div(_val);
			return *this;
		}

		VectorBase operator +(const T& _val)const
		{
			VectorBase<T, Array> out = *this;
			out.Add(_val);
			return out;
		}
		VectorBase operator -(const T& _val)const
		{
			VectorBase<T, Array> out = *this;
			out.Sub(_val);
			return out;
		}
		VectorBase operator *(const T& _val)const
		{
			VectorBase<T, Array> out = *this;
			out.Mul(_val);
			return out;
		}
		VectorBase operator /(const T& _val)const
		{
			VectorBase<T, Array> out = *this;
			out.Div(_val);
			return out;
		}

		bool operator ==(const VectorBase& _Array)const
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				if (_Array.val[i] == val[i])continue;
				return false;
			}
			return true;
		}

		bool operator !=(const VectorBase& _Array)const
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				if (_Array.val[i] == val[i])continue;
				return true;
			}
			return false;
		}

	public://Constructor Destructor//

		VectorBase()
		{
			Identity();
		}

		VectorBase(const T(&_val)[Array]) :val(_val) {}

		inline VectorBase(const T(&_val))
		{
			Set(_val);
		}

		VectorBase(const VectorBase& _val)
		{
			Set(_val);
		}

	public://Operator Math Function//

		void Set(const VectorBase& _vec)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				val[i] = _vec.val[i];
			}
		}

		void Set(const T& _val)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				val[i] = _val;
			}
		}

		void Set(const T(&_arrayVal)[Array])
		{

			for (unsigned long i = 0; i < Array; i++)
			{
				val[i] = _arrayVal[i];
			}
		}

		void Add(const VectorBase& _vec)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				val[i] += _vec.val[i];
			}
		}

		void Add(const T& _val)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				val[i] += _val;
			}
		}

		void Sub(const VectorBase& _vec)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				val[i] -= _vec.val[i];
			}
		}

		void Sub(const T& _val)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				val[i] -= _val;
			}
		}

		void Mul(const VectorBase& _vec)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				val[i] *= _vec.val[i];
			}
		}

		void Mul(const T& _val)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				val[i] *= _val;
			}
		}

		void Div(const VectorBase& _vec)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				val[i] /= _vec.val[i] != static_cast<T>(0.0f) ? _vec.val[i] : static_cast<T>(1.0f);
			}
		}

		void Div(const T& _val)
		{
			T tmp = _val != static_cast<T>(0.0f) ? _val : static_cast<T>(1.0f);

			for (unsigned long i = 0; i < Array; i++)
			{
				val[i] /= tmp;
			}
		}

	public://Serialize Deserialize//

#ifdef CRT
		template<typename CharaType>
		std::basic_string<CharaType> Serialize(
			const std::basic_string<CharaType>& _cutChar = ChStd::GetCommaChara<CharaType>(),
			const std::basic_string<CharaType>& _endChar = ChStd::GetSemiColonChara<CharaType>())
		{
			std::basic_string<CharaType> tmp = ChStd::GetZeroChara<CharaType>();
			for (unsigned char i = 0; i < Array; i++)
			{
				tmp += ChStr::GetTextFromNum<CharaType,T>(val[i]);
				if (i == (Array - 1))break;
				tmp += _cutChar;
			}

			tmp += _endChar;

			return tmp;
		}
#endif

#ifdef CRT
		template<typename CharaType>
		void Deserialize(
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

					val[i] = ChStr::GetNumFromText<T, CharaType>(Num);

					//val[i] = ChMath::Round(val[i], _digit);

					tmp += Num.length();
					tmp += 1;

				}
				if (Test >= EPos)return;
			}
		}
#endif

	public://Set Functions//

		void SetLen(const T _len)
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

			T l = tmp / add;

			l = SqrtEx(l);
			Mul(l);

		}

	public://Get Functions//

		constexpr const unsigned long GetArray()const  { return Array; }

		//ベクトルの要素の大きさを得る//
		T GetElementsLen()
		{
			VectorBase tmp = *this;
			tmp.Abs();

			T out = static_cast<T>(0.0f);
			for (unsigned long i = 0; i < Array; i++)
			{
				out += tmp.val[i];
			}

			return out;
		}

		//ベクトルの大きさを得る//
		T GetLen(const unsigned long _digit = 6)const
		{
			T Len = static_cast<T>(0.0f);

			for (unsigned long i = 0; i < Array; i++)
			{
				Len += val[i] * val[i];
			}

			return SqrtEx(Len,_digit);
		}

		T GetCos(
			const VectorBase& _vec,
			const unsigned long _digit = 6)const
		{
			VectorBase tmp1, tmp2;

			tmp1 = *this;
			tmp2 = _vec;

			if (!tmp1.Normalize(_digit) || !tmp2.Normalize(_digit))return 0.0f;

			return tmp1.GetDot(tmp2);
		}

		T GetRadian(
			const VectorBase& _vec,
			const unsigned long _digit = 6)const
		{
			T tmp = GetCos(_vec, _digit);

			return static_cast<T>(GetACos(tmp));
		}

		T GetDot(
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

		VectorBase GetCross(
			const VectorBase& _vec1,
			const VectorBase& _vec2,
			const unsigned long _digit = 6)const
		{

			VectorBase out;

			for (unsigned char i = 0; i < Array; i++)
			{
				out.val[i] =
					(_vec1.val[(i + 1) % Array] * _vec2.val[(i + 2) % Array])
					- (_vec1.val[(i + 2) % Array] * _vec2.val[(i + 1) % Array]);
			}

			out.Normalize(_digit);

			return out;
		}

		const T* const GetVal()const
		{
			return val;
		}

	public://Other Functions//

		inline void Abs()
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				val[i] = val[i] < static_cast<T>(0.0f) ? val[i] * static_cast<T>(-1.0f) : val[i];
			}
		}

		inline void Abs(const VectorBase& _vec)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				val[i] = _vec.val[i] < static_cast<T>(0.0f) ? _vec.val[i] * static_cast<T>(-1.0f) : _vec.val[i];
			}
		}

		void Cross(
			const VectorBase& _vec,
			const unsigned long _digit = 6)
		{
			Set(GetCross(*this, _vec, _digit));
		}

		void Cross(
			const VectorBase& _vec1,
			const VectorBase& _vec2, 
			const unsigned long _digit = 6)
		{
			Set(GetCross(_vec1, _vec2, _digit));
		}

		//補正を行う(Nowは0～1)
		void Correction(
			const VectorBase& _start,
			const VectorBase& _end,
			const float _Now)
		{
			if (_Now <= 0.0f)
			{
				return;
			}

			if (_Now >= 1.0f)
			{
				return;
			}

			VectorBase tmpVec;

			tmpVec = _end - _start;

			tmpVec = _start + (tmpVec * _Now);


		}

		void Identity()
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				val[i] = static_cast<T>(i != 3 ? 0.0f : 1.0f);
			}
		}

		//ベクトルの長さを1にする//
		bool Normalize(const unsigned long _digit = 6)
		{
			T len = GetLen(_digit);

			if (len == static_cast<T>(1.0))return true;
			if (len == static_cast<T>(0.0))return false;

			for (unsigned long i = 0; i < Array; i++)
			{
				val[i] /= len;
			}

			return true;
		}

		//ベクトルの要素の合計を1にする//
		bool ElementsNormalize()
		{

			T len = GetElementsLen();

			if (len == static_cast<T>(1.0))return true;
			if (len == static_cast<T>(0.0))return false;

			for (unsigned long i = 0; i < Array; i++)
			{
				val[i] /= len;
			}

			return true;
		}

		static VectorBase Lerp(
			const VectorBase& _start,
			const VectorBase& _end,
			const float _pow)
		{
			if (_pow <= 0.0f)return _start;
			if (_pow >= 1.0f)return _end;

			VectorBase out;

			out = (_start * (1.0f - _pow)) + (_end * _pow);

			return out;
		}

		static VectorBase SLerp(
			const VectorBase& _start,
			const VectorBase& _end,
			const float _pow)
		{

			if (_pow >= 1.0f)return _end;
			if (_pow <= 0.0f)return _start;

			VectorBase start = _start;
			VectorBase end = _end;

			float rad = start.GetDot(end);
			rad = GetACos(rad);
			if (rad == 0.0f)return start;

			float baseSin = GetSin(rad);

			if (baseSin == 0.0f)return start;

			start.Mul(GetSin((1.0f - _pow)* rad) / baseSin);
			end.Mul(GetSin(_pow* rad) / baseSin);

			return (start + end);
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
		operator MatrixBase<T, _Row, _Column>()const
		{
			MatrixBase<T, _Row, _Column> out;

			unsigned long MinRow = _Row > Row ? Row : _Row;
			unsigned long MinColumn = _Column > Column ? Column : _Column;

			for (unsigned long i = 0; i < MinColumn; i++)
			{
				for (unsigned long j = 0; j < MinRow; j++)
				{
					out[i][j] = m[i][j];
				}
			}

			return out;
		}

		VectorBase<T, Row>& operator [](const unsigned long _col)
		{
			return m[_col % Row];
		}

		VectorBase<T, Row> operator [](const unsigned long _col)const
		{
			return m[_col % Row];
		}

		explicit operator const T** const ()const
		{
			return m;
		}

		MatrixBase& operator =(const MatrixBase& _mat)
		{
			Set(_mat);
			return *this;
		}

		MatrixBase& operator +=(const MatrixBase& _mat)
		{
			Add(_mat);

			return *this;
		}

		MatrixBase operator +(const MatrixBase& _Array)const
		{
			MatrixBase out;

			out = *this;
			out += _Array;

			return out;
		}

		MatrixBase& operator -=(const MatrixBase& _mat)
		{
			Sub(_mat);
			return *this;
		}

		MatrixBase operator -(const MatrixBase& _Array)const
		{
			MatrixBase out;

			out = *this;
			out -= _Array;

			return out;
		}

		MatrixBase& operator *=(const MatrixBase& _mat)
		{
			Mul(_mat);
			return *this;
		}

		MatrixBase operator *(const MatrixBase& _Mat)const
		{
			MatrixBase out;

			out = *this;
			out *= _Mat;

			return out;
		}

		MatrixBase& operator /=(const MatrixBase& _mat)
		{
			Div(_mat);
			return *this;
		}

		MatrixBase operator /(const MatrixBase& _Mat)const
		{
			MatrixBase out;
			out = *this;
			out /= _Mat;

			return out;
		}

	public://Contructor Destructor//

		MatrixBase()
		{
			Identity();
		}

		MatrixBase(const MatrixBase& _Mat)
		{
			Set(_Mat);
		}

	public://Operator Math Function//

		void Set(const MatrixBase& _mat)
		{
			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					m[i][j] = _mat.m[i][j];
				}
			}
		}

		void Set(const T& _val)
		{
			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					m[i][j] = _val;
				}
			}
		}

		void Add(const MatrixBase& _mat)
		{
			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					m[i][j] += _mat.m[i][j];
				}
			}
		}

		void Sub(const MatrixBase& _mat)
		{
			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					m[i][j] -= _mat.m[i][j];
				}
			}
		}

		void Mul(const MatrixBase& _mat)
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
		VectorBase<T, _Arrarys> VerticalMul(const VectorBase<T, _Arrarys> _vec)const
		{

			MatrixBase<T, Row, Column> tmpMat;

			tmpMat.Set(static_cast<T>(0.0f));

			unsigned long maxSize = _Arrarys;

			maxSize = maxSize >= Row ? Row : maxSize;
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
		VectorBase<T, _Arrarys>HorizontalMul(const VectorBase<T, _Arrarys> _vec)const
		{

			MatrixBase<T, Row, Column> tmpMat;

			tmpMat.Set(static_cast<T>(0.0f));

			unsigned long maxSize = _Arrarys;

			maxSize = maxSize >= Column ? Column : maxSize;
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

		void Div(const MatrixBase& _mat)
		{
			MatrixBase tmpMat;
			tmpMat = _mat;

			tmpMat.Inverse();

			Mul(tmpMat);

		}

	public://Serialize Deserialize//

#ifdef CRT
		template<typename CharaType>
		std::basic_string<CharaType> Serialize(
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
#endif

#ifdef CRT
		template<typename CharaType>
		std::basic_string<CharaType> SerializeUpper(
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
#endif

#ifdef CRT
		template<typename CharaType>
		void Deserialize(
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
					size_t Test = tmpStr.find(_cutChar, tmp);

					if (Test > EPos)Test = EPos;

					{
						tmpFPos = Test;

						std::basic_string<CharaType> Num = tmpStr.substr(tmp, tmpFPos - tmp);

						m[i][j] = ChStr::GetNumFromText<T, CharaType>(Num);

						tmp = Test + 1;
					}

					if (Test >= EPos)return;
				}

			}

		}
#endif

	public://Get Functions//

		T GetLen()const
		{
			T out = static_cast<T>(0.0f);

			if (Row != Column)return out;
			
			unsigned long tmpNum;
			for (unsigned long i = 0; i < Column; i++)
			{
				T add = m[0][i];
				T sub = m[0][i];

				for (unsigned long j = 1; j < Row; j++)
				{
					tmpNum = (i + j) % Row;
					add *= m[j % Column][tmpNum];

					tmpNum = (Row + i - j) % Row;
					sub *= m[j % Column][tmpNum];
				}

				out = out + add - sub;
			}
			return out;
		}

		MatrixBase GetCofactor(const unsigned long _Row, const unsigned long _Col)const
		{
			MatrixBase out;

			if (_Row >= Row || _Col >= Column)return out;

			bool ColFlg = false;

			for (unsigned long i = 0; i < Column - 1; i++)
			{
				if (i == _Col)ColFlg = true;

				bool RowFlg = false;

				for (unsigned long j = 0; j < Row - 1; j++)
				{
					if (j == _Row)RowFlg = true;
					out.m[i][j] = m[ColFlg ? i + 1 : i][RowFlg ? j + 1 : j];
				}
			}
		}

		//行列式//
		T GetDeterminant()const
		{
			return GetLen();
		}

		//掃き出し法による逆行列//
		MatrixBase GetInverse()const
		{
			if(Row != Column)return *this;

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
		ULMatrix GetDLUMatrix()const
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

		constexpr const unsigned long GetColumn()const { return Column; }

		constexpr const unsigned long GetRow()const { return Row; }

	public://Is Functions//

		bool IsValue(const MatrixBase& _mat)const
		{
			for (unsigned long i = 0; i < Row; i++)
			{
				for (unsigned long j = 0; j < Column; j++)
				{
					float test = m[i][j] - _mat.m[i][j];
					if (test < 0.001f && test > -0.001f)continue;
					return false;
				}
			}

			return true;
		}

	public://Other Functions//

		void Identity()
		{
			for (unsigned long i = 0; i < Column;i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					m[i][j] = static_cast<T>(i != j ? 0.0f : 1.0f);
				}
			}
		}

		static MatrixBase Lerp(
			const MatrixBase& _start,
			const MatrixBase& _end,
			const float _pow)
		{
			MatrixBase out;

			for (unsigned long i = 0; i < Row; i++)
			{
				out[i] = VectorBase<T, Column>::Lerp(_start[i], _end[i], _pow);
			}


			return out;
		}

		void Inverse()
		{
			Set(GetInverse());
		}

		void Inverse(const MatrixBase<T, Row, Column>& _mat)
		{
			Set(_mat.GetInverse());
		}

	private:

		VectorBase<T, Column> m[Row];

	};

	template<typename T,unsigned long Array>
	using SquareMatrixBase = MatrixBase<T, Array, Array>;

	template<typename T>
	struct Vector2Base
	{
		union {
			struct
			{
				T x, y;
			};
			struct
			{
				T w, h;
			};
			struct
			{
				T start, end;
			};
			struct
			{
				T high, low;
			};
			VectorBase<T, 2> val;
		};

		inline Vector2Base()
		{
			val.Identity();
		}

		inline Vector2Base(const T _num)
		{
			val.Set(_num);
		}

		inline Vector2Base(
			const T _x, const T _y)
		{
			x = _x;
			y = _y;
		}

		inline Vector2Base(const Vector2Base& _vec) { val = _vec.val; }
	};

	template<typename T>
	struct Vector3Base
	{
		union {
			struct
			{
				T x, y, z;
			};
			struct
			{
				T r, g, b;
			};
			VectorBase<T, 3> val;
		};

		inline Vector3Base()
		{
			val.Identity();
		}

		inline Vector3Base(const T _num)
		{
			val.Set(_num);
		}

		inline Vector3Base(
			const T _x, const T _y, const T _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}

		inline Vector3Base(const Vector3Base& _vec) { val = _vec.val; }
	};

	template<typename T>
	struct Vector4Base
	{
		union {
			struct
			{
				T x, y, z, w;
			};
			struct
			{
				T r, g, b, a;
			};
			struct
			{
				T left, top, right, bottom;
			};
			VectorBase<T, 4> val;
		};

		inline Vector4Base()
		{
			val.Identity();
		}

		inline Vector4Base(const T _num)
		{
			val.Set(_num);
		}

		inline Vector4Base(
			const T _x, const T _y, const T _z, const T _w)
		{
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}

		inline Vector4Base(const Vector4Base<T>& _vec) { val = _vec.val; }

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

		//対象のVectorlで表される四角形に引数で入れたVectorlであらわされる四角形が重なっているかの確認//
		inline bool IsOverlaps(const Vector4Base<T>& _target) const
		{
			if (right < _target.left ||
				left > _target.right ||
				top < _target.bottom ||
				bottom > _target.top)
			{
				return false;
			}

			return true;
		}

		//対象のVectorlで表される四角形に引数で入れたVectorlで表される位置が重なっているかの確認//
		inline bool IsOnPoint(const Vector2Base<T>& _target) const
		{
			if (right < _target.x ||
				left > _target.x ||
				top < _target.y ||
				bottom > _target.y)
			{
				return false;
			}

			return true;
		}

		//対象のVectorlで表される四角形と引数で入れたVectorlであらわされる四角形に重なっている四角形をあらわした　Vectorlを取得する//
		inline void OverlapsRect(const Vector4Base<T>& _vec)
		{
			if (!IsOverlaps(_vec))return;

			top = _vec.top >= top ? top : _vec.top;
			left = _vec.left <= left ? left : _vec.left;
			bottom = _vec.bottom <= bottom ? bottom : _vec.bottom;
			right = _vec.right >= right ? right : _vec.right;

			return;
		}

		//対象のVectorlで表される四角形と引数で入れたVectorlであらわされる四角形に重なっている四角形をあらわした　Vectorlを取得する//
		inline static Vector4Base<T> OverlapsRect(const Vector4Base<T>& _vec1,const Vector4Base<T>& _vec2)
		{
			if (!_vec1.IsOverlaps(_vec2))return _vec1;

			Vector4Base<T> overlapsRect;

			overlapsRect.top = _vec2.top >= _vec1.top ? _vec1.top : _vec2.top;
			overlapsRect.left = _vec2.left <= _vec1.left ? _vec1.left : _vec2.left;
			overlapsRect.bottom = _vec2.bottom <= _vec1.bottom ? _vec1.bottom : _vec2.bottom;
			overlapsRect.right = _vec2.right >= _vec1.right ? _vec1.right : _vec2.right;

			return overlapsRect;
		}
	};

	template<typename T>
	struct QuaternionBase
	{
		union {
			struct
			{
				T x, y, z, w;
			};
			VectorBase<T, 4> val;
		};

		inline QuaternionBase()
		{
			val.Identity();
		}

		inline QuaternionBase(const QuaternionBase<T>& _vec) { val = _vec.val; }
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
			SquareMatrixBase<T, 2> m;
		};

		inline BaseMatrix2x2()
		{
			m.Identity();
		}

		inline BaseMatrix2x2(const BaseMatrix2x2& _mat) { m = _mat.m; }

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
			SquareMatrixBase<T, 3> m;
		};

		inline BaseMatrix3x3()
		{
			m.Identity();
		}

		inline BaseMatrix3x3(const BaseMatrix3x3& _mat) { m = _mat.m; }
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
			SquareMatrixBase<T, 4> m;
		};

		inline BaseMatrix4x4()
		{
			m.Identity();
		}

		inline BaseMatrix4x4(const BaseMatrix4x4& _mat) { m = _mat.m; }
	};
}

#endif