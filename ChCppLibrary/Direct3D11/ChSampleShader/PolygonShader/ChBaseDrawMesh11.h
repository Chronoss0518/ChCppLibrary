#ifndef Ch_D3D11_SS_BaseMesh_h
#define Ch_D3D11_SS_BaseMesh_h

#include"ChSamplePolygonShaderBase11.h"

namespace ChCpp
{
	class BaseObject;
	struct FrameComponent;
}


namespace ChD3D11
{

	class Mesh11;

	namespace Shader
	{

		class BaseDrawMesh11 final :public SamplePolygonShaderBase11
		{
			struct DrawData
			{
				ChLMat worldMatrix;
				ChLMat frameMatrix;
				FrameComponent11* drawFrame = nullptr;
			};

		public:

			virtual ~BaseDrawMesh11()
			{
				Release();
			}

		public://Init And Release//

			void Init(ID3D11Device* _device)override;

			void Release()override;

		protected://Init And Release//

			void InitVertexShader()override;

			void InitPixelShader()override;

		public://Other Functions//

			void DrawStart(ID3D11DeviceContext* _dc)override;

			void Draw(
				Mesh11& _mesh,
				const ChMat_11& _mat = ChMat_11());

			void DrawEnd()override;

		private:

			void DrawUpdate(ChCpp::FrameObject& _object);

			void DrawMain(ChCpp::FrameObject& _object);

			void Update(ID3D11DeviceContext* _dc)override;

		private://Member Value//

			CB::CBBone11 boneData;

			ChLMat worldMat;

			std::map<ChCpp::FrameComponent*,std::vector<ChPtr::Shared<DrawData>>>drawDatas;

		};
	}
}



#endif