#ifndef Ch_CPP_Queue_h
#define Ch_CPP_Queue_h

namespace ChArray
{
	//FIFO//
	template<typename T,unsigned long MaxSize>
	class Queue
	{
	public:

		Queue& operator=(const Queue& _array)
		{
			Set(_array);
			return *this;
		}

		bool operator==(const Queue& _array)
		{
			return Is(_array);
		}

		bool operator!=(const Queue& _array)
		{
			return IsNot(_array);
		}

	public:

		Queue() {}

		Queue(const Queue& _array)
		{
			Set(_array);
		}

		~Queue()
		{
			Clear();
		}

	public:

		void Set(const Queue& _array)
		{
			if (Is(_array))return;
			for (unsigned long i = 0; i < Array; i++)
			{
				item[i] = _array.item[i];
			}
			inCount = _array.inCount;
			outCount = _array.outCount;
		}

		bool Is(const Queue& _array)
		{
			return &_array == this;
		}

		bool IsNot(const Queue& _array)
		{
			return &_array != this;
		}

		bool IsNotValue(const Queue& _array)
		{
			if (inCount != _array.inCount)return true;
			if (outCount != _array.outCount)return true;

			unsigned long tmpValue = 0;
			for (unsigned long i = outCount; i < inCount + outCount; i++)
			{
				tmpValue = i % MaxSize;
				if (item[tmpValue] == _array.item[tmpValue])continue;
				return true;
			}

			return false;
		}

		bool IsValue(const Queue& _array)
		{
			return !IsNot(_array);
		}

	public://Get Function//

		inline unsigned long GetMaxSize() const { return MaxSize; }

		inline unsigned long GetRegistCount()const { return (inCount + MaxSize - outCount) % MaxSize; }

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