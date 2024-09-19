
#ifndef Ch_CPP_ModelObject_h
#define Ch_CPP_ModelObject_h

#ifdef CRT

#include<string>
#include<map>
#include<vector>

#include<float.h>

#endif

#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChPtr.h"
#include"../../BasePack/Ch3D.h"

#include"../ChBaseObject/ChBaseObject.h"

#include"ChModel.h"


#ifndef CH_FRAME_SET_MATRIX_FUNCTION
#define CH_FRAME_SET_MATRIX_FUNCTION(_methodName,_matrixType) \
void _methodName##(const Ch3D::Transform& _trans){\
	_matrixType##.SetPosition(_trans.pos);\
	_matrixType##.SetRotation(_trans.rot);\
	_matrixType##.SetScalling(_trans.scl);\
}\
void _methodName##(const ChLMat& _mat) { _matrixType = _mat; }\
void _methodName##(const ChRMat& _mat) { _matrixType = _mat.GetConvertAxis(); }
#endif

#ifndef CH_FRAME_GET_MATRIX_FUNCTION
#define CH_FRAME_GET_MATRIX_FUNCTION(_RLType,_returnMethod) \
Ch##_RLType##Mat GetOutSizdTransform##_RLType##Mat() { return outSideMat##_returnMethod##; }\
Ch##_RLType##Mat GetFrameTransform##_RLType##Mat() { return frameMat##_returnMethod##; }\
Ch##_RLType##Mat GetDraw##_RLType##HandMatrix() { UpdateDrawTransform(); return drawMat##_returnMethod##; }
#endif

namespace ChCpp
{
	template<typename CharaType>
	class ModelLoaderBase;

	template<typename CharaType>
	struct TargetBoneData
	{
		struct TargetBoneDataCRT
		{
#ifdef CRT
			std::basic_string<CharaType> boneObjectName = ChStd::GetZeroChara<CharaType>();
#endif	
		};

		TargetBoneData();

		virtual ~TargetBoneData();

		TargetBoneDataCRT& ValueIns() { return *value; }

		ChLMat boneOffset;

	private:

		TargetBoneDataCRT* value = nullptr;
	};

	template<typename CharaType>
	struct FrameComponent:public ChCpp::BaseComponent
	{

		struct FrameComponentCRT
		{
#ifdef CRT
			std::vector<ChPtr::Shared<Ch3D::Primitive>> primitives;
			std::vector<ChPtr::Shared<Ch3D::MaterialData<CharaType>>>materialList;
			std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>> vertexList;
			std::vector<ChPtr::Shared<TargetBoneData<CharaType>>>boneDatas;
			std::map<std::basic_string<CharaType>, size_t>mateNames;
#endif
		};

		FrameComponent();

		virtual ~FrameComponent();

		FrameComponentCRT& ValueIns() { return *value; }

		ChVec3 maxPos = ChVec3((10e+37f) * -1.0f);
		ChVec3 minPos = ChVec3(10e+37f);
		ChVec3 centerPos = ChVec3();
		ChVec3 boxSize = ChVec3();

	private:

		FrameComponentCRT* value = nullptr;

	};

	template<typename CharaType>
	struct AnimationComponent:public ChCpp::BaseComponent
	{
		struct AnimationObject
		{
			Ch3D::Transform start;
			Ch3D::Transform end;
			float animationTime = 0;
		};

		struct AnimationComponentCRT
		{
#ifdef CRT
			std::vector<ChPtr::Shared<AnimationObject>>keyframeAnimation;

			std::basic_string<CharaType> animationName = ChStd::GetZeroChara<CharaType>();
#endif
		};

		AnimationComponent();
		
		virtual ~AnimationComponent();

		AnimationComponentCRT& ValueIns() { return *value; }

	private:
		AnimationComponentCRT* value = nullptr;

	};

	template<typename CharaType>
	struct NearPointData
	{
		ChVec3 toVector = ChVec3();

		struct NearPointDataCRT
		{
#ifdef CRT
			std::basic_string<CharaType> materialName = ChStd::GetZeroChara<CharaType>();
#endif
		};

		NearPointData();
		
		virtual ~NearPointData();

		NearPointDataCRT& ValueIns() { return *value; }

	private:

		NearPointDataCRT* value = nullptr;

	};

