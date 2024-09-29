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
	Clear();
	AddSquare(_square);
}

void MathSquare::SetSquare(const MathSquare& _square)
{
	Clear();
	for(unsigned long i = 0;i < _square.GetCount(); i++)
		AddSquare(_square.GetSquare(i));
}

void MathSquare::SetSquare(const ChVec2& _leftTop, const ChVec2& _rightTop, const ChVec2& _rightBottom, const ChVec2& _leftBottom, const unsigned long _cutCount)
{
	if (_leftTop.x - _rightTop.x <= 0.0f)return;
	if (_rightTop.y - _rightBottom.y <= 0.0f)return;
	if (_rightBottom.x - _leftBottom.x <= 0.0f)return;
	if (_leftBottom.y -_leftTop.y <= 0.0f)return;
	Clear();
	AddSquare(_leftTop, _rightTop, _rightBottom, _leftBottom, _cutCount);

}

ChVec4 MathSquare::GetFirstSquare() const
{
	return GetSquare(0);
}

ChVec4 MathSquare::GetLastSquare() const
{
	return GetSquare(GetCount() - 1);
}

void MathSquare::AddSquare(const ChVec4& _square)
{
	if ((_square.right - _square.left) < 0.0f || (_square.top - _square.bottom) < 0.0f)return;
	PushBack(_square);
}

void MathSquare::AddSquare(const MathSquare& _square)
{
	if (_square.GetCount() <= 0)return;
	for (unsigned long i = 0; i < GetCount();i++)
		AddSquare(GetSquare(i));
}

void MathSquare::And(const MathSquare& _and)
{
	if (_and.IsEmpty())return;
	SetSquare(MathSquare::And(*this, _and));
}

void MathSquare::And(const ChVec4& _and)
{
	if (IsEmpty())return;
	SetSquare(MathSquare::And(*this, _and));
}

void MathSquare::Or(const MathSquare& _or)
{
	if (_or.IsEmpty())return;
	SetSquare(MathSquare::Or(*this, _or));
}

void MathSquare::Or(const ChVec4& _or)
{
	if (IsEmpty())return;
	SetSquare(MathSquare::Or(*this, _or));
}

void MathSquare::Sub(const MathSquare& _sub)
{
	if (_sub.IsEmpty())return;
	SetSquare(MathSquare::Sub(*this, _sub));
}

void MathSquare::Sub(const ChVec4& _sub)
{
	if (IsEmpty())return;
	SetSquare(MathSquare::Sub(*this, _sub));
}

MathSquare MathSquare::And(const MathSquare& _base, const MathSquare& _and)
{
	MathSquare res;

	if (_base.GetCount() <= 0)return res;
	if (_and.GetCount() <= 0)return res;

	for (unsigned long i = 0;i < _and.GetCount();i++)
		res.AddSquare(MathSquare::And(_base, _and.GetSquare(i)));

	return res;
}

MathSquare MathSquare::And(const MathSquare& _base, const ChVec4& _and)
{
	MathSquare res;

	if (_base.GetCount() <= 0)return res;

	for (unsigned long i = 0;i < _base.GetCount() ; i++)
		res.AddSquare(MathSquare::And(_base.GetSquare(i), _and));

	return res;
}

MathSquare MathSquare::Or(const MathSquare& _base, const MathSquare& _or)
{
	MathSquare res;

	if (_base.GetCount() <= 0)return res;
	if (_or.GetCount() <= 0)return res;

	for (unsigned long i = 0; i < _or.GetCount(); i++)
		res.AddSquare(MathSquare::Or(_base, _or.GetSquare(i)));

	return res;
}

MathSquare MathSquare::Or(const MathSquare& _base, const ChVec4& _or)
{
	MathSquare res;

	if (_base.GetCount() <= 0)return res;

	for (unsigned long i = 0; i < _base.GetCount(); i++)
		res.AddSquare(MathSquare::Or(_base.GetSquare(i), _or));

	return res;
}

MathSquare MathSquare::Sub(const MathSquare& _base, const MathSquare& _sub)
{
	MathSquare res;

	if (_base.GetCount() <= 0)return res;
	if (_sub.GetCount() <= 0)return res;

	for (unsigned long i = 0; i < _sub.GetCount(); i++)
		res.AddSquare(MathSquare::Sub(_base, _sub.GetSquare(i)));

	return res;
}

