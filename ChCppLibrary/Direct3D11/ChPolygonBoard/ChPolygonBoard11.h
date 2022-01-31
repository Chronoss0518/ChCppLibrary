#ifndef Ch_D3D11_PolyBoard_h
#define Ch_D3D11_PolyBoard_h

#include"../ChShaderStructures11.h"

namespace ChD3D11
{

	struct PolygonBoardVertex
	{

		ChVec4 pos;
		ChVec4 color;
		ChVec2 uv;
		unsigned long tmpBuf[2];
		ChVec3 normal;
		unsigned long tmpBuf2;
	};


	class PolygonBoard11:public DrawObject
	{
		public:

			inline ChPtr::Shared<PolygonBoardVertex> operator[](const unsigned long _num)
			{
				return (vertexList.size() > _num ? vertexList[_num] : nullptr);
			}

			inline const ChPtr::Shared<PolygonBoardVertex> operator[](const unsigned long _num)const
			{
				return (vertexList.size() > _num ? vertexList[_num] : nullptr);
			}

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init();

			void Init(ID3D11Device* _device);

			void Release();

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetDrawData(ID3D11DeviceContext* _dc);

			void SetVertexs(const std::vector<ChPtr::Shared<PolygonBoardVertex>>& _vertexs)
			{
				if (_vertexs.size() <= 0)return;
				
				Release();

				for (auto&& ver : _vertexs)
				{
					vertexList.push_back(ver);
				}

			}

			inline void SetPos(const unsigned char _posNum, const  ChVec4& _pos)
			{
				if (_posNum >= vertexList.size())return;
				vertexList[_posNum]->pos = _pos;
			}

			inline void SetUVPos(const unsigned char _posNum, const  ChVec2& _uv)
			{
				if (_posNum >= vertexList.size())return;
				vertexList[_posNum]->uv = _uv;
			}

			inline void SetColor(const unsigned char _posNum, const  ChVec4& _color)
			{
				if (_posNum >= vertexList.size())return;
				vertexList[_posNum]->color = _color;
			}

			inline void SetNormal(const unsigned char _posNum, const  ChVec3& _normal)
			{
				if (_posNum >= vertexList.size())return;
				vertexList[_posNum]->normal = _normal;
			}


			///////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			static inline std::vector<ChPtr::Shared<PolygonBoardVertex>> GetInitTriVertex()
			{
				auto out = GetInitSquareVertex();
				out.pop_back();
				return out;
			}

			static std::vector<ChPtr::Shared<PolygonBoardVertex>> GetInitSquareVertex();

			inline std::vector<ChPtr::Shared<PolygonBoardVertex>>& GetVertexList()
			{
				return vertexList;
			}

			inline const std::vector<ChPtr::Shared<PolygonBoardVertex>> GetVertexList()const
			{
				return vertexList;
			}

			///////////////////////////////////////////////////////////////////////////////////
			
			void inline AddVertexData(const PolygonBoardVertex& _vertex)
			{
				auto add = ChPtr::Make_S<PolygonBoardVertex>();
				*add = _vertex;
				vertexList.push_back(add);
			}



		protected:

			struct PolygonBoardBuffer
			{
				PolygonBoardVertex vertex[3];
			};

			unsigned long vertexNos[3] = { 0,1,2 };
			unsigned long indexNums[3] = { 0,1,2 };

			unsigned long num = 3;

			IndexBuffer11 indexBuffer;
			VertexBuffer11<unsigned long> vertexBuffer;
			PolygonBoardBuffer vertexDatas;
			ConstantBuffer11<PolygonBoardBuffer>constantBuffer;

			std::vector<ChPtr::Shared<PolygonBoardVertex>> vertexList;
	};
}

#endif
