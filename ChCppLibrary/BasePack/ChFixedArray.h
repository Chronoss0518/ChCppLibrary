#ifndef Ch_CPP_FixedArray_h
#define Ch_CPP_FixedArray_h

#include"ChArrayBase.h"

namespace ChArray
{
	//Normal Fixed Length Array//
	//í èÌÇÃå≈íËí∑îzóÒ//
	template<typename T,unsigned long Array>
	class FixedArray : public ArrayBase<T>
	{
	public:

		FixedArray& operator=(const FixedArray& _array)
		{
			Set(_array);
			return *this;
		}

		bool operator==(const FixedArray& _array)
		{
			return Is(_array);
		}

		bool operator!=(const FixedArray& _array)
		{
			return IsNot(_array);
		}

	public:

		inline FixedArray()
		{
			ArrayBase<T>::SetCount(Array);
		}

		FixedArray(const FixedArray& _array)
		{
			if (this == &_array)return;
			Set(_array);
		}

		inline ~FixedArray()
		{
			ArrayBase<T>::SetCount(0);
		}

	public:

		void Set(const FixedArray& _array)
		{
			if (Is(_array))return;
			for (unsigned long i = 0; i < Array; i++)
			{
				item[i] = _array.item[i];
			}
		}

		bool Is(const FixedArray& _array)
		{
			return &_array == this;
		}

		bool IsNot(const FixedArray& _array)
		{
			return &_array != this;
		}

		bool IsNotValue(const FixedArray& _array)
		{
			if (GetCount() != _array.GetCount())return true;

			for (unsigned long i = 0; i < ArrayBase<T>::GetCount(); i++)
			{
				if (item[i] == _array.item[i])continue;
				return true;
			}

			return false;
		}

		bool IsValue(const FixedArray& _array)
		{
			return !IsNot(_array);
		}

	public:

		inline T& GetItem(unsigned long _num)override
		{
			unsigned long num = _num;
			if (Array - 1<= num)num = Array - 1;
			return item[num];
		}

		inline unsigned long GetLength()const { return ArrayBase<T>::GetLength(); };

		inline unsigned long GetCount()const { return ArrayBase<T>::GetCount(); };

		inline unsigned long GetSize()const { return ArrayBase<T>::GetSize(); };

	private:

		T item[Array];

	};
}

#endif