#ifndef Ch_CPP_MappingArray_h
#define Ch_CPP_MappingArray_h

#include"ChPtr.h"
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
	public:

		MappingArray& operator=(const MappingArray& _array)
		{
			Set(_array);
			return *this;
		}

		bool operator==(const MappingArray& _array)
		{
			return Is(_array);
		}

		bool operator!=(const MappingArray& _array)
		{
			return IsNot(_array);
		}

	public://Operator Function//

		inline Value& operator[](Key _key)
		{
			return FindFromKey(_key).value;
		}

	public:

		MappingArray() {}

		MappingArray(const MappingArray& _array)
		{
			Set(_array);
		}

		~MappingArray()
		{
			Clear();
		}

	public:

		void Set(const MappingArray& _array);

		bool Is(const MappingArray& _array)
		{
			return &_array == this;
		}

		bool IsNot(const MappingArray& _array)
		{
			return &_array != this;
		}

		bool IsNotValue(const MappingArray& _array)
		{
			if (ArrayBase<MappingArrayPair<Key, Value>>::GetCount() != ArrayBase<MappingArrayPair<Key, Value>>::GetCount(_array))return true;

			for (unsigned long i = 0; i < ArrayBase<MappingArrayPair<Key, Value>>::GetCount(); i++)
			{
				if (base[i].key == _array.base[i].key)continue;
				if (base[i].value == _array.base[i].value)continue;
				return true;
			}

			return false;
		}

		bool IsValue(const MappingArray& _array)
		{
			return !IsNot(_array);
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