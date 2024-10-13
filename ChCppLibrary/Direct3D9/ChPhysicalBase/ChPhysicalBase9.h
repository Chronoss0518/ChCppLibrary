#ifndef Ch_D3D9_PhyBa_h
#define Ch_D3D9_PhyBa_h

namespace ChMesh
{
template<typename CharaType>
class BaseMesh9;
}


//(���ǒ�)//

//�ړ�����ۂɂ�������ɕ����I�ȗ͂������悤�ɂ���N���X//
//�x�[�X�N���X�̂��߁A��{�I�ɂ��ꎩ�̂��g�����Ƃ͂Ȃ�//
template<typename CharaType>
class ChPhysicalBase9:public ChCp::Initializer
{
public://Constructer Destructer//

	ChPhysicalBase9()
	{
		objCon = &ChObjCon9();
	}

	virtual  ~ChPhysicalBase9()
	{
		objCon = nullptr;
	}

public://InitAndRelease//

	virtual void Init(){}

	virtual void Init(const float _FPS){}

public://SetFunction//

	void SetMesh(const ChPtr::Shared<ChMesh::BaseMesh9<CharaType>> _mesh)
	{
		if (_mesh == nullptr)return;
		wpXList.push_back(_mesh);
	}

	//�d�͂̏ꍇ�͏d�̗͂͂�ύX�\(�ʏ펞�͉������ɕb��9.8�̑����ŗ�����)//
	inline virtual void SetData(const float) {}

	inline void SetLen(const float _baseLen) 
	{
		baseLen = _baseLen;
	}

	//�I�u�W�F�N�g�R���g���[���[�̃Z�b�g//
	//�g�������I�u�W�F�N�g�R���g���[���[���Z�b�g�ł���//
	inline void SetObjCon(ChObjectController9* _youUsedObjCon)
	{
		if (ChPtr::NullCheck(_youUsedObjCon))return;
		objCon = _youUsedObjCon;
	}

public://Mesh List Functions//

	ChMesh::BaseMesh9<CharaType>* GetMesh(unsigned long _num);

	unsigned long GetMeshCount();

	void RemoveMesh(unsigned long _num);

public://Update Functions//

	virtual bool UpDate(
		ChVec3_9*,
		const ChVec3_9*)
	{
		return true;
	};

protected:

	float baseLen = 1.0f;
	ChObjectController9* objCon = nullptr;
	float pow = 0.0f;
	float FPS = 60.0f;
	ChVec3_9 vec;

	std::vector<ChPtr::Weak<ChMesh::BaseMesh9<CharaType>>>wpXList;
};

//�d�͂𔭐�������N���X//
template<typename CharaType>
class ChGravity9 :public ChPhysicalBase9<CharaType>
{
public://Init And Release//
	
	void Init(const float _FPS)override;

public://Set Functions//

	inline void SetData(const float _data)override
	{
		g = _data;
	}

public://Update Functions//

	bool UpDate(
		ChVec3_9* _pos,
		const ChVec3_9* _moveDir)override;

private:

	float virtualHeight = 0.0f;
	float g = 9.8f;
	float tmpSpeed = 0.0f;
};

//���̂ւ̏Փˎ��ɉ����߂��N���X//
template<typename CharaType>
class ChPushBack9 :public ChPhysicalBase9<CharaType>
{

public://Init And Release//

	void Init()override;

public://Set Function//

	inline void SetData(const float _Data)override
	{
		backLine = _Data;
	}

public://Update Functions//

	bool UpDate(ChVec3_9*, const ChVec3_9*)override;

private:

	float backLine = 1.0f;
};


using ChGravityA9 = ChGravity9<char>;
using ChPushBackA9 = ChPushBack9<char>;
#ifdef CPP20
using ChGravityW9 = ChGravity9<wchar_t>;
using ChPushBackW9 = ChPushBack9<wchar_t>;
#endif


#endif