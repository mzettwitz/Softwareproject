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
#include <limits>

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

    try
    {
    //setup state
    Context context = createContext();

        std::vector<Material> mat;
        std::vector<Geometry> geom;
    //create sphere
    sphere s(make_float3(0.0f,1.0f,0.0f),1.0f,"sphereIntersectionProgram","sphereBoundingBoxProgram","sphere.cu");
    geom.push_back(s.createGeometry(context));
    plainColorMaterial sphereMaterial(make_float3(0.8f,0.4f,0.1f),"plainColorMaterial.cu");
    mat.push_back(sphereMaterial.createMaterial(context));

    //create sphere
    sphere s2(make_float3(2.0f,1.2f,0.0f),1.2f,"sphereIntersectionProgram","sphereBoundingBoxProgram","sphere.cu");
    geom.push_back(s2.createGeometry(context));
    plainColorMaterial sphereMaterial2(make_float3(1.0f,0.2f,0.6f),"plainColorMaterial.cu");
    mat.push_back(sphereMaterial2.createMaterial(context));

    //create groundplane
    infinitePlane plane(0.0f,"infinitePlaneIntersectionProgram","infinitePlaneBoundingBoxProgram","infinitePlane.cu");
    geom.push_back(plane.createGeometry(context));
    plainColorMaterial planeMaterial(make_float3(0.2f,0.3f,0.4f),"plainColorMaterial.cu");
    mat.push_back(planeMaterial.createMaterial(context));



    createInstances(context,geom,mat);
    context->validate();
    context->compile();
    context->launch(0,width,height);
    //displayImage
    context->checkError(sutilDisplayBufferInGlutWindow(argv[0],context["outputBuffer"]->getBuffer()->get()));

    //clean
    context->destroy();
    } catch( Exception &e)
    {
        sutilReportError(e.getErrorString().c_str());
        exit(1);
    }

    return 0;

}
std::string ptxPath(const std::string &path)
{
    return std::string(sutilSamplesPtxDir()) + "/sopro_generated_" + path + ".ptx";
}

Context createContext()
{
    Context context = Context::create();
    context->setRayTypeCount(2);
    context->setEntryPointCount(1);

    context["radianceRayType"]->setUint(0u);
    context["shadowRayType"]->setUint(1u);
    context["maxDepth"]->setUint(10u);
    context["sceneEpsilon"]->setFloat(1.e-3f);

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
    float3  eye     = {7.0f,3.0f,7.0f};
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




void createInstances(Context context, std::vector<Geometry> geometry, std::vector<Material> material)
{
    GeometryGroup gg = context->createGeometryGroup();
    gg->setChildCount(geometry.size());

    for(unsigned int i = 0;i < geometry.size();++i)
    {
        GeometryInstance gi = context->createGeometryInstance();
        gi->setMaterialCount(1);
        gi->setGeometry(geometry.at(i));
        gi->setMaterial(0,material.at(i));
        gg->setChild(i,gi);
    }
    gg->setAcceleration(context->createAcceleration("NoAccel","NoAccel"));
    context["topObject"]->set(gg);
    context["topShadower"]->set(gg);
}
