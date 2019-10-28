#include "Object_Texture.h"

Plane_Texture::Plane_Texture()
{

}

Plane_Texture::~Plane_Texture()
{
	if (_ib)
	{
		_ib->Release();
		_ib = 0;
	}
	if (_vb)
	{
		_vb->Release();
		_vb = 0;
	}

	for (int i = 0; i < 2; i++)
	{
		if (_texture[i])
		{
			_texture[i]->Release();
			_texture[i] = 0;
		}
	}

}


bool Plane_Texture::CreateBuffer(IDirect3DDevice9* _device)
{
	HRESULT hr = 0;
	//创建顶点缓存
	hr = _device->CreateVertexBuffer(
		4 * sizeof(TextureVertex),
		D3DUSAGE_WRITEONLY,
		TextureVertex::FVF,
		D3DPOOL_MANAGED,
		&_vb,
		0);

	if (FAILED(hr))
	{
		MessageBox(0, "Plane_Texture: CreateVertexBuffer() - FAILED", 0, 0);
		return false;
	}
	//访问顶点缓存区域
	TextureVertex* v;
	_vb->Lock(0, 0, (void**)&v, 0);

	v[0] = TextureVertex(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f);
	v[1] = TextureVertex(0.5f, -0.5f, 0.0f, 1.0f, 1.0f);
	v[2] = TextureVertex(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f);
	v[3] = TextureVertex(0.5f, 0.5f, 0.0f, 1.0f, 0.0f);

	_vb->Unlock();

	//创建索引缓存
	hr = _device->CreateIndexBuffer(
		2 * 3 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_ib,
		0);
	if (FAILED(hr))
	{
		MessageBox(0, "Plane_Texture: CreateIndexBuffer() - FAILED", 0, 0);
		return false;
	}

	//访问索引缓存区域
	WORD* i = 0;
	_ib->Lock(0, 0, (void**)&i, 0);

	i[0] = 0; i[1] = 2; i[2] = 1;
	i[3] = 2; i[4] = 3; i[5] = 1;

	_ib->Unlock();

	D3DXCreateTextureFromFile(_device, "Texture_1.jpg", &_texture[0]);
	D3DXCreateTextureFromFile(_device, "./img/test.jpg", &_texture[1]);
	_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	return true;
}

void Plane_Texture::Render(IDirect3DDevice9* _device)
{
	_device->SetStreamSource(0, _vb, 0, sizeof(TextureVertex));
	_device->SetIndices(_ib);
	_device->SetFVF(TextureVertex::FVF);

	_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	_device->SetRenderState(D3DRS_LIGHTING, false);
	_device->SetTransform(D3DTS_WORLD, &m_Transform);
	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	_device->SetTexture(0, _texture[0]);
	_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	_device->SetTexture(0, _texture[1]);
	_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}



Box_Texture::Box_Texture()
{

}

Box_Texture::~Box_Texture()
{
	if (_ib)
	{
		_ib->Release();
		_ib = 0;
	}
	if (_vb)
	{
		_vb->Release();
		_vb = 0;
	}
	for (int i = 0; i < 2; i++)
	{
		if (_texture[i])
		{
			_texture[i]->Release();
			_texture[i] = 0;
		}
	}
}


