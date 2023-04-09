#ifndef Ch_D3D9_BBox_h
#define Ch_D3D9_BBox_h

namespace ChMesh
{
	typedef class BaseMesh9 Mesh9;


	//(���ǒ�)//
	//���b�V�����쐬���ɐ��������o�E���f�B���O�{�b�N�X�A�o�E���f�B���O�X�t�B�A��p�N���X//
	//��Ƀ{�b�N�X�𗘗p���邽�ߖ��O�̓o�E���f�B���O�{�b�N�X//
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

		//XFile��萶�������o�E���f�B���O�{�b�N�X//
		void SetBBox(const ChPtr::Shared<ChMesh::Mesh9>& _mesh);

		//XFile��萶�������o�E���f�B���O�X�t�B�A//
		void SetBSphere(const ChPtr::Shared<ChMesh::Mesh9>& _mesh);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�ŏ��P�ʂƂȂ�ʒu//
		inline const ChVec3_9* GetBasePos() { return &main; }

		//�ő�P��-�ŏ��P�ʂŌv�Z���ꂽ�ʒu
		inline const ChVec3_9* GetDepth() { return &depth; }

		std::vector<ChPtr::Shared<ChVec3_9>> GetPosition();

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�_�Ɣ��̓����蔻��//
		bool IsHitToPos(
			const ChMat_9* _mat
			, const ChVec3_9* _pos);

		//���Ɣ��̓����蔻��(������)//
		bool IsHitToB_Box(
			const ChMat_9* _mat
			, const BoundingBox9* _pos);

		//���Ɣ��̓����蔻��//
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