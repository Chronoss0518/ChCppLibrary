
#ifndef Ch_CPP_CP_Rel_h
#define Ch_CPP_CP_Rel_h

namespace ChCpp
{
	namespace ClassPerts
	{

		//�p�����ė��p����//
		//�������J�����s����ۂɕK��Release�֐����Ă΂��//
		//Release�֐����I�[�o�[���C�h����K�v������//
		class Releaser
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			virtual void Release() {};

			///////////////////////////////////////////////////////////////////////////////////
			//ConstructorDestructor//

		protected:

			virtual ~Releaser()
			{
				Release();
			}

		};


	}
}
#endif
