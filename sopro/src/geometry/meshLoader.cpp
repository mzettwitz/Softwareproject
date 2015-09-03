#include "../../include/geometry/meshLoader.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <optixu/optixu_math_namespace.h>
using namespace std;
using namespace optix;

bool MeshLoader::loadOBJ(const char* path, std::vector <float3>& outVertices, std::vector<float3>& outNormals, std::vector<float2>& outUVs)
{
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<float3> tempVertices, tempNormals;
    std::vector<float2> tempUVs;

    tempVertices.clear();
    tempNormals.clear();
    tempUVs.clear();
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
            tempVertices.push_back(vertex);
        }
        else if(strcmp(lineHeader,"vt") == 0)
        {
            //texture coordinate
            float2 uv = make_float2(0,0);
            fscanf(file,"%f %f\n",&uv.x,&uv.y);
            tempUVs.push_back(uv);
        }
        else if(strcmp(lineHeader,"vn") == 0)
        {
            //normal
            float3 normal = make_float3(0,0,0);
            fscanf(file,"%f %f %f\n",&normal.x,&normal.y,&normal.z);
            tempNormals.push_back(normal);
        }
        else if(strcmp(lineHeader,"f") == 0)
        {
            //face
            unsigned int vertexIndex[3],normalIndex[3],uvIndex[3];

            if(tempUVs.size() > 0 && tempNormals.size() > 0)
            {
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",&vertexIndex[0],&uvIndex[0],&normalIndex[0],&vertexIndex[1],&uvIndex[1],&normalIndex[1],&vertexIndex[2],&uvIndex[2],&normalIndex[2]);
                if(matches != 9)
                {
                    std::cout << "Could NOT parse this kind of .obj file!" << std::endl;
                    return false;
                }


                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[1]);
                uvIndices.push_back(uvIndex[2]);

                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);

                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);

            }
            else if(tempUVs.size() == 0 && tempNormals.size() > 0)
            {
                int matches = fscanf(file, "%d//%d %d//%d %d//%d\n",&vertexIndex[0],&normalIndex[0],&vertexIndex[1],&normalIndex[1],&vertexIndex[2],&normalIndex[2]);
                if(matches != 6)
                {
                    std::cout << "Could NOT parse this kind of .obj file!" << std::endl;
                    return false;
                }

                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);

                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
            }
            else
            {
                int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0],&vertexIndex[1],&vertexIndex[2]);
                if(matches != 3)
                {
                    std::cout << "Could NOT parse this kind of .obj file!" << std::endl;
                    return false;
                }

                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
            }
        }
        else
        {
            //comment
            char buffer[1000];
            fgets(buffer,1000,file);
        }
    }

    //process file
    for(unsigned int i = 0; i< vertexIndices.size();++i)
    {
        unsigned int vertexIndex = vertexIndices[i];
        float3 vertex = tempVertices[vertexIndex-1];
        outVertices.push_back(vertex);

        if(uvIndices.size() > 0)
        {
            unsigned int uvIndex = uvIndices[i];
            float2 uv = tempUVs[uvIndex-1];
            outUVs.push_back(uv);
        }

        if(normalIndices.size() > 0)
        {
            unsigned int normalIndex = normalIndices[i];
            float3 normal = tempNormals[normalIndex-1];
            outNormals.push_back(normal);
        }




    }
    return true;
}
