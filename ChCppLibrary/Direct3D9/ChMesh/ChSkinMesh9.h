
#ifndef Ch_D3D9_SkMe_h
#define Ch_D3D9_SkMe_h

#include"ChBaseMesh9.h"
#include"../ChAnimationObject/ChAnimationObject9.h"
typedef class ChAnimationObject9 ChAniObj9;

namespace ChMesh
{
		template<typename CharaType>
		class SkinMesh9 :public BaseMesh9<CharaType>
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

				std::basic_string<CharaType> myName;
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

			//XFileよりアニメーションを取得//
			void SetAnimation(
				const std::basic_string<CharaType>& _aniamtionName,
				const std::basic_string<CharaType>& _xFileName);

			//外部で作成したアニメーションをセット//
			void SetAnimation(
				const std::basic_string<CharaType>& _aniamtionName,
				const std::map<std::basic_string<CharaType>, ChPtr::Shared<ChAnimationObject9>>& _animes)
			{
				animations[_aniamtionName] = _animes;

				if (startPlayAniCheck)return;
				startPlayAniCheck = true;
				nowPlayAniName = _aniamtionName;
			}

			//再生するアニメーションを変更//
			inline void SetPlayAniName(const std::basic_string<CharaType>& _aniName)
			{
				if (animations.find(_aniName) == animations.end())return;


				for (auto&& anis : animations[nowPlayAniName])
				{
					anis.second->Stop();
				}
				nowPlayAniName = _aniName;
				for (auto&& anis : animations[nowPlayAniName])
				{
					anis.second->Play();
				}

			}

			//再生するアニメーションの終了フレーム数を変更//
			inline void SetAniTime(
				const std::basic_string<CharaType>& _aniName,
				const float _playMaxTime)
			{
				if (animations.find(_aniName) == animations.end())
				{
					return;
				}

				for (auto&& anis : animations[_aniName])
				{
					anis.second->SetOneFrameTime(_playMaxTime);
				}
			}

			void SetSkin()override;

		protected://Set Functions//

			void SetOffsetVertex()override;

		public://Get Functions//

			inline std::vector<std::basic_string<CharaType>> GetAniNameList()
			{
				std::vector<std::basic_string<CharaType>> tmpStr;
				for (auto&& anis : animations)
				{
					tmpStr.push_back(anis.first);
				}

				return tmpStr;
			}

			ChMat_9 GetBoneMat(const std::basic_string<CharaType>& _str)override
			{
				if (boneList.find(_str) == boneList.end())return ChMat_9();
				return boneList[_str]->baseMat;
			}

			friend MeshManager9<CharaType>;
			friend MeshList9<CharaType>;

		protected://Member Value//

			std::basic_string<CharaType> testName = ChStd::GetZeroChara<CharaType>();

			std::vector<ChPtr::Shared<BoneVertex>>boneVertexList;

			//第一にアニメーション名//
			//第二にBone名を入れる。//
			using BoneAnimation = std::map<std::basic_string<CharaType>, ChPtr::Shared<ChAnimationObject9>>;

			std::map<std::basic_string<CharaType>, BoneAnimation> animations;

			std::basic_string<CharaType> nowPlayAniName = ChStd::GetZeroChara<CharaType>();

			std::map<std::basic_string<CharaType>, ChPtr::Shared<Bone>> boneList;

			std::vector<std::basic_string<CharaType>> boneNameList;
		};

#ifdef CPP20
		using SkinMeshA9 = SkinMesh9<char>;
		using SkinMeshW9 = SkinMesh9<wchar_t>;
#else
		using SkinMeshA9 = SkinMesh9<char>;
#endif

}

#endif
