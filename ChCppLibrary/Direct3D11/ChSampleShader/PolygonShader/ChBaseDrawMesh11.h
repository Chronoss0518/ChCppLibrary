#ifndef Ch_D3D11_SS_BaseMesh_h
#define Ch_D3D11_SS_BaseMesh_h

#include"../ChSampleShaderBase11.h"

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

		class BaseDrawMesh11 final :public SampleShaderBase11
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

			void Init(ID3D11Device* _device);

			void Release()override;

		protected://Init And Release//

			void InitVertexShader()override;

			void InitPixelShader()override;

		public://Set Functions//

			void SetProjectionMatrix(const ChLMat& _mat);

			void SetViewMatrix(const ChLMat& _mat);
			
			void SetFillMode(const D3D11_FILL_MODE _fill);
			
			void SetCullMode(const D3D11_CULL_MODE _cull);

		public://Get Functions//

			inline ChLMat GetProjectionMatrix() { return polyData.GetProjectionMatrix(); }

			inline ChLMat GetViewMatrix() { return polyData.GetViewMatrix(); }
			
			inline D3D11_FILL_MODE GetFillMode() { return fill; }

			inline D3D11_CULL_MODE GetCullMode() { return cull; }

		public://Other Functions//

			void DrawStart(ID3D11DeviceContext* _dc)override;

			void Draw(
				ID3D11DeviceContext* _dc,
				Mesh11& _mesh,
				const ChMat_11& _mat = ChMat_11());

			void DrawEnd()override;

		private:

			void DrawUpdate(
				ID3D11DeviceContext* _dc,
				ChCpp::FrameObject& _object);

			void DrawMain(
				ID3D11DeviceContext* _dc,
				ChCpp::FrameObject& _object);

			void Update(ID3D11DeviceContext* _dc)override;

		private://Member Value//

			CB::CBPolygon11 polyData;
			CB::CBBone11 boneData;

			ChLMat worldMat;

			D3D11_FILL_MODE fill = D3D11_FILL_MODE::D3D11_FILL_SOLID;
			D3D11_CULL_MODE cull = D3D11_CULL_MODE::D3D11_CULL_NONE;
			bool updateFlg = true;

			std::map<ChCpp::FrameComponent*,std::vector<ChPtr::Shared<DrawData>>>drawDatas;
			ID3D11DeviceContext* dc = nullptr;

		};
	}
}



#endif