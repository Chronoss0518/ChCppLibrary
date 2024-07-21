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

#ifdef CRT

		//�m�F�������l������//
		long Update(CharaType _value);

#endif

	private://Base Update Function//

#ifdef CRT

		long Update(const std::function<bool()>& _addMethod, const std::function<bool()>& _subMethod)override;

#endif

	private://Values//

		//count���グ��l//
		CharaType add;

		//count��������l//
		CharaType sub;

	};
}

#ifdef CRT

//�m�F�������l������//
template<typename CharaType>
long ChCpp::Cumulative<CharaType>::Update(CharaType _value)
{
	return Update([&]()->bool {return _value == add; }, [&]()->bool {return _value == sub; });
}

template<typename CharaType>
long ChCpp::Cumulative<CharaType>::Update(const std::function<bool()>& _addMethod, const std::function<bool()>& _subMethod)
{
	return Counter::Update(_addMethod, _subMethod);
}

#endif

#endif