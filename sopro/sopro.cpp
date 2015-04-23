
/*
 * Copyright (c) 2008 - 2009 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and proprietary
 * rights in and to this software, related documentation and any modifications thereto.
 * Any use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from NVIDIA Corporation is strictly
 * prohibited.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THIS SOFTWARE IS PROVIDED *AS IS*
 * AND NVIDIA AND ITS SUPPLIERS DISCLAIM ALL WARRANTIES, EITHER EXPRESS OR IMPLIED,
 * INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE.  IN NO EVENT SHALL NVIDIA OR ITS SUPPLIERS BE LIABLE FOR ANY
 * SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF
 * BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS) ARISING OUT OF THE USE OF OR
 * INABILITY TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES
 */

/*
 * sample1.cpp -- Renders a solid green image.
 *
 * A filename can be given on the command line to write the results to file.
 */

#include <optix.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sutil.h>

int main(int argc, char* argv[])
{
    /* Primary RTAPI objects */
    RTcontext context;
    RTprogram rayGenerationProgram;
    RTbuffer  buffer;

    /* Parameters */
    RTvariable result_buffer;
    RTvariable color;

    char path_to_ptx[512];

    unsigned int width  = 800u;
    unsigned int height = 600u;

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

    return( 0 );
}


