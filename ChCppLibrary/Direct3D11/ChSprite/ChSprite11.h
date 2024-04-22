#ifndef Ch_D3D11_Sprite_h
#define Ch_D3D11_Sprite_h

#include"../ChShaderStructures11.h"

namespace ChD3D11
{

	enum class SpritePositionName : unsigned char
	{
		LeftTop,RightTop,RightBottom, LeftBottom
	};

	class Sprite11
	{

	public:

		Sprite11& operator=(const Sprite11& _sp)
		{
			for (unsigned char i = 0; i < vertexs.size(); i++)
			{
				vertexs[i].pos = _sp.vertexs[i].pos;
				vertexs[i].color = _sp.vertexs[i].color;
				vertexs[i].uv = _sp.vertexs[i].uv;
			}

			return *this;

		}

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPos(const SpritePositionName _posNames, const  ChVec2& _posData)
		{
			SetPos(ChStd::EnumCast(_posNames), _posData);
		}

		void SetPos(const unsigned char _posNames, const  ChVec2& _posData);

		void SetPosRect(const  ChVec4& _rect);

		inline void SetUVPos(const SpritePositionName _posNames, const ChVec2& _posData)
		{
			SetUVPos(ChStd::EnumCast(_posNames), _posData);
		}

		//UVPosはスクリーン座標系で計算されます//
		void SetUVPos(const unsigned char _posNames, const  ChVec2& _posData);

		//UVPosはスクリーン座標系で計算されます//
		void SetUVPosRect(const  ChVec4& _rect);

		void SetInitPosition();

		void SetInitUV();

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline const std::array<Ch3D::Vertex, 4>& GetVertexs() { return vertexs; }

		inline ChVec2 GetPos(const SpritePositionName _posNames)const
		{
			return GetPos(ChStd::EnumCast(_posNames));
		}

		inline ChVec2 GetPos(const unsigned char _num)const
		{
			if (_num >= vertexs.size())return ChVec2();

			return vertexs[_num].pos;
		}

		inline ChVec4 GetPosRect()const
		{
			ChVec4 res;
			res.left = vertexs[ChStd::EnumCast(SpritePositionName::LeftTop)].pos.x;
			res.top = vertexs[ChStd::EnumCast(SpritePositionName::LeftTop)].pos.y;
			res.right = vertexs[ChStd::EnumCast(SpritePositionName::RightBottom)].pos.x;
			res.bottom = vertexs[ChStd::EnumCast(SpritePositionName::RightBottom)].pos.y;
			return res;
		}

		inline ChVec2 GetUV(const SpritePositionName _posNames)const
		{
			return GetUV(ChStd::EnumCast(_posNames));
		}

		ChVec2 GetUV(const unsigned char _num)const
		{
			if (_num >= vertexs.size())return ChVec2();

			return vertexs[_num].uv;
		}

		inline ChVec4 GetUVRect()const
		{
			ChVec4 res;
			res.left = vertexs[ChStd::EnumCast(SpritePositionName::LeftTop)].uv.x;
			res.top = vertexs[ChStd::EnumCast(SpritePositionName::LeftTop)].uv.y;
			res.right = vertexs[ChStd::EnumCast(SpritePositionName::RightBottom)].uv.x;
			res.bottom = vertexs[ChStd::EnumCast(SpritePositionName::RightBottom)].uv.y;
			return res;
		}

		///////////////////////////////////////////////////////////////////////////////////
		
		inline void Move(const ChVec2& _vec) { Move(_vec.x, _vec.y); }

		void Move(const float _x,const float _y);

		inline void MoveX(const float _x) { Move(_x, 0.0f); }

		inline void MoveY(const float _y) { Move(0.0f, _y); }

		///////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////

	protected:


		///////////////////////////////////////////////////////////////////////////////////

		std::array<Ch3D::Vertex, 4> vertexs;

	};

}

#endif