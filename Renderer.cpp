#include <vector>
#include "Objects.h"
#include "Graphics.h"
#include "Resources.h"
#include <D3d9types.h>

void RenderFrame(Graphics& pGfx, std::vector<PhysicalObject*> ObjectReg)
{
    //HRESULT hr = d3dDevice->TestCooperativeLevel();

    if (pGfx.pDevice()->TestCooperativeLevel() == D3DERR_DEVICELOST)
        return;

    // Инициализация матриц
    D3DXMATRIX matrixView;
    D3DXMATRIX matrixProjection;

    D3DXVECTOR3 Vector1(0, 0, 0);
    D3DXVECTOR3 Vector2(0, 0, 1);
    D3DXVECTOR3 Vector3(0, 1, 0);


    // Матрица вида
    D3DXMatrixLookAtLH(
        &matrixView,
        &Vector1,
        &Vector2,
        &Vector3);

    // Матрица проекции
    D3DXMatrixOrthoOffCenterLH(&matrixProjection, 0, pGfx.Width(), pGfx.Height(), 0, 0, 255);

    // Установка матриц в качестве текущих
    pGfx.pDevice()->SetTransform(D3DTS_VIEW, &matrixView);
    pGfx.pDevice()->SetTransform(D3DTS_PROJECTION, &matrixProjection);

    LPDIRECT3DVERTEXBUFFER9 pVertexObject = NULL;
    LPDIRECT3DVERTEXDECLARATION9 vertexDecl = NULL;

    struct VertexData
    {
        float x, y, z, r;
        D3DXCOLOR Color;
    };

    size_t count = ObjectReg.size();
    VertexData* vertexData = new VertexData[count];
    srand(clock());
    for (size_t i = 0; i < count; ++i)
    {
        vertexData[i].x = ObjectReg[i]->GetX();
        vertexData[i].y = ObjectReg[i]->GetY();
        vertexData[i].z = 0.f;
        vertexData[i].r = ObjectReg[i]->GetRadius();
        vertexData[i].Color = ObjectReg[i]->GetColor();
    }

    void* pVertexBuffer = NULL;

    //Создание вершинного буфера
    if (FAILED((pGfx.pDevice()->CreateVertexBuffer(
        count * sizeof(VertexData),
        D3DUSAGE_WRITEONLY,
        D3DFVF_XYZ,
        D3DPOOL_DEFAULT,
        &pVertexObject,
        NULL))))
    {
        MessageBox(NULL, L"Can`t create vertex buffer", L"Error", MB_OK | MB_ICONERROR);
        return;
    };

    // Блокировка буфера, чтобы записать туда данные о вершинах
    pVertexObject->Lock(0, count * sizeof(VertexData), &pVertexBuffer, 0);

    memcpy(pVertexBuffer, vertexData, count * sizeof(VertexData));

    pVertexObject->Unlock();

    delete[] vertexData;
    vertexData = nullptr;

    D3DVERTEXELEMENT9 decl[] =
    {
        { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        { 0, 12, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_PSIZE, 0 },
        { 0, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
        D3DDECL_END()
    };

    // Создаем объект с описанием вершин
    if (FAILED(pGfx.pDevice()->CreateVertexDeclaration(decl, &vertexDecl)))
    {
        MessageBox(NULL, L"Can`t create vertex declaration", L"Error", MB_OK | MB_ICONERROR);
        return;
    };



    pGfx.pDevice()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    // Устанавливаем источник вершин
    pGfx.pDevice()->SetStreamSource(0, pVertexObject, 0, sizeof(VertexData));
    // Указываем, что хранится в буфере
    pGfx.pDevice()->SetVertexDeclaration(vertexDecl);

    pGfx.pDevice()->BeginScene();

    if (FAILED(pGfx.pDevice()->DrawPrimitive(D3DPRIMITIVETYPE::D3DPT_POINTLIST,
        0,
        ObjectReg.size())))
    {
        MessageBox(NULL, L"Can`t create vertex declaration", L"Error", MB_OK | MB_ICONERROR);
        return;
    };

    pGfx.pDevice()->EndScene();
    pGfx.pDevice()->Present(NULL, NULL, NULL, NULL);
}