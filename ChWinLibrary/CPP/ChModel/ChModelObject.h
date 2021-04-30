#ifndef Ch_CPP_MObj_h
#define Ch_CPP_MObj_h

#include"../ChModel/ChModel.h"
#include"../ChModelCreater/ChModelCreater.h"
#include"../ChModelCreater/ChAnimationCreater.h"


namespace ChCpp
{

	class ModelObject :public ClassPerts::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Init() {};

		virtual void Release()override;

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		ChPtr::Shared<ModelFrame> GetModel()const
		{
			return model;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//



		///////////////////////////////////////////////////////////////////////////////////////
		//InsFunction//

		///////////////////////////////////////////////////////////////////////////////////////

		template<class T>
		auto CreateModel(const std::string& _filePath)->typename std::enable_if<
			std::is_base_of<ModelCreater, T>::value, void>::type
		{
			Release();

			ChPtr::Shared<ModelCreater> creater;
			creater = ChPtr::Make_S<T>();

			creater->Init(this);

			creater->CreateModel(_filePath);
		}

		///////////////////////////////////////////////////////////////////////////////////////

		template<class T>
		auto OutModelFile(const std::string& _filePath)->typename std::enable_if<
			std::is_base_of<ModelCreater, T>::value, void>::type
		{

		}

		friend ModelCreater;
		friend AnimationCreater;

	protected:

		ChPtr::Shared<ModelFrame>model = nullptr;

		std::vector<std::string>animatorNames;

	private:

		using FrameName = std::string;
		using  AnimationName = std::string;

		using Animation = std::map<AnimationName, ChPtr::Shared<ModelAnimator>>;

		static	std::map<FrameName, Animation>animatorList;

	};





}

#endif