bool Box_Texture::CreateBuffer(IDirect3DDevice9* _device)
{
	HRESULT hr = 0;
	//创建顶点缓存
	hr = _device->CreateVertexBuffer(
		6 * 4 * sizeof(TextureVertex),
		D3DUSAGE_WRITEONLY,
		TextureVertex::FVF,
		D3DPOOL_MANAGED,
		&_vb,
		0);

	if (FAILED(hr))
	{
		MessageBox(0, "Box_Texture: CreateVertexBuffer() - FAILED", 0, 0);
		return false;
	}
	//访问顶点缓存区域
	TextureVertex* v;
	_vb->Lock(0, 0, (void**)&v, 0);

	//front face
	v[0] = TextureVertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f);
	v[1] = TextureVertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f);
	v[2] = TextureVertex(0.5f, 0.5f, -0.5f, 1.0f, 1.0f);
	v[3] = TextureVertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f);

	//back face
	v[4] = TextureVertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f);
	v[5] = TextureVertex(0.5f, -0.5f, 0.5f, 0.0f, 1.0f);
	v[6] = TextureVertex(0.5f, 0.5f, 0.5f, 1.0f, 1.0f);
	v[7] = TextureVertex(-0.5f, 0.5f, 0.5f, 1.0f, 0.0f);

	// left face
	v[8] = TextureVertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f);
	v[9] = TextureVertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f);
	v[10] = TextureVertex(-0.5f, 0.5f, -0.5f, 1.0f, 1.0f);
	v[11] = TextureVertex(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f);

	// right face
	v[12] = TextureVertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f);
	v[13] = TextureVertex(0.5f, 0.5f, -0.5f, 0.0f, 1.0f);
	v[14] = TextureVertex(0.5f, 0.5f, 0.5f, 1.0f, 1.0f);
	v[15] = TextureVertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f);

	// top face
	v[16] = TextureVertex(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f);
	v[17] = TextureVertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f);
	v[18] = TextureVertex(0.5f, 0.5f, 0.5f, 1.0f, 1.0f);
	v[19] = TextureVertex(0.5f, 0.5f, -0.5f, 1.0f, 0.0f);

	// bottom face
	v[20] = TextureVertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f);
	v[21] = TextureVertex(0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
	v[22] = TextureVertex(0.5f, -0.5f, 0.5f, 1.0f, 1.0f);
	v[23] = TextureVertex(-0.5f, -0.5f, 0.5f, 1.0f, 0.0f);


	_vb->Unlock();

	//创建索引缓存
	hr = _device->CreateIndexBuffer(
		6 * 3 * 2 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_ib,
		0);
	if (FAILED(hr))
	{
		MessageBox(0, "Box_Texture: CreateIndexBuffer() - FAILED", 0, 0);
		return false;
	}

	//访问索引缓存区域
	WORD* i = 0;
	_ib->Lock(0, 0, (void**)&i, 0);

	// front face
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// back face
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// left face
	i[12] = 16; i[13] = 17; i[14] = 18;
	i[15] = 16; i[16] = 18; i[17] = 19;

	// right face 
	i[18] = 20; i[19] = 21; i[20] = 22;
	i[21] = 20; i[22] = 22; i[23] = 23;

	// top face 
	i[24] = 8; i[25] = 9; i[26] = 10;
	i[27] = 8; i[28] = 10; i[29] = 11;

	// fill in the bottom face index data
	i[30] = 12; i[31] = 13; i[32] = 14;
	i[33] = 12; i[34] = 14; i[35] = 15;

	_ib->Unlock();

	D3DXCreateTextureFromFile(_device, "Texture_1.jpg", &_texture[0]);
	D3DXCreateTextureFromFile(_device, "Texture_2.jpg", &_texture[1]);

	_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	return true;
}

void Box_Texture::Render(IDirect3DDevice9* _device)
{
	_device->SetStreamSource(0, _vb, 0, sizeof(TextureVertex));
	_device->SetIndices(_ib);
	_device->SetFVF(TextureVertex::FVF);

	_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	_device->SetRenderState(D3DRS_LIGHTING, false);
	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


	_device->SetTransform(D3DTS_WORLD, &m_Transform);
	//draw front, back, left and right face
	_device->SetTexture(0, _texture[0]);
	_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 8);

	//draw top and bottom face
	_device->SetTexture(0, _texture[1]);
	_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 24, 4);
}

Plane_Ring_Textrue::Plane_Ring_Textrue()
{

}

Plane_Ring_Textrue::~Plane_Ring_Textrue()
{
	if (_ib)
	{
		_ib->Release();
		_ib = 0;
	}
	if (_vb)
	{
		_vb->Release();
		_vb = 0;
	}
	for (int i = 0; i < 8; i++)
	{
		if (_texture[i])
		{
			_texture[i]->Release();
			_texture[i] = 0;
		}
	}
}

