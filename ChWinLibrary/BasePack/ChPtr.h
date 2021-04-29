#ifndef Ch_CPP_Ptr_h
#define Ch_CPP_Ptr_h

#ifndef MEMORY_
#include<memory>
#endif

#ifndef Ch_CPP_Std_h
#include"ChStd.h"
#endif

//ChLibraryで利用するポインタに対して利用する関数、変数群のまとまり//
namespace ChPtr
{

	//SharedPtrの簡略版//
	template<class T>
	using Shared = std::shared_ptr<T>;

	//UniquePtrの簡略版//
	template<class T>
	using Unique = std::unique_ptr<T>;

	//WeakPtrの簡略版//
	template<class T>
	using Weak = std::weak_ptr<T>;

	//SharedPtr用ダウンキャスト//
	template<class C, class C2>
	static inline Shared<C> SharedSafeCast(Shared<C2> _sPtr)
	{
		return std::dynamic_pointer_cast<C, C2>(_sPtr);
	}

	//*Ptr用ダウンキャスト//
	template<class C, class C2>
	static inline C* SafeCast(C2*_ptr)
	{
		return dynamic_cast<C*>(_ptr);
	}

	//クラスがNULLまたはnullptrかをチェックする関数//
	template<class C>
	static inline auto NullCheck(const C _class)->typename
		std::enable_if<std::is_pointer<C>::value, ChStd::Bool>::type
	{
		if (_class == NULL) return true;
		if (_class == nullptr)return true;
		return false;
	}

	//クラスがNULLとnullptrのどちらでもないかをチェックする関数//
	template<class C>
	static inline auto NotNullCheck(const C _class)->typename
		std::enable_if<std::is_pointer<C>::value, ChStd::Bool>::type
	{
		if (_class != NULL)
		{
			if (_class != nullptr)return true;
		}

		return false;
	}

	//make_sharedを短縮するための関数//
	template<class T, class... _Types>
	static inline Shared<T> Make_S(_Types&&... _args)
	{
		return std::make_shared<T>(_args...);
	}

	//make_uniqueを短縮するための関数//
	template<class T, class... _Types>
	static inline Unique<T> Make_U(_Types&&... _args)
	{
		return std::make_unique<T>(_args...);
	}

	//move_ptrを短縮するための関数//
	template<class T>
	static inline T Move(T _obj)
	{
		return std::move<T>(_obj);
	}

	///////////////////////////////////////////////////////////////////////////////////////

	template<class T>
	class CPtr
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//Operator//

		inline T& operator *()
		{
			return *instance;
		}

		inline T* const operator ->()
		{
			return instance;
		}

		inline T const * const operator ->()const
		{
			return instance;
		}

		inline operator bool()const
		{
			return ChPtr::NotNullCheck(instance);
		}

		template<class CC>
		inline CPtr<typename std::enable_if<std::is_base_of<T,CC>::value,T>::type>& operator=(CPtr<CC> _Obj)
		{
			Release();

			instance = _Obj->instance;
			lookCnt = _Obj->lookCnt;

			if (!*this)return *this;

			lookCnt++;

			return *this;
		}

		inline CPtr<T> operator=(const std::nullptr_t _Nulls)
		{
			if (!*this)return *this;
			*lookCnt -= 1;
			if (*lookCnt > 0)
			{
				instance = nullptr;
				return nullptr;
			}

			delete instance;
			instance = nullptr;

			delete lookCnt;
			lookCnt = nullptr;

			return *this;
		}


		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		template<class CC>
		inline CPtr<T>(
			const CPtr
			<typename std::enable_if
			<std::is_base_of<T, CC>::value, CC>::type>
			& _Ptr)
		{
			*this = _Ptr;
		}

		template<class CC, class... _Types>
		inline CPtr<T>(_Types&&... _Args)
		{
			Release();

			instance = nullptr;
			lookCnt = nullptr;

			instance = new CC(_Args...);
			lookCnt = new unsigned long(1);
		}

		inline CPtr<T>(const  CPtr<T>& _Null) { *this = _Null; }

		inline CPtr<T>(const std::nullptr_t& _Null) { Release(); }

		inline CPtr<T>() { Release(); }

		inline ~CPtr<T>()
		{
			Release();
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Release()
		{
			if (!*this)return;
			(*this) = nullptr;
		}

		///////////////////////////////////////////////////////////////////////////////////////

		template<class CC = T, class... _Types>
		inline auto Makes
			(_Types&&... _Args)->typename std::enable_if<std::is_base_of<T, CC>::value, void>::type
		{
			Release();

			instance = nullptr;
			lookCnt = nullptr;

			instance = new CC(_Args...);
			lookCnt = new unsigned long(1);
		}

	private:

		T* instance = nullptr;
		unsigned long* lookCnt = nullptr;

	};


	///////////////////////////////////////////////////////////////////////////////////////

	template<class T, class... _Types>
	static inline CPtr<T> Make_CPtr(_Types&&... _Args)
	{
		CPtr<T> Tmp = CPtr<T>(_Args...);
		return Tmp;
	}

	template<class T,class B>
	static inline CPtr<T>&
		Dynamic_CPtr
		(typename std::enable_if
			<std::is_base_of<B, T>::value, CPtr<B>>::type& _Base
		)
	{
		CPtr<T> Tmp;
		Tmp = _Base;
		Tmp->Instance = nullptr;
		Tmp->Instance = dynamic_cast<T>(_Base->Instance);
		if (Tmp->Instance == nullptr)Tmp.Release();
		return Tmp;
	}


}

#endif
