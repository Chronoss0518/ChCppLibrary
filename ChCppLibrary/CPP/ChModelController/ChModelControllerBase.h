
#ifndef Ch_CPP_MLBase_h
#define Ch_CPP_MLBase_h

#include<string>

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
	std::basic_string<CharaType> GetConvertText(const std::string& _str);

	template<typename CharaType>
	std::basic_string<CharaType> GetConvertText(const std::wstring& _str);

	template<typename CharaType>
	class ModelControllerBase
	{

	protected:
		
		inline void Init()
		{
			maxPos = ChVec3((10e+37f) * -1.0f);
			minPos = ChVec3(10e+37f);
		}

	public:

		virtual void LoadModel(const std::basic_string<CharaType>& _filePath) = 0;

		virtual void OutModel(const std::basic_string<CharaType>& _filePath) = 0;

		virtual void CreateModel(ChPtr::Shared<ModelObject<CharaType>> _model) = 0;

		virtual void SetModel(const ChPtr::Shared<ModelObject<CharaType>> _model) = 0;

		friend ModelObject<CharaType>;
		friend FrameObject<CharaType>;

	protected:

		inline void SetMaxPos(ModelObject<CharaType>& _model, const ChVec3& _pos) { _model.SetMaxPos(_pos); }

		inline void SetMinPos(ModelObject<CharaType>& _model, const ChVec3& _pos) { _model.SetMinPos(_pos); }

		inline void SetCenterPos(ModelObject<CharaType>& _model, const ChVec3& _pos) { _model.SetCenterPos(_pos); }

		inline void SetBoxSize(ModelObject<CharaType>& _model, const ChVec3& _size) { _model.SetBoxSize(_size); }

	protected:

		//カレントディレクトリからのルートパス取得//
		inline std::basic_string<CharaType> GetRoutePath(const std::basic_string<CharaType>& _filePath)
		{

			if (_filePath.find(ChStd::GetYenChara<CharaType>()) == _filePath.find(ChStd::GetSlashChara<CharaType>()))return ChStd::GetZeroChara<CharaType>();

			std::basic_string<CharaType> tmpPath = ChStr::StrReplase<CharaType>(_filePath, ChStd::GetYenChara<CharaType>(), ChStd::GetSlashChara<CharaType>());

			size_t tmp = tmpPath.rfind(ChStd::GetSlashChara<CharaType>());

			return tmpPath.substr(0, tmp + 1);
		}

	protected:

		inline ChVec3 TestMaxPos(const ChVec3& _pos1, const ChVec3& _pos2)
		{
			ChVec3 res;

			res.x = _pos1.x >= _pos2.x ? _pos1.x : _pos2.x;
			res.y = _pos1.y >= _pos2.y ? _pos1.y : _pos2.y;
			res.z = _pos1.z >= _pos2.z ? _pos1.z : _pos2.z;

			return res;
		}

		inline ChVec3 TestMinPos(const ChVec3& _pos1, const ChVec3& _pos2)
		{
			ChVec3 res;

			res.x = _pos1.x <= _pos2.x ? _pos1.x : _pos2.x;
			res.y = _pos1.y <= _pos2.y ? _pos1.y : _pos2.y;
			res.z = _pos1.z <= _pos2.z ? _pos1.z : _pos2.z;

			return res;
		}

	protected:

		inline ChVec3 CreateCenterPos(const ChVec3& _min, const ChVec3& _max) { return  (_min + _max) / 2.0f; }

		//CenterToTopLine And CenterToRightLine//
		inline ChVec3 CreateBoxSize(const ChVec3& _min, const ChVec3& _max) { return (_max - _min) / 2.0f; }

	protected:

		ChVec3 maxPos = ChVec3((10e+37f) * -1.0f);
		ChVec3 minPos = ChVec3(10e+37f);
	};
}

#endif