	template<typename CharaType>
	class FrameObject : public ChCpp::BaseObject<CharaType>
	{
	public:

		struct FrameObjectCRT
		{
#ifdef CRT
			std::basic_string<CharaType> animationName = ChStd::GetZeroChara<CharaType>();
#endif
		};

	public:

		FrameObject();

		virtual ~FrameObject();

	public://Set Functions//

		CH_FRAME_SET_MATRIX_FUNCTION(SetOutSizdTransform, outSideMat);

		CH_FRAME_SET_MATRIX_FUNCTION(SetFrameTransform, frameMat);

	public://Get Functions//


		CH_FRAME_GET_MATRIX_FUNCTION(L, );

		CH_FRAME_GET_MATRIX_FUNCTION(R, .GetConvertAxis());

	public:

#ifdef CRT
		static bool GetLenIsPointToPolyBoard(ChVec3& _outVector, const ChVec3& _point, Ch3D::Primitive& _prim, const std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>>& _vertexList, const float _maxLen = FLT_MAX, const ChLMat& _mat = ChLMat());

		static bool GetLenIsPointToPolyBoardFunction(ChVec3& _outVector, const ChVec3& _point, Ch3D::Primitive& _prim, const std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>>& _vertexList, const float _maxLen = FLT_MAX);

		void GetLenIsPointToPrimitive(std::vector<ChPtr::Shared<NearPointData<CharaType>>>& _res, const ChVec3& _point, const float _maxLen = FLT_MAX, const ChLMat& _mat = ChLMat());

		std::vector<ChPtr::Shared<NearPointData<CharaType>>> GetLenToPointAllChildTest(const ChVec3& _point, const float _maxLen = FLT_MAX, const ChLMat& _mat = ChLMat());
#endif

	private:

#ifdef CRT
		void GetLenToPointAllChildTest(std::vector<ChPtr::Shared<NearPointData<CharaType>>>& _outData, const ChVec3& _point, const float _maxLen = FLT_MAX, const ChLMat& _mat = ChLMat());
#endif

	public://Update Functions//

		void Update()override { UpdateDrawTransform(); }

		void UpdateDrawTransform();

		void UpdateAllDrawTransform();

#ifdef CRT
		void SetAnimationName(const std::basic_string<CharaType>& _name);
#endif

	public://Is Function//

	protected:

		ChLMat frameMat;
		ChLMat outSideMat;

	private:

		ChLMat drawMat;
		FrameObjectCRT* value = nullptr;
	};

	template<typename CharaType>
	class ModelObject :public FrameObject<CharaType>, public ChCp::Initializer
	{
	public:

		struct ModelObjectCRT
		{
#ifdef CRT
			std::vector<std::basic_string<CharaType>>animationNames;
			std::basic_string<CharaType> modelName = ChStd::GetZeroChara<CharaType>();
#endif
		};

	public:

		friend ModelLoaderBase<CharaType>;

	public:

		ModelObject();

		virtual ~ModelObject();

	public:

		inline void Init()override { SetInitFlg(true); }

		inline virtual void Release()override { SetInitFlg(false); }

	public:

		inline void SetShaderAxisType(const Ch3D::ShaderAxisType _type) { axisType = _type; }

#ifdef CRT
		void SetModelName(const std::basic_string<CharaType>& _name) { value->modelName = _name; }
#endif

	private:

		inline void SetMaxPos(const ChVec3& _pos) { maxPos = _pos; }

		inline void SetMinPos(const ChVec3& _pos) { minPos = _pos; }

		inline void SetCenterPos(const ChVec3& _pos) { centerPos = _pos; }

		inline void SetBoxSize(const ChVec3& _size) { boxSize = _size; }

	public:


#ifdef CRT
		inline std::basic_string<CharaType> GetModelName() { return value->modelName; }
#endif

		//初期化時に作成した全フレームの最大地点//
		inline ChVec3 GetInitAllFrameMaxPos() { return maxPos; }

		//初期化時に作成した全フレームの最小地点//
		inline ChVec3 GetInitAllFrameMinPos() { return minPos; }

		//初期化時に作成した全フレームの中央地点//
		inline ChVec3 GetInitAllFrameCenterPos() { return centerPos; }

		//初期化時に作成した全フレームの箱のサイズ//
		//CenterToTopLine And CenterToRightLine//
		inline ChVec3 GetInitAllFrameBoxSize() { return boxSize; }

