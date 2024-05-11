#ifndef Ch_CPP_Array_CRT_h
#define Ch_CPP_Array_CRT_h

#include<stdlib.h>
#include"ChPtr.h"
#include"ChListArray.h"
#include"ChFixedArray.h"

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

	ArrayBase<T>::SetCount(0);
}


#endif