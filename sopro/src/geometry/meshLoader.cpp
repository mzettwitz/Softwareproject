#include "../../include/geometry/meshLoader.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <optixu/optixu_math_namespace.h>
using namespace std;
using namespace optix;

bool MeshLoader::loadOBJ(const char* path, std::vector <float3>& outVertices, std::vector<float3>& outNormals, std::vector<float2>& outUVs,std::vector<int3> &outVertexIndices,std::vector<int3> &outNormalIndices,std::vector<int3> &outUVIndices,unsigned int &outNumPrimitives)
{

    //clear mesh
    outVertices.clear();
    outNormals.clear();
    outUVs.clear();
    outNormalIndices.clear();
    outNumPrimitives = 0;
    outUVIndices.clear();
    outVertexIndices.clear();
    //open file
    FILE * file = fopen(path,"r");

    if(file == NULL)
    {
        std::cout << "Could NOT open file!\n" << std::endl;
        return false;
    }

    //parse file
    while(true)
    {
        char lineHeader[128];
        //reead first the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if(res == EOF)
        {
            break;
        }

        if(strcmp(lineHeader,"v") == 0)
        {
            //vertex
            float3 vertex = make_float3(0,0,0);
            fscanf(file,"%f %f %f\n", &vertex.x,&vertex.y,&vertex.z);
            outVertices.push_back(vertex);
        }
        else if(strcmp(lineHeader,"vt") == 0)
        {
            //texture coordinate
            float2 uv = make_float2(0,0);
            fscanf(file,"%f %f\n",&uv.x,&uv.y);
            outUVs.push_back(uv);
        }
        else if(strcmp(lineHeader,"vn") == 0)
        {
            //normal
            float3 normal = make_float3(0,0,0);
            fscanf(file,"%f %f %f\n",&normal.x,&normal.y,&normal.z);
            outNormals.push_back(normal);
        }
        else if(strcmp(lineHeader,"f") == 0)
        {
            outNumPrimitives++;
            //face
            int3 vIndex,nIndex,uvIndex;

            if(outNormals.size() > 0 && outUVs.size() > 0)
            {
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",&vIndex.x,&uvIndex.x,&nIndex.x,&vIndex.y,&uvIndex.y,&nIndex.y,&vIndex.z,&uvIndex.z,&nIndex.z);
                if(matches != 9)
                {
                    std::cout << "Could NOT parse this kind of .obj file!" << std::endl;
                    return false;
                }

                uvIndex.x--;
                uvIndex.y--;
                uvIndex.z--;

                outUVIndices.push_back(uvIndex);

                nIndex.x--;
                nIndex.y--;
                nIndex.z--;

                outNormalIndices.push_back(nIndex);

                vIndex.x--;
                vIndex.y--;
                vIndex.z--;

                outVertexIndices.push_back(vIndex);

            }
            else if(outUVs.size() == 0 && outNormals.size() > 0)
            {
                int matches = fscanf(file, "%d//%d %d//%d %d//%d\n",&vIndex.x,&nIndex.x,&vIndex.y,&nIndex.y,&vIndex.z,&nIndex.z);
                if(matches != 6)
                {
                    std::cout << "Could NOT parse this kind of .obj file!" << std::endl;
                    return false;
                }

                nIndex.x--;
                nIndex.y--;
                nIndex.z--;

                outNormalIndices.push_back(nIndex);

                vIndex.x--;
                vIndex.y--;
                vIndex.z--;

                outVertexIndices.push_back(vIndex);
            }
            else
            {
                int matches = fscanf(file, "%d %d %d\n", &vIndex.x,&vIndex.y,&vIndex.z);
                if(matches != 3)
                {
                    std::cout << "Could NOT parse this kind of .obj file!" << std::endl;
                    return false;
                }

                vIndex.x--;
                vIndex.y--;
                vIndex.z--;

                outVertexIndices.push_back(vIndex);
            }
        }
        else
        {
            //comment
            char buffer[1000];
            fgets(buffer,1000,file);
        }
    }

    return true;
}
