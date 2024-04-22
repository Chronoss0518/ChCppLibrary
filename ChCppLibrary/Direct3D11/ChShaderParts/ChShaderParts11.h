#ifndef Ch_D3D11_SParts_h
#define Ch_D3D11_SParts_h

namespace ChD3D11
{
	namespace ShaderParts
	{
		class ViewPort final
		{

		public:

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			inline void SetTopLeftPos(const ChVec2& _Pos) { View.TopLeftX = _Pos.x; View.TopLeftY = _Pos.y; }

			inline void SetSize(const ChVec2& _Size) { View.Width = _Size.x; View.Height = _Size.y; }

			inline void SetDrawDepth(const float _Min,const float _Max) { View.MinDepth = _Min; View.MaxDepth = _Max; }

			void SetDrawData(ID3D11DeviceContext* _DC);

			///////////////////////////////////////////////////////////////////////////////////

		private:

			D3D11_VIEWPORT View = D3D11_VIEWPORT();

		};

		class DrawWindow final:public ChCp::Initializer
		{

		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init(
				ID3D11Device* _device
				,IDXGISwapChain* _sc);
			
			void Init(ChD3D11::DirectX3D11& _app);

			void Release();

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetSwapEffect(const DXGI_SWAP_EFFECT& _effect) { sEffect = _effect; }

			void SetDrawData(ID3D11DeviceContext* _dc, ID3D11DepthStencilView* _dsView = nullptr);

			///////////////////////////////////////////////////////////////////////////////////

			void SetBackGroundColor(ID3D11DeviceContext* _dc,const ChVec4& _color);

			///////////////////////////////////////////////////////////////////////////////////

			void Draw();

			///////////////////////////////////////////////////////////////////////////////////


		private:

			IDXGISwapChain* window = nullptr;

			//�`���Ƀo�b�N�o�b�t�@���������铙�̃t���O�����g//
			DXGI_SWAP_EFFECT sEffect = DXGI_SWAP_EFFECT_DISCARD;

			//�`��p//
			ID3D11RenderTargetView* bbTargetView = nullptr;
		};

	}

}


#endif
