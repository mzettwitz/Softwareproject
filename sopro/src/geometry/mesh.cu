#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_matrix_namespace.h>
#include <optixu/optixu_aabb_namespace.h>

using namespace optix;

rtBuffer<float3>    vertexBuffer;
rtBuffer<float3>    normalBuffer;
//rtBuffer<float2>    uvBuffer;
rtBuffer<int3>      vertexIndexBuffer;
rtBuffer<int3>      normalIndexBuffer;
//rtBuffer<int3>      uvIndexBuffer;

//rtDeclareVariable(float3,texCoord, attribute texCoord,);

rtDeclareVariable(float3,   geometricNormal,    attribute geometricNormal,);
rtDeclareVariable(float3,   shadingNormal,      attribute shadingNormal,);
rtDeclareVariable(Ray,      ray,                rtCurrentRay,);

RT_PROGRAM void meshIntersectionProgram(int primIdx)
{
    //get triangle
    int3 vertexIndex = vertexIndexBuffer[primIdx];

    float3 p0 = vertexBuffer[vertexIndex.x];
    float3 p1 = vertexBuffer[vertexIndex.y];
    float3 p2 = vertexBuffer[vertexIndex.z];

    float3 normal;
    float t, beta, gamma;
    //check for intersection
    if(intersect_triangle(ray,p0,p1,p2,normal,t,beta,gamma))
    {
        if(rtPotentialIntersection(t))
        {
            //get normal
            int3 normalIndex = normalIndexBuffer[primIdx];
            //interpolate if normals given

            if(normalBuffer.size() == 0 || normalIndex.x < 0 || normalIndex.y < 0 || normalIndex.z < 0)
            {
                //no normals given, use calculated from intersection
                shadingNormal = normalize(normal);
            }
            else
            {
                float3 n0 = normalBuffer[normalIndex.x];
                float3 n1 = normalBuffer[normalIndex.y];
                float3 n2 = normalBuffer[normalIndex.z];
                shadingNormal = normalize(n1*beta + n2*gamma + n0*(1.0f-beta-gamma));
            }
            geometricNormal = normalize(normal);

           /* //check for texture
            int3 uvIndex = uvIndexBuffer[primIdx];
            if(uvBuffer.size() == 0 || uvIndex.x < 0 || uvIndex.y < 0 || uvIndex.z < 0)
            {
                //no textureCoordinates given
                texCoord = make_float3(0.0f,0.0f,0.0f);
            }
            else
            {
                float t0 = uvBuffer[uvIndex.x];
                float t1 = uvBuffer[uvIndex.y];
                float t2 = uvBuffer[uvIndex.z];
                texCoord = make_float3(t1*beta+t2*gamma * t0(1.0f-beta-gamma));
            }*/

            rtReportIntersection(0);

        }
    }
}

RT_PROGRAM void meshBoundingBoxProgram(int primIdx, float result[6])
{
    const int3 vertexIndex = vertexIndexBuffer[primIdx];

    const float3 v0 = vertexBuffer[vertexIndex.x];
    const float3 v1 = vertexBuffer[vertexIndex.y];
    const float3 v2 = vertexBuffer[vertexIndex.z];

    const float area = length(cross(v1-v0,v2-v0));

    Aabb* aabb = (optix::Aabb*)result;

    if(area > 0.0f && !isinf(area))
    {
        aabb->m_min = fminf(fminf(v0,v1),v2);
        aabb->m_max = fmaxf(fmaxf(v0,v1),v2);
    }
    else
    {
        aabb->invalidate();
    }
}
