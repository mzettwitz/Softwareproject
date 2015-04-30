/*!
 * \brief Sample2 used in this Scene
 * Implementation of a Pinhole Camera,
 * Insteaf of using a box and a ground , setup of a cornell box
 * is used
 */


#include "../include/program2.h"

char path_to_ptx[512];

int program2(int argc,char* argv[])
{

    RTcontext context;
    RTbuffer outputBuffer;
    RTgeometry sphere;
    RTmaterial material;

    char outfile[512];

    //init glut
    sutilInitGlut(&argc,argv);

    //setup state
    createContext(&context, &outputBuffer);
    createGeometry(context, &sphere);
    createMaterial(context, &material);
    createInstances(context, sphere, material);

}


void createContext(RTcontext *context, RTbuffer *buffer,uint width, uint height)
{
    //declare variables
	RTprogram rayGenProgram;
	RTprogram missProgram;
	RTbuffer lightBufferObject;
	RTvariable outputBuffer;
	RTvariable sceneEpsilon;
	RTvariable radiance_ray_type;
	RTvariable shadow_ray_type;
	RTvariable maxDepth;
	

	//camera variables
	RTvariable eye;
	RTvariable U;
	RTvariable V;
	RTvariable W;

	//miss programm
	RTvariable bgColor; //background color

	//setup
	RT_CHECK_ERROR( rtContextCreate(context));
	RT_CHECK_ERROR( rtContextSetRayTypeCount(*context, 1));
	RT_CHECK_ERROR( rtContextSetEntryPointCount(*context, 1));
	
	//declare variables for context
	RT_CHECK_ERROR( rtContextDeclareVariable(*context, "outputBuffer", &outputBuffer));
	RT_CHECK_ERROR( rtContextDeclareVariable(*context, "maxDepth", &maxDepth));
	RT_CHECK_ERROR( rtContextDeclareVariable(*context, "radiance_ray_type",&radiance_ray_type));
	RT_CHECK_ERROR( rtContextDeclareVariable(*context, "shadow_ray_type", &shadow_ray_type));
	RT_CHECK_ERROR( rtContextDeclareVariable(*context, "sceneEpsilon", &sceneEpsilon));
	
	RT_CHECK_ERROR( rtBufferCreate(*context, RT_OUTPUT_BUFFER, &buffer));
	RT_CHECK_ERROR( rtBufferSetFormat( *buffer, RT_FORMAT_UNSIGNED_BYTE4));
	RT_CHECK_ERROR( rtBufferSize2D ( *buffer,width,height));
	RT_CHECK_ERROR( rtBufferSetObject ( outputBuffe, buffer);
	

    //setup context

    //setup buffer

    //setup light

    // 'light' buffer

    //set ray generation program
	sprintf(path_to_ptx, "%s/%s",sutilSamplesPtxDir(),"sopro_generated_pinholeCamera.cu.ptx");
	RT_CHECK_ERROR(rtProgramCreateFromPTXFile(*context,path_to_ptx,"pinholeCamera",&rayGenProgram));
	RT_CHECK_ERROR(rtProgramDeclareVariable(rayGenProgram,"eye",&eye));
	RT_CHECK_ERROR(rtProgramDeclareVariable(rayGenProgram,"U",&U));
	RT_CHECK_ERROR(rtProgramDeclareVariable(rayGenProgram,"V",&V));
	RT_CHECK_ERROR(rtProgramDeclareVariable(rayGenProgram,"W",&W));
	RT_CHECK_ERROR(rtProgramSetVariable(eye,0.0f,5.0f,5.0f));
	RT_CHECK_ERROR(rtProgramSetVariable(U,1.0f,0.0f,0.0f));
	RT_CHECK_ERROR(rtProgramSetVariable(V,0.0f,1.0f,0.0f));
	RT_CHECK_ERROR(rtProgramSetVariable(W,0.0f,0.0f,-1.0f));
	RT_CHEKK_ERROR(rtProgramSetRayGenerationProgram(*context, 0, rayGenProgram));
    //set miss program
	sprintf(path_to_ptx, "%s/%s",sutilSamplesPtxDir(),"sopro_generated_miss.cu.ptx");
	RT_CHECK_ERROR(rtProgramCreateFromPTXFile(*context,path_to_ptx,"miss",&missProgram));
	RT_CHECK_ERROR(rtProgramDeclareVariable(missProgram,"missColor",&bgColor));
	RT_CHECK_ERROR(rtVariableSet3f(bgColor,0.3f,0.3f,0.9f));
	RT_CHECK_ERROR(rtProgramMissProgram(*context,0,missProgram));

}


void createGeometry(RTcontext context, RTgeometry *geom)
{
    //needed : inersection,boundingbox, min , max

    //create Geometry

    //setup geometry


}


void createMaterial(RTcontext context, RTmaterial *material)
{
    //needed: closesthit, anyhit
    //set programs for any *material,
    //in this case , just 1, but for further implementations

}

void createInstances(RTcontext context, RTgeometry geom, RTmaterial material)
{
    //setup identitymatrix, push that to specific .h


    //create geometry instance from geom and material
    //set material properties

    //create group to hold instances

    //create acceleration node for group

    //add transformation node

    //place geomInstances under top level object


}
