
#ifndef Ch_CPP_ObjMa_h
#define Ch_CPP_ObjMa_h

#include"ChObjectList.h"

namespace ChCpp
{

	

	class ObjectManager:public ChCp::Releaser
	{
	public:

		void Release()override;

		//�I�u�W�F�N�g��o�^����//
		//BaseObject���p�������I�u�W�F�N�g�̂ݓo�^�\//
		template<class T>
		auto SetObject(const std::string& _objectName,const std::string _tag = "") ->typename std::enable_if
			<std::is_base_of<BaseObject, T>::value, ChPtr::Shared<T>>::type
		{

			auto&& list = objectList.find(_tag);
			if (list == objectList.end())
			{
				objectList[_tag] = ChPtr::Make_S<ObjectList>();
				list = objectList.find(_tag);
			}

			return (*list).second->SetObject<T>(_objectName);
		}

		void SetObject(ChPtr::Shared<BaseObject> _obj, const std::string& _tag = "");

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		template<class T = BaseObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject, T>::value, T>::type>>
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

		template<class T = BaseObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject, T>::value, T>::type>>
			GetObjectListForName(const std::string& _name)
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

		template<class T = BaseObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject, T>::value, T>::type>>
			GetObjectListForTag(const std::string& _tag = "")
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

		template<class T = BaseObject>
		inline std::vector<ChPtr::Weak<
			typename std::enable_if<std::is_base_of<BaseObject, T>::value, T>::type>>
			GetObjectListForNameAndTag(const std::string& _name,const std::string& _tag = "")
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

		///////////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		//�o�^����Ă���I�u�W�F�N�g���X�V����//
		void Update();

		//Update���敪����������//
		void ObjectUpdateBegin();

		void ObjectUpdate();

		void ObjectUpdateEnd();


		void Update(const std::string& _tag);

		void ObjectUpdateBegin(const std::string& _tag);

		void ObjectUpdate(const std::string& _tag);

		void ObjectUpdateEnd(const std::string& _tag);

		///////////////////////////////////////////////////////////////////////////////////////

		//�o�^����Ă���I�u�W�F�N�g���ړ�������//
		void Move();

		//Move���敪����������//
		void ObjectMoveBegin();

		void ObjectMove();

		void ObjectMoveEnd();


		void Move(const std::string& _tag);

		void ObjectMoveBegin(const std::string& _tag);

		void ObjectMove(const std::string& _tag);

		void ObjectMoveEnd(const std::string& _tag);

		///////////////////////////////////////////////////////////////////////////////////////

		//�o�^����Ă���I�u�W�F�N�g��`�悷��B
		void Draw();

		//Draw�����킯��������//
		void ObjectDrawBegin();

		void ObjectDraw2D();

		void ObjectDraw3D();

		void ObjectDrawEnd();


		void Draw(const std::string& _tag);

		void ObjectDrawBegin(const std::string& _tag);

		void ObjectDraw2D(const std::string& _tag);

		void ObjectDraw3D(const std::string& _tag);

		void ObjectDrawEnd(const std::string& _tag);

		///////////////////////////////////////////////////////////////////////////////////////

		//�ێ����Ă��邷�ׂẴI�u�W�F�N�g���폜����B
		void ClearObject();

		//�I�����ꂽ���O�̃I�u�W�F�N�g�����ׂď�������//
		void ClearObjectForName(const std::string& _name);

		//�I�����ꂽ���O�̃I�u�W�F�N�g�����ׂď�������//
		void ClearObjectForTag(const std::string& _tag);

		//�I�����ꂽ���O�̃I�u�W�F�N�g�����ׂď�������//
		void ClearObjectForNameAndTag(const std::string& _name, const std::string& _tag);

		///////////////////////////////////////////////////////////////////////////////////////

	private:

		std::map<std::string, ChPtr::Shared<ObjectList>>objectList;

		///////////////////////////////////////////////////////////////////////////////////////
		//CostructerDestructer//

		ObjectManager() {}
		~ObjectManager() {}

	public:

		static ObjectManager& GetIns()
		{
			static ObjectManager Ins;
			return Ins;
		}

	};

	static const std::function<ObjectManager&()>ObjManager = ObjectManager::GetIns;

}


#endif