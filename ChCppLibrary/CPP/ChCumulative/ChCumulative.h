#ifndef Ch_CPP_Cumulative_h
#define Ch_CPP_Cumulative_h


#include"../ChCounter/ChCounter.h"

namespace ChCpp
{
	template<typename CharaType>
	class Cumulative:public Counter
	{
	public://Constructor Destructor//

		inline Cumulative(const CharaType _add, const CharaType _sub)
		{
			SetAddCharactor(_add);
			SetSubCharactor(_sub);
		}

	public://Set Functions//

		inline void SetAddCharactor(const CharaType _add)
		{
			if (sub == _add)return;
			add = _add;
		}

		inline void SetSubCharactor(const CharaType _sub)
		{
			if (add == _sub)return;
			sub = _sub;
		}

	public://Get Functions//

		inline CharaType GetAddCharactor() { return add; }

		inline CharaType GetSubCharactor() { return sub; }

	public://Update Function//

		//確認したい値を入れる//
		long Update(CharaType _value)
		{
			return Update([&]()->bool {return _value == add; }, [&]()->bool {return _value == sub; });
		}

	private://Base Update Function//

		long Update(const std::function<bool()>& _addMethod, const std::function<bool()>& _subMethod)override
		{
			return Counter::Update(_addMethod, _subMethod);
		}

	private://Values//

		//countを上げる値//
		CharaType add;

		//countを下げる値//
		CharaType sub;

	};
}

#endif