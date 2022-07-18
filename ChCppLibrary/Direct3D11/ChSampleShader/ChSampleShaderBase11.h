#ifndef Ch_D3D11_SSBase_h
#define Ch_D3D11_SSBase_h

#include"../ChShaderObject/ChShaderObject11.h"

namespace ChD3D11
{
	namespace Shader
	{

		class SampleShaderBase11:public ChCp::Releaser
		{
		public://Init And Release//

			void Init(ID3D11Device* _device);

			void Release()override;

		protected://Init And Release//

			void InitBaseMesh();

			void InitBasePolygonBoard();

			void InitBaseSprite();

		protected://Get Functions//

			void SetShaderRasteriser(ID3D11DeviceContext* _dc);

		protected://Get Instance Functions//

			inline VertexShader11& GetVBaseMesh()
			{
				static VertexShader11 ins;
				return ins;
			}

			inline VertexShader11& GetVBasePobo()
			{
				static VertexShader11 ins;
				return ins;
			}

			inline PixelShader11& GetPBasePolygon()
			{
				static PixelShader11 ins;
				return ins;
			}

			inline VertexShader11& GetVBaseSprite()
			{
				static VertexShader11 ins;
				return ins;
			}

			inline PixelShader11& GetPBaseSprite()
			{
				static PixelShader11 ins;
				return ins;
			}

		protected://Other Functions//

			void CreateRasteriser(const D3D11_RASTERIZER_DESC& _desc);

		private://Init Functions//

			void InitVBaseMesh(ID3D11Device* _device);
			void InitVBasePobo(ID3D11Device* _device);
			void InitPBasePolygon(ID3D11Device* _device);

			void InitVBaseSprite(ID3D11Device* _device);
			void InitPBaseSprite(ID3D11Device* _device);

		private://Member Value//

			ID3D11RasterizerState* rasteriser = nullptr;
			ID3D11Device* device = nullptr;

		};
	}
}

#endif