/*!
 * \brief Sample2 used in this Scene
 * Implementation of a Pinhole Camera,
 * Insteaf of using a box and a ground , setup of a cornell box
 * is used
 */


#include "../include/program2.h"


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


void createContext(RTcontext *context, RTbuffer *buffer)
{
    //declare variables
	RT_CHECK_ERROR( rtContextCreate(&context));
	RT_CHECK_ERROR( rtContextSetRayTypeCount(context, 1));
	RT_CHECK_ERROR( rtContextSetEntryPointCount(context, 1));
	
	RT_CHECK_ERROR( rtBufferCreate(context, RT_OUTPUT_BUFFER, &buffer));
	RT_CHECK_ERROR( rtBufferSetFormat( buffer, RT_FORMAT_FLOAT4));
	

    //setup context

    //setup buffer

    //setup light

    // 'light' buffer

    //set ray generation program

    //set miss program
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
