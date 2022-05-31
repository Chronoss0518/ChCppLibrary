#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"ChPoint.h"

//ChINTPOINT Method//

ChINTPOINT& ChINTPOINT::operator+=(const ChINTPOINT& _cm)
{
	for (char i = 0; i < 2; i++)
	{
		val[i] += _cm.val[i];
	}
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
	for (char i = 0; i < 2; i++)
	{
		val[i] -= _cm.val[i];
	}
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
	for (char i = 0; i < 2; i++)
	{
		val[i] *= _cm.val[i];
	}
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
	for (char i = 0; i < 2; i++)
	{
		val[i] /= _cm.val[i] != 0 ? _cm.val[i] : 1;
	}
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
	for (char i = 0; i < 2; i++)
	{
		val[i] += _cm;
	}
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
	for (char i = 0; i < 2; i++)
	{
		val[i] -= _cm;
	}
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
	for (char i = 0; i < 2; i++)
	{
		val[i] *= _cm;
	}
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
	auto tmp = _cm != 0 ? _cm : 1;

	for (char i = 0; i < 2; i++)
	{
		val[i] /= tmp;
	}
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
	for (char i = 0; i < 2; i++)
	{
		val[i] += _cm.val[i];
	}
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
	for (char i = 0; i < 2; i++)
	{
		val[i] -= _cm.val[i];
	}
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
	for (char i = 0; i < 2; i++)
	{
		val[i] *= _cm.val[i];
	}
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
	for (char i = 0; i < 2; i++)
	{
		val[i] /= _cm.val[i] != 0 ? _cm.val[i] : 1;
	}
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
	for (char i = 0; i < 2; i++)
	{
		val[i] += _cm;
	}
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
	for (char i = 0; i < 2; i++)
	{
		val[i] -= _cm;
	}
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
	for (char i = 0; i < 2; i++)
	{
		val[i] *= _cm;
	}
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
	auto tmp = _cm != 0 ? _cm : 1;

	for (char i = 0; i < 2; i++)
	{
		val[i] /= tmp;
	}
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
