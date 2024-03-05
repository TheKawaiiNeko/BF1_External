#include "SDK.h"
#include "..\..\Utils\Config\Config.h"

uint64_t EncryptedPlayerMgr_GetPlayer(uint64_t ptr, int id)
{
    uint64_t XorValue1 = m.Read<uint64_t>(ptr + 0x20) ^ m.Read<uint64_t>(ptr + 0x8);
    uint64_t XorValue2 = XorValue1 ^ m.Read<uint64_t>(ptr + 0x10);
    if (XorValue2 == 0)
        return 0;

    return XorValue1 ^ m.Read<uint64_t>(XorValue2 + 0x8 * id);
}

uint64_t GetPlayerById(int id)
{
    uint64_t pClientGameContext = m.Read<uint64_t>(offset::ClientGameContext);
    if (pClientGameContext == 0)
        return 0;

    uint64_t pPlayerManager = m.Read<uint64_t>(pClientGameContext + 0x68);
    if (pPlayerManager == 0)
        return 0;

    uint64_t pObfuscationMgr = m.Read<uint64_t>(offset::ObfuscationMgr);
    if (pObfuscationMgr == 0)
        return 0;

    uint64_t PlayerListXorValue = m.Read<uint64_t>(pPlayerManager + 0xF8);
    uint64_t PlayerListKey = PlayerListXorValue ^ m.Read<uint64_t>(pObfuscationMgr + 0x70);

    uint64_t mpBucketArray = m.Read<uint64_t>(pObfuscationMgr + 0x10);


    int mnBucketCount = m.Read<int>(pObfuscationMgr + 0x18);
    if (mnBucketCount == 0)
        return 0;

    int startCount = (int)PlayerListKey % mnBucketCount;

    uint64_t mpBucketArray_startCount = m.Read<uint64_t>(mpBucketArray + (uint64_t)(startCount * 8));
    uint64_t node_first = m.Read<uint64_t>(mpBucketArray_startCount);
    uint64_t node_second = m.Read<uint64_t>(mpBucketArray_startCount + 0x8);
    uint64_t node_mpNext = m.Read<uint64_t>(mpBucketArray_startCount + 0x10);

    while (PlayerListKey != node_first)
    {
        mpBucketArray_startCount = node_mpNext;

        node_first = m.Read<uint64_t>(mpBucketArray_startCount);
        node_second = m.Read<uint64_t>(mpBucketArray_startCount + 0x8);
        node_mpNext = m.Read<uint64_t>(mpBucketArray_startCount + 0x10);
    }

    uint64_t EncryptedPlayerMgr = node_second;
    return EncryptedPlayerMgr_GetPlayer(EncryptedPlayerMgr, id);
}

bool WorldToScreen(const Vector3& vIn, Vector2& flOut)
{
    uint64_t GameRender = m.Read<uint64_t>(offset::GameRender);
    uint64_t RenderView = m.Read<uint64_t>(GameRender + 0x60);

    if (!GameRender || !RenderView)
        return false;

    Matrix view_projection = m.Read<Matrix>(RenderView + 0x460);

    float w = view_projection.m[0][3] * vIn.x + view_projection.m[1][3] * vIn.y + view_projection.m[2][3] * vIn.z + view_projection.m[3][3];

    if (w < 0.01)
        return false;

    flOut.x = view_projection.m[0][0] * vIn.x + view_projection.m[1][0] * vIn.y + view_projection.m[2][0] * vIn.z + view_projection.m[3][0];
    flOut.y = view_projection.m[0][1] * vIn.x + view_projection.m[1][1] * vIn.y + view_projection.m[2][1] * vIn.z + view_projection.m[3][1];

    float invw = 1.0f / w;

    flOut.x *= invw;
    flOut.y *= invw;

    int width = g.GameSize.right;
    int height = g.GameSize.bottom;

    float x = (float)width / 2;
    float y = (float)height / 2;

    x += 0.5 * flOut.x * (float)width + 0.5;
    y -= 0.5 * flOut.y * (float)height + 0.5;

    flOut.x = x;
    flOut.y = y;

    return true;
}

bool WorldToScreen(const Vector3& vIn, Vector3& flOut)
{
    uint64_t GameRender = m.Read<uint64_t>(offset::GameRender);
    uint64_t RenderView = m.Read<uint64_t>(GameRender + 0x60);

    if (!GameRender || !RenderView)
        return false;

    Matrix view_projection = m.Read<Matrix>(RenderView + 0x460);

    float w = view_projection.m[0][3] * vIn.x + view_projection.m[1][3] * vIn.y + view_projection.m[2][3] * vIn.z + view_projection.m[3][3];

    if (w < 0.01)
        return false;

    flOut.x = view_projection.m[0][0] * vIn.x + view_projection.m[1][0] * vIn.y + view_projection.m[2][0] * vIn.z + view_projection.m[3][0];
    flOut.y = view_projection.m[0][1] * vIn.x + view_projection.m[1][1] * vIn.y + view_projection.m[2][1] * vIn.z + view_projection.m[3][1];

    float invw = 1.0f / w;

    flOut.x *= invw;
    flOut.y *= invw;

    int width = g.GameSize.right;
    int height = g.GameSize.bottom;

    float x = (float)width / 2;
    float y = (float)height / 2;

    x += 0.5 * flOut.x * (float)width + 0.5;
    y -= 0.5 * flOut.y * (float)height + 0.5;

    flOut.x = x;
    flOut.y = y;

    return true;
}

AxisAlignedBox GetAABB(uint64_t soldier)
{
    AxisAlignedBox aabb = {};
    int Pose = m.Read<int>(soldier + offset::poseType);

    switch (Pose)
    {
    case 0:
        aabb.Min = Vector4(-0.350000f, 0.000000f, -0.350000f, 0);
        aabb.Max = Vector4(0.350000f, 1.700000f, 0.350000f, 0);
        break;
    case 1:
        aabb.Min = Vector4(-0.350000f, 0.000000f, -0.350000f, 0);
        aabb.Max = Vector4(0.350000f, 1.150000f, 0.350000f, 0);
        break;
    case 2:
        aabb.Min = Vector4(-0.350000f, 0.000000f, -0.350000f, 0);
        aabb.Max = Vector4(0.350000f, 0.400000f, 0.350000f, 0);
        break;
    default:
        break;
    }

    return aabb;
}

float GetDistance(Vector3 value1, Vector3 value2)
{
    float num = value1.x - value2.x;
    float num2 = value1.y - value2.y;
    float num3 = value1.z - value2.z;

    return sqrt(num * num + num2 * num2 + num3 * num3);
}