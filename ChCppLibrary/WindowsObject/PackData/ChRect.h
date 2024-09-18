#ifdef _WINDOWS_

#ifndef Ch_Win_Rect_h
#define Ch_Win_Rect_h

#include"../../BasePack/ChMath.h"

#ifndef	Ch_Win_RECT_MATH_METHOD
#define	Ch_Win_RECT_MATH_METHOD(_Operator,_BaseClass,_ArgsClass,_MathFunction) \
_BaseClass##& operator##_Operator##=(const _ArgsClass##& _cm){\
	_MathFunction\
	return *this;}\
\
_BaseClass operator##_Operator##(const _ArgsClass##& _cm)const{\
	_BaseClass res = *this;\
	res += _cm;\
	return res;}
#endif

#ifndef	Ch_Win_RECT_CONSTRUCTOR_METHOD
#define	Ch_Win_RECT_CONSTRUCTOR_METHOD(_BaseClass,_BaseType)\
_BaseClass##(const ChMath::Vector2Base<##_BaseType##>& _cm) :ChMath::Vector2Base<##_BaseType##>(_cm) {}\
_BaseClass##(const _BaseType _num) { val.Set(_num); }\
_BaseClass##() { val.Identity(); }
#endif

class ChLONGPOINT;

typedef class ChLONGRECT
{
public://Operator Functions//

	ChLONGRECT& operator=(const ChLONGRECT& _cm)
	{
		if (this == &_cm)return *this;
		vec.val.Set(_cm.val);
		return *this;
	}

	Ch_Win_RECT_MATH_METHOD(+, ChLONGRECT, ChLONGRECT, vec.val.Add(_cm.vec.val););
	Ch_Win_RECT_MATH_METHOD(-, ChLONGRECT, ChLONGRECT, vec.val.Sub(_cm.vec.val););
	Ch_Win_RECT_MATH_METHOD(*, ChLONGRECT, ChLONGRECT, vec.val.Mul(_cm.vec.val););
	Ch_Win_RECT_MATH_METHOD(/ , ChLONGRECT, ChLONGRECT, vec.val.Div(_cm.vec.val););

	ChLONGRECT& operator=(const ChMath::Vector4Base<long>& _cm)
	{
		if (&vec == &_cm)return *this;
		vec.val.Set(_cm.val);
		return *this;
	}

	Ch_Win_RECT_MATH_METHOD(+, ChLONGRECT, ChMath::Vector4Base<long>, vec.val.Add(_cm.val););
	Ch_Win_RECT_MATH_METHOD(-, ChLONGRECT, ChMath::Vector4Base<long>, vec.val.Sub(_cm.val););
	Ch_Win_RECT_MATH_METHOD(*, ChLONGRECT, ChMath::Vector4Base<long>, vec.val.Mul(_cm.val););
	Ch_Win_RECT_MATH_METHOD(/, ChLONGRECT, ChMath::Vector4Base<long>, vec.val.Div(_cm.val););

	ChLONGRECT& operator=(const RECT& _cm)
	{
		if (&pt == &_cm)return *this;
		pt = _cm;
		return *this;
	}

	Ch_Win_RECT_MATH_METHOD(+, ChLONGRECT, RECT, ChLONGRECT tmp = _cm;vec.val.Add(tmp.vec.val););
	Ch_Win_RECT_MATH_METHOD(-, ChLONGRECT, RECT, ChLONGRECT tmp = _cm;vec.val.Sub(tmp.vec.val););
	Ch_Win_RECT_MATH_METHOD(*, ChLONGRECT, RECT, ChLONGRECT tmp = _cm;vec.val.Mul(tmp.vec.val););
	Ch_Win_RECT_MATH_METHOD(/, ChLONGRECT, RECT, ChLONGRECT tmp = _cm;vec.val.Div(tmp.vec.val););

	ChLONGRECT& operator=(const long& _cm)
	{
		vec.val.Set(_cm);
		return *this;
	}

	Ch_Win_RECT_MATH_METHOD(+, ChLONGRECT, long, vec.val.Add(_cm););
	Ch_Win_RECT_MATH_METHOD(-, ChLONGRECT, long, vec.val.Sub(_cm););
	Ch_Win_RECT_MATH_METHOD(*, ChLONGRECT, long, vec.val.Mul(_cm););
	Ch_Win_RECT_MATH_METHOD(/, ChLONGRECT, long, vec.val.Div(_cm););


	operator ChMath::Vector4Base<long>()const { return vec; }

	operator ChMath::Vector4Base<long>* (){return &vec;}

	operator RECT()const { return pt; }

	operator RECT* (){return &pt;}

public://ConstructerDestructer//

	ChLONGRECT(const ChLONGRECT& _cm)
	{
		if (this == &_cm)return;
		*this = _cm;
	}

	ChLONGRECT(const ChMath::Vector2Base<long>& _pos, const ChMath::Vector2Base<long>& _size) { vec.SetScreenCoordinates(_pos, _size); }

	ChLONGRECT(const RECT& _cm)
	{
		if (&pt == &_cm)return;
		pt = _cm;
	}

	ChLONGRECT(const ChMath::Vector4Base<long>& _cm) { vec.val.Set(_cm.val); }

	ChLONGRECT() { vec.val.Identity(); }

	ChLONGRECT(const long _x, const long _y)
	{
		x = _x;
		y = _y;
	}

	ChLONGRECT(const long _num) { vec.val.Set(_num); }

public://Set Functions//

	void Set(const long _x, const long _y) { x = _x; y = _y; }

	void Set(const long _num) { vec.val.Set(_num); }

public://Is Functions//

	bool IsAll0()const
	{
		for (char i = 0; i < 2; i++)
		{
			if (val[i] == 0)continue;
			return false;
		}
		return true;
	}

	bool IsOverlaps(const ChLONGRECT& _vec) { return vec.IsOverlaps(_vec.vec); }


public://Other Functions//

	void Abs() { vec.val.Abs(); }

	void Identity() { vec.val.Identity(); }

	ChLONGRECT OverlapsRect(const ChLONGRECT& _vec)
	{
		ChLONGRECT out;
		out.vec.val.Set(ChMath::Vector4Base<long>::GetOverlapsRect(vec,_vec).val);
		return out;
	}

public://Member Values//

	union
	{
		ChMath::Vector4Base<long> vec = 0;
		RECT pt;
		struct
		{
			long x, y, w, h;
		};
		struct
		{
			long left, top, right, bottom;
		};
		long val[4];
	};

}ChRECT, ChRect;



#endif

#endif