#ifndef Ch_CPP_Array_CRT_h
#define Ch_CPP_Array_CRT_h

#include<stdlib.h>
#include"ChPtr.h"
#include"ChListArray.h"

namespace ChArray
{

	template<typename T>
	T& ListArray<T>::InsertAdd(unsigned long _num)
	{
		unsigned long num = _num;
		if (num >= ArrayBase<T>::GetCount())num = ArrayBase<T>::GetCount();

		ListArrayItem<T>* nowItem = itemBegin;

		for (unsigned long i = 1; i < num; i++)
		{
			nowItem = nowItem->GetNext();
		}

		ListArrayItem<T>* res = new ListArrayItem<T>();

		nowItem->SetNext(res);

		ListArrayItem<T>* nextTmp = nowItem->GetNext();

		if (ChPtr::NotNullCheck(nextTmp))
		{
			nextTmp->SetNext(res);
		}

		ArrayBase<T>::AddCount();

		return *res;
	}

	template<typename T>
	void ListArray<T>::Remove(unsigned long _num)
	{
		unsigned long num = _num;
		if (num >= ArrayBase<T>::GetCount())num = ArrayBase<T>::GetCount();

		ListArrayItem<T>* nowItem = itemBegin;

		for (unsigned long i = 1; i < num; i++)
		{
			nowItem = nowItem->GetNext();
		}

		ListArrayItem<T>* removeItem = nowItem->GetNext();

		ListArrayItem<T>* removeNextItem = removeItem->GetNext();

		nowItem->SetNext(removeNextItem);

		delete removeItem;

		ArrayBase<T>::SubCount();

	}

	template<typename T>
	void ListArray<T>::Clear()
	{
		ListArrayItem<T>* removeNextItem = itemBegin;

		for (unsigned long i = 0; i < ArrayBase<T>::GetCount(); i++)
		{
			if (ChPtr::NullCheck(removeNextItem))return;
			removeNextItem = removeNextItem->GetNext();
			delete removeNextItem;
			ArrayBase<T>::SubCount();
		}
	}



}

#endif