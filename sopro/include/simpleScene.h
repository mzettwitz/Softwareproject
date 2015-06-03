#ifndef SIMPLESCENE_H
#define SIMPLESCENE_H

#include <optix.h>
#include <optixu/optixpp_namespace.h>

using namespace optix;
class SimpleScene
{
public:
    SimpleScene();

    struct Camera
    {
        Camera(const float3 &pos,const float3 &dir, const float3 &rig) : position(pos),direction(dir),right(rig)
        {}
        optix::float3 position;
        optix::float3 direction;
        optix::float3 right;

    };

private:
    optix::GeometryGroup mGeometryGroup;
    int mWidth;
    int mHeight;
    optix::Context mContext;

private:
    void updateGeometry();
    Buffer createOutputBuffer(RTformat format, unsigned int width, unsigned int height);

public:
    void initScene(SimpleScene::Camera &camera);
    void trace(SimpleScene::Camera &camera);
    Buffer getOutputBuffer();

};

#endif //SIMPLESCENE_H
