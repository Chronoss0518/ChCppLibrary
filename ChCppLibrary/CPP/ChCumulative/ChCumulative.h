#ifndef Ch_CPP_Cumulative_h
#define Ch_CPP_Cumulative_h

#include"../ChCounter/ChCounter.h"

namespace ChCpp
{
	//�ݐϘa���s�����߂̃N���X//
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

		//�m�F�������l������//
		long long Update(CharaType _value)
		{
			if (add == _value)Add();
			else if (sub == _value)Sub();

			return GetCount();
		}

	private://Values//

		//count���グ��l//
		CharaType add;

		//count��������l//
		CharaType sub;

	};
}

#endif