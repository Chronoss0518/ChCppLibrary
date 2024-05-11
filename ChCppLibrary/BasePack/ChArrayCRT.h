#ifndef Ch_CPP_Array_CRT_h
#define Ch_CPP_Array_CRT_h

#include<stdlib.h>
#include"ChPtr.h"
#include"ChListArray.h"

template<typename T>
T& ChArray::ListArray<T>::InsertAdd(unsigned long _num)
{
	if (ChPtr::NullCheck(itemBegin))
	{
		itemBegin = new ListArrayItem<T>();

		ArrayBase<T>::AddCount();

		return *itemBegin;
	}

	unsigned long arrayCount = ArrayBase<T>::GetCount();

	unsigned long num = _num;

	if (num >= arrayCount)num = arrayCount;

	ListArrayItem<T>* nowItem = itemBegin;

	for (unsigned long i = 1; i < num; i++)
	{
		nowItem = nowItem->GetNext();
	}

	ListArrayItem<T>* res = new ListArrayItem<T>();

	ListArrayItem<T>* nextTmp = nowItem->GetNext();

	nowItem->SetNext(res);

	if (ChPtr::NotNullCheck(nextTmp))
	{
		res->SetNext(nextTmp);
	}

	ArrayBase<T>::AddCount();

	return *res;
}

template<typename T>
void ChArray::ListArray<T>::Remove(unsigned long _num)
{
	if (ChPtr::NullCheck(itemBegin))return;

	unsigned long arrayCount = ArrayBase<T>::GetCount() - 1;
	unsigned long num = _num;
	if (num >= arrayCount)num = arrayCount;

	if (num <= 0)
	{
		ListArrayItem<T>* tmpItem = itemBegin->GetNext();

		delete itemBegin;

		itemBegin = tmpItem;

		ArrayBase<T>::SubCount();
		return;
	}

	ListArrayItem<T>* nowItem = itemBegin;

	for (unsigned long i = 1; i < num; i++)
	{
		nowItem = nowItem->GetNext();
	}

	if (ChPtr::NullCheck(nowItem))return;

	ListArrayItem<T>* removeItem = nowItem->GetNext();

	if (ChPtr::NullCheck(removeItem))return;

	ListArrayItem<T>* removeNextItem = removeItem->GetNext();

	nowItem->SetNext(removeNextItem);

	delete removeItem;

	ArrayBase<T>::SubCount();
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

	ArrayBase<T>::SetCount(0);
}



#endif