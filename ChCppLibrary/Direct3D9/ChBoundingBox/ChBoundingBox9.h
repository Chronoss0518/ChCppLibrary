#ifndef Ch_D3D9_BBox_h
#define Ch_D3D9_BBox_h

#include"../../BasePack/ChPtr.h"

namespace ChMesh
{
	class BaseMesh9;


	//(改良中)//
	//メッシュを作成時に生成されるバウンディングボックス、バウンディングスフィア専用クラス//
	//主にボックスを利用するため名前はバウンディングボックス//
	typedef class BoundingBox9
	{

	public://Constructer Destructer//

		BoundingBox9() 
		{
			main = ChVec3_9();
			depth = ChVec3_9();
			radius = 0.0f;
		}

		BoundingBox9(const BoundingBox9& _box)
		{
			*this = _box;
		}
		
	public://Set Functions//

		//XFileより生成されるバウンディングボックス//
		void SetBBox(const ChPtr::Shared<ChMesh::BaseMesh9>& _mesh)
		{
			if (_mesh == nullptr)return;
			if (ChPtr::NullCheck(_mesh->GetMesh()))return;
			ChVec3_9 maxVec;
			ChVec3_9 minVec;

			DWORD vertexNum = _mesh->GetMesh()->GetNumVertices();
			DWORD vSize = _mesh->GetMesh()->GetNumBytesPerVertex();
			BYTE* p;

			_mesh->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&p);

			D3DXComputeBoundingBox((D3DXVECTOR3*)p, vertexNum, vSize, &minVec, &maxVec);

			_mesh->GetMesh()->UnlockVertexBuffer();

			main = minVec;

			depth = maxVec - minVec;
		}

		//XFileより生成されるバウンディングスフィア//
		void SetBSphere(const ChPtr::Shared<ChMesh::BaseMesh9>& _mesh)
		{
			if (_mesh == nullptr)return;
			if (ChPtr::NullCheck(_mesh->GetMesh()))return;

			DWORD vertexNum = _mesh->GetMesh()->GetNumVertices();
			DWORD vSize = _mesh->GetMesh()->GetNumBytesPerVertex();
			BYTE* p;

			_mesh->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&p);

			D3DXComputeBoundingSphere((D3DXVECTOR3*)p, vertexNum, vSize, &main, &radius);

			_mesh->GetMesh()->UnlockVertexBuffer();
		}

	public://Get Functions//

		//最小単位となる位置//
		inline const ChVec3_9* GetBasePos() { return &main; }

		//最大単位-最小単位で計算された位置
		inline const ChVec3_9* GetDepth() { return &depth; }

		std::vector<ChPtr::Shared<ChVec3_9>> GetPosition();

	public://Is Function//

		//点と箱の当たり判定//
		bool IsHitToPos(
			const ChMat_9* _mat,
			const ChVec3_9* _pos);

		//箱と箱の当たり判定(未完成)//
		bool IsHitToB_Box(
			const ChMat_9* _mat,
			const BoundingBox9* _pos);

		//球と箱の当たり判定//
		bool IsHitToBull(
			const ChMat_9* _mat,
			const ChVec3_9* _pos,
			const float _r);

	private:

		ChVec3_9 main = ChVec3_9();
		ChVec3_9 depth = ChVec3_9();
		float radius = 0.0f;

	}ChB_Box9;

}

#endif