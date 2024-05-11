#ifndef Ch_CPP_Queue_h
#define Ch_CPP_Queue_h

namespace ChArray
{
	//FIFO//
	template<typename T,unsigned long MaxSize>
	class Queue
	{
	public://Get Function//

		inline unsigned long GetMaxSize() { return MaxSize; }

		inline unsigned long GetRegistCount() { return (inCount + MaxSize - outCount) % MaxSize; }

	public://Item Controll Function//

		inline void Push(T _item)
		{
			item[inCount % MaxSize] = res;
			inCount++
		}

		inline T Back()
		{
			T& res = item[outCount % MaxSize];
			outCount++;
			return res;
		}

	private:

		T item[MaxSize];
		unsigned long inCount = 0;
		unsigned long outCount = 0;
	};
}

#endif