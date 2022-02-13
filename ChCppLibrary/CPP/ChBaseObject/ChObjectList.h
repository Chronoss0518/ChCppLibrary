
#ifndef Ch_CPP_ObjList_h
#define Ch_CPP_ObjList_h

#include"../ChBitBool/ChBitBool.h"

#include"ChBaseObject.h"

namespace ChCpp
{



	class ObjectList :public ChCp::Releaser
	{
	public:

		friend BaseObject;

		///////////////////////////////////////////////////////////////////////////////////////
		//CostructerDestructer//

		ObjectList() {}
		~ObjectList() {}

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�I�u�W�F�N�g��o�^����//
		//BaseObject���p�������I�u�W�F�N�g�̂ݓo�^�\//
		template<class T>
		auto SetObject(const std::string& _objectName, const std::string& _tag) ->typename std::enable_if
			<std::is_base_of<BaseObject, T>::value, ChPtr::Shared<T>>::type
		{

			ChPtr::Shared<BaseObject> tmpObj = ChPtr::Make_S<T>();

			tmpObj->BaseInit(_objectName, _tag, this);

			tmpObj->Init();

			objectList[_tag].push_back(tmpObj);

			return ChPtr::SharedSafeCast<T>(tmpObj);
		}
		
		//BaseObject���p�������I�u�W�F�N�g�̂ݓo�^�\//
		template<class T>
		auto SetObject(ChPtr::Shared<T> _obj) ->typename std::enable_if
			<std::is_base_of<BaseObject, T>::value, ChPtr::Shared<T>>::type
		{

			ChPtr::Shared<BaseObject> tmpObj = _obj;

			if (objectList.find(tmpObj->GetTag()) != objectList.end())
			{
				if (std::find(objectList[tmpObj->GetTag()].begin(), objectList[tmpObj->GetTag()].end(), tmpObj))return;
			}

			tmpObj->objMa = this;

			objectList[tmpObj->GetTag()].push_back(tmpObj);

			for (auto&& child : tmpObj->childList)
			{
				SetObject(child);
			}

			return ChPtr::SharedSafeCast<T>(tmpObj);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		std::vector<ChPtr::Weak<BaseObject>> GetObjectList();

		std::vector<ChPtr::Weak<BaseObject>> GetObjectListForTag(const std::string& _tagName);

		std::vector<ChPtr::Weak<BaseObject>> GetObjectListForName(const std::string& _name);

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

		//�I�����ꂽ�^�O�̃I�u�W�F�N�g�����ׂď�������//
		void ClearObjectForTag(const std::string& _tags);

		//�I�����ꂽ���O�̃I�u�W�F�N�g�����ׂď�������//
		void ClearObjectForName(const std::string& _name);

		//�I�����ꂽ�^�O�Ɗ֘A���閼�O�̃I�u�W�F�N�g�����ׂď�������//
		void ClearObjectForTagAndName(
			const std::string& _name,
			const std::string& _tags);

		///////////////////////////////////////////////////////////////////////////////////////
		
	protected:

		std::map<std::string, std::vector<ChPtr::Shared<BaseObject>>>objectList;


	};

}


#endif