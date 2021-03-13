#include "extensions/engine_extension.h"

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

ERef<Engine::EMesh> LoadMeshFunction(EString name, ESharedBuffer buffer)
{
    EVector<Engine::EMesh::EVertex>    vertices;
    EVector<u32>        indices;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFileFromMemory(buffer.Data<const void>(), buffer.GetSizeInByte(), aiProcess_Triangulate | aiProcess_PreTransformVertices | aiProcess_GenNormals);
    
    if (scene && scene->HasMeshes())
    {
        for (size_t meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
        {
        
            const aiMesh* currentMesh = scene->mMeshes[meshIndex];
            for (size_t vertexIndex = 0; vertexIndex < currentMesh->mNumVertices; vertexIndex++)
            {
                // TODO VERIFY MESH DATA BEFORE CREATING
                aiVector3D& position = currentMesh->mVertices[vertexIndex];
                aiVector3D& normal = currentMesh->mNormals[vertexIndex];
                aiVector3D uv = aiVector3D(0, 0, 0);
                if (currentMesh->HasTextureCoords(0))
                {
                    uv = currentMesh->mTextureCoords[0][vertexIndex];
                }

                Engine::EMesh::EVertex vert;
                vert.Position = EVec3(position.x, position.y, position.z);
                vert.Normal = EVec3(normal.x, normal.y, normal.z);
                vert.TexCoord = EVec2(uv.x, uv.y);
                vertices.push_back(vert);
            }

            for (size_t i = 0; i < currentMesh->mNumFaces; i++)
            {
                aiFace& currentFace = currentMesh->mFaces[i];
                for (size_t curr = 0; curr < currentFace.mNumIndices; curr++)
                {
                    indices.push_back(currentFace.mIndices[curr]);
                }
            }
        }
        ERef<Engine::EMesh> result = EMakeRef(Engine::EMesh, name, vertices, indices);
        return result;
    }
    return nullptr;
}


EE_ENTRY
{
    Engine::EResourceRegister::data().RegisterResource("Meshes", {"fbx", "3ds"}, &LoadMeshFunction);
}