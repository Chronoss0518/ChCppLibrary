#ifndef Ch_D3D11_CB_BasicShapes_h
#define Ch_D3D11_CB_BasicShapes_h

#include"../ChCBBase11.h"
#include"../../ChSampleShader/SpriteShader/Shader/BasicShapesPosition.hlsli"
#include"../../ChSampleShader/SpriteShader/Shader/BasicShapesCircle.hlsli"

namespace ChD3D11
{
	namespace CB
	{
		class CBBasicShapes11 final :public CBBase11
		{
		public:

			virtual ~CBBasicShapes11()
			{
				Release();
			}

		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init(
				ID3D11Device* _device);

			void Release()override;

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetSpriteMatrix(const ChLMat& _mat);

			void SetColor(const ChVec4& _color);

			void SetBasicShapesData(const BasicShapesData& _data);

			void SetPSBasicShapesData(ID3D11DeviceContext* _dc);

			void SetVSBasicShapesData(ID3D11DeviceContext* _dc);

			void SetShaderBasicShapesData(ID3D11DeviceContext* _dc);

			void SetShaderTexture(ID3D11DeviceContext* _dc);

			///////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			inline BasicShapesData GetSpriteData() { return bsData; }

			inline ChLMat GetSpriteMatrix() { return bsData.spriteMat; }

			inline ChVec4 GetColor() { return bsData.color; }

		private:

			void UpdateSD(ID3D11DeviceContext* _dc);

			BasicShapesData bsData;
			ConstantBuffer11<BasicShapesData> bsBuf;
			bool bsUpdateFlg = true;

		};

		class CBBasicShapesPosition11 final :public CBBase11
		{
		public:

			virtual ~CBBasicShapesPosition11()
			{
				Release();
			}

		public:

			void Init(
				ID3D11Device* _device);

			void Release()override;

		public:

			void SetPosition(const ChVec2& _position,int _no);

			void SetPSBasicShapesPositionData(ID3D11DeviceContext* _dc);

			void SetVSBasicShapesPositionData(ID3D11DeviceContext* _dc);

			void SetShaderBasicShapesPositionData(ID3D11DeviceContext* _dc);
		
		public:

			inline BasicShapesPositionData GetBasicShapesPositionData() { return positionData; }

			inline ChBasicShapesPositions GetPositions()
			{
				return positionData.positions;
			}

			inline int GetUsePositionCount()
			{
				return positionData.positions.usePositionCount;
			}

		public:

			void AddPosition(const ChVec2& _position);

		public:

			void PopPosition();

		public:

			void ClearPosition();

		private:

			void UpdateSD(ID3D11DeviceContext* _dc);

			BasicShapesPositionData positionData;
			ConstantBuffer11<BasicShapesPositionData> positionBuf;
			bool updateFlg = true;

		};

		class CBBasicShapesCircle11 final :public CBBase11
		{
		public:

			virtual ~CBBasicShapesCircle11()
			{
				Release();
			}

		public:

			void Init(
				ID3D11Device* _device);

			void Release()override;

		public:

			void SetCenterPosition(const ChVec2& _centerPos, int _no);

			void SetSize(float _size,int _no);

			void SetPSBasicShapesCircleData(ID3D11DeviceContext* _dc);

			void SetVSBasicShapesCircleData(ID3D11DeviceContext* _dc);

			void SetShaderBasicShapesCircleData(ID3D11DeviceContext* _dc);

		public:

			inline BasicShapesCircleData GetSpriteData() { return circleData; }

			inline int GetUseCircleCount() { return circleData.circleDatas.usePositionCount; }

		public:

			void AddCircleData(const ChVec2& _centerPos, float _size);

		public:

			void PopCircleData();

		public:

			void ClearCircleData();

		private:

			void UpdateSD(ID3D11DeviceContext* _dc);

			BasicShapesCircleData circleData;
			ConstantBuffer11<BasicShapesCircleData> circleBuf;
			bool updateFlg = true;

		};

	}

}


#endif
