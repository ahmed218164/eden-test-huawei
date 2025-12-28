/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Mesh utils.
 */

#ifndef MESH_H
#define MESH_H

#include "Rendering/Model/SubMesh.h"
#include "Rendering/RenderCommon.h"
#include "Rendering/VertexAttribute.h"

NS_CG_BEGIN

class DynamicBuffer;
class Buffer;
class VertexDeclaration;
class GraphicsRenderer;

/*
 * A mesh class used to add, delete, and query submeshes and obtain the mesh BBox.
 */
class CGKIT_EXPORT Mesh {
    friend class RenderStage;
    friend class RenderStageForward;
    friend class RenderStageDeferred;
    friend class RenderStageShadow;
    friend class RenderForward;
public:
    Mesh(const GraphicsRenderer* graphicsRenderer);
    Mesh(const Mesh& mesh) = delete;
    Mesh& operator=(const Mesh& mesh) = delete;
    ~Mesh();

    /*
     * Adds a submesh. The argument is a material pointer.
     */
    SubMesh* AddSubMesh();

    /*
     * Obtains a submesh. The argument is the index of a submesh.
     */
    const SubMesh* GetSubMesh(u32 index) const;

    /*
     * Obtains the number of submeshes.
     */
    u32 GetSubMeshCount() const;

    /*
     * Deletes a submesh. The argument is the index of a submesh.
     */
    void RemoveSubMesh(u32 index);

    /*
     * Returns true if a submesh exists. The argument is the index of a submesh.
     */
    bool HasSubMesh(u32 index) const;

    /*
     * Obtains the number of triangles in all submeshes.
     */
    u32 GetTriangleCount() const;

    /*
     * Obtains the mesh BBox.
     */
    const AABB& GetAABB();

    /*
     * Fill vertex data into mesh.
     */
    template<typename T>
    bool FillVertexData(const T* data, u64 count, const String& name);

    /*
     * Set the vertex buffer's count.
     */
    void SetVertexCount(u64 count);

    /*
     * Obtains the vertex buffer's count.
     */
    u64 GetVertexCount() const;

    /*
     * Fill index data into mesh.
     */
    template<typename T>
    bool FillIndexData(const T* data, u64 count);

    /*
     * Set the index buffer's count.
     */
    void SetIndexCount(u64 count);

    /*
     * Obtains the index buffer's count.
     */
    u64 GetIndexCount() const;

    /*
     * Set the index stride.
     */
    void SetIndexStride(u32 stride);

    /*
     * Get the index stride.
     */
    u32 GetIndexStride() const;

    /*
     * If VertexDeclaration is null, create. else Update vertexDeclaration by vertexAttributes.
     */
    void UpdateVertexDeclaration(const std::vector<VertexAttribute>& vertexAttributes);

protected:
    const VertexDeclaration* GetVertexDeclaration() const;
    const std::vector<DynamicBuffer*>& GetVertexBuffers() const;
    const Buffer* GetIndexBuffer() const;

private:
    void Destroy();
    void DestroyVertexBuffer();
    void DestroyIndexBuffer();

private:
    AABB m_aabb;
    DynamicBuffer* m_indexBuffer = nullptr;
    std::vector<DynamicBuffer*> m_vertexBuffers;
    std::vector<SubMesh*> m_subMeshes;
    VertexDeclaration* m_vertexDeclaration = nullptr;
    std::map<String, u32> m_vertexAttributeMapping;
    const GraphicsRenderer* m_graphicsRenderer = nullptr;

    u32 m_vertexCount = 0;
    u32 m_indexCount = 0;
    u32 m_indexStride = 0;
};

NS_CG_END

#endif
