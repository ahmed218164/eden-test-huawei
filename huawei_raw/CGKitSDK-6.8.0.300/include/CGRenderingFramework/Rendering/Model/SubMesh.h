/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: SubMesh.
 */

#ifndef SUB_MESH_H
#define SUB_MESH_H

#include "Math/Vector2.h"
#include "Math/AABB.h"
#include "Rendering/RenderCommon.h"

NS_CG_BEGIN

class AABB;
class Mesh;

/*
 * A submesh class used to store data such as vertex start and count, index start and count,
 * and MaterialInstanceIndex,Rendering tasks are processed in the unit of submeshes.
 */
class CGKIT_EXPORT SubMesh {
public:
    /*
     *  A constructor.
     *  Obtains the diagram element topology type of the submesh.
     */
    SubMesh(Mesh* mesh);

    /*
     * A destructor.
     */
    ~SubMesh();
    SubMesh(const SubMesh& rhs) = delete;
    SubMesh& operator=(const SubMesh& rhs) = delete;

    /*
     * get mesh
     * subMesh's parent.
     */
    const Mesh* GetMesh() const;

    /*
     * Sets the diagram element topology type of the submesh.
     * The argument is an enum value of PrimitiveMode.
     */
    void SetPrimitiveMode(PrimitiveMode mode);

    /*
     * Obtains the diagram element topology type of the submesh.
     */
    PrimitiveMode GetPrimitiveMode() const;

    /*
     * Obtains the number of indexes in the index buffer and the number of triangles based on the
     * diagram element topology type.
     */
    u32 GetTriangleCount() const;

    /*
     * Sets the submesh BBox. The argument is a BBox.
     */
    void SetAABB(const AABB& aabb);

    /*
     * Obtains the submesh BBox.
     */
    const AABB& GetAABB() const;

    /*
     * set submesh BBox's max and min.
     */
    void SetAABB(const Vector3& max, const Vector3& min);

    /*
     * set vertex count for submesh.
     */
    void SetVertexCount(u32 vertexCount);

    /*
     * get submesh's vertex count.
     */
    u32 GetVertexCount() const;

    /*
     * set vertex start pos for this submesh.
     */
    void SetVertexStart(u32 vertexStart);

    /*
     * get submesh's vertex start pos.
     */
    u32 GetVertexStart() const;

    /*
     * set vertex's index count for submesh.
     */
    void SetIndexCount(u32 indexCount);

    /*
     * get vertex's index count.
     */
    u32 GetIndexCount() const;

    /*
     * set vertex's index start pos.
     */
    void SetIndexStart(u32 indexStart);

    /*
     * get submesh's vertex index start pos.
     */
    u32 GetIndexStart() const;

    /*
     * set submesh's MaterialInstance's index.
     */
    void SetMaterialInstanceIndex(u32 materialInstanceIndex);
    /*
     * get submesh's MaterialInstance's index.
     */
    u32 GetMaterialInstanceIndex() const;

private:
    void Destroy();

private:
    Mesh* m_mesh;
    PrimitiveMode m_primitiveMode = PrimitiveMode::PRIMITIVE_MODE_TRIANGLE_LIST;
    u32 m_vertexStart;
    u32 m_vertexCnt;
    u32 m_indexStart;
    u32 m_indexCnt;
    u32 m_materialInstanceIndex;

    AABB m_aabb;
};

NS_CG_END

#endif