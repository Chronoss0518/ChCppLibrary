#ifndef Ch_CPP_Array_CRT_h
#define Ch_CPP_Array_CRT_h

#include"ChListArray.h"
#include"ChFixedArray.h"
#include"ChAllocArray.h"
#include"ChMappingArray.h"

#include"ChPtrCRT.h"

template<class T>
void ChArray::ListArray<T>::Set(const ListArray<T>& _array)
{
	if (Is(_array))return;
	Clear();
	for (unsigned long i = 0;i< ArrayBase<T>::GetCount(_array);i++)
	{
		Push(_array.item[i]);
	}
}

template<typename T>
T& ChArray::ListArray<T>::InsertAdd(unsigned long _num)
{
	unsigned long arrayCount = ArrayBase<T>::GetCount();

	unsigned long num = _num;

	if (num >= arrayCount)num = arrayCount;

	ArrayBase<T>::AddCount();

	ListArrayItem<T>* res = new ListArrayItem<T>();

	ListArrayItem<T>* nowItem = itemBegin;

	if (num <= 0)
	{
		nowItem = itemBegin;
		itemBegin = res;
		itemBegin->SetNext(nowItem);

		return *res;
	}

	for (unsigned long i = 1; i < num; i++)
	{
		nowItem = nowItem->GetNext();
	}

	ListArrayItem<T>* nextTmp = nowItem->GetNext();

	nowItem->SetNext(res);

	if (ChPtr::NotNullCheck(nextTmp))
	{
		res->SetNext(nextTmp);
	}

	return *res;
}

template<typename T>
void ChArray::ListArray<T>::Remove(unsigned long _num)
{
	if (ChPtr::NullCheck(itemBegin))return;

	unsigned long arrayCount = ArrayBase<T>::GetCount() - 1;
	unsigned long num = _num;
	if (num >= arrayCount)num = arrayCount;

	ArrayBase<T>::SubCount();

	if (num <= 0)
	{
		ListArrayItem<T>* tmpItem = itemBegin->GetNext();

		delete itemBegin;

		itemBegin = tmpItem;

		return;
	}

	ListArrayItem<T>* nowItem = itemBegin;
	ListArrayItem<T>* beforeItem = nullptr;

	for (unsigned long i = 0; i < num; i++)
	{
		beforeItem = nowItem;
		nowItem = nowItem->GetNext();
	}
	
	if(ChPtr::NotNullCheck(beforeItem))beforeItem->SetNext(nowItem->GetNext());

	delete nowItem;

}

template<typename T>
void ChArray::ListArray<T>::Clear()
{
	ListArrayItem<T>* removeNextItem = itemBegin;
	ListArrayItem<T>* tmp = nullptr;

	for (unsigned long i = 0; i < ArrayBase<T>::GetCount(); i++)
	{
		if (ChPtr::NullCheck(removeNextItem))return;
		tmp = removeNextItem->GetNext();
		delete removeNextItem;
		removeNextItem = tmp;
	}

	itemBegin = nullptr;

	ArrayBase<T>::SetCount(0);
}

template<typename T>
ChArray::AllocArray<T> ChArray::ListArray <T>::ToAllocArray()
{
	AllocArray<T>res;
	unsigned long count = ArrayBase<T>::GetCount();
	ListArrayItem<T>* nowItem = itemBegin;

	for (unsigned long i = 0; i < count; i++)
	{
		res.Push(nowItem->GetItem());
		nowItem = nowItem->GetNext();
	}

	return res;
}




template<class T>
void ChArray::AllocArray<T>::Set(const AllocArray& _array)
{
	if (Is(_array))return;
	Clear();
	for (unsigned long i = 0; i < ArrayBase<T>::GetCount(_array); i++)
	{
		Push(_array.item[i]);
	}
}

template<typename T>
T& ChArray::AllocArray<T>::InsertAdd(unsigned long _num)
{
	unsigned long count = ArrayBase<T>::GetCount();

	T* tmp = new T[count + 1];

	bool findFlg  = false;
	T* res = nullptr;

	for (unsigned long i = 0; i < count; i++)
	{
		if (i == _num)
		{
			findFlg = true;
			res = (tmp + i);
			continue;
		}
		tmp[findFlg ? (i + 1) : i] = item[i];
	}

	if (!findFlg)
	{
		res = (tmp + count);
	}
	if(ChPtr::NotNullCheck(item))delete[] item;
	item = tmp;

	ArrayBase<T>::AddCount();

	return *res;
}

template<typename T>
void ChArray::AllocArray<T>::Remove(unsigned long _num)
{
	if (ArrayBase<T>::IsEmpty())return;

	unsigned long count = ArrayBase<T>::GetCount();

	if (count <= 1)
	{
		delete[] item;
		ArrayBase<T>::SubCount();

		return;
	}

	T* tmp = new T[count - 1];

	bool findFlg;
	T* res = nullptr;

	for (unsigned long i = 0; i < count; i++)
	{
		if (i == _num)
		{
			findFlg = true;
			continue;
		}
		tmp[i] = item[findFlg ? (i + 1) : i];
	}

	delete[] item;
	item = tmp;

	ArrayBase<T>::SubCount();

	return;
}

template<typename T>
void ChArray::AllocArray<T>::Clear()
{
	if (ChPtr::NotNullCheck(item))
	{
		delete[] item;
		item = nullptr;
	}

	ArrayBase<T>::SetCount(0);
}

template<typename T>
void ChArray::AllocArray<T>::ReSize(unsigned long _newArraySize)
{
	unsigned long loopCount = ArrayBase<T>::GetCount();

	if (_newArraySize == loopCount)return;

	T* tmpArray = new T[_newArraySize];

	if (loopCount > _newArraySize)loopCount = _newArraySize;

	for (unsigned long i = 0; i < loopCount; i++)
	{
		*(tmpArray + i) = *(item + i);
	}

	delete[] item;
	item = tmpArray;

	ArrayBase<T>::SetCount(_newArraySize);
}

template<typename T>
ChArray::ListArray<T> ChArray::AllocArray <T>::ToListArray()
{
	ListArray<T>res;
	unsigned long count = ArrayBase<T>::GetCount();

	for (unsigned long i = 0; i < count; i++)
	{
		res.Push(*(item + i));
	}

	return res;
}

template<typename Key, typename Value>
void ChArray::MappingArray<Key, Value>::Set(const MappingArray& _array)
{
	if (Is(_array))return;
	Clear();
	for (unsigned long i = 0; i < ArrayBase<MappingArrayPair<Key, Value>>::GetCount(_array.base); i++)
	{
		auto&& pair = FindFromKey(_array[i].base.key);
		pair.value = base.value;
	}
}

template<typename Key, typename Value>
ChArray::MappingArrayPair<Key, Value>* ChArray::MappingArray<Key, Value>::FindKeyMethod(unsigned long& _outNum, Key _key)
{
	_outNum = 0;
	ChArray::MappingArrayPair<Key, Value>* res = nullptr;

	for (auto&& it : base)
	{
		if (it.key == _key) 
		{
			res = &it;
			break;
		}

		if (it.key >= _key)break;
		_outNum++;
	}

	return res;

}

#endif