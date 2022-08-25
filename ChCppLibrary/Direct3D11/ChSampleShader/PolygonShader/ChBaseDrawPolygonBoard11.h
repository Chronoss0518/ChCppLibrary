#ifndef Ch_D3D11_SS_BasePoBo_h
#define Ch_D3D11_SS_BasePoBo_h

#include"../ChSampleShaderBase11.h"


namespace ChD3D11
{

	class PolygonBoard11;


	namespace Shader
	{

		class BaseDrawPolygonBoard11 final :public SampleShaderBase11
		{
		public://Init And Release//

			void Init(ID3D11Device* _device);

			void Release();

		protected://Init And Release//

			void InitVertexShader()override;

			void InitPixelShader()override;

		public://Set Functions//

			void SetProjectionMatrix(const ChLMat& _mat);

			void SetViewMatrix(const ChLMat& _mat);

			void SetFillMode(const D3D11_FILL_MODE _fill);

			void SetCullMode(const D3D11_CULL_MODE _cull);

			void SetShaderDrawData(ID3D11DeviceContext* _dc);

			void SetShaderCharaData(ID3D11DeviceContext* _dc);

		public://Get Functions//

			inline D3D11_FILL_MODE GetFillMode() { return fill; }

			inline D3D11_CULL_MODE GetCullMode() { return cull; }

			inline ChLMat GetViewMatrix() { return polyData.GetViewMatrix(); }

			inline ChLMat GetProjectionMatrix() { return polyData.GetProjectionMatrix(); }

		public://Other Functions//

			void DrawStart(ID3D11DeviceContext* _dc)override;

			void Draw(
				ID3D11DeviceContext* _dc,
				TextureBase11& _tex,
				PolygonBoard11& _polygon,
				const ChMat_11& _mat = ChMat_11());

		private:

			void Update()override;

		private://Member Value//

			CB::CBPolygon11 polyData;

			Ch3D::PolyVertex drawVertexs[3];

			VertexBuffer11<Ch3D::PolyVertex> vertexBuffer;
			IndexBuffer11 indexBuffer;

			D3D11_FILL_MODE fill = D3D11_FILL_MODE::D3D11_FILL_SOLID;
			D3D11_CULL_MODE cull = D3D11_CULL_MODE::D3D11_CULL_NONE;
			ChStd::Bool updateFlg = true;


		};
	}
}



#endif