bool Plane_Ring_Textrue::CreateBuffer(IDirect3DDevice9 * _device)
{
	HRESULT hr = 0;
	//创建顶点缓存
	hr = _device->CreateVertexBuffer(
		4 * 4 * sizeof(TextureVertex),
		D3DUSAGE_WRITEONLY,
		TextureVertex::FVF,
		D3DPOOL_MANAGED,
		&_vb,
		0);

	if (FAILED(hr))
	{
		MessageBox(0, "Box_Texture: CreateVertexBuffer() - FAILED", 0, 0);
		return false;
	}
	//访问顶点缓存区域
	TextureVertex* v;
	_vb->Lock(0, 0, (void**)&v, 0);

	//front face
	v[0] = TextureVertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f);
	v[1] = TextureVertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f);
	v[2] = TextureVertex(0.5f, 0.5f, -0.5f, 1.0f, 1.0f);
	v[3] = TextureVertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f);

	//back face
	v[4] = TextureVertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f);
	v[5] = TextureVertex(0.5f, -0.5f, 0.5f, 0.0f, 1.0f);
	v[6] = TextureVertex(0.5f, 0.5f, 0.5f, 1.0f, 1.0f);
	v[7] = TextureVertex(-0.5f, 0.5f, 0.5f, 1.0f, 0.0f);

	// left face
	v[8] = TextureVertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f);
	v[9] = TextureVertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f);
	v[10] = TextureVertex(-0.5f, 0.5f, -0.5f, 1.0f, 1.0f);
	v[11] = TextureVertex(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f);

	// right face
	v[12] = TextureVertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f);
	v[13] = TextureVertex(0.5f, 0.5f, -0.5f, 0.0f, 1.0f);
	v[14] = TextureVertex(0.5f, 0.5f, 0.5f, 1.0f, 1.0f);
	v[15] = TextureVertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f);




	_vb->Unlock();

	//创建索引缓存
	hr = _device->CreateIndexBuffer(
		4 * 3 * 2 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_ib,
		0);
	if (FAILED(hr))
	{
		MessageBox(0, "Box_Texture: CreateIndexBuffer() - FAILED", 0, 0);
		return false;
	}

	//访问索引缓存区域
	WORD* i = 0;
	_ib->Lock(0, 0, (void**)&i, 0);

	// front face
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// back face
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// left face
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// right face 
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;


	_ib->Unlock();

	D3DXCreateTextureFromFile(_device, "./img/banana1.bmp", &_texture[0]);
	D3DXCreateTextureFromFile(_device, "./img/banana2.bmp", &_texture[1]);
	D3DXCreateTextureFromFile(_device, "./img/banana3.bmp", &_texture[2]);
	D3DXCreateTextureFromFile(_device, "./img/banana4.bmp", &_texture[3]);
	D3DXCreateTextureFromFile(_device, "./img/banana5.bmp", &_texture[4]);
	D3DXCreateTextureFromFile(_device, "./img/banana6.bmp", &_texture[5]);
	D3DXCreateTextureFromFile(_device, "./img/banana7.bmp", &_texture[6]);
	D3DXCreateTextureFromFile(_device, "./img/banana8.bmp", &_texture[7]);

	_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	return true;
}

void Plane_Ring_Textrue::Render(IDirect3DDevice9 * _device)
{
	_device->SetStreamSource(0, _vb, 0, sizeof(TextureVertex));
	_device->SetIndices(_ib);
	_device->SetFVF(TextureVertex::FVF);

	_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	_device->SetRenderState(D3DRS_LIGHTING, false);





	_device->SetTransform(D3DTS_WORLD, &m_Transform);
	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


	for (int i = 0; i < 4; i++)
	{
		_device->SetTexture(0, _texture[i]);
		_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, i * 6, 2);
	}

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);


	for (int i = 0; i < 4; i++)
	{
		_device->SetTexture(0, _texture[i + 4]);
		_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, i * 6, 2);
	}

}
