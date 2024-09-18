#ifndef Ch_CPP_Counter_h
#define Ch_CPP_Counter_h

#ifdef CRT

#include<functional>

#endif

namespace ChCpp
{
	class Counter
	{
	public://Get Functions//

		inline long GetCount() { return count; }

	public://Update Function//

#ifdef CRT

		//確認したい値を入れる//
		virtual long Update(const std::function<bool()>& _addMethod, const std::function<bool()>& _subMethod);

#endif

	public://Other Function//

		//countをリセットする//
		inline void Reset()
		{
			count = 0;
		}

	private://Values//

		long count = 0;
	};
}

#ifdef CRT

long ChCpp::Counter::Update(const std::function<bool()>& _addMethod, const std::function<bool()>& _subMethod)
{
	count = (_addMethod && _addMethod()) ? count + 1 : (_subMethod && _subMethod()) ? count - 1 : count;
	return count;
}

#endif

#endif