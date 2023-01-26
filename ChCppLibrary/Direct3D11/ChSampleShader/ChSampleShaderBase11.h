#ifndef Ch_D3D11_SSBase_h
#define Ch_D3D11_SSBase_h

#include"../ChShaderObject/ChShaderObject11.h"

namespace ChD3D11
{
	class Texture11;

	namespace Shader
	{

		class SampleShaderBase11:public ChCp::Releaser, public ChCp::Initializer
		{
		public://Init And Release//

			void Init(ID3D11Device* _device);

			void Release()override;

		protected://Init And Release//

			virtual void InitVertexShader() = 0;

			virtual void InitPixelShader() = 0;
			
			virtual void InitGeometryShader() {};

			virtual void InitHullShader() {};

			virtual void InitDomainShader() {};

			virtual void InitComputeShader() {};

		protected://Create Shader Functions//

			void CreateVertexShader(
				const D3D11_INPUT_ELEMENT_DESC* _decl,
				unsigned long _declNum,
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum);

			void CreatePixelShader(
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum);

			void CreateGeometryShader(
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum);

			void CreateHullShader(
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum);

			void CreateDomainShader(
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum);

			void CreateComputeShader(
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum);

		protected://Create Functions//

			void CreateRasteriser(const D3D11_RASTERIZER_DESC& _desc);

			void CreateBlender(const D3D11_BLEND_DESC& _desc);

		public://Set Functions//

			void SetShader(ID3D11DeviceContext* _dc);

		protected://Set Functions//

			void SetShaderRasteriser(ID3D11DeviceContext* _dc);

			void SetShaderBlender(ID3D11DeviceContext* _dc);

			void SetShaderDefaultBlender(ID3D11DeviceContext* _dc);

		protected://Get Functions//

			inline Texture11& GetWhiteTexture() { return *whiteTex; }

			inline Texture11& GetNormalTexture() { return *normalTex; }

			ID3D11Device* GetDevice() { return device; }

		private://Get Functions//

			inline static ChStd::Bool& GetShaderNowRunFlg()
			{
				static ChStd::Bool flg;
				return flg;
			}

		protected://Is Functions//

			ChStd::Bool IsDraw()const { return drawFlg; }

		public://Other Functions//

			virtual void DrawStart(ID3D11DeviceContext* _dc);

			virtual inline void DrawEnd() 
			{
				if (!drawFlg)return;
				drawFlg = false; 
				GetShaderNowRunFlg() = false;
			}

			virtual void Update(ID3D11DeviceContext* _dc) {};

		private://Member Value//

			ID3D11RasterizerState* rasteriser = nullptr;
			ID3D11Device* device = nullptr;

			VertexShader11 vs;
			GeometryShader11 gs;
			HullShader11 hs;
			DomainShader11 ds;
			PixelShader11 ps;
			ComputeShader11 cs;

			ChPtr::Unique<Texture11> whiteTex;
			ChPtr::Unique<Texture11> normalTex;

			ChStd::Bool drawFlg;

			ID3D11BlendState* blender = nullptr;

		};
	}
}

#endif