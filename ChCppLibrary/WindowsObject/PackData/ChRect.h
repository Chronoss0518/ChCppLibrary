#ifdef _WINDOWS_

#ifndef Ch_Win_Rect_h
#define Ch_Win_Rect_h

class ChLONGPOINT;

typedef class ChLONGRECT
{
public://Operator Functions//

	ChLONGRECT& operator=(const ChLONGRECT& _cm)
	{
		if (this == &_cm)return *this;
		x = _cm.x;
		y = _cm.y;
		return *this;
	}

	ChLONGRECT& operator+=(const ChLONGRECT& _cm);
	ChLONGRECT operator+(const ChLONGRECT& _cm)const;
	ChLONGRECT& operator-=(const ChLONGRECT& _cm);
	ChLONGRECT operator-(const ChLONGRECT& _cm)const;
	ChLONGRECT& operator*=(const ChLONGRECT& _cm);
	ChLONGRECT operator*(const ChLONGRECT& _cm)const;
	ChLONGRECT& operator/=(const ChLONGRECT& _cm);
	ChLONGRECT operator/(const ChLONGRECT& _cm)const;

	inline ChLONGRECT& operator=(const long& _cm)
	{
		vec.val.Set(_cm);
		return *this;
	}

	ChLONGRECT& operator+=(const long& _cm);
	ChLONGRECT operator+(const long& _cm)const;
	ChLONGRECT& operator-=(const long& _cm);
	ChLONGRECT operator-(const long& _cm)const;
	ChLONGRECT& operator*=(const long& _cm);
	ChLONGRECT operator*(const long& _cm)const;
	ChLONGRECT& operator/=(const long& _cm);
	ChLONGRECT operator/(const long& _cm)const;

	inline ChLONGRECT& operator=(const ChMath::Vector4Base<long>& _cm)
	{
		if (&vec == &_cm)return *this;
		vec.val.Set(_cm.val);
		return *this;
	}

	inline ChLONGRECT& operator=(const RECT& _cm)
	{
		if (&pt == &_cm)return *this;
		pt = _cm;
		return *this;
	}

	inline operator ChMath::Vector4Base<long>()const
	{
		return vec;
	}

	inline operator ChMath::Vector4Base<long>* ()
	{
		return &vec;
	}

	inline operator RECT()const
	{
		return pt;
	}

	inline operator RECT* ()
	{
		return &pt;
	}

public://ConstructerDestructer//

	ChLONGRECT(const ChLONGRECT& _cm)
	{
		if (this == &_cm)return;
		*this = _cm;
	}

	ChLONGRECT(const ChLONGPOINT& _pos, const ChLONGPOINT& _size);

	ChLONGRECT(const RECT& _cm)
	{
		if (&pt == &_cm)return;
		pt = _cm;
	}

	ChLONGRECT(const ChMath::Vector4Base<long>& _cm)
	{
		if (&vec == &_cm)return;
		vec.val.Set(_cm.val);
	}

	ChLONGRECT()
	{
		x = 0;
		y = 0;
	}

	ChLONGRECT(const long _x, const long _y)
	{
		x = _x;
		y = _y;
	}

	ChLONGRECT(const long _num)
	{
		Set(_num);
	}

public://Set Functions//

	inline void Set(const long _x, const long _y) { x = _x; y = _y; }

	inline void Set(const long _num) { x = _num; y = _num; }

public://Is Functions//

	bool IsAll0()const;

	inline bool IsOverlaps(const ChLONGRECT& _vec)
	{
		return vec.IsOverlaps(_vec.vec);
	}


public://Serialize Deserialize//

	inline std::string Serialize(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";")
	{
		return vec.val.Serialize(_cutChar, _endChar);
	}

	inline void Deserialize(
		const std::string& _str
		, const size_t _fPos = 0
		, const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const unsigned int _digit = 6)
	{
		vec.val.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
	}

public://Other Functions//

	inline void Abs() { vec.val.Abs(); }

	inline void Identity() { vec.val.Identity(); }

	inline ChLONGRECT OverlapsRect(const ChLONGRECT& _vec)
	{
		ChLONGRECT out;
		out.vec.val.Set(ChMath::Vector4Base<long>::OverlapsRect(vec,_vec).val);
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