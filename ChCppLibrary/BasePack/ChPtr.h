#ifndef Ch_CPP_Ptr_h
#define Ch_CPP_Ptr_h

#ifndef Ch_CPP_Std_h
#include"ChStd.h"
#endif

//ChLibraryで利用するポインタに対して利用する関数、変数群のまとまり//
namespace ChPtr
{

	template<typename T, class... _Types>
	T* Instantiate(_Types&&... _args);

	template<typename T>
	T* InstantiateArray(unsigned long _num);

	template<typename T>
	void Release(T*& _release);

	//クラスがNULLまたはnullptrかをチェックする関数//
	template<class C>
	static inline bool NullCheck(const C _class)
	{
		if (_class == NULL) return true;
		if (_class == nullptr)return true;
		return false;
	}

	//クラスがNULLとnullptrのどちらでもないかをチェックする関数//
	template<class C>
	static inline bool NotNullCheck(const C _class)
	{
		if (_class != NULL)
			if (_class != nullptr)return true;

		return false;
	}

}

#endif
