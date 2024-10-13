#ifndef Ch_D3D9_Ob_h
#define Ch_D3D9_Ob_h

#include"../ChVertexData9.h"

namespace ChMesh
{

	template<typename CharaType>
	class BaseMesh9;

}

namespace ChTex
{
	typedef class BaseTexture9 Texture9;

	class PolygonBoard9;
}

//���̂ɑ΂��Ă̊֐���L����N���X//
//�|���S����3D���f���ɑ΂��ċ@�\����//
class ChObjectController9 
{
public:

	//�ȈՓIXFile�̃��C����//
	template<typename CharaType>
	bool MeshHitRay(
		DWORD& _index,
		float& _len,
		const ChMesh::BaseMesh9<CharaType>& _mesh,
		const ChMat_9& _obj,
		const ChVec3_9& _pos,
		const ChVec3_9& _dir);

	template<typename CharaType>
	bool MeshHitRay(
		float& _len,
		const ChMesh::BaseMesh9<CharaType>& _mesh,
		const ChMat_9& _obj,
		const ChVec3_9& _pos,
		const ChVec3_9& _dir);

	template<typename CharaType>
	bool MeshHitRay(
		const ChMesh::BaseMesh9<CharaType>& _mesh,
		const ChMat_9& _obj,
		const ChVec3_9& _pos,
		const ChVec3_9& _dir);

	//�|���S���ɑ΂��Ă̗ᔻ��//
	bool PorygonHitRay(
		float& _len,
		const ChTex::PolygonBoard9& _poBo,
		const ChVec3_9& _pos,
		const ChVec3_9& _dir);

	//�A�j���[�V�������X�g��ۗL���Ȃ��Ă�//
	//�ȒP�ɃA�j���[�V������������֐�//
	void SimpleAnimetion(
		ChMat_9& _nowMat,
		const ChMat_9& _startMat,
		const ChMat_9& _endMat,
		const float& _nowTime);

	//�|���S�����̂������ƃJ�����̂ق��������悤�ɂ��郁�\�b�h
	void MatrixBillboard(
		ChMat_9& _outObj,
		const ChVec3_9& _objPos,
		const  ChMat_9& _camMat);

	// _MaskDirection��'x','y','z'�̂����ꂩ���L������ƁA//
	//���̕����ɂ��������蔻�肪����Ȃ��ʒu�ɂȂ�//
	bool LengthDecision(
		const ChMat_9 &_mat1,
		const ChMat_9 &_mat2,
		const float matLen,
		const char _maskDirection);


	//2D�ł̓����蔻��(���ǕK)//
	bool Hit2DDecision(
		const ChMat_9& _obj1Mat,
		const ChMat_9& _obj2Mat,
		const ChTex::BaseTexture9&_obj1Tex,
		const ChTex::BaseTexture9&_obj2Tex);

	//����_�Ƃ���ʂ܂ł̋���//
	//�������d���̂ŉ񐔂͏��Ȃ�//
	float GetLenToPosTri(
		const D3DXVECTOR3& _pos,
		const D3DXVECTOR3& _faceVer1,
		const D3DXVECTOR3& _faceVer2,
		const D3DXVECTOR3& _faceVer3);

	//����_�����镽�ʂɑ΂��鐂���ȍŒZ����//
	float GetLenToPosPlane(
		const D3DXVECTOR3& _pos,
		const D3DXVECTOR3& _faceVer1,
		const D3DXVECTOR3& _faceVer2,
		const D3DXVECTOR3& _faceVer3);

	//_ObjectMat�ɑ΂���_OffsetMat�����CrossVec�𐶐�//
	//_OutVec��NULL�܂���nullptr�������ꍇ�͎��s����//
	void LookObjectAxis(
		ChVec3_9&_outVec,
		const ChMat_9&_offsetMat,
		const ChMat_9& _objectMat);

	//��]�݂̂̊ȈՓI�A�j���[�V����//
	//(���ǕK)
	void SimpleOffsetAnimation(
		ChMat_9& _nowMat,
		const ChQua_9& _startQua,
		const ChQua_9& _endQua,
		const float _endTime,
		const float _nowTime);

protected:

	ChObjectController9() {}

	~ChObjectController9() {}

public:

	inline static ChObjectController9& GetIns()
	{
		static ChObjectController9 ins;
		return ins;
	}

};

inline ChObjectController9& ChObjCon9() { return ChObjectController9::GetIns(); }


#endif // !Ch_D3D9_Ob_h
//CopyRight Chronoss0518 2018/08