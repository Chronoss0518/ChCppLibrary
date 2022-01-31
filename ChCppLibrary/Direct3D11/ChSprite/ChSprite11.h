#ifndef Ch_D3D11_Sprite_h
#define Ch_D3D11_Sprite_h

#include"../ChShaderStructures11.h"

namespace ChD3D11
{
	struct SpriteVertex
	{
		ChVec2 pos;
		ChVec2 uv;
		ChVec4 color = ChVec4(1.0f);
	};

	struct SpriteVertexBuffer
	{
		SpriteVertex vertexs[4];
	};

	enum class SpritePositionName : unsigned char
	{
		LeftTop, RightTop, RightDown, LeftDown
	};

	class Sprite11 :public DrawObject
	{

	public:

		Sprite11& operator=(const Sprite11& _sp)
		{
			for (unsigned char i = 0; i < 4; i++)
			{
				vertexDatas.vertexs[i] = _sp.vertexDatas.vertexs[i];
			}

			return *this;

		}

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init();

		void Init(ID3D11Device* _device);

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPos(const SpritePositionName _posNames, const  ChVec2& _posData)
		{
			SetPos(ChStd::EnumCast(_posNames), _posData);
		}

		void SetPos(const unsigned char _posNames, const  ChVec2& _posData);

		inline void SetUVPos(const SpritePositionName _posNames, const ChVec2& _posData)
		{
			SetUVPos(ChStd::EnumCast(_posNames), _posData);
		}

		void SetUVPos(const unsigned char _posNames, const  ChVec2& _posData);

		inline void SetColor(const SpritePositionName _posNames, const  ChVec4& _colorData)
		{
			SetColor(ChStd::EnumCast(_posNames), _colorData);
		}

		void SetColor(const unsigned char _posNames, const  ChVec4& _colorData);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//


		inline ChVec2 GetPos(const SpritePositionName _posNames)
		{
			return GetPos(ChStd::EnumCast(_posNames));
		}

		inline ChVec2 GetPos(const unsigned char _num)
		{
			if (_num >= 4)return ChVec2();

			return vertexDatas.vertexs[_num].pos;
		}

		inline ChVec2 GetUVPos(const SpritePositionName _posNames)
		{
			return GetUVPos(ChStd::EnumCast(_posNames));
		}

		inline ChVec2 GetUVPos(const unsigned char _num)
		{
			if (_num >= 4)return ChVec2();

			return vertexDatas.vertexs[_num].uv;
		}

		inline ChVec4 GetColor(const SpritePositionName _posNames)
		{
			return GetColor(ChStd::EnumCast(_posNames));
		}

		inline ChVec4 GetColor(const unsigned char _num)
		{
			if (_num >= 4)return ChVec2();

			return vertexDatas.vertexs[_num].color;
		}

		///////////////////////////////////////////////////////////////////////////////////

		inline void Move(const ChVec2& _vec) { Move(_vec.x, _vec.y); }

		void Move(const float _x, const float _y);

		inline void MoveX(const float _x) { Move(_x, 0.0f); }

		inline void MoveY(const float _y) { Move(0.0f, _y); }

		///////////////////////////////////////////////////////////////////////////////////

		void SetDrawData(ID3D11DeviceContext* _dc);

		void SetDrawData(ID3D11DeviceContext* _dc, const SpriteVertexBuffer& _vertexs);

		void SetInitPos();

		void SetInitUV();

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		unsigned long vertexNos[4] = { 0,1,2,3 };
		unsigned long indexNums[6] = { 0,1,2,0,2,3 };

		IndexBuffer11 indexBuffer;
		VertexBuffer11<unsigned long> vertexBuffer;
		SpriteVertexBuffer vertexDatas;
		ConstantBuffer11<SpriteVertexBuffer>constantBuffer;
	};

}

#endif