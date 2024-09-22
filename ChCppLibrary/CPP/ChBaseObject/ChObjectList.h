
#ifndef Ch_CPP_ObjList_h
#define Ch_CPP_ObjList_h

#include"../../CRTPack/ChSmartPtrPack/ChSmartPtrPack.h"
#include"../../CRTPack/ChVectorPack/ChVectorPack.h"
#include"../../CRTPack/ChStringPack/ChStringPack.h"

#include"../../BasePack/ChPtr.h"

#include"ChBaseObject.h"

namespace ChCpp
{
	class BasicObject;

	class ObjectList
	{
	public:

		friend BasicObject;

	public://Constructor Destructor//

		ObjectList();

		virtual ~ObjectList();

	public://Init And Release//

		virtual void Release() { ClearObject(); }

	public://Set Function//

#ifdef CRT

		//�I�u�W�F�N�g��o�^����//
		//BaseObject���p�������I�u�W�F�N�g�̂ݓo�^�\//
		template<class T = BasicObject>
		typename std::enable_if<
			std::is_base_of<BasicObject, T>::value ||
			std::is_same<BasicObject, T>::value,
			ChPtr::Shared<T>>::type
			SetObject()
		{
			ChPtr::Shared<ChCpp::BasicObject> res = ChPtr::Make_S<T>();
			res->SetObjectList(this);
			res->Init();
			objectList.Push(res);
			return ChPtr::SharedSafeCast<T>(res);
		}

		void SetObject(ChPtr::Shared<BasicObject> _obj)
		{
			SetObjectCRT(_obj);
		}

#endif

		void SetObjectCRT(ChCRT::SharedPtrPack<BasicObject> _obj);

	public://Get Functions//

#ifdef CRT

		template<class T = BasicObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BasicObject, T>::value, T>::type>>
			GetObjectList()
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (size_t i = 0; i < objectList.GetSize(); i++)
			{
				if (ChPtr::NotNullCheck(objectList[i]->GetParent()))continue;
				auto&& test = ChPtr::SharedSafeCast<T>(objectList[i]);
				if (test == nullptr)continue;
				tmpObjList.push_back(test);
				for (auto&& childObj : obj->GetChildlen<T>())
				{
					tmpObjList.push_back(childObj);
				}
			}

			return tmpObjList;
		}

		template<class T = BasicObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BasicObject, T>::value, T>::type>>
			GetObjectListForName(const std::string& _name)
		{
			std::vector<ChPtr::Weak<BasicObject>>tmpObjList;

			for (size_t i = 0; i < objectList.GetSize(); i++)
			{
				if (ChPtr::NotNullCheck(objectList[i]->GetParent()))continue;
				auto&& test = ChPtr::SharedSafeCast<T>(objectList[i]);
				if (test == nullptr)continue;
				if (test->GetMyName() != _name)continue;
				tmpObjList.push_back(test);
				for (auto&& childObj : obj->GetChildlenForName<T>(_name))
				{
					tmpObjList.push_back(childObj);
				}
			}
			return tmpObjList;
		}

#endif

		inline size_t GetObjectCount() { return objectList.GetSize(); }

	public://Life Cycle Functions//

		//�o�^����Ă���I�u�W�F�N�g���X�V����//
		void Update()
		{
			ObjectUpdateBegin();

			ObjectUpdate();

			ObjectUpdateEnd();
		}

		//Update���敪����������//
		void ObjectUpdateBegin();

		void ObjectUpdate();

		void ObjectUpdateEnd();

		//�o�^����Ă���I�u�W�F�N�g���ړ�������//
		void Move()
		{
			ObjectMoveBegin();

			ObjectMove();

			ObjectMoveEnd();
		}

		//Move���敪����������//
		void ObjectMoveBegin();

		void ObjectMove();

		void ObjectMoveEnd();

		//�o�^����Ă���I�u�W�F�N�g��`�悷��B
		void Draw()
		{
			ObjectDrawBegin();

			ObjectDraw3D();

			ObjectDraw2D();

			ObjectDrawEnd();
		}


		//Draw�����킯��������//
		void ObjectDrawBegin();

		void ObjectDraw2D();

		void ObjectDraw3D();

		void ObjectDrawEnd();



		//�ێ����Ă��邷�ׂẴI�u�W�F�N�g���폜����B
		void ClearObject();

#ifdef CRT

		//�I�����ꂽ���O�̃I�u�W�F�N�g�����ׂď�������//
		template<typename CharaType>
		void ClearObjectForName(const std::basic_string<CharaType>& _name);

#endif

		//�폜�����I�u�W�F�N�g���m�F���č폜����//
		void DestroyObjectTest();


	private:

		template<typename CharaType>
		void ClearObjectForNameBase(const ChCRT::StringPack<CharaType>& _name);

	protected:

		ChCRT::VectorPack<ChCRT::SharedPtrPack<BasicObject>>objectList;

	};

}

#ifdef CRT

#endif

#include"SharedFunctions/ChObjectSharedObjectList.h"

#endif