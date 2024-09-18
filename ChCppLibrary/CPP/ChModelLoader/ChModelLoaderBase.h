
#ifndef Ch_CPP_MLBase_h
#define Ch_CPP_MLBase_h

#ifdef CRT

#include<string>

#endif

#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChPtr.h"

#include"../ChModel/ChModelObject.h"

namespace ChCpp
{
	template<typename CharaType>
	class ModelObject;

	template<typename CharaType>
	class FrameObject;

	template<typename CharaType>
	struct ModelFrame;

	template<typename CharaType>
	class ModelLoaderBase
	{

	protected:
		
		void Init();

	public:

#ifdef CRT
		virtual void CreateModel(ChPtr::Shared<ModelObject<CharaType>> _model, const std::basic_string<CharaType>& _filePath) = 0;

		virtual void OutModelFile(const ChPtr::Shared<ModelObject<CharaType>> _model, const std::basic_string<CharaType>& _filePath) = 0;
#endif
		friend ModelObject<CharaType>;
		friend FrameObject<CharaType>;

	protected:

		void SetMaxPos(ModelObject<CharaType>& _model, const ChVec3& _pos);

		void SetMinPos(ModelObject<CharaType>& _model, const ChVec3& _pos);

		void SetCenterPos(ModelObject<CharaType>& _model, const ChVec3& _pos);

		void SetBoxSize(ModelObject<CharaType>& _model, const ChVec3& _size);

	protected:

#ifdef CRT
		//カレントディレクトリからのルートパス取得//
		std::basic_string<CharaType> GetRoutePath(const std::basic_string<CharaType>& _filePath);
#endif
	protected:

		ChVec3 TestMaxPos(const ChVec3& _pos1, const ChVec3& _pos2);

		ChVec3 TestMinPos(const ChVec3& _pos1, const ChVec3& _pos2);

	protected:

		ChVec3 CreateCenterPos(const ChVec3& _min, const ChVec3& _max);

		//CenterToTopLine And CenterToRightLine//
		ChVec3 CreateBoxSize(const ChVec3& _min, const ChVec3& _max);

	protected:

		ChVec3 maxPos = ChVec3((10e+37f) * -1.0f);
		ChVec3 minPos = ChVec3(10e+37f);
	};
}

#ifdef CRT

template<typename CharaType>
void ChCpp::ModelLoaderBase<CharaType>::Init()
{
	maxPos = ChVec3((10e+37f) * -1.0f);
	minPos = ChVec3(10e+37f);
}

template<typename CharaType>
void ChCpp::ModelLoaderBase<CharaType>::SetMaxPos(ModelObject<CharaType>& _model, const ChVec3& _pos)
{
	_model.SetMaxPos(_pos);
}

template<typename CharaType>
void ChCpp::ModelLoaderBase<CharaType>::SetMinPos(ModelObject<CharaType>& _model, const ChVec3& _pos)
{
	_model.SetMinPos(_pos);
}

template<typename CharaType>
void ChCpp::ModelLoaderBase<CharaType>::SetCenterPos(ModelObject<CharaType>& _model, const ChVec3& _pos)
{
	_model.SetCenterPos(_pos);
}

template<typename CharaType>
void ChCpp::ModelLoaderBase<CharaType>::SetBoxSize(ModelObject<CharaType>& _model, const ChVec3& _size)
{
	_model.SetBoxSize(_size);
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::ModelLoaderBase<CharaType>::GetRoutePath(const std::basic_string<CharaType>& _filePath)
{

	if (_filePath.find(ChStd::GetYenChara<CharaType>()) == _filePath.find(ChStd::GetSlashChara<CharaType>()))return ChStd::GetZeroChara<CharaType>();

	std::basic_string<CharaType> tmpPath = ChStr::StrReplase<CharaType>(_filePath, ChStd::GetYenChara<CharaType>(), ChStd::GetSlashChara<CharaType>());

	unsigned long tmp = tmpPath.rfind(ChStd::GetSlashChara<CharaType>());

	return tmpPath.substr(0, tmp + 1);

}

template<typename CharaType>
ChVec3 ChCpp::ModelLoaderBase<CharaType>::TestMaxPos(const ChVec3& _pos1, const ChVec3& _pos2)
{
	ChVec3 res;

	res.x = _pos1.x >= _pos2.x ? _pos1.x : _pos2.x;
	res.y = _pos1.y >= _pos2.y ? _pos1.y : _pos2.y;
	res.z = _pos1.z >= _pos2.z ? _pos1.z : _pos2.z;

	return res;
}

template<typename CharaType>
ChVec3 ChCpp::ModelLoaderBase<CharaType>::TestMinPos(const ChVec3& _pos1, const ChVec3& _pos2)
{
	ChVec3 res;

	res.x = _pos1.x <= _pos2.x ? _pos1.x : _pos2.x;
	res.y = _pos1.y <= _pos2.y ? _pos1.y : _pos2.y;
	res.z = _pos1.z <= _pos2.z ? _pos1.z : _pos2.z;

	return res;
}

template<typename CharaType>
ChVec3 ChCpp::ModelLoaderBase<CharaType>::CreateCenterPos(const ChVec3& _min, const ChVec3& _max)
{
	return  (_min + _max) / 2.0f;
}

template<typename CharaType>
ChVec3 ChCpp::ModelLoaderBase<CharaType>::CreateBoxSize(const ChVec3& _min, const ChVec3& _max)
{
	return (_max - _min) / 2.0f;
}

#endif

#endif