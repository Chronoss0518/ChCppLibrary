

#ifndef Ch_CPP_CP_CNGet_h
#define Ch_CPP_CP_CNGet_h

namespace ChCp
{
	//継承して利用する//
	//自身のクラスネーム及びクラス自身の型を取得できる//
	template<class T>
	class ClassNameGetter
	{
	public://Get Functions//
		inline char* GetName()
		{
			char* tmp = nullptr;

#ifdef __GNUC__
			tmp = typeid(T).name();
#else
			tmp = typeid(T).raw_name();
#endif
			return tmp;
		}

	protected:

		ClassNameGetter() {}

	};

	template<class T>
	using CNGetter = ClassNameGetter<T>;

}

#endif
