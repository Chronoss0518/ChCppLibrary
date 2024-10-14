
#ifndef Ch_D3D9_SkMe_h
#define Ch_D3D9_SkMe_h

#include"ChBaseMesh9.h"
#include"../ChAnimationObject/ChAnimationObject9.h"
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
#ifdef CRT
				std::vector<ChPtr::Shared<BonePow>>updateMat;
#endif
			};

			struct Bone
			{
				ChMat_9 baseMat;
				ChMat_9 updateMat;
				ChMat_9 offMat;
#ifdef CRT
				std::string myName;
				ChPtr::Shared<Bone> offsetBone = nullptr;
#endif
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

#ifdef CRT

			//XFileよりアニメーションを取得//
			void SetAnimation(
				const std::string& _aniamtionName,
				const std::string& _xFileName);

			//外部で作成したアニメーションをセット//
			void SetAnimation(
				const std::string& _aniamtionName,
				const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _animes)
			{
				animations[_aniamtionName] = _animes;

				if (startPlayAniCheck)return;
				startPlayAniCheck = true;
				nowPlayAniName = _aniamtionName;
			}

			//再生するアニメーションを変更//
			inline void SetPlayAniName(const std::string& _aniName)
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
				const std::string& _aniName
				, const float _playMaxTime)
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
#endif

			void SetSkin()override;

		protected://Set Functions//

			void SetOffsetVertex()override;

		public://Get Functions//

#ifdef CRT

			inline std::vector<ChPtr::Shared<std::string>> GetAniNameList()
			{
				std::vector<ChPtr::Shared<std::string>> tmpStr;
				for (auto&& anis : animations)
				{
					auto str = ChPtr::Make_S<std::string>();
					*str = anis.first;
					tmpStr.push_back(str);

				}

				return tmpStr;
			}

			ChMat_9 GetBoneMat(const std::string& _str)override
			{
				if (boneList.find(_str) == boneList.end())return ChMat_9();
				return boneList[_str]->baseMat;
			}

#endif

			friend MeshManager9;
			friend MeshList9;

		protected://Member Value//

#ifdef CRT

			std::string testName = "";

			std::vector<ChPtr::Shared<BoneVertex>>boneVertexList;

			//第一にアニメーション名//
			//第二にBone名を入れる。//
			using BoneAnimation = std::map<std::string, ChPtr::Shared<ChAnimationObject9>>;
			
			std::map<std::string, BoneAnimation> animations;

			std::string nowPlayAniName = "";

			std::map<std::string, ChPtr::Shared<Bone>> boneList;
			
			std::vector<std::string> boneNameList;
#endif
		};
	
}

#ifdef CRT


void ChMesh::SkinMesh9::Release()
{
	boneList.clear();
	boneNameList.clear();
	tAni.Release();
}

void ChMesh::SkinMesh9::SetAnimation(
	const std::string& _animationName,
	const std::string& _XFileName)
{
	BoneAnimation tmpAni;

	tmpAni = ChANiSupport().CreateKeyFrame(_XFileName);

	size_t aniNum = 0;
	for (auto&& bones : boneList)
	{
		if (tmpAni.find(bones.first) == tmpAni.end())continue;
		aniNum = tmpAni[bones.first]->GetAniCnt();
		break;
	}

	for (auto&& bones : boneList)
	{
		if (tmpAni.find(bones.first) != tmpAni.end())continue;
		auto ani = ChPtr::Make_S<ChAnimationObject9>();

		for (size_t i = 0; i < aniNum; i++)
		{
			ani->SetAniObject(ChMat_9());
		}
		tmpAni[bones.first] = ani;

	}

	if (tmpAni.size() < boneList.size())return;

	animations[_animationName] = tmpAni;

	if (startPlayAniCheck)return;
	startPlayAniCheck = true;
	nowPlayAniName = _animationName;

	for (auto&& ani : animations[nowPlayAniName])
	{
		ani.second->Play();
	}
}

void ChMesh::SkinMesh9::SetSkin()
{
	if (ChPtr::NullCheck(mesh))return;
	if (animations.size() <= 0)return;
	if (boneList.size() <= 0)return;

	MeshVertex9* tmpVer = nullptr;
	mesh->LockVertexBuffer(NULL, (LPVOID*)&tmpVer);

	if (ChPtr::NullCheck(tmpVer))return;

	//BoneUpdate//
	for (auto&& boneName : boneNameList)
	{
		ChMat_9 tmpMat = boneList[boneName]->offMat;

		boneList[boneName]->updateMat = animations[nowPlayAniName][boneName]->Update();
	}

	//LastUpdateBone//

	for (unsigned long i = boneNameList.size() - 1; i + 1 > 0; i--)
	{

		ChMat_9 tmpMat = boneList[boneNameList[i]]->offMat;

		if (boneList[boneNameList[i]]->offsetBone == nullptr)
		{

			boneList[boneNameList[i]]->updateMat
				= tmpMat * boneList[boneNameList[i]]->updateMat;

			continue;
		}

		boneList[boneNameList[i]]->updateMat
			= tmpMat
			* boneList[boneNameList[i]]->updateMat
			* boneList[boneNameList[i]]->offsetBone->updateMat;
	}

	//UpdateVertex//
	for (unsigned long ver = 0; ver < mesh->GetNumVertices(); ver++)
	{
		ChMat_9 tmpMat;
		tmpMat.Clear0();
		ChVec3_9 tmpVec;

		tmpVec = GetOffsetVertex(ver);

		for (auto&& bones : boneVertexList[ver]->updateMat)
		{

			if (bones->waitPow <= 0.0f)continue;

			ChMat_9 tmp;
			tmp = (*bones->updateMat
				* bones->waitPow);

			tmpMat += tmp;

		}

		tmpVec.MatPos(tmpMat, tmpVec);

		(tmpVer + ver)->pos = tmpVec;
	}

	mesh->UnlockVertexBuffer();

}


void ChMesh::SkinMesh9::SetOffsetVertex()
{
	if (ChPtr::NullCheck(mesh))return;

	MeshVertex9* tmpVer = nullptr;
	mesh->LockVertexBuffer(NULL, (LPVOID*)&tmpVer);

	if (ChPtr::NullCheck(tmpVer))return;

	for (unsigned long ver = 0; ver < mesh->GetNumVertices(); ver++)
	{
		auto tmpPos = ChPtr::Make_S<ChVec3_9>();
		auto tmpVertex = ChPtr::Make_S<BoneVertex>();

		*tmpPos = (tmpVer + ver)->pos;

		tmpVertex->pos = (tmpVer + ver)->pos;

		offsetVertexList.push_back(tmpPos);

		boneVertexList.push_back(tmpVertex);
	}


	mesh->UnlockVertexBuffer();
	return;
}

#endif

#include"ChMeshShared9.h"

#endif
