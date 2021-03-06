#ifndef Ch_D3D11_PolyBoard_h
#define Ch_D3D11_PolyBoard_h

#include"../ChShaderStructures11.h"

namespace ChD3D11
{


	class PolygonBoard11 
	{

		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init();

			void Init(ID3D11Device* _device);

			void Release();

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetVertexList(const std::vector<ChPtr::Shared<Ch3D::PolyVertex>>& _vertexList);

			void SetPos(const unsigned char _posNo, const ChVec3& _posData);

			void SetUV(const unsigned char _posNo, const ChVec2& _posData);

			void SetDrawData(ID3D11DeviceContext* _CD);

			inline void SetInitTri()
			{
				vertexs.pop_back();
			}

			void SetInitSquare();

			///////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			inline ChVec3 GetPos(const unsigned char _num)
			{
				if (_num >= vertexs.size())return ChVec3();
				
				return vertexs[_num]->pos;
				
			}

			inline ChVec2 GetUVPos(const unsigned char _num)
			{
				if (_num >= vertexs.size())return ChVec2();
				
				return vertexs[_num]->uv;
				
			}

			///////////////////////////////////////////////////////////////////////////////////
			//AddFunction//

			inline void AddVertex()
			{
				Ch3D::PolyVertex vertex;
				AddVertex(vertex);
			}

			void AddVertex(const Ch3D::PolyVertex& _vertexs);

			///////////////////////////////////////////////////////////////////////////////////

		protected:
			
			std::vector<ChPtr::Shared<Ch3D::PolyVertex>> vertexs;

			Ch3D::PolyVertex drawVertexs[3];
			VertexBuffer11<Ch3D::PolyVertex> vertexBuffer;
			IndexBuffer11 indexBuffer;
			ShaderUseMaterial11 material;
			ConstantBuffer11<ShaderUseMaterial11> materialBuffer;
	};
}

#endif
