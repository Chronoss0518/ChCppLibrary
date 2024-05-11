#ifndef Ch_CPP_FixedArray_h
#define Ch_CPP_FixedArray_h

#include"ChArrayBase.h"

namespace ChArray
{
	//Normal Fixed Length Array//
	//’Êí‚ÌŒÅ’è’·”z—ñ//
	template<typename T,unsigned long Array>
	class FixedArray : public ArrayBase<T>
	{
	public:

		inline FixedArray()
		{
			ArrayBase<T>::SetCount(Array);
		}

		inline ~FixedArray()
		{
			ArrayBase<T>::SetCount(0);
		}

	public:

		inline T& GetItem(unsigned long _num)override
		{
			unsigned long num = _num;
			if (Array - 1<= num)num = Array - 1;
			return item[num];
		}

	private:

		T item[Array];

	};
}

#endif