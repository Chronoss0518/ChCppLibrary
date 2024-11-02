#ifndef Ch_CRT_Base
#define Ch_CRT_Base

#ifdef CRT
#ifndef Ch_CRT_Operator_Functions_To_Base
#define Ch_CRT_Operator_Functions_To_Base(_BaseClass)\
inline _BaseClass##& operator =(const _BaseClass& _val) { if(this != &_val)value->pack = _val.value->pack; return *this; }
#endif
#else
#ifndef Ch_CRT_Operator_Functions_To_Base
#define Ch_CRT_Operator_Functions_To_Base(_BaseClass)
#endif
#endif

#ifdef CRT
#ifndef Ch_CRT_Operator_Functions_To_Pack
#define Ch_CRT_Operator_Functions_To_Pack(_BaseClass,_PackClass)\
inline _BaseClass##& operator =(const _PackClass##& _val) { if(reinterpret_cast<size_t>(&value->pack) != reinterpret_cast<size_t>(&_val))value->pack = _val; return *this; }\
inline operator _PackClass##& () { return value->pack; }
#endif
#else
#ifndef Ch_CRT_Operator_Functions_To_Pack
#define Ch_CRT_Operator_Functions_To_Pack(_BaseClass,_PackClass)
#endif
#endif

#ifdef CRT
#ifndef Ch_CRT_ConstructorDestructor_Functions
#define Ch_CRT_ConstructorDestructor_Functions(_BaseClass,_PackClass)\
inline _BaseClass##(const _PackClass& _val) {\
	value = new _BaseClass##CRT();\
	if (reinterpret_cast<size_t>(&_val) != reinterpret_cast<size_t>(&value->pack))value->pack = _val; }\
inline _BaseClass##(_PackClass&& _val) {\
	value = new _BaseClass##CRT();\
	if (reinterpret_cast<size_t>(&_val) != reinterpret_cast<size_t>(&value->pack))value->pack = _val; }
#endif
#else
#ifndef Ch_CRT_ConstructorDestructor_Functions
#define Ch_CRT_ConstructorDestructor_Functions(_BaseClass,_PackClass)
#endif
#endif

#endif