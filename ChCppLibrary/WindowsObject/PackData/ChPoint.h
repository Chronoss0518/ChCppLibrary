#ifdef _WINDOWS_

#ifndef Ch_Win_Point_h
#define Ch_Win_Point_h

#include"../../BasePack/ChMath.h"

#ifndef	Ch_Win_POINT_MATH_METHOD
#define	Ch_Win_POINT_MATH_METHOD(_Operator,_BaseClass,_ArgsClass,_MathFunction) \
_BaseClass##& operator##_Operator##=(const _ArgsClass##& _cm){\
	_MathFunction\
	return *this;}\
\
_BaseClass operator##_Operator##(const _ArgsClass##& _cm)const{\
	_BaseClass res = *this;\
	res += _cm;\
	return res;}
#endif

#ifndef	Ch_Win_POINT_CONSTRUCTOR_METHOD
#define	Ch_Win_POINT_CONSTRUCTOR_METHOD(_BaseClass,_BaseType)\
_BaseClass##(const ChMath::Vector2Base<##_BaseType##>& _cm) :ChMath::Vector2Base<##_BaseType##>(_cm) {}\
_BaseClass##(const _BaseType _num) { val.Set(_num); }\
_BaseClass##() { val.Identity(); }
#endif

#ifndef Ch_Win_POINT_IS_ALL0_METHOD
#define Ch_Win_POINT_IS_ALL0_METHOD \
bool IsAll0()const{\
	for (char i = 0; i < 2; i++){\
		if (val[i] == 0)continue;\
		return false;}\
	return true;}
#endif

typedef class ChINTPOINT:public ChMath::Vector2Base<int>
{
public://Operator Functions//

	ChINTPOINT& operator=(const ChMath::Vector2Base<int>& _cm)
	{
		if (this == &_cm)return *this;
		val.Set(_cm.val);
		return *this;
	}

	Ch_Win_POINT_MATH_METHOD(+, ChINTPOINT, ChMath::Vector2Base<int>, val.Add(_cm.val););
	Ch_Win_POINT_MATH_METHOD(-, ChINTPOINT, ChMath::Vector2Base<int>, val.Sub(_cm.val););
	Ch_Win_POINT_MATH_METHOD(*, ChINTPOINT, ChMath::Vector2Base<int>, val.Mul(_cm.val););
	Ch_Win_POINT_MATH_METHOD(/, ChINTPOINT, ChMath::Vector2Base<int>, val.Div(_cm.val););

	ChINTPOINT& operator=(const long& _cm)
	{
		val.Set(_cm);
		return *this;
	}

	Ch_Win_POINT_MATH_METHOD(+, ChINTPOINT, int, val.Add(_cm););
	Ch_Win_POINT_MATH_METHOD(-, ChINTPOINT, int, val.Sub(_cm););
	Ch_Win_POINT_MATH_METHOD(*, ChINTPOINT, int, val.Mul(_cm););
	Ch_Win_POINT_MATH_METHOD(/, ChINTPOINT, int, val.Div(_cm););

public://Constructor Destructor//

	Ch_Win_POINT_CONSTRUCTOR_METHOD(ChINTPOINT, int);

	ChINTPOINT(const int _x, const int _y)
	{
		x = _x;
		y = _y;
	}


public://Set Functions//

	inline void Set(const int _x, const int _y) { x = _x; y = _y; }

public://Is Functions//

	Ch_Win_POINT_IS_ALL0_METHOD

public://Other Functions//

	void Abs() { val.Abs(); }

	void Identity() { val.Identity(); }


}ChIPoint;

