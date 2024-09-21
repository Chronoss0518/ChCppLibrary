#ifndef Ch_CRT_SmartPtr
#define Ch_CRT_SmartPtr

#include"../ChCRTBase.h"

#ifdef CRT
#include<memory>
#endif

namespace ChCRT
{
	template<class T>
	class SharedPtrPack final
	{
		struct SharedPtrPackCRT
		{
#ifdef CRT
			std::shared_ptr<T>pack = nullptr;
#endif
		};

	public:

		Ch_CRT_Operator_Functions_To_Base(SharedPtrPack);
		Ch_CRT_Operator_Functions_To_Pack(SharedPtrPack, std::shared_ptr<T>);

		operator T*();

		operator const T*()const;

	public:

		Ch_CRT_ConstructorDestructor_Functions(SharedPtrPack, std::shared_ptr<T>);

		SharedPtrPack(T* _val);

		SharedPtrPack();

		~SharedPtrPack();

	public:

		void Set(T* _val);

#ifdef CRT
		void SetPack(const std::shared_ptr<T>& _val) { value->pack = _val; }
#endif

	public:

		const T* Get()const;

#ifdef CRT
		std::shared_ptr<T> GetPack()const { return value->pack; }
#endif

	public:

		void Make();

	private:

		SharedPtrPackCRT* value = nullptr;
	};


	template<class T>
	class WeakPtrPack final
	{
		struct WeakPtrPackCRT
		{
#ifdef CRT
			std::weak_ptr<T>pack;
#endif
		};

	public:

		Ch_CRT_Operator_Functions_To_Base(WeakPtrPack);
		Ch_CRT_Operator_Functions_To_Pack(WeakPtrPack, std::weak_ptr<T>);

	public:

		Ch_CRT_ConstructorDestructor_Functions(WeakPtrPack, std::weak_ptr<T>);

		Ch_CRT_ConstructorDestructor_Functions(WeakPtrPack, std::shared_ptr<T>);

		WeakPtrPack(const SharedPtrPack<T> _pack);

		WeakPtrPack();

		~WeakPtrPack();

	public:

		void Set(const SharedPtrPack<T>& _val);

#ifdef CRT
		void SetPack(const std::weak_ptr<T>& _val) { value->pack = _val; }

		void SetPack(const std::shared_ptr<T>& _val) { value->pack = _val; }
#endif
	public:

#ifdef CRT
		std::weak_ptr<T> GetPack() const { return value->pack; }
#endif

	public:

		bool IsExpired()const;

		SharedPtrPack<T> LockChPtr()const;

#ifdef CRT
		std::shared_ptr<T> LockPtr()const { return value->pack.lock(); }
#endif
	private:

		WeakPtrPackCRT* value = nullptr;
	};
}

#endif