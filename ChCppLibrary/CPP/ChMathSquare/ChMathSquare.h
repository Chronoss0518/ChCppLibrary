#ifndef Ch_Cpp_MSquare_h
#define Ch_Cpp_MSquare_h

#ifdef CRT

#include<vector>

#endif

#include"../../BasePack/ChMath3D.h"

namespace ChCpp
{

	class MathSquare
	{
	public:

		struct MathSquareCRT
		{
#ifdef CRT
			std::vector<ChPtr::Shared<ChVec4>> squareList;
#endif
		};

	public://Operatore Functions//

		MathSquare& operator = (const MathSquare& _mathSquare);

	public://Operatore Functions//

		MathSquare() { CRTInit(); }

		MathSquare(const MathSquare& _mathSquare)
		{
			CRTInit();
			SetSquare(_mathSquare);
		}

		MathSquare(const ChVec4& _square)
		{
			CRTInit();
			SetSquare(_square);
		}

#ifdef CRT
		MathSquare(const std::vector<ChPtr::Shared<ChVec4>>& _squareList)
		{
			CRTInit();
			SetSquare(_squareList);
		}
#endif

		MathSquare(const float _left, const float _top, const float _right, const float _bottom)
		{
			CRTInit();
			SetSquare(ChVec4(_left, _top, _right, _bottom));
		}

		MathSquare(const ChVec2& _leftTop, const ChVec2& _rightTop, const ChVec2& _rightBottom, const ChVec2& _leftBottom, const unsigned long _cutCount = 1)
		{
			CRTInit();
			SetSquare(_leftTop, _rightTop, _rightBottom, _leftBottom, _cutCount);
		}

		~MathSquare() { CRTRelease(); }

	public:

		void CRTInit();

		void CRTRelease();

	public://Set Functions//

		void SetSquare(const ChVec4& _square);

#ifdef CRT
		void SetSquare(const std::vector<ChPtr::Shared<ChVec4>>& _square)
		{
			if (&_square == &value->squareList)return;
			if (!value->squareList.empty())value->squareList.clear();
			for (auto&& quare_it : _square)
			{
				AddSquare(*quare_it);
			}
		}
#endif

		void SetSquare(const MathSquare& _square);

		void SetSquare(const ChVec2& _leftTop, const ChVec2& _rightTop, const ChVec2& _rightBottom, const ChVec2& _leftBottom, const unsigned long _cutCount = 1);

	public://Get Functions//

#ifdef CRT
		std::vector<ChPtr::Shared<ChVec4>> GetSquare() const { return value->squareList; }
#endif

		ChVec4 GetSquare(unsigned long _num)const;

		ChVec4 GetFirstSquare() const;

		ChVec4 GetLastSquare() const;

		unsigned long GetCount() const;

	public://Add Function//

		void AddSquare(const ChVec4& _square);

		void AddSquare(const MathSquare& _square);

		void AddSquare(const ChVec2& _leftTop, const ChVec2& _rightTop, const ChVec2& _rightBottom, const ChVec2& _leftBottom,const unsigned long _cutCount = 1);

	public:

		bool IsEmpty()const;

	public://Math Functions//

		void And(const MathSquare& _and);

		void And(const ChVec4& _and);

		void Or(const MathSquare& _or);

		void Or(const ChVec4& _or);

		void Sub(const MathSquare& _sub);

		void Sub(const ChVec4& _sub);

	public://Math Static Functions//

		static MathSquare And(const MathSquare& _base, const MathSquare& _and);

		static MathSquare And(const MathSquare& _base, const ChVec4& _and);

		static MathSquare Or(const MathSquare& _base, const MathSquare& _or);

		static MathSquare Or(const MathSquare& _base, const ChVec4& _or);

		static MathSquare Sub(const MathSquare& _base, const MathSquare& _sub);

		static MathSquare Sub(const MathSquare& _base, const ChVec4& _sub);

		static MathSquare And(const ChVec4& _base, const ChVec4& _and);

		static MathSquare Or(const ChVec4& _base, const ChVec4& _or);

		static MathSquare Sub(const ChVec4& _base, const ChVec4& _sub);


	protected://Other Functions//

		void Clear();

		void PushBack(const ChVec4& _pushSquare);

	private:

		enum class DirectionName :unsigned char
		{
			LeftTopToRightTop,
			RightTopTopRightBottom,
			LeftBottomToRightBottom,
			LeftTopToLeftBottom,
		};

		MathSquareCRT* value = nullptr;

	};
}

#ifdef CRT

void ChCpp::MathSquare::CRTInit()
{
	value = new MathSquareCRT();
}

void ChCpp::MathSquare::CRTRelease()
{
	delete value;
}

bool ChCpp::MathSquare::IsEmpty()const
{
	return value->squareList.empty();
}

unsigned long ChCpp::MathSquare::GetCount() const
{
	return value->squareList.size();
}

ChVec4 ChCpp::MathSquare::GetSquare(unsigned long _num)const
{
	if (_num >= GetCount())return ChVec4();
	return *value->squareList[_num];
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

		direction[ChStd::EnumCast(DirectionName::LeftTopToRightTop)] =
			_rightTop - _leftTop;
		length[ChStd::EnumCast(DirectionName::LeftTopToRightTop)] = direction[ChStd::EnumCast(DirectionName::LeftTopToRightTop)].GetLen();


		direction[ChStd::EnumCast(DirectionName::RightTopTopRightBottom)] =
			_rightBottom - _rightTop;
		length[ChStd::EnumCast(DirectionName::RightTopTopRightBottom)] = direction[ChStd::EnumCast(DirectionName::RightTopTopRightBottom)].GetLen();


		direction[ChStd::EnumCast(DirectionName::LeftBottomToRightBottom)] =
			_rightBottom - _leftBottom;
		length[ChStd::EnumCast(DirectionName::LeftBottomToRightBottom)] = direction[ChStd::EnumCast(DirectionName::LeftBottomToRightBottom)].GetLen();


		direction[ChStd::EnumCast(DirectionName::LeftTopToLeftBottom)] =
			_leftBottom - _leftTop;
		length[ChStd::EnumCast(DirectionName::LeftTopToLeftBottom)] = direction[ChStd::EnumCast(DirectionName::LeftTopToLeftBottom)].GetLen();

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
	if (value->squareList.empty())return;
	value->squareList.clear();
}

void ChCpp::MathSquare::PushBack(const ChVec4& _pushSquare)
{
	auto square = ChPtr::Make_S<ChVec4>();
	*square = _pushSquare;
	value->squareList.push_back(square);
}

#endif

#endif