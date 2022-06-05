#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"ChRect.h"

//ChLONGRECT Method//

ChLONGRECT& ChLONGRECT::operator+=(const ChLONGRECT& _cm)
{
	vec.val.Add(_cm.vec.val);
	return *this;
}

ChLONGRECT ChLONGRECT::operator+(const ChLONGRECT& _cm)const
{
	ChLONGRECT out(*this);

	out += _cm;

	return out;
}

ChLONGRECT& ChLONGRECT::operator-=(const ChLONGRECT& _cm)
{
	vec.val.Sub(_cm.vec.val);
	return *this;
}

ChLONGRECT ChLONGRECT::operator-(const ChLONGRECT& _cm)const
{
	ChLONGRECT out(*this);

	out -= _cm;

	return out;
}

ChLONGRECT& ChLONGRECT::operator*=(const ChLONGRECT& _cm)
{
	vec.val.Mul(_cm.vec.val);
	return *this;
}

ChLONGRECT ChLONGRECT::operator*(const ChLONGRECT& _cm)const
{
	ChLONGRECT out(*this);

	out *= _cm;

	return out;
}

ChLONGRECT& ChLONGRECT::operator/=(const ChLONGRECT& _cm)
{
	vec.val.Div(_cm.vec.val);
	return *this;
}

ChLONGRECT ChLONGRECT::operator/(const ChLONGRECT& _cm)const
{
	ChLONGRECT out(*this);

	out /= _cm;

	return out;
}

ChLONGRECT& ChLONGRECT::operator+=(const long& _cm)
{
	vec.val.Add(_cm);
	return *this;
}

ChLONGRECT ChLONGRECT::operator+(const long& _cm)const
{
	ChLONGRECT out(*this);

	out += _cm;

	return out;
}

ChLONGRECT& ChLONGRECT::operator-=(const long& _cm)
{
	vec.val.Sub(_cm);
	return *this;
}

ChLONGRECT ChLONGRECT::operator-(const long& _cm)const
{
	ChLONGRECT out(*this);

	out -= _cm;

	return out;
}

ChLONGRECT& ChLONGRECT::operator*=(const long& _cm)
{
	vec.val.Mul(_cm);
	return *this;
}

ChLONGRECT ChLONGRECT::operator*(const long& _cm)const
{
	ChLONGRECT out(*this);

	out *= _cm;

	return out;
}

ChLONGRECT& ChLONGRECT::operator/=(const long& _cm)
{
	vec.val.Div(_cm);
	return *this;
}

ChLONGRECT ChLONGRECT::operator/(const long& _cm)const
{
	ChLONGRECT out(*this);

	out /= _cm;

	return out;
}

ChStd::Bool ChLONGRECT::IsAll0()const
{
	for (char i = 0; i < 2; i++)
	{
		if (val[i] == 0)continue;
		return false;
	}
	return true;
}
