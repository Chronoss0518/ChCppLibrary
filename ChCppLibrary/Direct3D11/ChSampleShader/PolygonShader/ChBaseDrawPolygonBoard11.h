#ifndef Ch_D3D11_SS_BasePoBo_h
#define Ch_D3D11_SS_BasePoBo_h

#include"ChSamplePolygonShaderBase11.h"


namespace ChD3D11
{

	class PolygonBoard11;


	namespace Shader
	{

		class BaseDrawPolygonBoard11 final :public SamplePolygonShaderBase11
		{
		public:

			virtual ~BaseDrawPolygonBoard11()
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
				TextureBase11& _tex,
				PolygonBoard11& _polygon,
				const ChMat_11& _mat = ChMat_11());

		private:

			void Update(ID3D11DeviceContext* _dc)override;

		private://Member Value//

			Ch3D::PolyVertex drawVertexs[3];

			VertexBuffer11<Ch3D::PolyVertex> vertexBuffer;
			IndexBuffer11 indexBuffer;


		};
	}
}



#endif