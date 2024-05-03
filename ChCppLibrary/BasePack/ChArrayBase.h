#ifndef Ch_CPP_ArrayBase_h
#define Ch_CPP_ArrayBase_h

namespace ChArray
{
	template<typename T>
	class ArrayBase;

	template<typename T>
	class ArrayIterator
	{
	public:

		friend ArrayBase<T>;

	public://Operator Functions//

		ArrayIterator& operator = (const ArrayIterator& _it)
		{
			base = _it.base;
			value = _it.value;
			return *this;
		}

		ArrayIterator& operator++();

		ArrayIterator operator+(const unsigned long _num)const;

		ArrayIterator& operator+=(const unsigned long _num);

		T& operator->();

		bool operator==(const ArrayIterator& _it)
		{
			return _it.value == value && _it.base == base;
		}

		bool operator!=(const ArrayIterator& _it)
		{
			return _it.value != value || _it.base != base;
		}

	public://Constructor Destructor//

		ArrayIterator(ArrayBase<T>* _base)
		{
			base = _base;
		}

	private:

		ArrayBase<T>* base = nullptr;
		unsigned long value = 0;

	};

	template<typename T>
	class ArrayBase
	{
	public://Operator Functions//

		inline T& operator[](unsigned long _num)
		{
			return GetItem(_num);
		}

	public://begin end Functions//

		inline ArrayIterator<T> begin()
		{
			return ArrayIterator<T>(this, 0);
		}

		inline ArrayIterator<T> end()
		{
			ArrayIterator<T> res = ArrayIterator<T>(this,itemCount);

			return res;
		};

	public://Get Functions//

		virtual T& GetItem(unsigned long _num) = 0;

		inline unsigned long GetLength() { return itemCount; };

		inline unsigned long GetCount() { return itemCount; };

		inline unsigned long GetSize() { return itemCount; };

	protected://Get Functions//

		inline unsigned long GetItNum(const ArrayIterator<T>& _it)
		{
			return _it.value;
		}

	protected://Count Controll//

		inline void AddCount()
		{
			itemCount++; 
		}

		inline void SubCount()
		{
			if (itemCount <= 0)return;
			itemCount--;
		}

	private:

		unsigned long itemCount = 0;

	};

	template<typename T>
	ArrayIterator<T>& ArrayIterator<T>::operator++()
	{
		value++;
		if (value >= base->GetLength())value = base->GetLength();
		return *this;
	}

	template<typename T>
	ArrayIterator<T> ArrayIterator<T>::operator+(const unsigned long _num)const
	{
		ArrayIterator res = ArrayIterator(base,value);
		res.value += _num;
		if (res.value >= base->GetLength())res.value = base->GetLength();
		return res;
	}

	template<typename T>
	ArrayIterator<T>& ArrayIterator<T>::operator+=(const unsigned long _num)
	{
		*this = *this + _num;
		return *this;
	}

	template<typename T>
	T& ArrayIterator<T>::operator->()
	{
		return base->GetItem();
	}

}

#endif