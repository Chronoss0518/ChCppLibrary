#ifndef Ch_Cpp_MSquare_h
#define Ch_Cpp_MSquare_h

namespace ChCpp
{

	class MathSquare
	{
	public://Operatore Functions//

		MathSquare& operator = (const MathSquare& _mathSquare);

	public://Operatore Functions//

		MathSquare(){}

		MathSquare(const MathSquare& _mathSquare) { SetSquare(_mathSquare); }

		MathSquare(const ChVec4& _square) { SetSquare(_square); }

		MathSquare(const std::vector<ChPtr::Shared<ChVec4>>& _squareList) { SetSquare(_squareList); }

		MathSquare(const float _left, const float _top, const float _right, const float _bottom)
		{
			SetSquare(ChVec4(_left, _top, _right, _bottom));
		}

		MathSquare(const ChVec2& _leftTop, const ChVec2& _rightTop, const ChVec2& _rightBottom, const ChVec2& _leftBottom, const unsigned long _cutCount = 1)
		{
			SetSquare(_leftTop, _rightTop, _rightBottom, _leftBottom, _cutCount);
		}

	public://Set Functions//

		void SetSquare(const ChVec4& _square);

		void SetSquare(const std::vector<ChPtr::Shared<ChVec4>>& _square);

		void SetSquare(const MathSquare& _square);

		void SetSquare(const ChVec2& _leftTop, const ChVec2& _rightTop, const ChVec2& _rightBottom, const ChVec2& _leftBottom, const unsigned long _cutCount = 1);

	public://Get Functions//

		inline std::vector<ChPtr::Shared<ChVec4>> GetSquare() const { return squareList; }

		ChVec4 GetFirstSquare() const;

		ChVec4 GetLastSquare() const;

		inline unsigned long GetCount() const { return squareList.size(); }

	public://Add Function//

		void AddSquare(const ChVec4& _square);

		void AddSquare(const MathSquare& _square);

		void AddSquare(const ChVec2& _leftTop, const ChVec2& _rightTop, const ChVec2& _rightBottom, const ChVec2& _leftBottom,const unsigned long _cutCount = 1);

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

	private:

		enum class DirectionName :unsigned char
		{
			LeftTopToRightTop,
			RightTopTopRightBottom,
			LeftBottomToRightBottom,
			LeftTopToLeftBottom,
		};

		std::vector<ChPtr::Shared<ChVec4>> squareList;

	};
}

#endif