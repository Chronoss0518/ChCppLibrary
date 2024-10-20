#ifndef Ch_CPP_Cumulative_h
#define Ch_CPP_Cumulative_h

#include"../ChCounter/ChCounter.h"

namespace ChCpp
{
	//累積和を行うためのクラス//
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
		long long Update(CharaType _value)
		{
			if (add == _value)Add();
			else if (sub == _value)Sub();

			return GetCount();
		}

	private://Values//

		//countを上げる値//
		CharaType add;

		//countを下げる値//
		CharaType sub;

	};
}

#endif