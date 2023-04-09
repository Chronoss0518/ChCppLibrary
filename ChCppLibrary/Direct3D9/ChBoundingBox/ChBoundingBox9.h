#ifndef Ch_D3D9_BBox_h
#define Ch_D3D9_BBox_h

namespace ChMesh
{
	typedef class BaseMesh9 Mesh9;


	//(改良中)//
	//メッシュを作成時に生成されるバウンディングボックス、バウンディングスフィア専用クラス//
	//主にボックスを利用するため名前はバウンディングボックス//
	typedef class BoundingBox9
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

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

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//XFileより生成されるバウンディングボックス//
		void SetBBox(const ChPtr::Shared<ChMesh::Mesh9>& _mesh);

		//XFileより生成されるバウンディングスフィア//
		void SetBSphere(const ChPtr::Shared<ChMesh::Mesh9>& _mesh);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//最小単位となる位置//
		inline const ChVec3_9* GetBasePos() { return &main; }

		//最大単位-最小単位で計算された位置
		inline const ChVec3_9* GetDepth() { return &depth; }

		std::vector<ChPtr::Shared<ChVec3_9>> GetPosition();

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//点と箱の当たり判定//
		bool IsHitToPos(
			const ChMat_9* _mat
			, const ChVec3_9* _pos);

		//箱と箱の当たり判定(未完成)//
		bool IsHitToB_Box(
			const ChMat_9* _mat
			, const BoundingBox9* _pos);

		//球と箱の当たり判定//
		bool IsHitToBull(
			const ChMat_9* _mat
			, const ChVec3_9* _pos
			, const float _r);

	private:

		ChVec3_9 main = ChVec3_9();
		ChVec3_9 depth = ChVec3_9();
		float radius = 0.0f;

	}ChB_Box9;

}

#endif