MathSquare MathSquare::Sub(const MathSquare& _base, const ChVec4& _sub)
{
	MathSquare res;

	if (_base.GetCount() <= 0)return res;

	for (unsigned long i = 0; i < _base.GetCount(); i++)
		res.AddSquare(MathSquare::Sub(_base.GetSquare(i), _sub));

	return res;
}

MathSquare MathSquare::And(const ChVec4& _base, const ChVec4& _and)
{
	MathSquare res;

	if ((_base.right - _base.left) <= 0|| (_base.top - _base.bottom) <= 0)return  res;
	if ((_and.right - _and.left) <= 0 || (_and.top - _and.bottom) <= 0)return  res;

	if (!_base.IsOverlaps(_and))return res;

	ChVec4 square = _base;
	square.SetOverlapsRect(_and);

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

	onSquare.SetOverlapsRect(_sub);

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

bool ChCpp::MathSquare::IsEmpty()const
{
	return squareList.empty();
}

size_t ChCpp::MathSquare::GetCount() const
{
	return squareList.size();
}

ChVec4 ChCpp::MathSquare::GetSquare(size_t _num)const
{
	if (_num >= GetCount())return ChVec4();
	return *squareList[_num];
}


void ChCpp::MathSquare::AddSquare(const ChVec2& _leftTop, const ChVec2& _rightTop, const ChVec2& _rightBottom, const ChVec2& _leftBottom, const unsigned long _cutCount)
{
	if (_leftTop.x - _rightTop.x <= 0.0f)return;
	if (_rightTop.y - _rightBottom.y <= 0.0f)return;
	if (_rightBottom.x - _leftBottom.x <= 0.0f)return;
	if (_leftBottom.y - _leftTop.y <= 0.0f)return;

	std::vector<ChVec3>verticalDirectionList;
	verticalDirectionList.resize(_cutCount + 2);

	std::vector<ChVec3>horizontalDirectionList;
	horizontalDirectionList.resize(verticalDirectionList.size());

	{
		ChVec2 direction[4];
		float length[4];

		direction[static_cast<unsigned char>(DirectionName::LeftTopToRightTop)] =
			_rightTop - _leftTop;
		length[static_cast<unsigned char>(DirectionName::LeftTopToRightTop)] = direction[static_cast<unsigned char>(DirectionName::LeftTopToRightTop)].GetLen();


		direction[static_cast<unsigned char>(DirectionName::RightTopTopRightBottom)] =
			_rightBottom - _rightTop;
		length[static_cast<unsigned char>(DirectionName::RightTopTopRightBottom)] = direction[static_cast<unsigned char>(DirectionName::RightTopTopRightBottom)].GetLen();


		direction[static_cast<unsigned char>(DirectionName::LeftBottomToRightBottom)] =
			_rightBottom - _leftBottom;
		length[static_cast<unsigned char>(DirectionName::LeftBottomToRightBottom)] = direction[static_cast<unsigned char>(DirectionName::LeftBottomToRightBottom)].GetLen();


		direction[static_cast<unsigned char>(DirectionName::LeftTopToLeftBottom)] =
			_leftBottom - _leftTop;
		length[static_cast<unsigned char>(DirectionName::LeftTopToLeftBottom)] = direction[static_cast<unsigned char>(DirectionName::LeftTopToLeftBottom)].GetLen();

		for (unsigned long i = 0; i < 4; i++)
		{
			direction[i].Normalize();
		}

		for (unsigned long i = 0; i < verticalDirectionList.size(); i++)
		{

		}
	}

	for (unsigned long w = 0; w < horizontalDirectionList.size() - 1; w++)
	{
		for (unsigned long h = 0; h < verticalDirectionList.size() - 1; h++)
		{

		}
	}
}

void ChCpp::MathSquare::Clear()
{
	squareList.clear();
}

void ChCpp::MathSquare::PushBack(const ChVec4& _pushSquare)
{
	ChPtr::Shared<ChVec4> square = ChPtr::Make_S<ChVec4>();

	*square = _pushSquare;
	squareList.push_back(square);
}