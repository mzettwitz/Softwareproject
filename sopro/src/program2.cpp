/*!
 * \brief program2
 *
 * Implementation of a Pinhole Camera,
 * Insteaf of using a box and a ground , setup of a cornell box
 * is used
 *
 * \fn program2(int argc,char* argv[])
 *
 *
 * \TODO use cppwrapper, refactor
 */


#include "../include/program2.h"

unsigned int width = 800;
unsigned int height = 600;

using namespace optix;
/*!
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
    sutilInitGlut(&argc,argv);

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
    context->checkError(sutilDisplayBufferInGlutWindow(argv[0],context["output_buffer"]->getBuffer()->get()));

    //clean
    context->destroy();

    return 0;

}
/*!
 * \brief ptxPath
 * \param file name of .cu file
 * \return path to generated .ptx from .cu file
 */
std::string ptxPath(const std::string &file)
{
    return std::string(sutilSamplesPtxDir() + "/sopro_generated_" + file + ".ptx");
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

    //Outputbuffer
    Variable outputBuffer = context["outputBuffer"];
    Buffer buffer = context->createBuffer(RT_BUFFER_OUTPUT,RT_FORMAT_FLOAT4,width,height);
    outputBuffer->setBuffer(buffer);
    //RayGenerationProgram
    std::string usedPTXPath(ptxPath("pinholeCamera.cu"));
    Program rayGenerationProgram = context->createProgramFromPTXFile(usedPTXPath,"pinholeCamera");
    context->setRayGenerationProgram(0,rayGenerationProgram);

    //set Camera
    float3  eye     = {0.0f,0.0f,5.0f};
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
    usedPTXPath(ptxPath("miss.cu"));
    Program missProgram = context->createProgramFromPTXFile(usedPTXPath,"miss");
    context->setMissProgram(0,miss);
    context["missColor"]->setFloat(0.3f,0.5f,0.8f,1.0f);

}

Geometry createGeometry(Context context)
{

}

Material createMaterial(Context context)
{

}

void createInstances(Context context, Geometry geometry, Material material)
{

}
