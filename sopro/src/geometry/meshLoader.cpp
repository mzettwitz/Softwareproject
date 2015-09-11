#include "../../include/geometry/meshLoader.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <optixu/optixu_math_namespace.h>
#include "../../include/geometry/mesh.h"
using namespace std;
using namespace optix;

bool MeshLoader::loadOBJ(const char* path, std::vector <float3>& outVertices, std::vector<float3>& tempNormals, std::vector<float2>& tempUVs,std::vector<int3> &outVertexIndices,std::vector<int3> &outNormalIndices,std::vector<int3> &outUVIndices,unsigned int &outNumPrimitives)
{

    //clear mesh
    bool firstObject = true;
    outVertices.clear();
    tempNormals.clear();
    tempUVs.clear();
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
        //read first the first word of the line
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
            outNumPrimitives++;
            //face
            int3 vIndex,nIndex,uvIndex;

            if(tempNormals.size() > 0 && tempUVs.size() > 0)
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
            else if(tempUVs.size() == 0 && tempNormals.size() > 0)
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

bool MeshLoader::loadOBJScene(const char *path,std::shared_ptr<std::vector<std::shared_ptr<Mesh>>> meshes)
{
    //clear mesh
    std::string f = std::string(sutilSamplesDir()) + "/sopro/assets/" + std::string(path);
    bool firstObject = true;
    Mesh tempMesh = Mesh("",make_float3(0,0,0));
    std::vector<float3> tempVertices;
    std::vector<float2> tempUVs;
    std::vector<float3> tempNormals;
    std::vector<int3> tempVertexIndices;
    std::vector<int3> tempUVIndices;
    std::vector<int3> tempNormalIndices;
    unsigned int tempNumPrimitives = 0;
    unsigned int offsetV = 0;
    unsigned int offsetUV = 0;
    unsigned int offsetN = 0;
    tempMesh.setFilename(std::string(path));
    char objectname[256];
    char groupname[256];
    //open file
    FILE * file = fopen(f.c_str(),"r");

    if(file == NULL)
    {
        std::cout << "Could NOT open file!" << std::endl;
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
            tempNumPrimitives++;
            //face
            int3 vIndex,nIndex,uvIndex;

            if(tempNormals.size() > 0 && tempUVs.size() > 0)
            {
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",&vIndex.x,&uvIndex.x,&nIndex.x,&vIndex.y,&uvIndex.y,&nIndex.y,&vIndex.z,&uvIndex.z,&nIndex.z);
                if(matches != 9)
                {
                    std::cout << "Could NOT parse this kind of .obj file!" << std::endl;
                    return false;
                }

                uvIndex.x = uvIndex.x -1 - offsetUV;
                uvIndex.y = uvIndex.y -1 - offsetUV;
                uvIndex.z = uvIndex.z -1 - offsetUV;

                tempUVIndices.push_back(uvIndex);

                nIndex.x = nIndex.x - 1 - offsetN;
                nIndex.y = nIndex.y - 1 - offsetN;
                nIndex.z = nIndex.z - 1 - offsetN;

                tempNormalIndices.push_back(nIndex);

                vIndex.x= vIndex.x - 1 -offsetV;
                vIndex.y = vIndex.y -1 - offsetV;
                vIndex.z = vIndex.z - 1 -offsetV;

                tempVertexIndices.push_back(vIndex);

            }
            else if(tempUVs.size() == 0 && tempNormals.size() > 0)
            {
                int matches = fscanf(file, "%d//%d %d//%d %d//%d\n",&vIndex.x,&nIndex.x,&vIndex.y,&nIndex.y,&vIndex.z,&nIndex.z);
                if(matches != 6)
                {
                    std::cout << "Could NOT parse this kind of .obj file!" << std::endl;
                    return false;
                }

                nIndex.x = nIndex.x - 1 - offsetN;
                nIndex.y = nIndex.y - 1 - offsetN;
                nIndex.z = nIndex.z - 1 - offsetN;

                tempNormalIndices.push_back(nIndex);

                vIndex.x = vIndex.x -1 - offsetV;
                vIndex.y = vIndex.y -1 - offsetV;
                vIndex.z = vIndex.z -1 - offsetV;

                tempVertexIndices.push_back(vIndex);
            }
            else
            {
                int matches = fscanf(file, "%d %d %d\n", &vIndex.x,&vIndex.y,&vIndex.z);
                if(matches != 3)
                {
                    std::cout << "Could NOT parse this kind of .obj file!" << std::endl;
                    return false;
                }

                vIndex.x = vIndex.x - 1 -offsetV;
                vIndex.y = vIndex.y - 1 -offsetV;
                vIndex.z = vIndex.z - 1 -offsetV;

                tempVertexIndices.push_back(vIndex);
            }
        }
        //object
        else if(strcmp(lineHeader,"o") == 0)
        {
            if(!firstObject)
            {
                float3 center = make_float3(0,0,0);
                //get something like the center of object
                for(unsigned int i = 0;i < tempVertices.size();++i)
                {
                    center+= tempVertices.at(i);
                }
                center = center / tempVertices.size();
                for(unsigned int i = 0;i < tempVertices.size();++i)
                {
                    tempVertices.at(i) -= center;
                }
                tempMesh.setPosition(center);
                tempMesh.setData(tempVertices,tempVertexIndices,tempNormals,tempNormalIndices,tempUVs,tempUVIndices,tempNumPrimitives);
                std::shared_ptr<Mesh> outMesh = std::make_shared<Mesh>(tempMesh);
                meshes->push_back(outMesh);
                tempMesh.clear();
                offsetV += tempVertices.size();
                offsetUV += tempUVs.size();
                offsetN += tempNormals.size();
                tempVertices.clear();
                tempNormals.clear();
                tempUVs.clear();
                tempNormalIndices.clear();
                tempVertexIndices.clear();
                tempUVIndices.clear();
                tempNumPrimitives = 0;
            }
            firstObject = false;
            fscanf(file,"%s\n",objectname);
            tempMesh.setObjectname(objectname);

        }
        //group
        else if(strcmp(lineHeader,"g") == 0)
        {
            fscanf(file,"%s %s\n",groupname,objectname);
        }
        else
        {
            //comment
            char buffer[1000];
            fgets(buffer,1000,file);
        }
    }

    float3 center = make_float3(0,0,0);
    //get something like the center of object
    for(unsigned int i = 0;i < tempVertices.size();++i)
    {
        center+= tempVertices.at(i);
    }
    center = center / tempVertices.size();
    for(unsigned int i = 0;i < tempVertices.size();++i)
    {
        tempVertices.at(i) -= center;
    }
    tempMesh.setPosition(center);
    tempMesh.setData(tempVertices,tempVertexIndices,tempNormals,tempNormalIndices,tempUVs,tempUVIndices,tempNumPrimitives);
    std::shared_ptr<Mesh> outMesh = std::make_shared<Mesh>(tempMesh);
    meshes->push_back(outMesh);
    return true;
}
