#ifndef Ch_CPP_Stack_h
#define Ch_CPP_Stack_h

namespace ChArray
{
	//LIFO//
	template<typename T, unsigned long MaxSize>
	class Stack
	{
	public:

		Stack& operator=(const Stack& _array)
		{
			Set(_array);
			return *this;
		}

		bool operator==(const Stack& _array)
		{
			return Is(_array);
		}

		bool operator!=(const Stack& _array)
		{
			return IsNot(_array);
		}

	public:

		Stack() {}

		Stack(const Stack& _array)
		{
			if (this == &_array)return;
			Set(_array);
		}

		~Stack()
		{
			Clear();
		}

	public:

		void Set(const Stack& _array)
		{
			if (Is(_array))return;
			for (unsigned long i = 0; i < Array; i++)
			{
				item[i] = _array.item[i];
			}
			count = _array.count;
		}

		bool Is(const Stack& _array)
		{
			return &_array == this;
		}

		bool IsNot(const Stack& _array)
		{
			return &_array != this;
		}

		bool IsNotValue(const Stack& _array)
		{
			if (count != _array.count)return true;

			for (unsigned long i = 0; i < count; i++)
			{
				if (item[i] == _array.item[i])continue;
				return true;
			}

			return false;
		}

		bool IsValue(const Stack& _array)
		{
			return !IsNot(_array);
		}

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