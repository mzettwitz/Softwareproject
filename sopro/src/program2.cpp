/*!
 * \brief Sample2 used in this Scene
 * Implementation of a Pinhole Camera,
 * Insteaf of using a box and a ground , setup of a cornell box
 * is used
 */


#include "sopro/include/program2.h"


int program2(int argc,char* argv[])
{

    RTcontext context;
    RTbuffer outputBuffer;
    RTGeometry sphere;
    RTMaterial material;

    char outfile[512];

    //init glut
    sutilInitGlut(&argc,argv);

    //setup state
    createContext(&context, &outputBuffer);
    createGeometry(context, &box);
    createMaterial(context, &material);
    createInstances(context, sphere, material);

}


void createContext(RTcontext *context, RTbuffer *buffer)
{
    //declare variables

    //setup context

    //setup buffer

    //setup light

    // 'light' buffer

    //set ray generation program

    //set miss program
}


void createGeometry(RTContext context, RTGeometry *geom)
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

createInstances(RTcontext context, RTgeometry geom, RTmaterial material)
{
    //setup identitymatrix, push that to specific .h


    //create geometry instance from geom and material
    //set material properties

    //create group to hold instances

    //create acceleration node for group

    //add transformation node

    //place geomInstances under top level object


}
