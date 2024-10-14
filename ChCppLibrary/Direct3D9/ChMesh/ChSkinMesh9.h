
#ifndef Ch_D3D9_SkMe_h
#define Ch_D3D9_SkMe_h

#include"ChBaseMesh9.h"
typedef class ChAnimationObject9 ChAniObj9;

namespace ChMesh
{

		class SkinMesh9 :public BaseMesh9
		{
		protected:

			struct BoneVertex
			{
				struct BonePow
				{
					ChMat_9* updateMat;
					ChMat_9* offMat;
					float waitPow = 0.0f;

				};

				ChVec3_9 pos;
				std::vector<ChPtr::Shared<BonePow>>updateMat;
			};

			struct Bone
			{
				ChMat_9 baseMat;
				ChMat_9 updateMat;
				ChMat_9 offMat;
				std::string myName;
				ChPtr::Shared<Bone> offsetBone = nullptr;
			};

			bool startPlayAniCheck = false;
			ChAniObj9 tAni;

		public://Constructer Destructer//

			inline virtual ~SkinMesh9()
			{
				Release();
			}

			void Release();

		public://Set Functions//

			//XFile���A�j���[�V�������擾//
			void SetAnimation(
				const std::string& _aniamtionName,
				const std::string& _xFileName);

			//�O���ō쐬�����A�j���[�V�������Z�b�g//
			void SetAnimation(
				const std::string& _aniamtionName,
				const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _animes);

			//�Đ�����A�j���[�V������ύX//
			void SetPlayAniName(const std::string& _aniName);

			//�Đ�����A�j���[�V�����̏I���t���[������ύX//
			inline void SetAniTime(
				const std::string& _aniName,
				const float _playMaxTime);

			void SetSkin()override;

		protected://Set Functions//

			void SetOffsetVertex()override;

		public://Get Functions//

			std::vector<ChPtr::Shared<std::string>> GetAniNameList();

			ChMat_9 GetBoneMat(const std::string& _str)override;

			friend MeshManager9;
			friend MeshList9;

		protected://Member Value//

			std::string testName = "";

			std::vector<ChPtr::Shared<BoneVertex>>boneVertexList;

			//���ɃA�j���[�V������//
			//����Bone��������B//
			using BoneAnimation = std::map<std::string, ChPtr::Shared<ChAnimationObject9>>;

			std::map<std::string, BoneAnimation> animations;

			std::string nowPlayAniName = "";

			std::map<std::string, ChPtr::Shared<Bone>> boneList;

			std::vector<std::string> boneNameList;
		};
	
}

#endif