	public:

#ifdef CRT
		void AddAnimationName(const std::basic_string<CharaType>& _name) { value->animationNames.push_back(_name); }
#endif
	public:

		virtual void Create(){}

	private:

		ChVec3 maxPos = ChVec3();
		ChVec3 minPos = ChVec3();
		ChVec3 centerPos = ChVec3();
		ChVec3 boxSize = ChVec3();

		Ch3D::ShaderAxisType axisType = Ch3D::ShaderAxisType::LeftHand;

		ModelObjectCRT* value = nullptr;
	};

}

#ifdef CRT

template<typename CharaType>
ChCpp::TargetBoneData<CharaType>::TargetBoneData()
{
	value = new TargetBoneDataCRT();
}

template<typename CharaType>
ChCpp::TargetBoneData<CharaType>::~TargetBoneData()
{
	delete value;
}

template<typename CharaType>
ChCpp::FrameComponent<CharaType>::FrameComponent()
{
	value = new FrameComponentCRT();
}

template<typename CharaType>
ChCpp::FrameComponent<CharaType>::~FrameComponent()
{
	delete value;
}

template<typename CharaType>
ChCpp::AnimationComponent<CharaType>::AnimationComponent()
{
	value = new AnimationComponentCRT();
}

template<typename CharaType>
ChCpp::AnimationComponent<CharaType>::~AnimationComponent()
{
	delete value;
}

template<typename CharaType>
ChCpp::NearPointData<CharaType>::NearPointData()
{
	value = new NearPointData();
}

template<typename CharaType>
ChCpp::NearPointData<CharaType>::~NearPointData()
{
	delete value;
}

template<typename CharaType>
ChCpp::FrameObject<CharaType>::FrameObject()
{
	value = new FrameObjectCRT();
}

template<typename CharaType>
ChCpp::FrameObject<CharaType>::~FrameObject()
{
	delete value;
}

template<typename CharaType>
bool ChCpp::FrameObject<CharaType>::GetLenIsPointToPolyBoard(ChVec3& _outVector, const ChVec3& _point, Ch3D::Primitive& _prim, const std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>>& _vertexList, const float _maxLen, const ChLMat& _mat)
{

	if (_prim.ValueIns().vertexData.size() <= 2)return false;
	std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>> vertexList;
	for (auto&& vertex : _vertexList)
	{
		auto ver = ChPtr::Make_S<Ch3D::SavePolyVertex>();
		*ver = *vertex;
		ver->pos = _mat.Transform(ver->pos);
		vertexList.push_back(ver);
	}

	return GetLenIsPointToPolyBoardFunction(_outVector, _point, _prim, vertexList, _maxLen);
}

template<typename CharaType>
bool ChCpp::FrameObject<CharaType>::GetLenIsPointToPolyBoardFunction(ChVec3& _outVector, const ChVec3& _point, Ch3D::Primitive& _prim, const std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>>& _vertexList, const float _maxLen)
{
	if (_prim.ValueIns().vertexData.size() <= 2)return false;

	auto&& vertexDataList = _prim.ValueIns().vertexData;

	ChVec3 firstPos = _vertexList[vertexDataList[0]->vertexNo]->pos;

	ChVec3 faceNormal = _vertexList[vertexDataList[1]->vertexNo]->pos - firstPos;
	faceNormal.SetCross(
		faceNormal,
		_vertexList[vertexDataList[vertexDataList.size() - 1]->vertexNo]->pos - firstPos);

	{
		ChVec3 testNormal = _point - firstPos;
		testNormal.Normalize();
		if (faceNormal.GetCos(faceNormal, testNormal) == 0.0f)return false;
	}

	float len = ChVec3::GetDot(faceNormal, _point - firstPos);

	if (len < 0.0f)return false;
	if (_maxLen < len)return false;

	ChVec3 tmpPoint = _point + (faceNormal * -len);

	bool onFaceFlg = true;

	ChVec3 tmpNormal = ChVec3::GetCross(
		firstPos - tmpPoint,
		_vertexList[vertexDataList[1]->vertexNo]->pos - tmpPoint);

	for (unsigned long i = 1; i < vertexDataList.size() - 1; i++)
	{
		if (tmpNormal == ChVec3::GetCross(
			firstPos - tmpPoint,
			_vertexList[vertexDataList[1]->vertexNo]->pos - tmpPoint))continue;

		onFaceFlg = false;
		break;
	}

	if (!onFaceFlg)return false;
	auto data = ChPtr::Make_S<NearPointData>();
	_outVector = faceNormal * -len;

	return true;
}

