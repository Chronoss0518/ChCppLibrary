#ifdef _WINDOWS_

#ifndef Ch_Win_Point_h
#define Ch_Win_Point_h

typedef class ChINTPOINT:public ChMath::Vector2Base<int>
{
public://Operator Functions//

	ChINTPOINT& operator=(const ChINTPOINT& _cm)
	{
		if (this == &_cm)return *this;
		val.Set(_cm.val);
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

public://Constructor Destructor//

	ChINTPOINT(const ChINTPOINT& _cm)
	{
		if (this == &_cm)return;
		*this = _cm;
	}

	ChINTPOINT(const ChMath::Vector2Base<int>& _cm)
	{
		val.Set(_cm.val);
	}

	ChINTPOINT()
	{
		x = 0;
		y = 0;
	}

	ChINTPOINT(const int _x, const int _y)
	{
		x = _x;
		y = _y;
	}

	ChINTPOINT(const int _num)
	{
		val.Set(_num);
	}

public://Set Functions//

	inline void Set(const int _x, const int _y) { x = _x; y = _y; }

public://Is Functions//

	bool IsAll0()const;

public://Serialize Deserialize//

	inline std::string Serialize(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";")
	{
		return val.Serialize(_cutChar, _endChar);
	}

	inline void Deserialize(
		const std::string& _str
		, const size_t _fPos = 0
		, const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const unsigned int _digit = 6)
	{
		val.Deserialize(_str, _fPos, _cutChar, _endChar, _digit);
	}

public://Other Functions//

	inline void Abs() { val.Abs(); }

	inline void Identity() { val.Identity(); }


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

	bool IsAll0()const;

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