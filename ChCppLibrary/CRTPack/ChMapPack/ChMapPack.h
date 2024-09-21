#ifndef Ch_CRT_Map
#define Ch_CRT_Map

#include"../ChCRTBase.h"

#ifdef CRT
#include<map>
#endif

#ifndef Ch_MapPack_PackClass
#define Ch_MapPack_PackClass std::map<_Key, _Value>
#endif

namespace ChCRT
{
	template<class _Key,class _Value>
	class MapPack final
	{
		struct MapPackCRT
		{
#ifdef CRT
			Ch_MapPack_PackClass pack;
#endif
		};
	public:

		Ch_CRT_Operator_Functions_To_Base(MapPack);
		Ch_CRT_Operator_Functions_To_Pack(MapPack, Ch_MapPack_PackClass);

		_Value& operator[](const _Key& _key);

		const _Value& operator [](const _Key& _key) const;

	public:

		Ch_CRT_ConstructorDestructor_Functions(MapPack, Ch_MapPack_PackClass);

		MapPack();

		~MapPack();

	public:

		size_t GetSize();

#ifdef CRT
		Ch_MapPack_PackClass& GetPackMap() { return value->pack; }
#endif

	public:

		_Value* Find(const _Key& _key);

		_Value& Insert(const _Key& _key);

		void Remove(const _Key& _key);

		void Clear();

	private:

		MapPackCRT* value = nullptr;

	};
}

#endif