template<typename CharaType>
void ChCpp::FrameObject<CharaType>::GetLenIsPointToPrimitive(std::vector<ChPtr::Shared<NearPointData<CharaType>>>& _res, const ChVec3& _point, const float _maxLen, const ChLMat& _mat)
{
	auto&& com = ChCpp::BasicObject::GetComponent<FrameComponent<CharaType>>();

	if (com == nullptr)return;
	if (com->ValueIns().vertexList.size() <= 2)return;

	std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>> vertexList;
	{
		ChLMat tmpMat = _mat;
		tmpMat = GetDrawLHandMatrix() * tmpMat;

		for (auto&& vertex : com->ValueIns().vertexList)
		{
			auto ver = ChPtr::Make_S<Ch3D::SavePolyVertex>();
			*ver = *vertex;
			ver->pos = _mat.Transform(ver->pos);
			vertexList.push_back(ver);
		}
	}

	for (auto&& prim : com->ValueIns().primitives)
	{
		auto primitive = *prim;
		ChVec3 res;
		if (!GetLenIsPointToPolyBoardFunction(res, _point, primitive, vertexList, _maxLen))return;
		auto data = ChPtr::Make_S<NearPointData<CharaType>>();

		data->toVector = res;
		data->materialName = com->ValueIns().materialList[primitive.mateNo]->mateName;

		_res.push_back(data);
	}
	return;
}

template<typename CharaType>
std::vector<ChPtr::Shared<ChCpp::NearPointData<CharaType>>> ChCpp::FrameObject<CharaType>::GetLenToPointAllChildTest(const ChVec3& _point, const float _maxLen, const ChLMat& _mat)
{
	std::vector<ChPtr::Shared<NearPointData<CharaType>>> res;
	GetLenIsPointToPrimitive(res, _point, _maxLen, _mat);

	for (auto&& child : ChCpp::BasicObject::GetChildlen<FrameObject<CharaType>>())
	{
		if (child.expired())continue;

		child.lock()->GetLenToPointAllChildTest(res, _point, _maxLen, _mat);

	}
	return res;
}

template<typename CharaType>
void ChCpp::FrameObject<CharaType>::GetLenToPointAllChildTest(std::vector<ChPtr::Shared<NearPointData<CharaType>>>& _outData, const ChVec3& _point, const float _maxLen, const ChLMat& _mat)
{
	GetLenIsPointToPrimitive(_outData, _point, _maxLen, _mat);

	for (auto&& child : ChCpp::BasicObject::GetChildlen<FrameObject<CharaType>>())
	{
		if (child.expired())continue;
		child.lock()->GetLenToPointAllChildTest(_outData, _point, _maxLen, _mat);
	}
	return;
}

template<typename CharaType>
void ChCpp::FrameObject<CharaType>::UpdateDrawTransform()
{
	ChLMat parentDrawMat;

	{
		auto parent = ChPtr::SharedSafeCast<FrameObject>(ChCpp::BasicObject::GetParent().lock());

		if (parent != nullptr)
		{
			parentDrawMat = parent->drawMat;
		}
	}
	drawMat = outSideMat * frameMat * parentDrawMat;
}

template<typename CharaType>
void ChCpp::FrameObject<CharaType>::UpdateAllDrawTransform()
{
	ChLMat parentDrawMat;
	{
		auto parent = ChPtr::SharedSafeCast<FrameObject<CharaType>>(ChCpp::BasicObject::GetParent().lock());

		if (parent != nullptr)
		{
			parent->UpdateAllDrawTransform();
			parentDrawMat = parent->drawMat;
		}
	}
	drawMat = outSideMat * frameMat * parentDrawMat;
}

template<typename CharaType>
ChCpp::ModelObject<CharaType>::ModelObject()
{
	value = new ModelObjectCRT();
}

template<typename CharaType>
ChCpp::ModelObject<CharaType>::~ModelObject()
{ 
	Release();
	delete value;
}


#endif

#endif