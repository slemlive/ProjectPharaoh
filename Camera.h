
#pragma once

class CCamera : public CSingleton< CCamera >
{
private:
	friend CSingleton< CCamera >;

private:
	D3DXMATRIX m_matView;

	D3DXVECTOR3 m_vLook;
	D3DXVECTOR3 m_vAt;
	
	D3DXVECTOR3 m_vLocal;
	D3DXVECTOR3 m_vRot;

	float m_fWidth;
	float m_fHeight;

protected:
	CCamera();
	virtual ~CCamera();

public:
	void SetFovProjection();
	void UpdateView();

public:
	D3DXVECTOR3* GetLook() { return &m_vLook; }
	D3DXVECTOR3* GetAt() { return &m_vAt; }
	D3DXVECTOR3* GetLocal() { return &m_vLocal; }
	D3DXVECTOR3* GetRot() { return &m_vRot; }

	D3DXMATRIX* GetView() { return &m_matView; }

	float GetWidth() { return m_fWidth; }
	float GetHeight() { return m_fHeight; }

	void CursorViewPos();
};