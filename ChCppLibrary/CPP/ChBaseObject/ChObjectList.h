
#ifndef Ch_CPP_ObjList_h
#define Ch_CPP_ObjList_h

#include"../ChBitBool/ChBitBool.h"

#include"ChBaseObject.h"

namespace ChCpp
{



	class ObjectList
	{
	public:

		friend BaseObject;

		///////////////////////////////////////////////////////////////////////////////////////
		//CostructerDestructer//

		ObjectList() {}

		virtual ~ObjectList()
		{
			Release();
		}


		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual void Release();

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�I�u�W�F�N�g��o�^����//
		//BaseObject���p�������I�u�W�F�N�g�̂ݓo�^�\//
		template<class T>
		auto SetObject(const std::string& _objectName) ->typename std::enable_if
			<std::is_base_of<BaseObject, T>::value, ChPtr::Shared<T>>::type
		{

			ChPtr::Shared<BaseObject> tmpObj = ChPtr::Make_S<T>();

			tmpObj->BaseInit(_objectName, this);

			tmpObj->Init();

			objectList.push_back(tmpObj);

			return ChPtr::SharedSafeCast<T>(tmpObj);
		}
		
		void SetObject(ChPtr::Shared<BaseObject> _obj);

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		template<class T = BaseObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject, T>::value, T>::type>>
			GetObjectList()
		{
			std::vector<ChPtr::Weak<T>>tmpObjList;

			for (auto&& obj : objectList)
			{
				if (obj->parent.lock() != nullptr)continue;
				auto&& test = ChPtr::SharedSafeCast<T>(obj);
				if (test == nullptr)continue;
				tmpObjList.push_back(test);
				for (auto&& childObj : obj->GetChildlen<T>())
				{
					tmpObjList.push_back(childObj);
				}

			}

			return tmpObjList;
		}

		template<class T = BaseObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject, T>::value, T>::type>>
			GetObjectListForName(const std::string& _name)
		{
			std::vector<ChPtr::Weak<BaseObject>>tmpObjList;

			for (auto&& obj : objectList)
			{
				if (obj->parent.lock() != nullptr)continue;
				auto&& test = ChPtr::SharedSafeCast<T>(obj);
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

		inline unsigned long GetObjectCount(){ return objectList.size(); }

		///////////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		//�o�^����Ă���I�u�W�F�N�g���X�V����//
		void Update();

		//Update���敪����������//
		void ObjectUpdateBegin();

		void ObjectUpdate();

		void ObjectUpdateEnd();

		///////////////////////////////////////////////////////////////////////////////////////

		//�o�^����Ă���I�u�W�F�N�g���ړ�������//
		void Move();

		//Move���敪����������//
		void ObjectMoveBegin();

		void ObjectMove();

		void ObjectMoveEnd();

		///////////////////////////////////////////////////////////////////////////////////////

		//�o�^����Ă���I�u�W�F�N�g��`�悷��B
		void Draw();

		//Draw�����킯��������//
		void ObjectDrawBegin();

		void ObjectDraw2D();

		void ObjectDraw3D();

		void ObjectDrawEnd();

		///////////////////////////////////////////////////////////////////////////////////////

		//�ێ����Ă��邷�ׂẴI�u�W�F�N�g���폜����B
		void ClearObject();

		//�I�����ꂽ���O�̃I�u�W�F�N�g�����ׂď�������//
		void ClearObjectForName(const std::string& _name);

		//�폜�����I�u�W�F�N�g���m�F���č폜����//
		void DestroyObjectTest();

		///////////////////////////////////////////////////////////////////////////////////////
		
	protected:

		std::vector<ChPtr::Shared<BaseObject>>objectList;

	};

}


#endif