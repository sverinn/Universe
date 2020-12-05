#pragma once
#include <d3dx9.h>

size_t RenderPointlist(
    IDirect3DDevice9*& d3dDevice,
    LPDIRECT3DVERTEXBUFFER9& pVertexObject,
    LPDIRECT3DVERTEXDECLARATION9& vertexDecl,
    void*& pVertexBuffer,
    std::vector<PhysicalObject*>& ObjectReg);