
#ifndef Ch_CPP_ObjMa_h
#define Ch_CPP_ObjMa_h

#ifdef CRT
#include<string>
#include<map>
#endif

#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChPtr.h"

#include"ChObjectList.h"

#ifndef CH_OBJECT_MGR_METHOD
#define CH_OBJECT_MGR_METHOD(_FunctionNameBase) \
template<typename CharaType>\
void ChCpp::ObjectManager<CharaType>::##_FunctionNameBase##()\
{\
	for (auto&& objList : objectList) { objList.second->##_FunctionNameBase##(); }\
}
#endif


#ifndef CH_OBJECT_MGR_TAG_METHOD
#define CH_OBJECT_MGR_TAG_METHOD(_FunctionNameBase) \
template<typename CharaType>\
void ChCpp::ObjectManager<CharaType>::##_FunctionNameBase##(const std::basic_string<CharaType>& _tag)\
{\
	auto&& it = objectList.find(_tag);\
	if (it == objectList.end())return;\
	(*it).second->##_FunctionNameBase##();\
}
#endif



namespace ChCpp
{
	template<typename CharaType>
	class ObjectManager
	{
	public:

		virtual void Release();

	public://Set Functions//

#ifdef CRT

		//�I�u�W�F�N�g��o�^����//
		//BaseObject���p�������I�u�W�F�N�g�̂ݓo�^�\//
		template<class T = BaseObject<CharaType>>
		typename std::enable_if<std::is_base_of<BaseObject<CharaType>, T>::value ||
			std::is_same<BaseObject<CharaType>, T>::value, ChPtr::Shared<T>>::type
			SetObject(const std::basic_string<CharaType>& _tag = ChStd::GetZeroChara<CharaType>())
		{

			auto&& list = objectList.find(_tag);
			if (list == objectList.end())
			{
				objectList[_tag] = ChPtr::Make_S<ObjectList>();
				list = objectList.find(_tag);
			}

			return (*list).second->SetObject<T>();
		}

		void SetObject(ChPtr::Shared<BaseObject<CharaType>> _obj, const std::basic_string<CharaType>& _tag = ChStd::GetZeroChara<CharaType>());

#endif

	public://Get Functions//

#ifdef CRT

		template<class T = BaseObject<CharaType>>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject<CharaType>, T>::value, T>::type>>
			GetObjectList()
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (auto&& objlist : objectList)
			{
				for (auto&& outObj : objlist.second->GetObjectList<T>())
				{
					tmpObjList.push_back(outObj);
				}
			}

			return tmpObjList;
		}

		template<class T = BaseObject<CharaType>>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject<CharaType>, T>::value, T>::type>>
			GetObjectListForName(const std::basic_string<CharaType>& _name)
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (auto&& objlist : objectList)
			{
				for (auto&& outObj : objlist.second->GetObjectListForName<T>(_name))
				{
					tmpObjList.push_back(outObj);
				}
			}

			return tmpObjList;
		}

		template<class T = BaseObject<CharaType>>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject<CharaType>, T>::value, T>::type>>
			GetObjectListForTag(const std::basic_string<CharaType>& _tag = ChStd::GetZeroChara<CharaType>())
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			auto&& it = objectList.find(_tag);

			if (it == objectList.end())return tmpObjList;

			for (auto&& outObj : (*it).second->GetObjectList<T>())
			{
				tmpObjList.push_back(outObj);
			}

			return tmpObjList;
		}

		template<class T = BaseObject<CharaType>>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject<CharaType>, T>::value, T>::type>>
			GetObjectListForNameAndTag(const std::basic_string<CharaType>& _name,const std::basic_string<CharaType>& _tag = "")
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			auto&& it = objectList.find(_tag);

			if (it == objectList.end())return tmpObjList;

			for (auto&& outObj : (*it).second->GetObjectListForName<T>(_name))
			{
				tmpObjList.push_back(outObj);
			}

			return tmpObjList;
		}

		std::vector<std::basic_string<CharaType>> GetTagList();

#endif

		unsigned long GetObjectCount();

		unsigned long GetTagCount();

	public://Life Cycle Functions//

		//�o�^����Ă���I�u�W�F�N�g���X�V����//
		void Update();

		//Update���敪����������//
		void ObjectUpdateBegin();

		void ObjectUpdate();

		void ObjectUpdateEnd();


#ifdef CRT

		void Update(const std::basic_string<CharaType>& _tag);

		void ObjectUpdateBegin(const std::basic_string<CharaType>& _tag);

		void ObjectUpdate(const std::basic_string<CharaType>& _tag);

		void ObjectUpdateEnd(const std::basic_string<CharaType>& _tag);

#endif

		//�o�^����Ă���I�u�W�F�N�g���ړ�������//
		void Move();

		//Move���敪����������//
		void ObjectMoveBegin();

		void ObjectMove();

		void ObjectMoveEnd();


#ifdef CRT

		void Move(const std::basic_string<CharaType>& _tag);

		void ObjectMoveBegin(const std::basic_string<CharaType>& _tag);

		void ObjectMove(const std::basic_string<CharaType>& _tag);

		void ObjectMoveEnd(const std::basic_string<CharaType>& _tag);

#endif

		//�o�^����Ă���I�u�W�F�N�g��`�悷��B
		void Draw();

		//Draw�����킯��������//
		void ObjectDrawBegin();

		void ObjectDraw2D();

		void ObjectDraw3D();

		void ObjectDrawEnd();


#ifdef CRT

		void Draw(const std::basic_string<CharaType>& _tag);

		void ObjectDrawBegin(const std::basic_string<CharaType>& _tag);

		void ObjectDraw2D(const std::basic_string<CharaType>& _tag);

		void ObjectDraw3D(const std::basic_string<CharaType>& _tag);

		void ObjectDrawEnd(const std::basic_string<CharaType>& _tag);

