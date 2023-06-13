#ifndef Ch_D3D11_CB_Bone_h
#define Ch_D3D11_CB_Bone_h

#include"../ChCBBase11.h"
#include"../../../ShaderHeaderFiles/HLSL/5.0/BoneBlending.hlsli"

namespace ChD3D11
{
	namespace CB
	{

		class CBBone11 final :public CBBase11
		{
		public:

			virtual ~CBBone11()
			{
				Release();
			}

		public:

			void Init(ID3D11Device* _device);

			void Release()override;

		public://Set Functions//

			void SetBoneObjectDrawMatrix(const ChLMat& _mat,const unsigned long _no);

			void SetBoneOffsetMatrix(const ChLMat& _mat,const unsigned long _no);

			void SetPSDrawData(ID3D11DeviceContext* _dc);

			void SetVSDrawData(ID3D11DeviceContext* _dc);

			void SetDrawData(ID3D11DeviceContext* _dc);

		public://Get Functions//



		private:

			void Update(ID3D11DeviceContext* _dc);

			ChBoneData bone;
			ConstantBuffer11<ChBoneData> buf;
			bool updateFlg = true;


		};

	}

}


#endif
