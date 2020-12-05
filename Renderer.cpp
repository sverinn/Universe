#include <Windows.h>
#include <vector>
#include "ObjectHandler.h"
#include "EventHandler.h"
#include <d3dx9.h>

size_t RenderPointlist(
    IDirect3DDevice9*& d3dDevice,
    LPDIRECT3DVERTEXBUFFER9& pVertexObject,
    LPDIRECT3DVERTEXDECLARATION9& vertexDecl,
    void*& pVertexBuffer,
    std::vector<PhysicalObject*>& ObjectReg)
{


    struct VertexData
    {
        D3DXVECTOR3 XYZ = { NULL, NULL, NULL };
        float r = NULL;
        D3DCOLOR RGB = { NULL };
    };

    size_t count = ObjectReg.size();
    VertexData* vertexData = new VertexData[count];

    /*
    float totalRadius = 0;

    for (int i = 0; i < count; i++)
        totalRadius += ObjectReg[i]->GetSize();

    int totalLines = 2 * 3.14 * totalRadius;
    */


    for (size_t i = 0; i < count; ++i)
    {
        vertexData[i].XYZ = { (float)ObjectReg[i]->GetX(), (float)ObjectReg[i]->GetY(), 0.f };
        vertexData[i].r = (float)ObjectReg[i]->GetSize();
        vertexData[i].RGB = D3DCOLOR_XRGB(255,255,255);
    }

    //Создание вершинного буфера
    if (FAILED((d3dDevice->CreateVertexBuffer(
        count * sizeof(VertexData),
        D3DUSAGE_WRITEONLY,
        D3DFVF_XYZW | D3DFVF_DIFFUSE,
        D3DPOOL_MANAGED,
        &pVertexObject,
        NULL))))
    {
        MessageBox(NULL, L"Can`t create vertex buffer", L"Error", MB_OK | MB_ICONERROR);
        return 0;
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
        { 0, 16, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
        D3DDECL_END()
    };



    // Создание объекта с описанием вершин
    if (FAILED(d3dDevice->CreateVertexDeclaration(decl, &vertexDecl)))
    {
        MessageBox(NULL, L"Can`t create vertex declaration", L"Error", MB_OK | MB_ICONERROR);
        return 0;
    };

    return sizeof(VertexData);
}