typedef class ChLONGPOINT
{
public://Operator Functions//

	ChLONGPOINT& operator=(const ChLONGPOINT& _cm)
	{
		if (this == &_cm)return *this;
		x = _cm.x;
		y = _cm.y;
		return *this;
	}

	Ch_Win_POINT_MATH_METHOD(+, ChLONGPOINT, ChLONGPOINT, vec.val.Add(_cm.vec.val););
	Ch_Win_POINT_MATH_METHOD(-, ChLONGPOINT, ChLONGPOINT, vec.val.Sub(_cm.vec.val););
	Ch_Win_POINT_MATH_METHOD(*, ChLONGPOINT, ChLONGPOINT, vec.val.Mul(_cm.vec.val););
	Ch_Win_POINT_MATH_METHOD(/ , ChLONGPOINT, ChLONGPOINT, vec.val.Div(_cm.vec.val););

	ChLONGPOINT& operator=(const ChMath::Vector2Base<long>& _cm)
	{
		if (&vec == &_cm)return *this;
		vec.val.Set(_cm.val);
		return *this;
	}

	Ch_Win_POINT_MATH_METHOD(+, ChLONGPOINT, ChMath::Vector2Base<long>, vec.val.Add(_cm.val););
	Ch_Win_POINT_MATH_METHOD(-, ChLONGPOINT, ChMath::Vector2Base<long>, vec.val.Sub(_cm.val););
	Ch_Win_POINT_MATH_METHOD(*, ChLONGPOINT, ChMath::Vector2Base<long>, vec.val.Mul(_cm.val););
	Ch_Win_POINT_MATH_METHOD(/ , ChLONGPOINT, ChMath::Vector2Base<long>, vec.val.Div(_cm.val););

	ChLONGPOINT& operator=(const POINT& _cm)
	{
		if (&pt == &_cm)return *this;
		pt = _cm;
		return *this;
	}

	Ch_Win_POINT_MATH_METHOD(+, ChLONGPOINT, POINT, ChLONGPOINT tmp = _cm;vec.val.Add(tmp.val););
	Ch_Win_POINT_MATH_METHOD(-, ChLONGPOINT, POINT, ChLONGPOINT tmp = _cm;vec.val.Sub(tmp.val););
	Ch_Win_POINT_MATH_METHOD(*, ChLONGPOINT, POINT, ChLONGPOINT tmp = _cm;vec.val.Mul(tmp.val););
	Ch_Win_POINT_MATH_METHOD(/, ChLONGPOINT, POINT, ChLONGPOINT tmp = _cm;vec.val.Div(tmp.val););

	ChLONGPOINT& operator=(const long& _cm) 
	{
		vec.val.Set(_cm); 
		return *this;
	}

	Ch_Win_POINT_MATH_METHOD(+, ChLONGPOINT, long, vec.val.Add(_cm););
	Ch_Win_POINT_MATH_METHOD(-, ChLONGPOINT, long, vec.val.Sub(_cm););
	Ch_Win_POINT_MATH_METHOD(*, ChLONGPOINT, long, vec.val.Mul(_cm););
	Ch_Win_POINT_MATH_METHOD(/, ChLONGPOINT, long, vec.val.Div(_cm););

	operator ChMath::Vector2Base<long>()const { return vec; }

	operator ChMath::Vector2Base<long>* () { return &vec; }
	
	operator POINT()const { return pt; }
	
	operator POINT* () { return &pt; }

public://ConstructerDestructer//

	ChLONGPOINT(const ChLONGPOINT& _cm) { *this = _cm; }

	ChLONGPOINT(const POINT& _cm)
	{
		if (&pt == &_cm)return;
		pt = _cm;
	}

	ChLONGPOINT(const ChMath::Vector2Base<long>& _cm)
	{
		vec.val.Set(_cm.val);
	}

	ChLONGPOINT() { vec.val.Identity(); }

	ChLONGPOINT(const long _x, const long _y)
	{
		x = _x;
		y = _y;
	}

	ChLONGPOINT(const long _num) { vec.val.Set(_num); }

public://Set Functions//

	void Set(const long _x, const long _y) { x = _x; y = _y; }

	void Set(const long _num) { vec.val.Set(_num); }

public://Is Functions//
	
	Ch_Win_POINT_IS_ALL0_METHOD

public://Other Functions//

	inline void Abs() { vec.val.Abs(); }

	inline void Identity() { vec.val.Identity(); }

public://Member Values//

	union
	{
		ChMath::Vector2Base<long> vec = 0;
		POINT pt;
		struct
		{
			long x, y;
		};
		struct
		{
			long w, h;
		};
		long val[2];
	};

}ChPOINT,ChPoint;



#endif

#endif