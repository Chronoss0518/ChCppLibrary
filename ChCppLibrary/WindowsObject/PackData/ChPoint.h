#ifndef Ch_Win_Point_h
#define Ch_Win_Point_h

typedef class ChINTPOINT:public ChMath::Vector2Base<long>
{

	ChINTPOINT& operator=(const ChINTPOINT& _cm)
	{
		if (this == &_cm)return *this;
		x = _cm.x;
		y = _cm.y;
		return *this;
	}

	ChINTPOINT& operator+=(const ChINTPOINT& _cm);
	ChINTPOINT operator+(const ChINTPOINT& _cm)const;
	ChINTPOINT& operator-=(const ChINTPOINT& _cm);
	ChINTPOINT operator-(const ChINTPOINT& _cm)const;
	ChINTPOINT& operator*=(const ChINTPOINT& _cm);
	ChINTPOINT operator*(const ChINTPOINT& _cm)const;
	ChINTPOINT& operator/=(const ChINTPOINT& _cm);
	ChINTPOINT operator/(const ChINTPOINT& _cm)const;

	inline ChINTPOINT& operator=(const long& _cm)
	{
		val.Set(_cm);
		return *this;
	}

	ChINTPOINT& operator+=(const int& _cm);
	ChINTPOINT operator+(const int& _cm)const;
	ChINTPOINT& operator-=(const int& _cm);
	ChINTPOINT operator-(const int& _cm)const;
	ChINTPOINT& operator*=(const int& _cm);
	ChINTPOINT operator*(const int& _cm)const;
	ChINTPOINT& operator/=(const int& _cm);
	ChINTPOINT operator/(const int& _cm)const;

	ChINTPOINT(const ChINTPOINT& _cm)
	{
		if (this == &_cm)return;
		*this = _cm;
	}

	ChINTPOINT()
	{
		x = 0;
		y = 0;
	}

	ChINTPOINT(const long _x, const long _y)
	{
		x = _x;
		y = _y;
	}

	ChINTPOINT(const long _num)
	{
		val.Set(_num);
	}

public://Set Functions//

	inline void Set(const long _x, const long _y) { x = _x; y = _y; }

public://Is Functions//

	ChStd::Bool IsAll0()const;
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

	ChLONGPOINT& operator+=(const ChLONGPOINT& _cm);
	ChLONGPOINT operator+(const ChLONGPOINT& _cm)const;
	ChLONGPOINT& operator-=(const ChLONGPOINT& _cm);
	ChLONGPOINT operator-(const ChLONGPOINT& _cm)const;
	ChLONGPOINT& operator*=(const ChLONGPOINT& _cm);
	ChLONGPOINT operator*(const ChLONGPOINT& _cm)const;
	ChLONGPOINT& operator/=(const ChLONGPOINT& _cm);
	ChLONGPOINT operator/(const ChLONGPOINT& _cm)const;

	inline ChLONGPOINT& operator=(const long& _cm) 
	{
		vec.val.Set(_cm); 
		return *this;
	}

	ChLONGPOINT& operator+=(const long& _cm);
	ChLONGPOINT operator+(const long& _cm)const;
	ChLONGPOINT& operator-=(const long& _cm);
	ChLONGPOINT operator-(const long& _cm)const;
	ChLONGPOINT& operator*=(const long& _cm);
	ChLONGPOINT operator*(const long& _cm)const;
	ChLONGPOINT& operator/=(const long& _cm);
	ChLONGPOINT operator/(const long& _cm)const;

	inline ChLONGPOINT& operator=(const ChMath::Vector2Base<long>& _cm)
	{
		if (&vec == &_cm)return *this;
		vec.val.Set(_cm.val);
		return *this;
	}

	inline ChLONGPOINT& operator=(const POINT& _cm)
	{
		if (&pt == &_cm)return *this;
		pt = _cm;
		return *this;
	}

	inline operator ChMath::Vector2Base<long>()const
	{
		return vec;
	}

	inline operator ChMath::Vector2Base<long>* ()
	{
		return &vec;
	}

	inline operator POINT()const
	{
		return pt;
	}

	inline operator POINT* ()
	{
		return &pt;
	}

public://ConstructerDestructer//

	ChLONGPOINT(const ChLONGPOINT& _cm)
	{
		if (this == &_cm)return;
		*this = _cm;
	}

	ChLONGPOINT(const POINT& _cm)
	{
		if (&pt == &_cm)return;
		pt = _cm;
	}

	ChLONGPOINT(const ChMath::Vector2Base<long>& _cm)
	{
		if (&vec == &_cm)return;
		vec.val.Set(_cm.val);
	}

	ChLONGPOINT()
	{
		x = 0;
		y = 0;
	}

	ChLONGPOINT(const long _x, const long _y)
	{
		x = _x;
		y = _y;
	}

	ChLONGPOINT(const long _num)
	{
		Set(_num);
	}

public://Set Functions//

	inline void Set(const long _x, const long _y) { x = _x; y = _y; }

	inline void Set(const long _num) { x = _num; y = _num; }

public://Is Functions//

	ChStd::Bool IsAll0()const;

public://Member Values//

	union
	{
		ChMath::Vector2Base<long> vec;
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