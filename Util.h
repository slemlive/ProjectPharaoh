
namespace Util
{
	void D3DXMatrixMakeRot(D3DXMATRIX& matRot, D3DXVECTOR3& vRot);
	void D3DXMatrixMakeTrans(D3DXMATRIX& matTrans, D3DXVECTOR3& vTrans);

	RECT GetRect(CTextureUI* pTextureUI);

	typedef struct SRay
	{
		D3DXVECTOR3 m_vOri;
		D3DXVECTOR3 m_vDir;
	}*LPRAY;

	LPRAY CreateRay();
	bool CheckMeshPicking(LPD3DXMESH* ppMesh, D3DXMATRIX* pmatWorld, D3DXVECTOR3* pOut);
};

using namespace Util;