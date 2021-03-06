/*!
 * \file program1.cpp
 * \brief
 * build after sample 1 of Optix QuickstartGuide
 * Setup of a Context and Output of an NVidia Green image
 */

/*!
 * \fn program1(int argc, char* argv[])
 * \brief creates Optix context, returns green Image and 0 if succesful
 * \param argc from main
 * \param argv[] from main
 */
#include "../include/program1.h"



int program1(int argc, char* argv[])
{
    //context for communication with gpu, rayGenerationProgram as it says, buffer as "image"
     RTcontext context;
     RTprogram rayGenerationProgram;
     RTbuffer  buffer;

     //parameters for .cu file, see "entrypoint.cu"
     RTvariable result_buffer;
     RTvariable color;

     //
     char path_to_ptx[512];

     //image size
     unsigned int width  = 800u;
     unsigned int height = 600u;

     //init glut
      RT_CHECK_ERROR_NO_CONTEXT( sutilInitGlut( &argc, argv ) );


     //create object and states
     RT_CHECK_ERROR( rtContextCreate( &context ) );
     RT_CHECK_ERROR( rtContextSetRayTypeCount( context, 1 ) );
     RT_CHECK_ERROR( rtContextSetEntryPointCount( context, 1 ) );

     RT_CHECK_ERROR( rtBufferCreate( context, RT_BUFFER_OUTPUT, &buffer ) );
     RT_CHECK_ERROR( rtBufferSetFormat( buffer, RT_FORMAT_FLOAT4 ) );
     RT_CHECK_ERROR( rtBufferSetSize2D( buffer, width, height ) );
     RT_CHECK_ERROR( rtContextDeclareVariable( context, "result_buffer", &result_buffer ) );
     RT_CHECK_ERROR( rtVariableSetObject( result_buffer, buffer ) );

     //get string to ptx file
     sprintf( path_to_ptx, "%s/%s", sutilSamplesPtxDir(), "sopro_generated_entrypoint.cu.ptx" );
     //create program, like shaders, from ptxfile
     RT_CHECK_ERROR( rtProgramCreateFromPTXFile( context, path_to_ptx, "drawColor", &rayGenerationProgram ) );
     // "pass" color to cuda file
     RT_CHECK_ERROR( rtProgramDeclareVariable( rayGenerationProgram, "color", &color ) );
     // set color, NVIDIA green
     RT_CHECK_ERROR( rtVariableSet4f( color, 0.462f, 0.725f, 0.0f ,0.f) );
     // set rayGenerationProgram
     RT_CHECK_ERROR( rtContextSetRayGenerationProgram( context, 0, rayGenerationProgram ) );

     //run
     RT_CHECK_ERROR( rtContextValidate( context ) );
     RT_CHECK_ERROR( rtContextCompile( context ) );
     RT_CHECK_ERROR( rtContextLaunch2D( context, 0 /* entry point */, width, height ) );

     //pass buffer to window
       RT_CHECK_ERROR( sutilDisplayBufferInGlutWindow( argv[0], buffer ) );

     //clean
     RT_CHECK_ERROR( rtBufferDestroy( buffer ) );
     RT_CHECK_ERROR( rtProgramDestroy( rayGenerationProgram ) );
     RT_CHECK_ERROR( rtContextDestroy( context ) );

     return 0;
}
