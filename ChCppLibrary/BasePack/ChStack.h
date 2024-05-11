#ifndef Ch_CPP_Stack_h
#define Ch_CPP_Stack_h

namespace ChArray
{
	//LIFO//
	template<typename T, unsigned long MaxSize>
	class Stack
	{
	public://Get Function//

		inline unsigned long GetMaxSize() { return MaxSize; }

		inline unsigned long GetRegistCount() { return count; }

	public://Item Controll Function//

		inline void Push(T _item)
		{
			if (count >= MaxSize - 1)return;
			item[count] = _item;
			count++;
		}

		inline T Back()
		{
			T& res = item[count];
			if (count > 0)count--;
			return res;
		}

	private:

		T item[MaxSize];
		unsigned long count = 0;
	};
}

#endif