
#ifndef Ch_CPP_MLBase_h
#define Ch_CPP_MLBase_h

namespace ChCpp
{
	class ModelObject;
	class FrameObject;
	class ModelObject;
	struct ModelFrame;

	class ModelLoaderBase
	{

	public:


		///////////////////////////////////////////////////////////////////////////////////////

		virtual void CreateModel(ChPtr::Shared<ModelObject> _model, const std::string& _filePath) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		virtual void OutModelFile(const ChPtr::Shared<ModelObject> _model, const std::string& _filePath) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		friend ModelObject;
		friend FrameObject;

	protected:

		void SetPosition(Ch3D::Position* _pos, ChVec3 _val);

		void SetPosition(Ch3D::UV* _uv, ChVec2 _val);

		void SetPosition(Ch3D::Color* _col, ChVec4 _val);

		void SetPosition(Ch3D::Normal* _normal, ChVec3 _val);

		void SetPosition(Ch3D::FaceNormal* _faceNormal, ChVec3 _val);

		//カレントディレクトリからのルートパス取得//
		std::string GetRoutePath(const std::string& _filePath);

	private:

	};
}


#endif