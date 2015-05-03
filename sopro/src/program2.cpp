/*!
 * \brief program2 setup
 *
 * Implementation of a Pinhole Camera,
 * Instead of using a box and a ground , setup of a cornell box
 * is used
 *
 * \TODO use cppwrapper, refactor
 */


#include "../include/program2.h"

unsigned int width = 800;
unsigned int height = 600;

using namespace optix;

/*! \fn program2(int argc,char* argv[])
 * \brief program2
 *          setup state for Optix
 *          includes Context, Geometry, Material, Instances
 *
 * \param argc
 * \param argv
 * \return
 */
int program2(int argc,char* argv[])
{
    RT_CHECK_ERROR_NO_CONTEXT(sutilInitGlut(&argc,argv));

//    try
//    {
    //setup state
    Context context = createContext();
    Geometry sphere = createGeometry(context);
    Material material = createMaterial(context);
    createInstances(context,sphere,material);
    //run
    context->validate();
    context->compile();
    context->launch(0,width,height);
    //displayImage
    context->checkError(sutilDisplayBufferInGlutWindow(argv[0],context["outputBuffer"]->getBuffer()->get()));

    //clean
    context->destroy();
/*    } catch( Exception &e)
    {
        sutilReportError(e.getErrorString().c_str());
        exit(1);
    }*/

    return 0;

}
/*!
 * \brief ptxPath
 * \param file name of .cu file
 * \return path to generated .ptx from .cu file
 */
std::string ptxPath(const std::string &file)
{
    return std::string(sutilSamplesPtxDir()) + "/sopro_generated_" + file + ".ptx";
}

Context createContext()
{
    Context context = Context::create();
    context->setRayTypeCount(2);
    context->setEntryPointCount(1);

    context["radianceRayType"]->setUint(0u);
    context["shadowRayType"]->setUint(1u);
    context["maxDepth"]->setUint(10u);
    context["sceneEpsilon"]->setFloat(1.e-5f);

    //set Light(s)
    BasicLight light;
    light.color = make_float3(1.0f,1.0f,1.0f);
    light.pos = make_float3(100.f,100.f,-40.f);
    light.casts_shadow = 1;
    light.padding = 0;


    Buffer lightBuffer = context->createBuffer(RT_BUFFER_INPUT,RT_FORMAT_USER,width,height);
    lightBuffer->setElementSize(sizeof(BasicLight));
    lightBuffer->setSize(1);
    memcpy(lightBuffer->map(),&light,sizeof(light));
    lightBuffer->unmap();

    context["lights"]->set(lightBuffer);

    //Outputbuffer
    Variable outputBuffer = context["outputBuffer"];
    Buffer buffer = context->createBuffer(RT_BUFFER_OUTPUT,RT_FORMAT_FLOAT4,width,height);
    outputBuffer->setBuffer(buffer);
    //RayGenerationProgram
    std::string usedPTXPath(ptxPath("pinholeCamera.cu"));
    Program rayGenerationProgram = context->createProgramFromPTXFile(usedPTXPath,"pinholeCamera");
    context->setRayGenerationProgram(0,rayGenerationProgram);

    //set Camera
    float3  eye     = {5.0f,0.0f,5.0f};
    float3  lookat  = {0.0f,0.0f,0.0f};
    float3  up      = {0.0f,1.0f,0.0f};
    float   fov     = 45.0f;
    float   aspectratio = float(width) /float(height);
    float3  u,v,w;
    sutilCalculateCameraVariables(&eye.x,&lookat.x,&up.x,fov,aspectratio,&u.x,&v.x,&w.x);

    context["eye"]->setFloat(eye);
    context["U"]->setFloat(u);
    context["V"]->setFloat(v);
    context["W"]->setFloat(w);

    //ExceptionProgram
    Program exceptionProgram = context->createProgramFromPTXFile(usedPTXPath,"exception");
    context->setExceptionProgram(0,exceptionProgram);
    context["excpetionColor"]->setFloat(1.0f,0.0f,0.0f,1.0f);
    //MissProgram
    usedPTXPath = ptxPath("miss.cu");
    Program missProgram = context->createProgramFromPTXFile(usedPTXPath,"miss");
    context->setMissProgram(0,missProgram);
    context["missColor"]->setFloat(0.3f,0.5f,0.8f,1.0f);

    return context;

}

Geometry createGeometry(Context context)
{
    std::string usedPTXpath(ptxPath("sphere.cu"));
    Geometry sphere = context->createGeometry();
    sphere->setPrimitiveCount(1);
    sphere->setBoundingBoxProgram(context->createProgramFromPTXFile(usedPTXpath,"sphereBounds"));
    sphere->setIntersectionProgram(context->createProgramFromPTXFile(usedPTXpath,"sphereIntersect"));
    //coordinates(x,y,z,r)
    sphere["coordinates"]->setFloat(0.0f,0.0f,0.0f,1.0f);
    return sphere;
}

Material createMaterial(Context context)
{
    std::string usedPTXpath(ptxPath("material.cu"));
    Material material = context->createMaterial();
    material->setAnyHitProgram(1,context->createProgramFromPTXFile(usedPTXpath,"anyhit_shadow"));
    material->setClosestHitProgram(0,context->createProgramFromPTXFile(usedPTXpath,"closesthit_radiance"));
    material["color"]->setFloat(0.8f,0.4f,0.1f);
    return material;
}

void createInstances(Context context, Geometry geometry, Material material)
{
    GeometryInstance gi = context->createGeometryInstance();
    gi->setMaterialCount(1);
    gi->setGeometry(geometry);
    gi->setMaterial(0,material);

    GeometryGroup gg = context->createGeometryGroup();
    gg->setChildCount(1);
    gg->setChild(0,gi);
    gg->setAcceleration(context->createAcceleration("NoAccel","NoAccel"));

    context["topObject"]->set(gg);
    context["topShadower"]->set(gg);
}
