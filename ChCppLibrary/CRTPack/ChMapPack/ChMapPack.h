#ifndef Ch_CRT_Map
#define Ch_CRT_Map

#include"../ChCRTBase.h"

#ifdef CRT
#include<map>
#include<iterator>
#endif

#include"../ChVectorPack/ChVectorPack.h"

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
		
#ifdef CRT

		typename std::map<_Key, _Value>::iterator begin()const { return value->pack.begin(); }

		typename std::map<_Key, _Value>::iterator end()const { return value->pack.end(); }

#endif

	public:

		_Value* Find(const _Key& _key)const;

		_Value& Insert(const _Key& _key);

		void Remove(const _Key& _key);

		void Clear();

	private:

		MapPackCRT* value = nullptr;

	};

	template<class _Key,class _Value>
	VectorPack<_Key>GetKeyListCRT(const MapPack<_Key, _Value>& _map);

	template<class _Key, class _Value>
	VectorPack<_Value>GetValueListCRT(const MapPack<_Key, _Value>& _map);

#ifdef CRT
	template<class _Key, class _Value>
	std::vector<_Key>GetKeyList(const MapPack<_Key, _Value>& _map)
	{
		std::vector<_Key> res;

		for (auto&& it : _map)
		{
			res.push_back(it.first);
		}

		return res;
	}

	template<class _Key, class _Value>
	std::vector<_Value>GetValueList(const MapPack<_Key, _Value>& _map)
	{
		std::vector<_Key> res;

		for (auto&& it : _map)
		{
			res.push_back(it.second);
		}

		return res;
	}

#endif
}

#endif