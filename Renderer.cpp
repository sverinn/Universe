
#include <vector>
#include "Objects.h"
#include "Graphics.h"
#include "Resources.h"
#include <D3d9types.h>

static const int CIRCLE_RESOLUTION = 64;

struct VERTEX_2D_DIF { // transformed colorized
    float x, y, z, rhw;
    D3DCOLOR color;
    static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
};

void DrawCircleFilled(Graphics& pGfx, float mx, float my, float r, D3DCOLOR color)
{
    VERTEX_2D_DIF verts[CIRCLE_RESOLUTION + 1];

    for (int i = 0; i < CIRCLE_RESOLUTION + 1; i++)
    {
        verts[i].x = mx + r * cos(D3DX_PI * (i / (CIRCLE_RESOLUTION / 2.0f)));
        verts[i].y = my + r * sin(D3DX_PI * (i / (CIRCLE_RESOLUTION / 2.0f)));
        verts[i].z = 0;
        verts[i].rhw = 1;
        verts[i].color = color;
    }

    pGfx.pDevice()->SetFVF(VERTEX_2D_DIF::FVF);
    pGfx.pDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, CIRCLE_RESOLUTION - 1, &verts, sizeof(VERTEX_2D_DIF));
}

void RenderFrame(Graphics& pGfx, std::vector<PhysicalObject*> ObjectReg)
{
    //HRESULT hr = d3dDevice->TestCooperativeLevel();

    if (pGfx.pDevice()->TestCooperativeLevel() == D3DERR_DEVICELOST)
        return;

    // Create matrix viev
    D3DXMATRIX matrixView;
    D3DXMATRIX matrixProjection;

    D3DXVECTOR3 Vector1(0, 0, 0);
    D3DXVECTOR3 Vector2(0, 0, 1);
    D3DXVECTOR3 Vector3(0, 1, 0);

    D3DXMatrixLookAtLH(
        &matrixView,
        &Vector1,
        &Vector2,
        &Vector3);

    D3DXMatrixOrthoOffCenterLH(&matrixProjection, 0, pGfx.Width(), pGfx.Height(), 0, 0, 255);

    // Set matrix
    pGfx.pDevice()->SetTransform(D3DTS_VIEW, &matrixView);
    pGfx.pDevice()->SetTransform(D3DTS_PROJECTION, &matrixProjection);

    /*
    LPDIRECT3DVERTEXBUFFER9 pVertexObject = NULL;
    LPDIRECT3DVERTEXDECLARATION9 vertexDecl = NULL;

    struct VertexData
    {
        float x, y, z;
        //D3DXCOLOR Color;
    };

    //size_t count = ObjectReg.size();


    void* pVertexBuffer = NULL;

    // Create buffer
    if (FAILED((pGfx.pDevice()->CreateVertexBuffer(
        sizeof(VertexData),
        D3DUSAGE_WRITEONLY,
        D3DFVF_XYZ,
        D3DPOOL_DEFAULT,
        &pVertexObject,
        NULL))))
    {
        MessageBox(NULL, L"Can`t create vertex buffer", L"Error", MB_OK | MB_ICONERROR);
        return;
    };

    // Copy vertices to gpu memory
    pVertexObject->Lock(0, sizeof(VertexData)*6, &pVertexBuffer, 0);

    memcpy(pVertexBuffer, vertexData, sizeof(VertexData) * 6);

    pVertexObject->Unlock();

    D3DVERTEXELEMENT9 decl[] =
    {
        { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        //{ 0, 12, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_PSIZE, 0 },
        //{ 0, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
        D3DDECL_END()
    };

    // Vertex decl
    if (FAILED(pGfx.pDevice()->CreateVertexDeclaration(decl, &vertexDecl)))
    {
        MessageBox(NULL, L"Can`t create vertex declaration", L"Error", MB_OK | MB_ICONERROR);
        return;
    };


    */
    pGfx.pDevice()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    /*
    pGfx.pDevice()->SetStreamSource(0, pVertexObject, 0, sizeof(VertexData));

    pGfx.pDevice()->SetVertexDeclaration(vertexDecl);
    */
    pGfx.pDevice()->BeginScene();

    /*if (FAILED(pGfx.pDevice()->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 4)))
    {
        MessageBox(NULL, L"Can`t create vertex declaration", L"Error", MB_OK | MB_ICONERROR);
        return;
    };*/

    for (auto iObject : ObjectReg)
    {
        DrawCircleFilled(pGfx, iObject->GetX(), iObject->GetY(), iObject->GetRadius(), iObject->GetColor());
    }

    pGfx.pDevice()->EndScene();
    pGfx.pDevice()->Present(NULL, NULL, NULL, NULL);
}