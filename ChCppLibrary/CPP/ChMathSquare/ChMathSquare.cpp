#include"../../BaseIncluder/ChBase.h"

#include"ChMathSquare.h"

using namespace ChCpp;


MathSquare& MathSquare::operator = (const MathSquare& _mathSquare)
{
	if (this == &_mathSquare)return *this;

	SetSquare(_mathSquare);

	return *this;
}

void MathSquare::SetSquare(const ChVec4& _square)
{
	if ((_square.right - _square.left) < 0.0f || (_square.top - _square.bottom) < 0.0f)return;
	if(!squareList.empty())squareList.clear();
	auto square = ChPtr::Make_S<ChVec4>();
	*square = _square;
	squareList.push_back(square);
}

void MathSquare::SetSquare(const std::vector<ChPtr::Shared<ChVec4>>& _square)
{
	if (&_square == &squareList)return;
	if (!squareList.empty())squareList.clear();
	for (auto&& quare_it : _square)
	{
		AddSquare(*quare_it);
	}
}

void MathSquare::SetSquare(const MathSquare& _square)
{
	SetSquare(_square.squareList);
}

ChVec4 MathSquare::GetFirstSquare() const
{
	if (squareList.empty())return ChVec4();
	return *squareList[0];
}

ChVec4 MathSquare::GetLastSquare() const
{
	if (squareList.empty())return ChVec4();
	return *squareList[squareList.size() - 1];
}

void MathSquare::AddSquare(const ChVec4& _square)
{
	if ((_square.right - _square.left) < 0.0f || (_square.top - _square.bottom) < 0.0f)return;
	auto square = ChPtr::Make_S<ChVec4>();
	*square = _square;
	squareList.push_back(square);
}

void MathSquare::AddSquare(const MathSquare& _square)
{
	if (_square.GetCount() <= 0)return;
	for (auto&& square : _square.GetSquare())
	{
		squareList.push_back(square);
	}
}

void MathSquare::And(const MathSquare& _and)
{
	if (_and.squareList.empty())return;

	SetSquare(MathSquare::And(*this, _and));
}

void MathSquare::And(const ChVec4& _and)
{
	if (squareList.empty())return;

	SetSquare(MathSquare::And(*this, _and));
}

void MathSquare::Or(const MathSquare& _or)
{
	if (_or.squareList.empty())return;

	SetSquare(MathSquare::Or(*this, _or));
}

void MathSquare::Or(const ChVec4& _or)
{
	if (squareList.empty())return;

	SetSquare(MathSquare::Or(*this, _or));
}

void MathSquare::Sub(const MathSquare& _sub)
{
	if (_sub.squareList.empty())return;

	SetSquare(MathSquare::Sub(*this, _sub));
}

void MathSquare::Sub(const ChVec4& _sub)
{
	if (squareList.empty())return;

	SetSquare(MathSquare::Sub(*this, _sub));
}

MathSquare MathSquare::And(const MathSquare& _base, const MathSquare& _and)
{
	MathSquare res;

	if (_base.GetCount() <= 0)return res;
	if (_and.GetCount() <= 0)return res;

	for (auto&& andSquare : _and.GetSquare())
	{
		res.AddSquare(MathSquare::And(_base, *andSquare));
	}

	return res;
}

MathSquare MathSquare::And(const MathSquare& _base, const ChVec4& _and)
{
	MathSquare res;

	if (_base.GetCount() <= 0)return res;

	for (auto&& square : _base.GetSquare())
	{
		res.AddSquare(MathSquare::And(*square, _and));
	}

	return res;
}

MathSquare MathSquare::Or(const MathSquare& _base, const MathSquare& _or)
{
	MathSquare res;

	if (_base.GetCount() <= 0)return res;
	if (_or.GetCount() <= 0)return res;

	for (auto&& andSquare : _or.GetSquare())
	{
		res.AddSquare(MathSquare::Or(_base, *andSquare));
	}

	return res;
}

MathSquare MathSquare::Or(const MathSquare& _base, const ChVec4& _or)
{
	MathSquare res;

	if (_base.GetCount() <= 0)return res;

	for (auto&& square : _base.GetSquare())
	{
		res.AddSquare(MathSquare::Or(*square, _or));
	}

	return res;
}

MathSquare MathSquare::Sub(const MathSquare& _base, const MathSquare& _sub)
{
	MathSquare res;

	if (_base.GetCount() <= 0)return res;
	if (_sub.GetCount() <= 0)return res;

	for (auto&& andSquare : _sub.GetSquare())
	{
		res.AddSquare(MathSquare::Sub(_base, *andSquare));
	}

	return res;
}

MathSquare MathSquare::Sub(const MathSquare& _base, const ChVec4& _sub)
{
	MathSquare res;

	if (_base.GetCount() <= 0)return res;

	for (auto&& square : _base.GetSquare())
	{
		res.AddSquare(MathSquare::Sub(*square, _sub));
	}

	return res;
}

MathSquare MathSquare::And(const ChVec4& _base, const ChVec4& _and)
{
	MathSquare res;

	if ((_base.right - _base.left) <= 0|| (_base.top - _base.bottom) <= 0)return  res;
	if ((_and.right - _and.left) <= 0 || (_and.top - _and.bottom) <= 0)return  res;

	if (!_base.IsOverlaps(_and))
	{
		return res;
	}

	ChVec4 square = _base;
	square.OverlapsRect(_and);

	res.AddSquare(square);

	return res;

}

MathSquare MathSquare::Or(const ChVec4& _base, const ChVec4& _or)
{
	MathSquare res = MathSquare::Sub(_base, _or);

	res.AddSquare(MathSquare::And(_base, _or));
	res.AddSquare(MathSquare::And(_or, _base));

	return res;
}

MathSquare MathSquare::Sub(const ChVec4& _base, const ChVec4& _sub)
{
	MathSquare res;

	if ((_base.right - _base.left) <= 0 || (_base.top - _base.bottom) <= 0)return  res;
	if ((_sub.right - _sub.left) <= 0 || (_sub.top - _sub.bottom) <= 0)
	{
		res.AddSquare(_base);
		return  res;
	}

	if (_base.right < _sub.left ||
		_base.left > _sub.right ||
		_base.top < _sub.bottom ||
		_base.bottom > _sub.top)
	{
		res.AddSquare(_base);
		return  res;
	}

	ChVec4 onSquare = _base;

	onSquare.OverlapsRect(_sub);

	ChVec4 testSquareList[8]{
		ChVec4(_base.left,_base.top,onSquare.left,onSquare.top),//ç∂è„//
		ChVec4(onSquare.left,_base.top,onSquare.right,onSquare.top),//è„//
		ChVec4(onSquare.right,_base.top,_base.right,onSquare.top),//âEè„//
		ChVec4(onSquare.right,onSquare.top,_base.right,onSquare.bottom),//âE//
		ChVec4(onSquare.right,onSquare.bottom,_base.right,_base.bottom),//âEâ∫//
		ChVec4(onSquare.left,onSquare.bottom,onSquare.right,_base.bottom),//â∫//
		ChVec4(_base.left,onSquare.bottom,onSquare.left,_base.bottom),//ç∂â∫//
		ChVec4(_base.left,onSquare.top,onSquare.left,onSquare.bottom),//ç∂//
	};

	for (unsigned long i = 0; i < 8; i++)
	{
		if (testSquareList[i].right - testSquareList[i].left <= 0.0f)continue;
		if (testSquareList[i].top - testSquareList[i].bottom <= 0.0f)continue;

		res.AddSquare(testSquareList[i]);
	}

	return res;
}
