#ifndef Ch_CRT_Vector
#define Ch_CRT_Vector

#include"../ChCRTBase.h"

#ifdef CRT
#include<vector>
#endif

namespace ChCRT
{
	template<class T>
	class VectorPack final
	{
		struct VectorPackCRT
		{
#ifdef CRT
			std::vector<T> pack;
#endif
		};

	public:

		Ch_CRT_Operator_Functions(VectorPack, std::vector<T>);

	public:

		Ch_CRT_ConstructorDestructor_Functions(VectorPack, std::vector<T>);

		VectorPack();

		~VectorPack();

	public:
		
		operator T*();

		operator const T* () const;

	public:

		size_t GetSize();

#ifdef CRT
		std::vector<T>& GetPackVector() { return value->pack; }
#endif

	public:

		bool IsEmpty();

	public:

		void Push(T& _val);

		void Pop();

		void Remove(const size_t& _num);

		void Clear();

	protected:

		VectorPackCRT* value = nullptr;
	};
}

#endif