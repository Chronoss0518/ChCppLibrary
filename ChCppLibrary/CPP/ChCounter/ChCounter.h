#ifndef Ch_CPP_Counter_h
#define Ch_CPP_Counter_h


namespace ChCpp
{
	class Counter
	{
	public://Get Functions//

		inline long GetCount() { return count; }

	public://Update Function//

		//確認したい値を入れる//
		virtual long Update(const std::function<bool()>& _addMethod, const std::function<bool()>& _subMethod);

	public://Other Function//

		//countをリセットする//
		inline void Reset()
		{
			count = 0;
		}

	private://Values//

		long count = 0;
	};
}

#endif