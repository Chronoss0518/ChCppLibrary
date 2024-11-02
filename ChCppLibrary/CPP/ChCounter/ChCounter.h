#ifndef Ch_CPP_Counter_h
#define Ch_CPP_Counter_h

namespace ChCpp
{
	class Counter
	{
	public://Get Functions//

		inline long long GetCount() { return count; }

	public://Update Function//

		void Add() { count++; }

		void Sub() { count--; }

	public://Other Function//

		//count‚ðƒŠƒZƒbƒg‚·‚é//
		inline void Reset()
		{
			count = 0;
		}

	private://Values//

		long long count = 0;
	};
}

#endif