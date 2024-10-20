#ifndef Ch_CRT_Vector
#define Ch_CRT_Vector

#include"../ChCRTBase.h"

#ifdef CRT
#include<vector>
#include<iterator>
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

		Ch_CRT_Operator_Functions_To_Base(VectorPack);
		Ch_CRT_Operator_Functions_To_Pack(VectorPack, std::vector<T>);

		T& operator[](const size_t _num);

		const T& operator [](const size_t _num) const;

	public:

		Ch_CRT_ConstructorDestructor_Functions(VectorPack, std::vector<T>);

		VectorPack();

		~VectorPack();

	public:

		size_t GetSize()const;

#ifdef CRT
		std::vector<T>& GetPackVector() { return value->pack; }
#endif

	public:

		bool IsEmpty()const;

		bool IsFind(T& _val)const;

	public:

		void Push(const T& _val);

		void Insert(const size_t& _num,const T& _val);

		void Pop();

		void Resize(const size_t _num);

		void Remove(const size_t& _num);

		bool RemoveObj(const T& _val);

		void Clear();

	public:

#ifdef CRT

		typename std::vector<T>::iterator begin()const { return value->pack.begin(); }

		typename std::vector<T>::iterator end()const { return value->pack.end(); }

#endif

	protected:

		VectorPackCRT* value = nullptr;
	};
}

#endif