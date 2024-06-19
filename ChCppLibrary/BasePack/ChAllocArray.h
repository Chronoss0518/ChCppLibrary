#ifndef Ch_CPP_AllocArray_h
#define Ch_CPP_AllocArray_h

#include"ChValiableLengthArrayBase.h"

namespace ChArray
{
	template<typename T>
	class ListArray;

	//“®“I‚ÉˆêŠ‡‚Åƒƒ‚ƒŠ‚ğŠm•Û‚·‚é‰Â•Ï’·”z—ñ//
	template<typename T>
	class AllocArray :public VLArrayBase<T>
	{
	public:

		AllocArray& operator=(const AllocArray& _array)
		{
			Set(_array);
			return *this;
		}

		bool operator==(const AllocArray& _array)
		{
			return Is(_array);
		}

		bool operator!=(const AllocArray& _array)
		{
			return IsNot(_array);
		}

	public:

		AllocArray(){}

		AllocArray(const AllocArray& _array)
		{
			Set(_array);
		}

		~AllocArray() { Clear(); }

	public:

		void Set(const AllocArray& _array);

		bool Is(const AllocArray& _array)
		{
			return &_array == this;
		}

		bool IsNot(const AllocArray& _array)
		{
			return &_array != this;
		}

		bool IsNotValue(const AllocArray& _array)
		{
			if (ArrayBase<T>::GetCount() != ArrayBase<T>::GetCount(_array))return true;

			for (unsigned long i = 0; i < ArrayBase<T>::GetCount(); i++)
			{
				if (item[i] == _array.item[i])continue;
				return true;
			}

			return false;
		}

		bool IsValue(const AllocArray& _array)
		{
			return !IsNot(_array);
		}

	public:

		inline unsigned long GetLength()const { return ArrayBase<T>::GetLength(); };

		inline unsigned long GetCount() const { return ArrayBase<T>::GetCount(); };

		inline unsigned long GetSize()const { return ArrayBase<T>::GetSize(); };

		inline T& GetItem(unsigned long _num)override
		{
			unsigned long num = _num;
			if (GetCount() - 1 <= num)num = GetCount() - 1;
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

		void ReSize(unsigned long _newArraySize);

		ListArray<T> ToListArray();

	private:
		
		T* item = nullptr;

	};
}

#endif