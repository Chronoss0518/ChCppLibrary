#ifndef Ch_D3D11_Sprite_h
#define Ch_D3D11_Sprite_h

#include"../ChShaderStructures11.h"

namespace ChD3D11
{

	enum class SpritePositionName : unsigned char
	{
		LeftTop,RightTop,RightDown, LeftDown
	};

	class Sprite11 :public ShaderObject<Vertex11>
	{

	public:

		Sprite11& operator=(const Sprite11& _sp)
		{
			for (unsigned char i = 0; i < 4; i++)
			{
				vertexs[i].pos = _sp.vertexs[i].pos;
				vertexs[i].uvPos = _sp.vertexs[i].uvPos;
				vertexs[i].color = _sp.vertexs[i].color;
			}

			return *this;

		}

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init();

		void Init(ID3D11Device* _device);

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPos(const SpritePositionName _posNames, const  ChVec2& _posData)
		{
			SetPos(ChStd::EnumCast(_posNames), _posData);
		}

		void SetPos(const unsigned char _posNames, const  ChVec2& _posData);

		inline void SetUV(const SpritePositionName _posNames, const ChVec2& _posData)
		{
			SetUV(ChStd::EnumCast(_posNames), _posData);
		}

		void SetUV(const unsigned char _posNames, const  ChVec2& _posData);

		inline void SetColor(const SpritePositionName _posNames, const ChVec4& _color)
		{
			SetUV(ChStd::EnumCast(_posNames), _color);
		}

		void SetColor(const unsigned char _posNames, const  ChVec4& _color);

		void SetInitPos();

		void SetInitUV();

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//


		inline ChVec2 GetPos(const SpritePositionName _posNames)
		{
			return vertexs[ChStd::EnumCast(_posNames)].pos;
		}

		inline ChVec2 GetPos(const unsigned char _num)
		{
			if (_num >= 4)return ChVec2();

			return vertexs[_num].pos;
		}

		inline ChVec2 GetUV(const SpritePositionName _posNames)
		{
			return vertexs[ChStd::EnumCast(_posNames)].uvPos;
		}

		ChVec2 GetUV(const unsigned char _num)
		{
			if (_num >= 4)return ChVec2();

			return vertexs[_num].uvPos;
		}

		inline ChVec4 GetColor(const SpritePositionName _posNames)
		{
			return vertexs[ChStd::EnumCast(_posNames)].color;
		}

		ChVec4 GetColor(const unsigned char _num)
		{
			if (_num >= 4)return ChVec4();

			return vertexs[_num].color;
		}

		///////////////////////////////////////////////////////////////////////////////////
		
		inline void Move(const ChVec2& _vec) { Move(_vec.x, _vec.y); }

		void Move(const float _x,const float _y);

		inline void MoveX(const float _x) { Move(_x, 0.0f); }

		inline void MoveY(const float _y) { Move(0.0f, _y); }

		///////////////////////////////////////////////////////////////////////////////////

		void SetDrawData(ID3D11DeviceContext* _dc)override;

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		Vertex11 vertexs[4];
		IndexBuffer11 indexBuf;
		VertexBuffer11<Vertex11>vertexBuf;


		PrimitiveData11<Vertex11> primitives;

	};

}

#endif