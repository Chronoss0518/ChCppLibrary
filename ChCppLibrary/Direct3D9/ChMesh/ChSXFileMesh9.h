
#ifndef Ch_D3D9_SXMe_h
#define Ch_D3D9_SXMe_h

#include"ChSkinMesh9.h"

namespace ChMesh
{

	//ñ¢äÆê¨//
	class SXFileMesh9 :public SkinMesh9
	{
	public:

		void OpenFile(
			const std::string& _fileName,
			const std::string& _pathName,
			const LPDIRECT3DDEVICE9& _dev)override;

	public://Set Functions//

		void SetBone(const std::string& _fileName);

		void SetBoneVertex(const std::string& _fStr);

	public:

		void CreateBoneTree(
			const std::string& _fStr,
			size_t& _fPos,
			const ChPtr::Shared<Bone>& _bone = nullptr);

	protected:

	};
}

#endif