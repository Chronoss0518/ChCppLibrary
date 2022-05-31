#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"ChPoint.h"

//ChINTPOINT Method//

ChINTPOINT& ChINTPOINT::operator+=(const ChINTPOINT& _cm)
{
	val.Add(_cm.val);
	return *this;
}

ChINTPOINT ChINTPOINT::operator+(const ChINTPOINT& _cm)const
{
	ChINTPOINT out = *this;

	out += _cm;

	return out;
}

ChINTPOINT& ChINTPOINT::operator-=(const ChINTPOINT& _cm)
{
	val.Sub(_cm.val);
	return *this;
}

ChINTPOINT ChINTPOINT::operator-(const ChINTPOINT& _cm)const
{
	ChINTPOINT out = *this;

	out -= _cm;

	return out;
}

ChINTPOINT& ChINTPOINT::operator*=(const ChINTPOINT& _cm)
{
	val.Mul(_cm.val);
	return *this;
}

ChINTPOINT ChINTPOINT::operator*(const ChINTPOINT& _cm)const
{
	ChINTPOINT out = *this;

	out *= _cm;

	return out;
}

ChINTPOINT& ChINTPOINT::operator/=(const ChINTPOINT& _cm)
{
	val.Div(_cm.val);
	return *this;
}

ChINTPOINT ChINTPOINT::operator/(const ChINTPOINT& _cm)const
{
	ChINTPOINT out = *this;

	out /= _cm;

	return out;
}

ChINTPOINT& ChINTPOINT::operator+=(const int& _cm)
{

	val.Add(_cm);
	return *this;
}

ChINTPOINT ChINTPOINT::operator+(const int& _cm)const
{
	ChINTPOINT out = *this;

	out += _cm;

	return out;
}

ChINTPOINT& ChINTPOINT::operator-=(const int& _cm)
{
	val.Sub(_cm);
	return *this;
}

ChINTPOINT ChINTPOINT::operator-(const int& _cm)const
{
	ChINTPOINT out = *this;

	out -= _cm;

	return out;
}

ChINTPOINT& ChINTPOINT::operator*=(const int& _cm)
{
	val.Mul(_cm);
	return *this;
}

ChINTPOINT ChINTPOINT::operator*(const int& _cm)const
{
	ChINTPOINT out = *this;

	out *= _cm;

	return out;
}

ChINTPOINT& ChINTPOINT::operator/=(const int& _cm)
{
	val.Div(_cm);
	return *this;
}

ChINTPOINT ChINTPOINT::operator/(const int& _cm)const
{
	ChINTPOINT out = *this;

	out /= _cm;

	return out;
}

//ChPOINT Method//

ChPOINT& ChPOINT::operator+=(const ChPOINT& _cm)
{
	vec.val.Add(_cm.vec.val);
	return *this;
}

ChPOINT ChPOINT::operator+(const ChPOINT& _cm)const
{
	ChPOINT out(*this);

	out += _cm;

	return out;
}

ChPOINT& ChPOINT::operator-=(const ChPOINT& _cm)
{
	vec.val.Sub(_cm.vec.val);
	return *this;
}

ChPOINT ChPOINT::operator-(const ChPOINT& _cm)const
{
	ChPOINT out(*this);

	out -= _cm;

	return out;
}

ChPOINT& ChPOINT::operator*=(const ChPOINT& _cm)
{
	vec.val.Mul(_cm.vec.val);
	return *this;
}

ChPOINT ChPOINT::operator*(const ChPOINT& _cm)const
{
	ChPOINT out(*this);

	out *= _cm;

	return out;
}

ChPOINT& ChPOINT::operator/=(const ChPOINT& _cm)
{
	vec.val.Div(_cm.vec.val);
	return *this;
}

ChPOINT ChPOINT::operator/(const ChPOINT& _cm)const
{
	ChPOINT out(*this);

	out /= _cm;

	return out;
}

ChPOINT& ChPOINT::operator+=(const long& _cm)
{
	vec.val.Add(_cm);
	return *this;
}

ChPOINT ChPOINT::operator+(const long& _cm)const
{
	ChPOINT out(*this);

	out += _cm;

	return out;
}

ChPOINT& ChPOINT::operator-=(const long& _cm)
{
	vec.val.Sub(_cm);
	return *this;
}

ChPOINT ChPOINT::operator-(const long& _cm)const
{
	ChPOINT out(*this);

	out -= _cm;

	return out;
}

ChPOINT& ChPOINT::operator*=(const long& _cm)
{
	vec.val.Mul(_cm);
	return *this;
}

ChPOINT ChPOINT::operator*(const long& _cm)const
{
	ChPOINT out(*this);

	out *= _cm;

	return out;
}

ChPOINT& ChPOINT::operator/=(const long& _cm)
{
	vec.val.Div(_cm);
	return *this;
}

ChPOINT ChPOINT::operator/(const long& _cm)const
{
	ChPOINT out(*this);

	out /= _cm;

	return out;
}

ChStd::Bool ChPOINT::IsAll0()const
{
	for (char i = 0; i < 2; i++)
	{
		if (val[i] == 0)continue;
		return false;
	}
	return true;
}
