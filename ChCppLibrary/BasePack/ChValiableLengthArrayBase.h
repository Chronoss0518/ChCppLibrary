#ifndef Ch_CPP_VLABase_h
#define Ch_CPP_VLABase_h

#include"ChArrayBase.h"

namespace ChArray
{

	template<typename T>
	class VLArrayBase : public ArrayBase<T>
	{
	public://Other Functions//

		virtual void Push(const T& _pushItem) = 0;

		virtual T& Add() = 0;

		virtual void Insert(const T& _item,unsigned long _num) = 0;

		virtual T& InsertAdd(unsigned long _num) = 0;

		virtual void Remove(unsigned long _num) = 0;

		virtual ArrayIterator<T> Erase(const ArrayIterator<T>& _it) = 0;

		virtual void Pop() = 0;

		virtual void Clear() = 0;
	};

}

#endif