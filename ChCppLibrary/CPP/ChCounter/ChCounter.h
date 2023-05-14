#ifndef Ch_CPP_Counter_h
#define Ch_CPP_Counter_h


namespace ChCpp
{
	class Counter
	{
	public://Get Functions//

		inline long GetCount() { return count; }

	public://Update Function//

		//�m�F�������l������//
		virtual long Update(const std::function<bool()>& _addMethod, const std::function<bool()>& _subMethod);

	public://Other Function//

		//count�����Z�b�g����//
		inline void Reset()
		{
			count = 0;
		}

	private://Values//

		long count = 0;
	};
}

#endif