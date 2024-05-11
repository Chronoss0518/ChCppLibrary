#ifndef Ch_CPP_AllocArray_h
#define Ch_CPP_AllocArray_h

#include"ChValiableLengthArrayBase.h"

namespace ChArray
{
	template<typename T>
	class AllocArray :public VLArrayBase<T>
	{
	public:

		~AllocArray() { Clear(); }

	public:

		inline T& GetItem(unsigned long _num)override
		{
			unsigned long num = _num;
			if (ArrayBase<T>::GetCount() - 1 <= num)num = ArrayBase<T>::GetCount() - 1;
			return *(item + num);
		}

	public:

		void Push(const T& _pushItem)override
		{
			auto&& res = InsertAdd(ArrayBase<T>::GetLength());

			res = _pushItem;
		}

		T& Add()override
		{
			return InsertAdd(ArrayBase<T>::GetLength());
		}

		void Insert(const T& _item, unsigned long _num)override
		{
			auto&& value = InsertAdd(_num);
			value = _item;
		}

		T& InsertAdd(unsigned long _num)override;

		void Remove(unsigned long _num)override;

		ArrayIterator<T> Erase(const ArrayIterator<T>& _it)override
		{
			Remove(ArrayBase<T>::GetItNum(_it));
			return ArrayIterator<T>(this, ArrayBase<T>::GetItNum(_it) - 1);
		}

		void Pop()override
		{
			Remove(ArrayBase<T>::GetCount());
		}

		void Clear()override;

	private:
		
		T* item;

	};
}

#endif