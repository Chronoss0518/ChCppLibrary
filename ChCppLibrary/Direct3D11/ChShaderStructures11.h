
//SStruct = ShaderStructure//
#ifndef Ch_D3D11_SStruct_h
#define Ch_D3D11_SStruct_h

namespace ChD3D11
{
	class TextureBase11;

	struct ShaderUseMaterial11 :public Ch3D::Material
	{
		ChMat_11 frameMatrix;
	};

	struct Material11
	{
		ShaderUseMaterial11 material;

		std::string materialName;

		std::map<Ch3D::TextureType, ChPtr::Shared<TextureBase11>>textures;
	};

	struct SkinMeshVertex11 : public Ch3D::MeshVertex
	{
		float blendPow[96];
	};

	struct BaseDatas
	{
		//�r���[�ϊ��s��//
		ChMat_11 viewMat;
		//�ˉe�ϊ��s��//
		ChMat_11 projMat;
		//��ʃT�C�Y//
		ChVec4 windSize;
	};

	struct CharaDatas
	{
		//���f���s��//
		ChMat_11 modelMat;

		ChMat_11 frameMatrix;
	};

	struct PolygonDatas
	{
		//���f���s��//
		ChMat_11 modelMat;
		//�X�v���C�g�x�[�X�F//
		ChVec4 baseColor = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	class ShaderObjectBase11 :public ChCp::Initializer
	{
	public:

		virtual ~ShaderObjectBase11()
		{
			Release();
		}

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Init() { SetInitFlg(true); }

		inline virtual void Release()
		{
			SetInitFlg(false);
			if (ChPtr::NullCheck(buf))return;
			buf->Release();
			buf = nullptr;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		//AddFunction//

		//Flg���\�b�h//
		inline void AddCPUAccessFlg(const D3D11_CPU_ACCESS_FLAG& _flg)
		{
			cpuAccessFlg |= _flg;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//Flg���\�b�h//
		inline void SetUsageFlg(const D3D11_USAGE& _flg)
		{
			usage = _flg;
		}

		//Flg���\�b�h//
		inline void SetCPUAccessFlg(const D3D11_CPU_ACCESS_FLAG& _flg)
		{
			cpuAccessFlg = _flg;
		}

		template<class T>
		inline void SetDynamicBuffer(ID3D11DeviceContext* _dc, const T* _buf, const unsigned long _bufSize)
		{
			if (!(usage & D3D11_USAGE::D3D11_USAGE_DYNAMIC))return;

			D3D11_MAPPED_SUBRESOURCE map;
			ZeroMemory(&map, sizeof(D3D11_MAPPED_SUBRESOURCE));

			//  Disable GPU access to the vertex buffer data.
			_dc->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
			//  Update the vertex buffer here.
			memcpy(map.pData, _buf, _bufSize);
			//  Reenable GPU access to the vertex buffer data.
			_dc->Unmap(buf, 0);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		template<class T>
		inline void UpdateResouce(
			ID3D11DeviceContext* _dc,
			const T* _content)
		{

			if (!*this)return;
			if (ChPtr::NullCheck(_dc))return;
			if (ChPtr::NullCheck(_content))return;

			_dc->UpdateSubresource(buf, 0, nullptr, _content, 0, 0);
		}

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//CreateFunction//

		template<class T>
		inline D3D11_BUFFER_DESC CreateBufferDesc(const unsigned long _num)
		{

			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
			desc.ByteWidth = sizeof(T) * _num;
			desc.Usage = usage;
			desc.BindFlags = bindFlg;
			desc.CPUAccessFlags = cpuAccessFlg;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;

			return desc;
		}


		inline D3D11_SUBRESOURCE_DATA CreateSubresourceData(void* _buf)
		{
			D3D11_SUBRESOURCE_DATA data;
			ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
			data.pSysMem = _buf;
			data.SysMemPitch = 0;
			data.SysMemSlicePitch = 0;

			return data;
		}

		///////////////////////////////////////////////////////////////////////////////////

		ID3D11Buffer* buf = nullptr;

		unsigned int cpuAccessFlg = 0;
		D3D11_USAGE usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		D3D11_BIND_FLAG bindFlg = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	};

	class IndexBuffer11 : public ShaderObjectBase11
	{
	public:

		virtual ~IndexBuffer11()
		{
			Release();
		}

	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//CreateFunction//

		//Create���ĂԑO�ɕK�v�ȏꍇ�̓t���O�֌W�𑀍삷�郁�\�b�h���Ăт܂�//
		inline void CreateBuffer(
			ID3D11Device* _device,
			unsigned long* _indexBuffer,
			const unsigned long _indexNum)
		{
			if (ChPtr::NullCheck(_device))return;

			Release();

			bindFlg = D3D11_BIND_INDEX_BUFFER;

			D3D11_BUFFER_DESC desc = CreateBufferDesc<unsigned long>(_indexNum);

			D3D11_SUBRESOURCE_DATA data = CreateSubresourceData(_indexBuffer);

			format = DXGI_FORMAT_R32_UINT;

			_device->CreateBuffer(&desc, &data, &buf);

			Init();
		}

		//Create���ĂԑO�ɕK�v�ȏꍇ�̓t���O�֌W�𑀍삷�郁�\�b�h���Ăт܂�//
		inline void CreateBuffer(
			ID3D11Device* _device,
			unsigned char* _indexBuffer,
			const unsigned char _indexNum)
		{
			if (ChPtr::NullCheck(_device))return;

			Release();

			bindFlg = D3D11_BIND_INDEX_BUFFER;

			D3D11_BUFFER_DESC desc = CreateBufferDesc<unsigned char>(_indexNum);

			D3D11_SUBRESOURCE_DATA data = CreateSubresourceData(_indexBuffer);

			format = DXGI_FORMAT_R8_UINT;

			_device->CreateBuffer(&desc, &data, &buf);

			Init();
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetIndexBuffer(ID3D11DeviceContext* _dc)
		{
			if (!*this)return;
			if (ChPtr::NullCheck(_dc))return;

			_dc->IASetIndexBuffer(buf, format, 0);
		}

	private:
		DXGI_FORMAT format = DXGI_FORMAT_R32_UINT;

	};

	template<class vertex = Ch3D::Vertex>
	class VertexBuffer11 : public ShaderObjectBase11
	{
	public:

		virtual ~VertexBuffer11()
		{
			Release();
		}

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//CreateFunction//

		//Create���ĂԑO�ɕK�v�ȏꍇ�̓t���O�֌W�𑀍삷�郁�\�b�h���Ăт܂�//
		inline void CreateBuffer(
			ID3D11Device* _device,
			vertex* _vertexArray,
			const unsigned long _vertexNum)
		{
			if (ChPtr::NullCheck(_device))return;
			if (ChPtr::NullCheck(_vertexArray))return;

			Release();

			bindFlg = D3D11_BIND_VERTEX_BUFFER;

			D3D11_BUFFER_DESC desc = CreateBufferDesc<vertex>(_vertexNum);

			D3D11_SUBRESOURCE_DATA data = CreateSubresourceData(_vertexArray);

			_device->CreateBuffer(&desc, &data, &buf);

			Init();
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetVertexBuffer(
			ID3D11DeviceContext* _dc,
			const unsigned int _offset)
		{

			if (!*this)return;
			if (ChPtr::NullCheck(_dc))return;

			unsigned int strides = sizeof(vertex);

			_dc->IASetVertexBuffers(0, 1, &buf, &strides, &_offset);
		}

		inline void SetVertexBuffer(
			ID3D11DeviceContext* _dc,
			const unsigned int _startSlot,
			const unsigned int _bufferCount,
			const unsigned int _offset)
		{

			if (!*this)return;
			if (ChPtr::NullCheck(_dc))return;
			unsigned int strides = sizeof(vertex);

			_dc->IASetVertexBuffers(_startSlot, _bufferCount, &buf, &strides, &_offset);
		}

	};

	template<class content>
	class ConstantBuffer11 :public ShaderObjectBase11
	{
	public:

		virtual ~ConstantBuffer11()
		{
			Release();
		}

	public://Create Functions//

		//Create���ĂԑO�ɕK�v�ȏꍇ�̓t���O�֌W�𑀍삷�郁�\�b�h���Ăт܂�//
		inline void CreateBuffer(
			ID3D11Device* _device,
			const unsigned long _registerNo)
		{
			if (ChPtr::NullCheck(_device))return;

			Release();

			bindFlg = D3D11_BIND_CONSTANT_BUFFER;

			D3D11_BUFFER_DESC desc = CreateBufferDesc<content>(1);

			unsigned long makeUpBuffer = desc.ByteWidth % 16;

			desc.ByteWidth = makeUpBuffer == 0 ? desc.ByteWidth : desc.ByteWidth + (16 - makeUpBuffer);

			_device->CreateBuffer(&desc, nullptr, &buf);

			registerNo = _registerNo;

			Init();
		}

	public://Set Functions//

		inline void SetRegisterNo(const unsigned long _registerNo) { registerNo = _registerNo; }

		inline void SetToVertexShader(
			ID3D11DeviceContext* _dc,
			const unsigned long updateCount = 1)
		{
			if (!*this)return;
			if (ChPtr::NullCheck(_dc))return;

			_dc->VSSetConstantBuffers(registerNo, updateCount, &buf);

		}

		inline void SetToGeometryShader(
			ID3D11DeviceContext* _dc,
			const unsigned long updateCount = 1)
		{
			if (!*this)return;
			if (ChPtr::NullCheck(_dc))return;

			_dc->GSSetConstantBuffers(registerNo, updateCount, &buf);

		}

		inline void SetToHullShader(
			ID3D11DeviceContext* _dc,
			const unsigned long updateCount = 1)
		{
			if (!*this)return;
			if (ChPtr::NullCheck(_dc))return;

			_dc->HSSetConstantBuffers(registerNo, updateCount, &buf);

		}

		inline void SetToDomainShader(
			ID3D11DeviceContext* _dc,
			const unsigned long updateCount = 1)
		{
			if (!*this)return;
			if (ChPtr::NullCheck(_dc))return;

			_dc->DSSetConstantBuffers(registerNo, updateCount, &buf);

		}

		inline void SetToPixelShader(
			ID3D11DeviceContext* _dc,
			const unsigned long updateCount = 1)
		{
			if (!*this)return;
			if (ChPtr::NullCheck(_dc))return;

			_dc->PSSetConstantBuffers(registerNo, updateCount, &buf);

		}

		inline void SetToComputeShader(
			ID3D11DeviceContext* _dc,
			const unsigned long updateCount = 1)
		{
			if (!*this)return;
			if (ChPtr::NullCheck(_dc))return;

			_dc->CSSetConstantBuffers(registerNo, updateCount, &buf);

		}

	public://Get Functions//

		inline unsigned long GetRegisterNo() { return registerNo; }

	protected:

		unsigned long registerNo = 0;
	};


}

#endif