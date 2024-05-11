#ifndef Ch_CPP_FAllocArray_h
#define Ch_CPP_FAllocArray_h

#include"ChArrayBase.h"

namespace ChArray
{
	//This Array is Fixed Length Alloc //
	//‚±‚Ì”z—ñ‚ÍŒÅ’è’·‚ÌŠ„‚è“–‚Ä‚ğs‚¢‚Ü‚·//
	template<typename T>
	class FixedAllocArray : public ArrayBase<T>
	{
	public:

		FixedAllocArray(unsigned long _arraySize);

		~FixedAllocArray();

	public:

		inline T& GetItem(unsigned long _num)override
		{
			unsigned long num = _num;
			if (ArrayBase<T>::GetCount() - 1 <= num)num = ArrayBase<T>::GetCount() - 1;
			return *(item + num);
		}

	public://Other Function//

		void ReSize(unsigned long _newArraySize);

	private:

		T* item;

	};
}

#endif