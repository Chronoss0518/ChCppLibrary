#ifndef Ch_CPP_MappingArray_h
#define Ch_CPP_MappingArray_h

#include"ChListArray.h"

namespace ChArray
{

	template<typename Key, typename Value>
	class MappingArray;

	template<typename Key, typename Value>
	struct MappingArrayPair
	{
		Key key;

		Value value;
	};

	template<typename Key,typename Value>
	class MappingArray: public ArrayBase<MappingArrayPair<Key,Value>>
	{
	public://Operator Function//

		inline Value& operator[](Key _key)
		{
			return FindFromKey(_key).value;
		}

	public:

		~MappingArray()
		{
			base.Clear();
		}

	public://Get Function//

		inline MappingArrayPair<Key, Value>& GetItem(unsigned long _num)override
		{
			unsigned long num = _num;
			if (ArrayBase<MappingArrayPair<Key, Value>>::GetCount() - 1 <= num)num = ArrayBase<MappingArrayPair<Key, Value>>::GetCount() - 1;
			unsigned long startNum = 0;
			return base[_num];
		}

	public://Find Function//

		MappingArrayPair<Key, Value>& FindFromKey(Key _key)
		{

			unsigned long outNum = 0;
			auto pair = FindKeyMethod(outNum, _key);
			if (ChPtr::NullCheck(pair))
			{
				auto&& res = base.InsertAdd(outNum);
				res.key = _key;
				ArrayBase<MappingArrayPair<Key, Value>>::AddCount();

				return res;
			}

			return *pair;
		}

		void EraseFromKey(Key _key)
		{
			unsigned long outNum = 0;
			auto pair = FindKeyMethod(outNum, _key);

			if (ChPtr::NullCheck(pair))return;

			base.Remove(outNum);

		}

	private://Find Function//

		MappingArrayPair<Key, Value>* FindKeyMethod(unsigned long& _outNum, Key _key);

	public://Is Function//

		bool IsFindKey(Key _key)
		{
			unsigned long outNum = 0;
			auto&& pair = FindKeyMethod(outNum, _key);
			return ChPtr::NotNullCheck(pair);
		}

	public://Other Function//

		inline void Clear()
		{
			base.Clear();
			ArrayBase<MappingArrayPair<Key, Value>>::SetCount(0);
		}

	private:

		ListArray<MappingArrayPair<Key, Value>>base;
	};
}

#endif