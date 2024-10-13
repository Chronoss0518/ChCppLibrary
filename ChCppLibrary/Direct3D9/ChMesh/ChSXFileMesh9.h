
#ifndef Ch_D3D9_SXMe_h
#define Ch_D3D9_SXMe_h

#include"../../BasePack/Ch3D.h"
#include"ChSkinMesh9.h"

namespace ChMesh
{

	//ñ¢äÆê¨//
	template<typename CharaType>
	class SXFileMesh9 :public SkinMesh9<CharaType>, public XFileMeshBase<CharaType>
	{
	public:

		void OpenFile(
			const std::basic_string<CharaType>& _fileName,
			const std::basic_string<CharaType>& _pathName,
			const LPDIRECT3DDEVICE9& _dev)override;

	public://Set Functions//

		void SetBone(const std::basic_string<CharaType>& _fileName);

		void SetBoneVertex(const std::basic_string<CharaType>& _fStr);

	public:

		void CreateBoneTree(
			const std::basic_string<CharaType>& _fStr,
			size_t& _fPos,
			const ChPtr::Shared<typename ChMesh::SkinMesh9<CharaType>::Bone>& _bone = nullptr);

	protected:

	};

#ifdef CPP20
	using SXFileMeshA9 = SXFileMesh9<char>;
	using SXFileMeshW9 = SXFileMesh9<wchar_t>;
#else
	using SXFileMeshA9 = SXFileMesh9<char>;
#endif

}

#endif