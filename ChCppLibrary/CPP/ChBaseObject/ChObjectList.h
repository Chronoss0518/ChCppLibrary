
#ifndef Ch_CPP_ObjList_h
#define Ch_CPP_ObjList_h

#include<vector>
#include<string>

#include"../../BasePack/ChPtr.h"

#include"ChBaseObject.h"

namespace ChCpp
{
	class BasicObject;

	class ObjectList
	{
	public:

		friend BasicObject;

	public://Init And Release//

		virtual void Release() { ClearObject(); }

	public://Set Function//

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
			objectList.push_back(res);
			return ChPtr::SharedSafeCast<T>(res);
		}

		void SetObject(ChPtr::Shared<BasicObject> _obj);

	public://Get Functions//

		template<class T = BasicObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BasicObject, T>::value, T>::type>>
			GetObjectList()
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (size_t i = 0; i < objectList.size(); i++)
			{
				if (objectList[i]->GetParent() != nullptr)continue;
				auto&& test = ChPtr::SharedSafeCast<T>(objectList[i]);
				if (test == nullptr)continue;
				tmpObjList.push_back(test);
				for (auto&& childObj : test[i]->GetChildlen<T>())
				{
					tmpObjList.push_back(childObj);
				}
			}

			return tmpObjList;
		}

		inline size_t GetObjectCount() { return objectList.size(); }

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

		//�I�����ꂽ���O�̃I�u�W�F�N�g�����ׂď�������//
		template<typename CharaType>
		void ClearObjectForName(const std::basic_string<CharaType>& _name);

		//�폜�����I�u�W�F�N�g���m�F���č폜����//
		void DestroyObjectTest();

	protected:

		std::vector<ChPtr::Shared<BasicObject>>objectList;

	};

}

#endif