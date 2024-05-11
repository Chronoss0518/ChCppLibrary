#ifndef Ch_CPP_ListArray_h
#define Ch_CPP_ListArray_h

#include"ChValiableLengthArrayBase.h"

namespace ChArray
{

	template<typename T>
	class ListArrayItem
	{
	public:

		T& operator->() { return item; }

		T& operator*() { return item; }

		operator T& () { return item; }

	public:

		inline void SetItem(T _item)
		{
			item = _item;
		}

		inline void SetNext(ListArrayItem<T>* _next)
		{
			next = _next;
		}

	public:

		inline T& GetItem()
		{
			return item;
		}

		inline ListArrayItem<T>* GetNext()
		{
			return next;
		}

	private:

		T item;
		ListArrayItem* next = nullptr;

	};

	//This Valiable Length Array is Use List Structure //
	//List構造を使用した可変長配列//
	template<typename T>
	class ListArray : public VLArrayBase<T>
	{
	public:

		~ListArray()
		{
			Clear();
		}

	public:

		inline T& GetItem(unsigned long _num)override
		{
			ListArrayItem<T>* res = itemBegin;
			ListArrayItem<T>* test = nullptr;
			for (unsigned long i = 0; i < _num; i++)
			{
				test = res->GetNext();
				if (test == nullptr)return *res;
				res = test;
			}

			return *res;
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
			Remove(ArrayBase<T>::GetLength());
		}

		void Clear()override;

	private:

		ListArrayItem<T>* itemBegin;

	};

}


#endif