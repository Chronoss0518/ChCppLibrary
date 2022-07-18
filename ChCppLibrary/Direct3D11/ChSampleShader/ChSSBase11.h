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

			void Release()override;

		protected:

			void InitBaseMesh(ID3D11Device* _device);

			void InitBasePolygonBoard(ID3D11Device* _device);

			void InitBaseSprite(ID3D11Device* _device);

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


		private://Init Functions//

			void InitVBaseMesh(ID3D11Device* _device);
			void InitVBasePobo(ID3D11Device* _device);
			void InitPBasePolygon(ID3D11Device* _device);

			void InitVBaseSprite(ID3D11Device* _device);
			void InitPBaseSprite(ID3D11Device* _device);

		};
	}
}

#endif