#endif

	public:
	
		//�ێ����Ă��邷�ׂẴI�u�W�F�N�g���폜����B
		void ClearObject();

#ifdef CRT

		//�I�����ꂽ���O�̃I�u�W�F�N�g�����ׂď�������//
		void ClearObjectForName(const std::basic_string<CharaType>& _name);

		//�I�����ꂽ���O�̃I�u�W�F�N�g�����ׂď�������//
		void ClearObjectForTag(const std::basic_string<CharaType>& _tag);

		//�I�����ꂽ���O�̃I�u�W�F�N�g�����ׂď�������//
		void ClearObjectForNameAndTag(const std::basic_string<CharaType>& _name, const std::basic_string<CharaType>& _tag);
#endif
	private://Member Value//

#ifdef CRT

		std::map<std::basic_string<CharaType>, ChPtr::Shared<ObjectList>>objectList;

#endif

	private:

		ObjectManager() {}
		virtual ~ObjectManager() { Release(); }

	public:

		static ObjectManager<CharaType>& GetIns()
		{
			static ObjectManager<CharaType> Ins;
			return Ins;
		}

	};

	template<typename CharaType>
	static ObjectManager<CharaType>& ObjManager() { return ObjectManager<CharaType>::GetIns(); };

}


#ifdef CRT

template<typename CharaType>
void ChCpp::ObjectManager<CharaType>::Release() { ClearObject(); }

template<typename CharaType>
void ChCpp::ObjectManager<CharaType>::SetObject(ChPtr::Shared<BaseObject<CharaType>> _obj, const std::basic_string<CharaType>& _tag)
{
	if (_obj == nullptr)return;

	auto&& list = objectList.find(_tag);
	if (list == objectList.end())
	{
		objectList[_tag] = ChPtr::Make_S<ObjectList>();
		list = objectList.find(_tag);
	}

	list->second->SetObject(_obj);
}

template<typename CharaType>
std::vector<std::basic_string<CharaType>> ChCpp::ObjectManager<CharaType>::GetTagList()
{
	std::vector<std::basic_string<CharaType>> res;

	for (auto&& objList : objectList)
	{
		res.push_back(objList.first);
	}

	return res;
}

template<typename CharaType>
unsigned long ChCpp::ObjectManager<CharaType>::GetObjectCount()
{
	unsigned long res = 0;
	for (auto&& objList : objectList)
	{
		res += objList.second->GetObjectCount();
	}
	return res;
}

template<typename CharaType>
unsigned long ChCpp::ObjectManager<CharaType>::GetTagCount() { return objectList.size(); }


CH_OBJECT_MGR_METHOD(Update);
CH_OBJECT_MGR_METHOD(ObjectUpdateBegin);
CH_OBJECT_MGR_METHOD(ObjectUpdate);
CH_OBJECT_MGR_METHOD(ObjectUpdateEnd);

CH_OBJECT_MGR_TAG_METHOD(Update);
CH_OBJECT_MGR_TAG_METHOD(ObjectUpdateBegin);
CH_OBJECT_MGR_TAG_METHOD(ObjectUpdate);
CH_OBJECT_MGR_TAG_METHOD(ObjectUpdateEnd);

CH_OBJECT_MGR_METHOD(Move);
CH_OBJECT_MGR_METHOD(ObjectMoveBegin);
CH_OBJECT_MGR_METHOD(ObjectMove);
CH_OBJECT_MGR_METHOD(ObjectMoveEnd);

CH_OBJECT_MGR_TAG_METHOD(Move);
CH_OBJECT_MGR_TAG_METHOD(ObjectMoveBegin);
CH_OBJECT_MGR_TAG_METHOD(ObjectMove);
CH_OBJECT_MGR_TAG_METHOD(ObjectMoveEnd);

CH_OBJECT_MGR_METHOD(Draw);
CH_OBJECT_MGR_METHOD(ObjectDrawBegin);
CH_OBJECT_MGR_METHOD(ObjectDraw2D);
CH_OBJECT_MGR_METHOD(ObjectDraw3D);
CH_OBJECT_MGR_METHOD(ObjectDrawEnd);

CH_OBJECT_MGR_TAG_METHOD(Draw);
CH_OBJECT_MGR_TAG_METHOD(ObjectDrawBegin);
CH_OBJECT_MGR_TAG_METHOD(ObjectDraw3D);
CH_OBJECT_MGR_TAG_METHOD(ObjectDraw2D);
CH_OBJECT_MGR_TAG_METHOD(ObjectDrawEnd);

template<typename CharaType>
void ChCpp::ObjectManager<CharaType>::ClearObject()
{
	for (auto&& objList : objectList)
	{
		objList.second->ClearObject();
	}
	objectList.clear();
}

template<typename CharaType>
void ChCpp::ObjectManager<CharaType>::ClearObjectForName(const std::basic_string<CharaType>& _name)
{
	for (auto&& objList : objectList)
	{
		objList.second->ClearObjectForName(_name);
	}
}

template<typename CharaType>
void ChCpp::ObjectManager<CharaType>::ClearObjectForTag(const std::basic_string<CharaType>& _tag)
{
	auto&& it = objectList.find(_tag);
	if (it == objectList.end())return;
	(*it).second->ClearObject();
	objectList.erase(it);
}

template<typename CharaType>
void ChCpp::ObjectManager<CharaType>::ClearObjectForNameAndTag(const std::basic_string<CharaType>& _name, const std::basic_string<CharaType>& _tag)
{
	auto&& it = objectList.find(_tag);
	if (it == objectList.end())return;
	(*it).second->ClearObjectForName(_name);
}

#endif

#endif