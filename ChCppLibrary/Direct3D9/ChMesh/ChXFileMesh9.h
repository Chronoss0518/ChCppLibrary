
#ifndef Ch_D3D9_XMe_h
#define Ch_D3D9_XMe_h

#include"ChBaseMesh9.h"

namespace ChMesh
{
	template<typename CharaType>
	class XFileMesh9 :public BaseMesh9<CharaType>,public XFileMeshBase<CharaType>
	{
	public:

		void OpenFile(
			const std::basic_string<CharaType>& _fileName,
			const std::basic_string<CharaType>& _pathName,
			const LPDIRECT3DDEVICE9& _dev)override;
	};
}

#endif